#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_H

#include "VulkanPhysicalDeviceTypes.h"
#include "VulkanPhysicalDeviceMemory.hpp"
#include "VulkanQueueFamily.hpp"

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

			PhysicalDevice(VkPhysicalDevice physicalDeviceHandle) noexcept;

			Void Initialize() noexcept;

			constexpr PhysicalDeviceType Type() const noexcept { return type; }
			constexpr MultibyteString Name() const noexcept { return name; }
			constexpr UInt32 VendorID() const noexcept { return vendorID; }
			constexpr UInt32 DeviceID() const noexcept { return deviceID; }
			inline Version DriverVersion() const noexcept { return driverVersion; }
			inline Version VulkanVersion() const noexcept { return vulkanVersion; }
		
			constexpr Bool HasGraphicsQueue() const noexcept { return std::ranges::any_of(std::as_const(queueFamilies), [](auto queueFamily) { return queueFamily->SupportOperation(QueueOperation::Graphics); }); }

			inline Rc<PhysicalDeviceMemory> GetMemory() const noexcept { return memory; }
			inline Vector<Rc<QueueFamily>> GetQueueFamilies() const noexcept { return queueFamilies; }

			constexpr VkPhysicalDevice GetHandle() const noexcept { return handle; }
		private:
			Void InitializeMemory() noexcept;
			Void InitializeQueueFamilies() noexcept;
		private:
			VkPhysicalDevice handle = VK_NULL_HANDLE;
		private:
			PhysicalDeviceType type;
			MultibyteString name;
			UInt32 deviceID, vendorID;
			Version driverVersion, vulkanVersion;
		private:
			Rc<PhysicalDeviceMemory> memory;
			Vector<Rc<QueueFamily>> queueFamilies;
		};
	}
}

#endif