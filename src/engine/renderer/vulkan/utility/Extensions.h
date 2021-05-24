#ifndef _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_EXTENSIONS_H
#define _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_EXTENTIONS_H

#include "../../../core/Core.h"

#include <vulkan/vulkan.hpp>

namespace Micron
{
	namespace Vulkan
	{
		namespace Utility
		{
			Vector<VkExtensionProperties> GetAvailableInstanceExtensionProperties() noexcept;

			Vector<NullTerminatedConstantString> GetRequiredInstanceExtensionNames() noexcept;
		}
	}
}

#endif