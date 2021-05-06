#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_INSTANCE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_INSTANCE_H

#include "../../core/Core.h"

#include "utility/VulkanUtilities.h"

namespace Micron
{
	namespace Vulkan
	{
		class Instance
		{
		public:
			inline Instance() noexcept = default;
			inline ~Instance() noexcept = default;
			
			Void Initialize() noexcept;
			Void Destroy() noexcept;
		private:
			Vector<NullTerminatedConstantString> PickEnabledExtensions() noexcept;
			Vector<NullTerminatedConstantString> PickEnabledLayers() noexcept;
		private:
			VkInstance instance;
		};
	}
}

#endif