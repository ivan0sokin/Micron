#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_TYPES_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_TYPES_H

#include "utility/VulkanUtilities.h"

namespace Micron
{
	namespace Vulkan
	{
		enum class PhysicalDeviceType : UInt16
		{
			Other = VK_PHYSICAL_DEVICE_TYPE_OTHER,
			IntegratedGPU = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
			DiscreteGPU = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,
			VirtualGPU = VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,
			CPU = VK_PHYSICAL_DEVICE_TYPE_CPU,
		};

		MultibyteString ToString(PhysicalDeviceType const &physicalDeviceType) noexcept;
	}
}

#endif