#include "App.hpp"

#include "RenderSystem.hpp"
#include "Camera.hpp"


// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

namespace Tutorial {

FirstApp::FirstApp() { loadGameObjects(); }

FirstApp::~FirstApp() {}

void FirstApp::run() {
  RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
  Camera camera{};
  float time = 0.0f;

  while (!window.shouldClose()) {
    glfwPollEvents();
    
    float aspect = renderer.getAspectRatio();
    //camera.setOrthographicProjection(-aspect,aspect,-1,1,-1,1);
    camera.setPerspectiveProjection(glm::radians(90.0f),aspect,0.1f,100.0f);

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
  std::shared_ptr<Model> lveModel = createCubeModel(device, {.0f, .0f, .0f});
  auto cube = GameObject::createGameObject();
  cube.model = lveModel;
  cube.transform.translation = {.0f, .0f, 1.5f};
  cube.transform.scale = {.5f, .5f, .5f};
  gameObjects.push_back(std::move(cube));
}

}
