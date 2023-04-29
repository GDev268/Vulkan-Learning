#pragma once

#include "Window.hpp"
#include "Pipeline.hpp"
#include "Device.hpp"
#include "Swapchain.hpp"
#include "Model.hpp"

#include <memory>
#include <vector>

namespace Tutorial
{
    class FirstApp
    {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 640;

        void run();

        FirstApp();
        ~FirstApp();

        FirstApp(const FirstApp &) = delete;
        FirstApp &operator=(const FirstApp &) = delete;

    private:
        void loadModels(); 
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        Tutorial::Window window = Tutorial::Window("Hello Vulkan!", WIDTH, HEIGHT);
        Tutorial::Device device = Tutorial::Device(window);
        Tutorial::Swapchain swapchain = Tutorial::Swapchain(device, window.getExtent());
        std::unique_ptr<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<Model> model;
    };
}