#include "test_app.hpp"

#include <stdexcept>

namespace rrr {

    TestApp::TestApp() {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    TestApp::~TestApp() {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void TestApp::run() {
        while (!window.shouldClose()) {
            glfwPollEvents();
        }
    }

    void TestApp::createPipelineLayout() {
        VkPipelineLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        layoutInfo.setLayoutCount = 0;
        layoutInfo.pSetLayouts = nullptr;
        layoutInfo.pushConstantRangeCount = 0;
        layoutInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(device.device(), &layoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout!");
        }
    }

    void TestApp::createPipeline() {
        auto pipelineConfig = RrrPipeline::defaultPiplelineConfigInfo(swapChain.width(), swapChain.height());
        pipelineConfig.renderPass = swapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<RrrPipeline>(device, "assets/shaders/basic_shader.vert.spv", "assets/shaders/basic_shader.frag.spv", pipelineConfig);
    }

    void TestApp::createCommandBuffers() {}
    void TestApp::drawFrame() {}

}
