#ifndef RRRDEVICE_HPP
#define RRRDEVICE_HPP

#include <vulkan/vulkan.hpp>

#include "../rrr_window.hpp"

namespace rrr {
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    class RrrDevice {
    public:
        RrrDevice(RrrWindow &window);
        ~RrrDevice();
    private:
        struct CommandPools {
            VkCommandPool graphics;
            VkCommandPool compute;
        };

        struct Queues {
            VkQueue graphics;
            VkQueue present;
            VkQueue compute;
        };

        VkInstance instance;
        VkDevice device;
        VkPhysicalDevice physicalDevice;
        VkSurfaceKHR surface;
        VkPhysicalDeviceProperties properties;

        std::vector<const char *> deviceExtensions;
        std::vector<VkPresentModeKHR> presentModes;

        VkPresentModeKHR vsyncPresentMode;
        VkPresentModeKHR nonVsyncPresentMode;

        CommandPools commandPools;
        Queues queues;

        VkDebugUtilsMessengerEXT debugMessenger;
        const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    };
} // rrr

#endif //RRRDEVICE_HPP
