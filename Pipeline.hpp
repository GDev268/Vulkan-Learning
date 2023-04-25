#pragma once

#include "Device.hpp"

#include <string>
#include <vector>

namespace Tutorial
{
    struct PipelineConfigInfo
    {
    };

    class Pipeline
    {
    public:
        Pipeline(Device& device,const std::string &vertFilePath, const std::string &fragFilePath, const PipelineConfigInfo &configInfo);
        ~Pipeline(){};

        Pipeline(const Pipeline&)  = delete;

        static PipelineConfigInfo defaultPipelineInfo(uint32_t width,uint32_t height);

    private:
        std::vector<char> readFile(const std::string &filepath);

        void createGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath,const PipelineConfigInfo &configInfo);

        void createShaderModule(std::vector<char>& code, VkShaderModule* shaderModule);

        Device &device;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };

}