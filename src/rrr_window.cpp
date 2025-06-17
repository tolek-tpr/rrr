#include "rrr_window.hpp"

#include <stdexcept>

namespace rrr {

    RrrWindow::RrrWindow(int width, int height, std::string windowName) : width{width}, height{height}, windowName{std::move(windowName)} {
        initWindow();
    }

    RrrWindow::~RrrWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }


    void RrrWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }

    void RrrWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface!");
        }
    }

}