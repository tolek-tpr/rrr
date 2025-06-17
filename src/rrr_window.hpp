#ifndef RRR_WINDOW_HPP
#define RRR_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace rrr {

    class RrrWindow {
        public:
            RrrWindow(int width, int height, std::string windowName);
            ~RrrWindow();

            RrrWindow(const RrrWindow &) = delete;
            RrrWindow &operator=(const RrrWindow &) = delete;

            bool shouldClose() { return glfwWindowShouldClose(window); }
            void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
            VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }

        private:
            GLFWwindow* window;

            const int width, height;
            const std::string windowName;

            void initWindow();
    };


};

#endif //RRR_WINDOW_HPP
