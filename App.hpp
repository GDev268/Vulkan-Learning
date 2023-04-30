#pragma once

#include "Device.hpp"
#include "Model.hpp"
#include "Pipeline.hpp"
#include "Swapchain.hpp"
#include "Window.hpp"

// std
#include <memory>
#include <vector>

namespace Tutorial {
class FirstApp {
 public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;

  FirstApp();
  ~FirstApp();

  FirstApp(const FirstApp &) = delete;
  FirstApp &operator=(const FirstApp &) = delete;

  void run();

 private:
  void loadModels();
  void createPipelineLayout();
  void createPipeline();
  void createCommandBuffers();
  void drawFrame();
  void recreateSwapChain();
  void recordCommandBuffer(int imageIndex);

  Window window{WIDTH, HEIGHT, "Hello Vulkan!"};
  Device device{window};
  std::unique_ptr<Swapchain> swapchain;
  std::unique_ptr<Model> model;
  std::unique_ptr<Pipeline> pipeline;
  VkPipelineLayout pipelineLayout;
  std::vector<VkCommandBuffer> commandBuffers;
};
}  // namespace lve