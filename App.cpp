#include "App.hpp"

#include "RenderSystem.hpp"
#include "Camera.hpp"
#include "Keyboard.hpp"


// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <iostream>
#include <chrono>
#include <array>
#include <cassert>
#include <stdexcept>

namespace Tutorial {

FirstApp::FirstApp() { loadGameObjects(); }

FirstApp::~FirstApp() {}

void FirstApp::run() {
  RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
  Camera camera{};
  GameObject viewerObject = GameObject::createGameObject();
  //camera.setViewDirection(glm::vec3{0.0f},glm::vec3{0.5f,0.0f,1.0f}); 
  //camera.setViewTarget(glm::vec3(-1.0f,-2.0f,2.0f),glm::vec3(0.0f,0.0f,2.5f)); 
  float time = 0.0f;

  auto currentTime = std::chrono::high_resolution_clock::now();
  Keyboard cameraController{};

  while (!window.shouldClose()) {
    glfwPollEvents();
    
    auto newTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float,std::chrono::seconds::period>(newTime - currentTime).count();
    currentTime = newTime;

    cameraController.moveInPlaneXZ(window.getGLFWwindow(),deltaTime,viewerObject);
    camera.setViewYXZ(viewerObject.transform.translation,viewerObject.transform.rotation);

    float aspect = renderer.getAspectRatio();
    //camera.setOrthographicProjection(-aspect,aspect,-1,1,-1,1);
    camera.setPerspectiveProjection(glm::radians(50.0f),aspect,0.1f,100.0f);

    if (auto commandBuffer = renderer.beginFrame()) {
      renderer.beginSwapChainRenderPass(commandBuffer);
      renderSystem.renderGameObjects(commandBuffer, gameObjects,camera);
      renderer.endSwapChainRenderPass(commandBuffer);
      renderer.endFrame();
    }
    gameObjects[0].transform.translation.x = sin(time);
    gameObjects[0].transform.translation.y = cos(time);
    
    time += 0.01f;
  }

  vkDeviceWaitIdle(device.device());
} 

// temporary helper function, creates a 1x1x1 cube centered at offset
std::unique_ptr<Model> createCubeModel(Device& device, glm::vec3 offset) {
  std::vector<Model::Vertex> vertices{

      // left face (white)
      {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
      {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
      {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
      {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
      {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},
      {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},

      // right face (yellow)
      {{.5f, -.5f, -.5f}, {.9f, .9f, .0f}},
      {{.5f, .5f, .5f}, {.9f, .9f, .0f}},
      {{.5f, -.5f, .5f}, {.9f, .9f, .0f}},
      {{.5f, -.5f, -.5f}, {.9f, .9f, .0f}},
      {{.5f, .5f, -.5f}, {.9f, .9f, .0f}},
      {{.5f, .5f, .5f}, {.9f, .9f, .0f}},

      // top face (orange, remember y axis points down)
      {{-.5f, -.5f, -.5f}, {.9f, .0f, .9f}},
      {{.5f, -.5f, .5f}, {.9f, .0f, .9f}},
      {{-.5f, -.5f, .5f}, {.9f, .0f, .9f}},
      {{-.5f, -.5f, -.5f}, {.9f, .0f, .9f}},
      {{.5f, -.5f, -.5f}, {.9f, .0f, .9f}},
      {{.5f, -.5f, .5f}, {.9f, .0f, .9f}},

      // bottom face (red)
      {{-.5f, .5f, -.5f}, {.9f, .0f, .0f}},
      {{.5f, .5f, .5f}, {.9f, .0f, .0f}},
      {{-.5f, .5f, .5f}, {.9f, .0f, .0f}},
      {{-.5f, .5f, -.5f}, {.9f, .0f, .0f}},
      {{.5f, .5f, -.5f}, {.9f, .0f, .0f}},
      {{.5f, .5f, .5f}, {.9f, .0f, .0f}},

      // nose face (blue)
      {{-.5f, -.5f, 0.5f}, {.0f, .0f, .9f}},
      {{.5f, .5f, 0.5f}, {.0f, .0f, .9f}},
      {{-.5f, .5f, 0.5f}, {.0f, .0f, .9f}},
      {{-.5f, -.5f, 0.5f}, {.0f, .0f, .9f}},
      {{.5f, -.5f, 0.5f}, {.0f, .0f, .9f}},
      {{.5f, .5f, 0.5f}, {.0f, .0f, .9f}},

      // tail face (green)
      {{-.5f, -.5f, -0.5f}, {.0f, .9f, .0f}},
      {{.5f, .5f, -0.5f}, {.0f, .9f, .0f}},
      {{-.5f, .5f, -0.5f}, {.0f, .9f, .0f}},
      {{-.5f, -.5f, -0.5f}, {.0f, .9f, .0f}},
      {{.5f, -.5f, -0.5f}, {.0f, .9f, .0f}},
      {{.5f, .5f, -0.5f}, {.0f, .9f, .0f}},

  };
  for (auto& v : vertices) {
    v.position += offset;
  }
  return std::make_unique<Model>(device, vertices);
}

void FirstApp::loadGameObjects() {
  std::shared_ptr<Model> model = createCubeModel(device, {.0f, .0f, .0f});
  auto cube = GameObject::createGameObject();
  cube.model = model;
  cube.transform.translation = {.0f, .0f, 2.5f};
  cube.transform.scale = {.5f, .5f, .5f};
  gameObjects.push_back(std::move(cube));
}

}
