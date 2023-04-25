#pragma oncce

#include "Window.hpp"
#include "Pipeline.hpp"
#include "Device.hpp"

namespace Tutorial
{
    class FirstApp
    {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;

        void run();

    private:
        Tutorial::Window window = Tutorial::Window("Hello Vulkan!", WIDTH, HEIGHT);
        Tutorial::Device device = Tutorial::Device(window);
        Tutorial::Pipeline pipeline = Tutorial::Pipeline(device,"shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv",Tutorial::Pipeline::defaultPipelineInfo(WIDTH,HEIGHT));
    };
}