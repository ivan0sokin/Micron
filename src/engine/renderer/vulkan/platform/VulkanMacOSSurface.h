#ifndef _MICRON_ENGINE_RENDERER_VULKAN_PLATFORM_VULKAN_MACOS_SURFACE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_PLATFORM_VULKAN_MACOS_SURFACE_H

#include "../VulkanSurface.h"

#if defined MICRON_CURRENT_PLATFORM_MACOS

#include <vulkan/vulkan_macos.h>

#define PLATFORM_SURFACE_EXTENSION_NAME VK_MVK_MACOS_SURFACE_EXTENSION_NAME

namespace Micron
{
    namespace Vulkan
    {
        class MacOSSurface : public Surface
        {
        public:
            inline MacOSSurface() noexcept = default;
            inline ~MacOSSurface() noexcept override = default;

            constexpr MacOSSurface(VkInstance instanceHandle, const void *pView) noexcept :
                Surface(instanceHandle), pView(pView)
            {}

            Void Create() noexcept override;
        private:
            void *pView;
        }
    }
}

#else

namespace Micron
{
    namespace Vulkan
    {
        class MacOSSurface : public Surface
        {
        public:
            inline MacOSSurface() noexcept = default;
            inline ~MacOSSurface() noexcept override = default;

            Void Create() noexcept override { return; }
        };
    }
}

#endif

#endif