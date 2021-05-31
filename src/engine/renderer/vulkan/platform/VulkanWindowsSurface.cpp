#include "VulkanWindowsSurface.h"

namespace Micron
{
    namespace Vulkan
    {
        Void WindowsSurface::CreateHandle() noexcept 
        {
            VkWin32SurfaceCreateInfoKHR windowsSurfaceCreateInfoKHR = {};
            windowsSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
            windowsSurfaceCreateInfoKHR.hinstance = this->moduleHandle;
            windowsSurfaceCreateInfoKHR.hwnd = this->windowHandle;

            Utility::Result windowsSurfaceKHRCreate = vkCreateWin32SurfaceKHR(this->instanceHandle, &windowsSurfaceCreateInfoKHR, nullptr, &this->handle);

            if (windowsSurfaceKHRCreate.Failed())
            {
                CoreLogger::Error("Failed to create Vulkan Windows surface handle, message: {}", windowsSurfaceKHRCreate.ToString());
                return;
            }

            CoreLogger::Info("Vulkan Windows surface handle created");
        }
    }
}