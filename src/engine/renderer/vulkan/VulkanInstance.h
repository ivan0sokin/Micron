#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_INSTANCE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_INSTANCE_H

#include "utility/VulkanUtilities.h"

namespace Micron
{
	namespace Vulkan
	{
		class Instance
		{
		public:
			inline ~Instance() noexcept = default;
			
			Instance(Instance const &other) = delete;
			Instance(Instance &&other) = delete;
    		Void operator=(Instance const &other) = delete;
			Void operator=(Instance &&other) = delete;

			Void Initialize() noexcept;
			Void Destroy() noexcept;
		
			Vector<VkPhysicalDevice> GetPhysicalDeviceHandles() const noexcept;

			inline Vector<NullTerminatedConstantString> GetEnabledLayers() const noexcept { return enabledLayers; }
			inline Vector<NullTerminatedConstantString> GetEnabledExtensions() const noexcept { return enabledExtensions; }

			static Rc<Instance> GetInstance() noexcept;
		private:
			inline Instance() noexcept = default;

			VkApplicationInfo PickApplicationInfo() const noexcept;

			Void InitializeEnabledLayers() noexcept;
			Bool CheckValidationLayersAreAvailable() const noexcept;
			Vector<MultibyteString> GetAvailableLayerNames() const noexcept;

			Void InitializeEnabledExtensions() noexcept;
			Bool CheckRequiredExtensionsAreAvailable() const noexcept;
			Vector<MultibyteString> GetAvailableExtensionNames() const noexcept;
		private:
			VkInstance handle = VK_NULL_HANDLE;
		private:
			inline static Rc<Instance> instance;

			Vector<NullTerminatedConstantString> enabledLayers;
			Vector<NullTerminatedConstantString> enabledExtensions;
		};
	}
}

#endif