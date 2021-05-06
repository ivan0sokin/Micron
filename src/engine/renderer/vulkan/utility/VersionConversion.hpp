#ifndef _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_VERSION_CONVERSION_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_VERSION_CONVERSION_HPP

#include "../../../core/Core.h"

#include <vulkan/vulkan.hpp>

namespace Micron
{
	namespace Vulkan
	{
		namespace Utility
		{
			inline UInt32 ToVulkanVersion(Version const &micronVersion) noexcept
			{
				return VK_MAKE_VERSION(micronVersion.major, micronVersion.minor, micronVersion.patch);
			}

			inline Version ToMicronVersion(UInt32 vulkanVersion) noexcept
			{
				return Version(VK_VERSION_MAJOR(vulkanVersion), VK_VERSION_MINOR(vulkanVersion), VK_VERSION_PATCH(vulkanVersion));
			}
		}
	}
}

#endif