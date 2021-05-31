#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_PROPERTIES_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_PROPERTIES_H

#include "VulkanPhysicalDeviceTypes.h"

namespace Micron
{
    namespace Vulkan
    {
        class PhysicalDeviceProperties
        {
        public:
            inline PhysicalDeviceProperties() noexcept = default;
            inline ~PhysicalDeviceProperties() noexcept = default;

            constexpr PhysicalDeviceProperties(VkPhysicalDeviceProperties const &physicalDeviceProperties) noexcept :
                type(static_cast<PhysicalDeviceType>(physicalDeviceProperties.deviceType)),
                name(physicalDeviceProperties.deviceName),
                deviceID(physicalDeviceProperties.deviceID), vendorID(physicalDeviceProperties.vendorID),
                driverVersion(Utility::ToMicronVersion(physicalDeviceProperties.driverVersion)), vulkanVersion(Utility::ToMicronVersion(physicalDeviceProperties.apiVersion))
            {
                TrimString(this->name);
            }

            PhysicalDeviceType GetType() const noexcept { return type; }
            MultibyteString GetName() const noexcept { return name; }
            UInt32 GetDeviceID() const noexcept { return deviceID; }
            UInt32 GetVendorID() const noexcept { return vendorID; }
            Version GetDriverVersion() const noexcept { return driverVersion; }
            Version GetVulkanVersion() const noexcept { return vulkanVersion; }
        private:
            PhysicalDeviceType type;
			MultibyteString name;
			UInt32 deviceID, vendorID;
			Version driverVersion, vulkanVersion;
        };
    }
}

#endif