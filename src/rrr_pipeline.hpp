#ifndef RRR_PIPELINE_HPP
#define RRR_PIPELINE_HPP

#include "rrr_device.hpp"
#include <string>
#include <vector>

namespace rrr {

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class RrrPipeline {
    public:
            RrrPipeline(RrrDevice &device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo pipelineConfigInfo);
            ~RrrPipeline();

            RrrPipeline(const RrrPipeline &) = delete;
            RrrPipeline &operator=(const RrrPipeline &) = delete;

            static PipelineConfigInfo defaultPiplelineConfigInfo(uint32_t width, uint32_t height);
    private:
            RrrDevice &device;
            VkPipeline graphicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;

            static std::vector<char> readFile(const std::string& filepath);

            void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo pipelineConfigInfo);
            void createShaderModule(const std::vector<char>& shaderCode, VkShaderModule* shaderModule);
    };
}

#endif //RRR_PIPELINE_HPP
