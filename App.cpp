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

namespace Tutorial
{

  FirstApp::FirstApp() { loadGameObjects(); }

  FirstApp::~FirstApp() {}

  void FirstApp::run()
  {
    RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
    Camera camera{};
    GameObject viewerObject = GameObject::createGameObject();
    // camera.setViewDirection(glm::vec3{0.0f},glm::vec3{0.5f,0.0f,1.0f});
    // camera.setViewTarget(glm::vec3(-1.0f,-2.0f,2.0f),glm::vec3(0.0f,0.0f,2.5f));

    auto currentTime = std::chrono::high_resolution_clock::now();
    Keyboard cameraController{};

    while (!window.shouldClose())
    {
      glfwPollEvents();

      auto newTime = std::chrono::high_resolution_clock::now();
      float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
      currentTime = newTime;

      cameraController.moveInPlaneXZ(window.getGLFWwindow(), deltaTime, viewerObject);
      camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

      float aspect = renderer.getAspectRatio();
      // camera.setOrthographicProjection(-aspect,aspect,-1,1,-1,1);
      camera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 100.0f);

      if (auto commandBuffer = renderer.beginFrame())
      {
        renderer.beginSwapChainRenderPass(commandBuffer);
        renderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
        renderer.endSwapChainRenderPass(commandBuffer);
        renderer.endFrame();
      }
      gameObjects[0].transform.rotation.y += deltaTime * 2;
      gameObjects[0].transform.rotation.x += deltaTime * 2;
      gameObjects[0].transform.rotation.z += deltaTime * 2;
    }

    vkDeviceWaitIdle(device.device());
  }

  void FirstApp::loadGameObjects()
  {
    std::shared_ptr<Model> lveModel =
        Model::createModelFromFile(device, "models/demoman.obj");
    auto gameObj = GameObject::createGameObject();
    gameObj.model = lveModel;
    gameObj.transform.translation = {.0f, .0f, 2.5f};
    gameObj.transform.scale = glm::vec3(3.f);
    gameObjects.push_back(std::move(gameObj));
  }

}
