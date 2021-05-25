#include "VulkanLinuxSurface.h"

namespace Micron
{
    namespace Vulkan
    {
        Void LinuxSurface::Create() noexcept 
        {
            VkXlibSurfaceCreateInfoKHR linuxSurfaceCreateInfoKHR = {};
            linuxSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
            linuxSurfaceCreateInfoKHR.dpy = display;
            linuxSurfaceCreateInfoKHR.window = window;

            Utility::Result linuxSurfaceKHRCreate = vkCreateXlibSurfaceKHR(this->instanceHandle, &linuxSurfaceCreateInfoKHR, nullptr, &this->handle);

            if (linuxSurfaceKHRCreate.Failed())
            {
                CoreLogger::Error("Failed to create Vulkan Linux surface, message: {}", linuxSurfaceKHRCreate.ToString());
                return;
            }

            CoreLogger::Info("Vulkan Linux surface created");
        }
    }
}