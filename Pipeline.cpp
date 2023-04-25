#include "Pipeline.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

Tutorial::Pipeline::Pipeline(Device& device,const std::string &vertFilePath, const std::string &fragFilePath, const PipelineConfigInfo &configInfo) : device{device}
{
    createGraphicsPipeline(vertFilePath, fragFilePath,configInfo);
}

Tutorial::PipelineConfigInfo Tutorial::Pipeline::defaultPipelineInfo(uint32_t width, uint32_t height)
{
    PipelineConfigInfo configInfo{};

    return configInfo;
}

std::vector<char> Tutorial::Pipeline::readFile(const std::string &filepath)
{
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Couldn't open the file: " + filepath);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());

    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

void Tutorial::Pipeline::createGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath,const PipelineConfigInfo &configInfo)
{
    auto vertCode = readFile(vertFilePath);
    auto fragCode = readFile(fragFilePath);

    std::cout << "Vertex Shader Code Size: " << vertCode.size() << std::endl;
    std::cout << "Fragment Shader Code Size: " << fragCode.size() << std::endl;
}

void Tutorial::Pipeline::createShaderModule(std::vector<char> &code, VkShaderModule *shaderModule)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.size());

    if(vkCreateShaderModule(device.device(),&createInfo,nullptr,shaderModule) != VK_SUCCESS){
        throw std::runtime_error("Failed to create shader module");
    }
}
