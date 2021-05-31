#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_H

#include "VulkanPhysicalDeviceProperties.hpp"
#include "VulkanExtension.hpp"
#include "VulkanPhysicalDeviceMemoryProperties.hpp"
#include "VulkanQueueFamily.h"
#include "VulkanLogicalDevice.h"

namespace Micron
{
	namespace Vulkan
	{
		class PhysicalDevice
		{
		public:
			
		public:
			inline PhysicalDevice() noexcept = default;
			inline ~PhysicalDevice() noexcept = default;

			constexpr PhysicalDevice(VkPhysicalDevice physicalDeviceHandle) noexcept :
				handle(physicalDeviceHandle)
			{}

			Void Initialize() noexcept;
			Void InitializeMemory() noexcept;
			Void InitializeQueueFamilies() noexcept;
			Void InitializeExtensions() noexcept;		

			constexpr Bool HasGraphicsQueueFamily() const noexcept { return std::ranges::any_of(std::as_const(queueFamilies), [](auto queueFamily) { return queueFamily->SupportOperation(QueueOperation::Graphics); }); }

			Bool SupportExtensions(Set<MultibyteString> extensionNames) noexcept;

			Rc<LogicalDevice> CreateLogicalDevice(UnorderedSet<UInt32> const &queueFamilyIndices) noexcept;	

			inline Rc<PhysicalDeviceProperties> GetProperties() const noexcept { return properties; }
			inline Rc<PhysicalDeviceMemoryProperties> GetMemoryProperties() const noexcept { return memoryProperties; }
			inline Vector<Rc<QueueFamily>> GetQueueFamilies() const noexcept { return queueFamilies; }
			inline Vector<Rc<Extension>> GetAvailableExtensions() const noexcept { return availableExtensions; }

			inline Vector<Rc<LogicalDevice>> GetCreatedLogicalDevices() const noexcept { return createdLogicalDevices; }
		private:
            Vector<VkExtensionProperties> GetAvailableExtensionProperties() const noexcept;
            UInt32 GetAvailableExtensionCount() const noexcept;
		private:
			VkPhysicalDevice handle = VK_NULL_HANDLE;
		private:
			Rc<PhysicalDeviceProperties> properties;
			Rc<PhysicalDeviceMemoryProperties> memoryProperties;
			Vector<Rc<QueueFamily>> queueFamilies;
			Vector<Rc<Extension>> availableExtensions;

			Vector<Rc<LogicalDevice>> createdLogicalDevices;
		};
	}
}

#endif