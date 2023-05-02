#pragma once

#include "Device.hpp"
#include "Swapchain.hpp"
#include "Window.hpp"

// std
#include <cassert>
#include <memory>
#include <vector>

namespace Tutorial {
class Renderer {
 public:
  Renderer(Window &window, Device &device);
  ~Renderer();

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  VkRenderPass getSwapChainRenderPass() const { return swapchain->getRenderPass(); }
  float getAspectRatio() const { return swapchain->extentAspectRatio(); }
  bool isFrameInProgress() const { return isFrameStarted; }

  VkCommandBuffer getCurrentCommandBuffer() const {
    assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
    return commandBuffers[currentFrameIndex];
  }

  int getFrameIndex() const {
    assert(isFrameStarted && "Cannot get frame index when frame not in progress");
    return currentFrameIndex;
  }

  VkCommandBuffer beginFrame();
  void endFrame();
  void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
  void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

 private:
  void createCommandBuffers();
  void freeCommandBuffers();
  void recreateSwapChain();

  Window &window;
  Device &device;
  std::unique_ptr<Swapchain> swapchain;
  std::vector<VkCommandBuffer> commandBuffers;

  uint32_t currentImageIndex;
  int currentFrameIndex{0};
  bool isFrameStarted{false};
};
}
