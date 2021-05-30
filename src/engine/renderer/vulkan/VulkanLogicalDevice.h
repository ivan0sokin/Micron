#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_LOGICAL_DEVICE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_LOGICAL_DEVICE_H

#include "VulkanQueue.hpp"

namespace Micron
{
    namespace Vulkan
    {
        class LogicalDevice
        {
        public:
            inline LogicalDevice() noexcept = default;
            inline ~LogicalDevice() noexcept = default;

            inline LogicalDevice(VkPhysicalDevice physicalDeviceHandle) noexcept :
                physicalDeviceHandle(physicalDeviceHandle)
            {}

            Void Create() noexcept;
            Void Destroy() noexcept;

            Void InitializeQueues() noexcept;

            inline Void SetEnabledLayerNames(Vector<NullTerminatedConstantString> const &enabledLayerNames) noexcept { this->enabledLayerNames = enabledLayerNames; }
            inline Void SetQueueFamilyIndices(UnorderedSet<UInt32> const &queueFamilyIndices) noexcept { this->queueFamilyIndices = queueFamilyIndices; }
        private:
            Vector<VkDeviceQueueCreateInfo> PickQueueCreateInfos() const noexcept;
        private:
            VkDevice handle = VK_NULL_HANDLE;
            VkPhysicalDevice physicalDeviceHandle = VK_NULL_HANDLE;
        private:
            Vector<NullTerminatedConstantString> enabledLayerNames;
            UnorderedSet<UInt32> queueFamilyIndices;
            UnorderedMap<UInt32, Rc<Queue>> queues;
        private:
            constexpr static UInt32 queueCount = 1;
            constexpr static Float32 queuePriority = 1.0f;
            constexpr static UInt32 queueIndex = 0;
        };
    }
}

#endif