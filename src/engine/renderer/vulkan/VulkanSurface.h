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

            virtual Void Create() noexcept { return; }
            Void Destroy() noexcept;
        protected:
            VkSurfaceKHR handle = VK_NULL_HANDLE;
            VkInstance instanceHandle = VK_NULL_HANDLE;
        };
    }
}

#endif