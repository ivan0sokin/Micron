#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_QUEUE_FAMILY_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_QUEUE_FAMILY_HPP

#include "VulkanQueueOperations.h"

namespace Micron
{
	namespace Vulkan
	{
		class QueueFamily
		{
		public:
			inline QueueFamily() noexcept = default;
			inline ~QueueFamily() noexcept = default;

			constexpr QueueFamily(UInt32 queueFamilyIndex, VkQueueFamilyProperties const &queueFamilyProperties) noexcept :
				index(queueFamilyIndex), queueCount(queueFamilyProperties.queueCount)
			{
				for (USize i = 1; i < 16; i *= 2)
				{
					if (i & queueFamilyProperties.queueFlags)
						supportedOperations.push_back(static_cast<QueueOperation>(i));
				}
			}
			
			constexpr UInt32 Index() const noexcept { return index; }
			constexpr UInt32 QueueCount() const noexcept { return queueCount; }

			Vector<QueueOperation> SupportedOperations() const noexcept { return supportedOperations; }
			constexpr Bool SupportOperation(QueueOperation const &operation) const noexcept { return std::ranges::any_of(std::as_const(supportedOperations), [&](auto const &queueOperation){ return queueOperation == operation; }); }
		private:
			UInt32 index;
			UInt32 queueCount;
			Vector<QueueOperation> supportedOperations;
		};
	}
}

#endif