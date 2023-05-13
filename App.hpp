#pragma once

#include "Device.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Descriptor.hpp"

// std
#include <memory>
#include <vector>

namespace Tutorial
{
  class FirstApp
  {
  public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    FirstApp();
    ~FirstApp();

    FirstApp(const FirstApp &) = delete;
    FirstApp &operator=(const FirstApp &) = delete;

    void run();

  private:
    void loadGameObjects();

    Window window{WIDTH, HEIGHT, "Vulkan Tutorial"};
    Device device{window};
    Renderer renderer{window, device};

    std::unique_ptr<DescriptorPool> globalPool{};
    std::vector<GameObject> gameObjects;
  };
}
