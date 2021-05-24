#ifndef _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_LAYERS_H
#define _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_LAYERS_H

#include "../../../core/Core.h"

#include <vulkan/vulkan.hpp>

namespace Micron
{
	namespace Vulkan
	{
		namespace Utility
		{
			Vector<VkLayerProperties> GetAvailableInstanceLayerProperties() noexcept;

			constexpr Bool ValidationLayersEnabled() noexcept 
			{
				#if defined _MICRON_DEBUG
					return true;
				#else
					return false;
				#endif
			}

			Vector<NullTerminatedConstantString> GetValidationLayerNames() noexcept;
		}
	}
}

#endif