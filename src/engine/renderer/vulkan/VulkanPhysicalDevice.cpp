#include "VulkanPhysicalDevice.h"

namespace Micron
{
	namespace Vulkan
	{
		PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDeviceHandle) noexcept :
			handle(physicalDeviceHandle)
		{
			VkPhysicalDeviceProperties physicalDeviceProperties = {};
			vkGetPhysicalDeviceProperties(this->handle, &physicalDeviceProperties);

			this->type = static_cast<PhysicalDeviceType>(physicalDeviceProperties.deviceType);

			this->name = physicalDeviceProperties.deviceName;
			TrimString(this->name);

			this->deviceID = physicalDeviceProperties.deviceID;
			this->vendorID = physicalDeviceProperties.vendorID;

			this->driverVersion = Utility::ToMicronVersion(physicalDeviceProperties.driverVersion);
			this->vulkanVersion = Utility::ToMicronVersion(physicalDeviceProperties.apiVersion);
		}

		Void PhysicalDevice::Initialize() noexcept
		{
			this->InitializeMemory();
			this->InitializeQueueFamilies();
		}

		Void PhysicalDevice::InitializeMemory() noexcept
		{
			VkPhysicalDeviceMemoryProperties memoryProperties = {};
			vkGetPhysicalDeviceMemoryProperties(this->handle, &memoryProperties);
			
			memory = MakeRc<PhysicalDeviceMemory>(memoryProperties);
		}

		Void PhysicalDevice::InitializeQueueFamilies() noexcept
		{
			UInt32 queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(this->handle, &queueFamilyCount, nullptr);

			queueFamilies.reserve(queueFamilyCount);

			Vector<VkQueueFamilyProperties> physicalDeviceQueueFamilies = Vector<VkQueueFamilyProperties>(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(this->handle, &queueFamilyCount, physicalDeviceQueueFamilies.data());

			UInt32 queueFamilyIndex = 0;
			std::ranges::for_each(std::as_const(physicalDeviceQueueFamilies), [&](auto const &queueFamilyProperties)
			{
				queueFamilies.emplace_back(new QueueFamily(this->handle, queueFamilyIndex, queueFamilyProperties));

				++queueFamilyIndex;
			});
		}

		Rc<LogicalDevice> PhysicalDevice::CreateLogicalDevice() const noexcept
		{
			return MakeRc<LogicalDevice>(this->handle);
		}
	}
}
