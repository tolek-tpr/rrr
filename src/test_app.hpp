#ifndef TEST_APP_HPP
#define TEST_APP_HPP

#include "rrr_window.hpp"
#include "rrr_pipeline.hpp"
#include "rrr_device.hpp"
#include "rrr_swap_chain.hpp"

#include <memory>
#include <vector>

namespace rrr {
    class TestApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;

        TestApp();
        ~TestApp();

        TestApp(const TestApp &) = delete;
        TestApp &operator=(const TestApp &) = delete;

        void run();
    private:
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        RrrWindow window{WIDTH, HEIGHT, "Vulkan Torture"};
        RrrDevice device{window};
        RrrSwapChain swapChain{device, window.getExtent()};
        //RrrPipeline pipeline{device, "assets/shaders/basic_shader.vert.spv", "assets/shaders/basic_shader.frag.spv", RrrPipeline::defaultPiplelineConfigInfo(WIDTH, HEIGHT)};
        std::unique_ptr<RrrPipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
    };
}

#endif //TEST_APP_HPP
