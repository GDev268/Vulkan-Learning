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
    float time;

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
      time += 0.01f;

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
      gameObjects[0].transform.translation.x += deltaTime * 2;
      if(gameObjects[0].transform.translation.x >= 20){
        gameObjects[0].transform.translation.x = 0;
      }

      gameObjects[1].transform.rotation.y += deltaTime * 2;

      gameObjects[1].transform.translation.x += sin(time) / 100;
      gameObjects[1].transform.translation.z += cos(time) / 100;

      gameObjects[2].transform.translation.y -= deltaTime * 2;
      if(gameObjects[2].transform.translation.y <= -10){
        gameObjects[2].transform.translation.y = 10;
      }

      gameObjects[2].transform.rotation.y += deltaTime * 2;
      gameObjects[2].transform.rotation.x += deltaTime * 2;

      gameObjects[3].transform.scale += glm::vec3(sin(time) / 10);

      
    }

    vkDeviceWaitIdle(device.device());
  }

  void FirstApp::loadGameObjects()
  {
    std::shared_ptr<Model> model =
        Model::createModelFromFile(device, "models/faker.obj");
    auto gameObj = GameObject::createGameObject();
    gameObj.model = model;
    gameObj.transform.translation = {.0f, .5f, 2.5f};
    gameObj.transform.scale = glm::vec3(3.f,1.5f,3.0f);
    gameObj.transform.rotation = glm::vec3(0.0f,191.0f,0.0f);
    gameObjects.push_back(std::move(gameObj));

    model =
        Model::createModelFromFile(device, "models/sage.obj");
    gameObj = GameObject::createGameObject();
    gameObj.model = model;
    gameObj.transform.translation = {5.0f, .5f, 2.5f};
    gameObj.transform.scale = glm::vec3(3.f,1.5f,3.0f);
    gameObjects.push_back(std::move(gameObj));

    model =
        Model::createModelFromFile(device, "models/demoman.obj");
    gameObj = GameObject::createGameObject();
    gameObj.model = model;
    gameObj.transform.translation = {10.0f, .5f, 2.5f};
    gameObj.transform.scale = glm::vec3(3.f,1.5f,3.0f);
    gameObjects.push_back(std::move(gameObj));

    model =
        Model::createModelFromFile(device, "models/spy.obj");
    gameObj = GameObject::createGameObject();
    gameObj.model = model;
    gameObj.transform.translation = {10.0f, .5f, 2.5f};
    gameObj.transform.scale = glm::vec3(3.f,1.5f,3.0f);
    gameObjects.push_back(std::move(gameObj));
  }

}
