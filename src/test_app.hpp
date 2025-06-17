#ifndef TEST_APP_HPP
#define TEST_APP_HPP

#include "rrr_window.hpp"
#include "rrr_pipeline.hpp"

namespace rrr {
    class TestApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;

        void run();
    private:
        RrrWindow window{WIDTH, HEIGHT, "Vulkan Torture"};
        RrrPipeline pipeline{"assets/shaders/basic_shader.vert.spv", "assets/shaders/basic_shader.frag.spv"};
    };
}

#endif //TEST_APP_HPP
