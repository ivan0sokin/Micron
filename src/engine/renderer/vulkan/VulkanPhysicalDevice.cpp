#include "VulkanPhysicalDevice.h"

namespace Micron
{
	namespace Vulkan
	{
		Void PhysicalDevice::Initialize() noexcept
		{
			VkPhysicalDeviceProperties physicalDeviceProperties = {};
			vkGetPhysicalDeviceProperties(this->handle, &physicalDeviceProperties);

			properties = MakeRc<PhysicalDeviceProperties>(physicalDeviceProperties);
		}

		Void PhysicalDevice::InitializeMemory() noexcept
		{
			VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = {};
			vkGetPhysicalDeviceMemoryProperties(this->handle, &physicalDeviceMemoryProperties);
			
			memoryProperties = MakeRc<PhysicalDeviceMemoryProperties>(physicalDeviceMemoryProperties);
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
		
		Void PhysicalDevice::InitializeExtensions() noexcept
		{
			auto availableExtensionProperties = this->GetAvailableExtensionProperties();

            availableExtensions.reserve(availableExtensionProperties.size());

            std::ranges::for_each(std::as_const(availableExtensionProperties), [&](auto const &extensionProperties)
            {
                availableExtensions.emplace_back(new Extension(extensionProperties));
            });
		}

		Vector<VkExtensionProperties> PhysicalDevice::GetAvailableExtensionProperties() const noexcept
		{
			UInt32 extensionCount = this->GetAvailableExtensionCount();
            auto availableExtensionProperties = Vector<VkExtensionProperties>(extensionCount);

            Utility::Result availableExtensionPropertiesEnumerate = vkEnumerateDeviceExtensionProperties(this->handle, nullptr, &extensionCount, availableExtensionProperties.data());

            if (availableExtensionPropertiesEnumerate.Failed())
            {
                CoreLogger::Error("Failed to enumerate Vulkan device extension properties, message: {}", availableExtensionPropertiesEnumerate.ToString());
                return Vector<VkExtensionProperties>();
            }

            return availableExtensionProperties;
		}
		
		UInt32 PhysicalDevice::GetAvailableExtensionCount() const noexcept
		{
			UInt32 extensionCount = 0;

            Utility::Result extensionCountRetrieve = vkEnumerateDeviceExtensionProperties(this->handle, nullptr, &extensionCount, nullptr);

            if (extensionCountRetrieve.Failed())
            {
                CoreLogger::Error("Failed to retrieve Vulkan device extension properties count, message: {}", extensionCountRetrieve.ToString());
                return -1;
            }

            return extensionCount;
		}

		Rc<LogicalDevice> PhysicalDevice::CreateLogicalDevice(UnorderedSet<UInt32> const &queueFamilyIndices) noexcept
		{
			return createdLogicalDevices.emplace_back(new LogicalDevice(this->handle, queueFamilyIndices));
		}
		
		Bool PhysicalDevice::SupportExtensions(Set<MultibyteString> extensionNames) noexcept
		{
			std::ranges::for_each(std::as_const(availableExtensions), [&](auto extension)
			{
				extensionNames.erase(extension->GetName().c_str());
			});

			Bool extensionsSupported = extensionNames.empty();

			if (!extensionsSupported)
				CoreLogger::Error("Extensions {} are not supported", fmt::join(extensionNames, ", "));

			return extensionsSupported;
		}
	}
}
