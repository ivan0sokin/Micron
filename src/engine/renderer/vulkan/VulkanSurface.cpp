#include "VulkanSurface.h"

namespace Micron
{
    namespace Vulkan
    {
        Void Surface::Destroy() noexcept
        {
            if (this->handle == nullptr)
            {
                CoreLogger::Error("Can not destroy Vulkan surface, because it is not created");
                return;
            }

            vkDestroySurfaceKHR(this->instanceHandle, this->handle, nullptr);
        }
    }
}