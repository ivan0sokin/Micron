#include "VulkanMacOSSurface.h"

namespace Micron
{
    namespace Vulkan
    {
        Void MacOSSurface::Create() noexcept 
        {
            VkMacOSSurfaceCreateInfoMVK macOSSurfaceCreateInfoMVK = {};
            macOSSurfaceCreateInfoMVK.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
            macOSSurfaceCreateInfoMVK.pView = this->pView;

            Utility::Result macOsSurfaceKHRCreate = vkCreateMacOSSurfaceMVK(this->instanceHandle, &macOSSurfaceCreateInfoMVK, nullptr, &this->handle);

            if (macOsSurfaceKHRCreate.Failed())
            {
                CoreLogger::Error("Failed to create Vulkan MacOS surface, message: {}", macOsSurfaceKHRCreate.ToString());
                return;
            }

            CoreLogger::Info("Vulkan MacOS surface created");
        }
    }
}