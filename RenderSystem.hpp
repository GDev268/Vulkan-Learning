#pragma once

#include "Camera.hpp"
#include "Device.hpp"
#include "GameObject.hpp"
#include "Pipeline.hpp"
#include "FrameInfo.hpp"

// std
#include <memory>
#include <vector>

namespace Tutorial {
class RenderSystem {
 public:
  RenderSystem(Device &device, VkRenderPass renderPass);
  ~RenderSystem();

  RenderSystem(const RenderSystem &) = delete;
  RenderSystem &operator=(const RenderSystem &) = delete;

  void renderGameObjects(FrameInfo &frameinfo, std::vector<GameObject> &gameObjects);

 private:
  void createPipelineLayout();
  void createPipeline(VkRenderPass renderPass);

  Device &device;

  std::unique_ptr<Pipeline> lvePipeline;
  VkPipelineLayout pipelineLayout;
};
}