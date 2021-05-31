#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_SURFACE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_SURFACE_H

#include "utility/VulkanUtilities.h"

namespace Micron
{
    namespace Vulkan
    {
        class Surface
        {
            friend class QueueFamily;
        public:
            inline Surface() noexcept = default;
            virtual inline ~Surface() noexcept = default;

            constexpr Surface(VkInstance instanceHandle) noexcept :
                instanceHandle(instanceHandle)
            {}

            virtual Void CreateHandle() noexcept { return; }
            Void DestroyHandle() noexcept;

            constexpr static MultibyteString GetExtensionName() noexcept { return VK_KHR_SWAPCHAIN_EXTENSION_NAME; }
        protected:
            VkSurfaceKHR handle = VK_NULL_HANDLE;
            VkInstance instanceHandle = VK_NULL_HANDLE;
        };
    }
}

#endif