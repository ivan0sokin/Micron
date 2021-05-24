#include "VulkanPhysicalDeviceTypes.h"

namespace Micron
{
	namespace Vulkan
	{
		static Array<MultibyteString, 5> const physicalDevicesAsStrings =
		{
			"Other",
			"IntegratedGPU",
			"DiscreteGPU",
			"VirtualGPU",
			"CPU",
		};

		MultibyteString ToString(PhysicalDeviceType const &physicalDeviceType) noexcept
		{
			return physicalDevicesAsStrings[EnumToUnsignedSizeType(physicalDeviceType)];
		}
	}
}