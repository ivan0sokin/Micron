#include "VulkanQueueFamily.h"

namespace Micron
{
    namespace Vulkan
    {
        QueueFamily::QueueFamily(VkPhysicalDevice physicalDeviceHandle, UInt32 queueFamilyIndex, VkQueueFamilyProperties const &queueFamilyProperties) noexcept :
            physicalDeviceHandle(physicalDeviceHandle), index(queueFamilyIndex), queueCount(queueFamilyProperties.queueCount)
        {
            for (UInt32 i = 1; i < 16; i *= 2)
            {
                if (i & queueFamilyProperties.queueFlags)
                    supportedOperations.push_back(static_cast<QueueOperation>(i));
            }
        }
    
        Bool QueueFamily::SupportPresentationToSurface(Rc<Surface> surface) const noexcept
        {
            VkBool32 presentationSupported = false;

            Utility::Result supportPresentationDetermine = vkGetPhysicalDeviceSurfaceSupportKHR(this->physicalDeviceHandle, this->index, surface->handle, &presentationSupported);
        
            if (supportPresentationDetermine.Failed())
            {
                CoreLogger::Error("Failed to determine queue family, that supports presentation to a surface, message: {}", supportPresentationDetermine.ToString());
                return false;
            }

            return static_cast<Bool>(presentationSupported);
        }
    }
}