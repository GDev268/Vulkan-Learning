#include "App.hpp"

#include <stdexcept>
#include <array>

void Tutorial::FirstApp::run()
{
  while (!window.shouldClose())
  {
    glfwPollEvents();
    drawFrame();
  }

  vkDeviceWaitIdle(device.device());
} // namespace lve

Tutorial::FirstApp::FirstApp()
{
  createPipelineLayout();
  createPipeline();
  createCommandBuffers();
}

Tutorial::FirstApp::~FirstApp()
{
  vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
}

void Tutorial::FirstApp::createPipelineLayout()
{
  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0;
  pipelineLayoutInfo.pSetLayouts = nullptr;
  pipelineLayoutInfo.pushConstantRangeCount = 0;
  pipelineLayoutInfo.pPushConstantRanges = nullptr;

  if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
  {
    throw std::runtime_error("Failed to create pipeline info!");
  }
}

void Tutorial::FirstApp::createPipeline()
{
  auto pipelineConfig = Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT);
  pipelineConfig.renderPass = swapchain.getRenderPass();
  pipelineConfig.pipelineLayout = pipelineLayout;
  pipeline = std::make_unique<Pipeline>(device, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
}

void Tutorial::FirstApp::createCommandBuffers()
{
  commandBuffers.resize(swapchain.imageCount());

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = device.getCommandPool();
  allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

  if (vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
  {
    throw std::runtime_error("couldn't allocate command buffers");
  }

  for (int i = 0; i < commandBuffers.size(); i++)
  {
    VkCommandBufferBeginInfo beingInfo{};
    beingInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffers[i], &beingInfo) != VK_SUCCESS)
    {
      throw std::runtime_error("couldn't begin command buffer");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = swapchain.getRenderPass();
    renderPassInfo.framebuffer = swapchain.getFrameBuffer(i);
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapchain.getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    pipeline->bind(commandBuffers[i]);
    vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

    vkCmdEndRenderPass(commandBuffers[i]);
    if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
    {
      throw std::runtime_error("failed to record command buffer");
    }
  }
}

void Tutorial::FirstApp::drawFrame()
{
  uint32_t imageIndex;
  auto result = swapchain.acquireNextImage(&imageIndex);
  if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("failed to acquire swap chain image");
  }

  result = swapchain.submitCommandBuffers(&commandBuffers[imageIndex],&imageIndex);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to present swap chain image!");
  }
}
