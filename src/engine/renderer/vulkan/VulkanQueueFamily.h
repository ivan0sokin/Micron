#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_QUEUE_FAMILY_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_QUEUE_FAMILY_H

#include "VulkanQueueOperations.h"
#include "VulkanSurface.h"

namespace Micron
{
	namespace Vulkan
	{
		class QueueFamily
		{
		public:
			inline QueueFamily() noexcept = default;
			inline ~QueueFamily() noexcept = default;

			QueueFamily(VkPhysicalDevice physicalDeviceHandle, UInt32 queueFamilyIndex, VkQueueFamilyProperties const &queueFamilyProperties) noexcept;

			constexpr UInt32 Index() const noexcept { return index; }
			constexpr UInt32 QueueCount() const noexcept { return queueCount; }

			Bool SupportPresentationToSurface(Rc<Surface> surface) const noexcept;

			Vector<QueueOperation> SupportedOperations() const noexcept { return supportedOperations; }
			constexpr Bool SupportOperation(QueueOperation const &operation) const noexcept { return std::ranges::any_of(std::as_const(supportedOperations), [&](auto const &queueOperation){ return queueOperation == operation; }); }
		private:
			VkPhysicalDevice physicalDeviceHandle = VK_NULL_HANDLE;
			UInt32 index;
			UInt32 queueCount;
			Vector<QueueOperation> supportedOperations;
		};
	}
}

#endif