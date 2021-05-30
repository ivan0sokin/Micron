#ifndef _MICRON_ENGINE_RENDERER_VULKAN_PLATFORM_VULKAN_LINUX_SURFACE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_PLATFORM_VULKAN_LINUX_SURFACE_H

#include "../VulkanSurface.h"

#if defined MICRON_CURRENT_PLATFORM_LINUX

#include <vulkan/vulkan_xlib.h>

#define PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_XLIB_SURFACE_EXTENSION_NAME

namespace Micron
{
    namespace Vulkan
    {
        class LinuxSurface : public Surface
        {
        public:
            inline LinuxSurface() noexcept = default;
            inline ~LinuxSurface() noexcept override = default;

            constexpr LinuxSurface(VkInstance instanceHandle, Display *display, Window window) noexcept :
                Surface(instanceHandle), display(display), window(window)
            {}

            Void Create() noexcept override;
        private:
            Dispplay *display;
            Window window;
        }
    }
}

#else

namespace Micron
{
    namespace Vulkan
    {
        class LinuxSurface : public Surface
        {
        public:
            inline LinuxSurface() noexcept = default;
            inline ~LinuxSurface() noexcept override = default;

            Void Create() noexcept override { return; }
        };
    }
}

#endif

#endif