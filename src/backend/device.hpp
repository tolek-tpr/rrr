#ifndef RRRDEVICE_HPP
#define RRRDEVICE_HPP

#include <iostream>
#include <vulkan/vulkan.hpp>

#include "../rrr_window.hpp"

#ifndef NDEBUG
#define VK_RENAME(device, handle, type, name) device->setObjectName(reinterpret_cast<uint64_t>(handle), type, name);
#else
#define VK_RENAME(device, handle, type, name)
#endif

namespace rrr {
    struct RequestedExtensions {
        bool drawIndirectCount = false;
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
        uint32_t computeFamily;
        bool graphicsFamilyHasValue = false;
        bool presentFamilyHasValue = false;
        bool computeFamilyHasValue = false;
        bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue && computeFamilyHasValue; }
    };

    class RrrDevice {
    public:
        RrrDevice(RrrWindow &window, RequestedExtensions extensions);
        ~RrrDevice();

        RrrDevice(const RrrDevice &) = delete;
        void operator=(const RrrDevice &) = delete;
        RrrDevice(RrrDevice &&) = delete;
        RrrDevice &operator=(RrrDevice &&) = delete;

        VkCommandPool getComputeCommandPool() const { return commandPools.compute; }
        VkCommandPool getGraphicsCommandPool() const { return commandPools.graphics; }
        VkQueue getGraphicsQueue() const { return queues.graphics; }
        VkQueue getComputeQueue() const { return queues.compute; }
        VkQueue getPresentQueue() const { return queues.present; }
        VkDevice getDevice() const { return device; }
        VkSurfaceKHR getSurface() const { return surface; }

        SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }

        VkFormat findSupportedFormat(
    const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        QueueFamilyIndices findPhysicalQueueFamilies() const { findQueueFamilies(physicalDevice) };


        void createBuffer(
            VkDeviceSize size,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkBuffer &buffer,
            VkDeviceMemory &bufferMemory);
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void copyBufferToImage(
            VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);
        void createImageWithInfo(const VkImageCreateInfo &imageInfo,
            VkMemoryPropertyFlags properties,
            VkImage &image,
            VkDeviceMemory &imageMemory);
#ifndef NDEBUG
        void setObjectName(uint64_t handle, VkObjectType type, const char* name);
#endif
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

        void createInstance(RequestedExtensions extensions, bool enableValidationLayers);
        void pickPhysicalDevice();
        void createLogicalDevice(bool enableValidationLayers);
        void setupDebugMessenger();
        void createCommandPool();

        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkValidationLayerSupport();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void hasGflwRequiredInstanceExtensions();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        std::vector<const char *> getRequiredExtensions(bool enableValidationLayers, RequestedExtensions extensions);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        VkInstance instance;
        VkDevice device;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkSurfaceKHR surface;
        VkPhysicalDeviceProperties properties;

        std::vector<const char *> deviceExtensions;
        std::vector<VkPresentModeKHR> presentModes;

        VkPresentModeKHR vsyncPresentMode;
        VkPresentModeKHR nonVsyncPresentMode;

        CommandPools commandPools;
        Queues queues;

#ifndef NDEBUG
        VkDebugUtilsMessengerEXT debugMessenger;
        const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
#endif
    };
} // rrr

#endif //RRRDEVICE_HPP
