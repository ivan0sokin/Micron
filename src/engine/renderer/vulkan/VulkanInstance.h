#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_INSTANCE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_INSTANCE_H

#include "platform/VulkanLinuxSurface.h"
#include "platform/VulkanWindowsSurface.h"
#include "platform/VulkanMacOSSurface.h"

#include <IOWindow/IOWin32Window.h>
#include <IOWindow/IOLinuxWindow.h>

namespace Micron
{
	namespace Vulkan
	{
		class Instance
		{
		public:
			inline ~Instance() noexcept = default;
			inline Instance() noexcept = default;

			Void Create() noexcept;
			Void Destroy() noexcept;

			Rc<Surface> CreateSurface() noexcept;

			Vector<VkPhysicalDevice> GetPhysicalDeviceHandles() const noexcept;

			inline Vector<NullTerminatedConstantString> GetEnabledLayers() const noexcept { return enabledLayers; }
			inline Vector<NullTerminatedConstantString> GetEnabledExtensions() const noexcept { return enabledExtensions; }
		private:
			VkApplicationInfo PickApplicationInfo() const noexcept;

			Void InitializeEnabledLayers() noexcept;
			Bool CheckValidationLayersAreAvailable() const noexcept;
			Vector<MultibyteString> GetAvailableLayerNames() const noexcept;

			Void InitializeEnabledExtensions() noexcept;
			Bool CheckRequiredExtensionsAreAvailable() const noexcept;
			Vector<MultibyteString> GetAvailableExtensionNames() const noexcept;

			Rc<LinuxSurface> CreateLinuxSurface() noexcept;
			Rc<WindowsSurface> CreateWindowsSurface() noexcept;
			Rc<MacOSSurface> CreateMacOSSurface() noexcept;
			Rc<IOPlatformWindow> GetPlatformWindow() const noexcept;
		private:
			VkInstance handle = VK_NULL_HANDLE;
		private:
			Vector<NullTerminatedConstantString> enabledLayers;
			Vector<NullTerminatedConstantString> enabledExtensions;
		};
	}
}

#endif