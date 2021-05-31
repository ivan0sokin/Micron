#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_INSTANCE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_INSTANCE_H

#include "VulkanLayer.hpp"
#include "VulkanExtension.hpp"

#include "VulkanPhysicalDevice.h"

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

			Void InitializeLayers() noexcept;
			Void InitializeExtensions() noexcept;

			Void CreateHandle() noexcept;
			Void DestroyHandle() noexcept;

			Void InitializeSurface() noexcept;
			Void InitializePhysicalDevices() noexcept;

			Rc<Surface> GetSurface() const noexcept { return surface; }

			Vector<Rc<PhysicalDevice>> GetPhysicalDevices() const noexcept { return physicalDevices; }

			inline Vector<Rc<Layer>> GetAvailableLayers() const noexcept { return availableLayers; }
			inline Vector<Rc<Extension>> GetAvailableExtensions() const noexcept { return availableExtensions; }
		private:
			Vector<VkLayerProperties> GetAvailableLayerProperties() const noexcept;
			UInt32 GetAvailableLayerCount() const noexcept;

			Vector<VkExtensionProperties> GetAvailableExtensionProperties() const noexcept;
			UInt32 GetAvailableExtensionCount() const noexcept;

			VkApplicationInfo PickApplicationInfo() const noexcept;

			Void InitializeEnabledLayerNames() noexcept;
			Bool CheckValidationLayersAreAvailable() const noexcept;
			Vector<MultibyteString> GetAvailableLayerNames() const noexcept;

			Void InitializeEnabledExtensionNames() noexcept;
			Bool CheckRequiredExtensionsAreAvailable() const noexcept;
			Vector<MultibyteString> GetAvailableExtensionNames() const noexcept;

			Vector<VkPhysicalDevice> GetPhysicalDeviceHandles() const noexcept;
			UInt32 GetPhysicalDeviceCount() const noexcept;

			Rc<LinuxSurface> CreateLinuxSurface() const noexcept;
			Rc<WindowsSurface> CreateWindowsSurface() const noexcept;
			Rc<MacOSSurface> CreateMacOSSurface() const noexcept;
			Rc<IOPlatformWindow> GetPlatformWindow() const noexcept;
		private:
			VkInstance handle = VK_NULL_HANDLE;
		private:
			Vector<Rc<Layer>> availableLayers;
			Vector<Rc<Extension>> availableExtensions;

			Vector<Rc<PhysicalDevice>> physicalDevices;
			Rc<Surface> surface;

			Vector<NullTerminatedConstantString> enabledLayerNames;
			Vector<NullTerminatedConstantString> enabledExtensionNames;
		private:
			constexpr static Bool validationLayersEnabled = Micron::IsDebugEnabled();
			constexpr static Array< NullTerminatedConstantString, 1> validationLayerNames = { "VK_LAYER_KHRONOS_validation" };
			constexpr static Array<NullTerminatedConstantString, 2> requiredExtensionNames = { VK_KHR_SURFACE_EXTENSION_NAME, PLATFORM_SURFACE_EXTENSION_NAME };
		};
	}
}

#endif