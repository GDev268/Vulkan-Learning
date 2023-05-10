#include "App.hpp"

#include "RenderSystem.hpp"
#include "Camera.hpp"
#include "Keyboard.hpp"
#include "Buffer.hpp"

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
  struct GlobalUBO
  {
    glm::mat4 projectionView{1.0f};
    glm::vec3 lightDirection = glm::normalize(glm::vec3{1.0f, -3.0f, -1.0f});
  };

  FirstApp::FirstApp() { loadGameObjects(); }

  FirstApp::~FirstApp() {}

  void FirstApp::run()
  {
    float time;
    float lightX,lightY;

    std::vector<std::unique_ptr<Buffer>> uboBuffers(Swapchain::MAX_FRAMES_IN_FLIGHT);
    for (int i = 0; i < uboBuffers.size(); i++)
    {
      uboBuffers[i] = std::make_unique<Buffer>(
        device,
        sizeof(GlobalUBO),
        1,
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
      );
      uboBuffers[i]->map();
    };

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
      time += deltaTime;

      cameraController.moveInPlaneXZ(window.getGLFWwindow(), deltaTime, viewerObject);
      camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

      lightX = sin(time);
      lightY = cos(time);

      float aspect = renderer.getAspectRatio();
      // camera.setOrthographicProjection(-aspect,aspect,-1,1,-1,1);
      camera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 100.0f);

      if (auto commandBuffer = renderer.beginFrame())
      {
        int frameIndex = renderer.getFrameIndex();
        FrameInfo frameInfo = {
            frameIndex,
            deltaTime,
            commandBuffer,
            camera};

        // update
        GlobalUBO ubo{};
        ubo.projectionView = camera.getProjection() * camera.getView();
        uboBuffers[frameIndex]->writeToBuffer(&ubo);
        uboBuffers[frameIndex]->flush();

        // render
        renderer.beginSwapChainRenderPass(commandBuffer);
        renderSystem.renderGameObjects(frameInfo, gameObjects);
        renderer.endSwapChainRenderPass(commandBuffer);
        renderer.endFrame();
      }
    }

    vkDeviceWaitIdle(device.device());
  }

  void FirstApp::loadGameObjects()
  {
    std::shared_ptr<Model> model =
        Model::createModelFromFile(device, "models/flat_vase.obj");
    auto flatVase = GameObject::createGameObject();
    flatVase.model = model;
    flatVase.transform.translation = {-.5f, .5f, 2.5f};
    flatVase.transform.scale = {3.f, 1.5f, 3.f};
    gameObjects.push_back(std::move(flatVase));

    model = Model::createModelFromFile(device, "models/smooth_vase.obj");
    auto smoothVase = GameObject::createGameObject();
    smoothVase.model = model;
    smoothVase.transform.translation = {.5f, .5f, 2.5f};
    smoothVase.transform.scale = {3.f, 1.5f, 3.f};
    gameObjects.push_back(std::move(smoothVase));
  }
}
