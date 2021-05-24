#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_QUEUE_OPERATIONS_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_QUEUE_OPERATIONS_HPP

#include "utility/VulkanUtilities.h"

namespace Micron
{
	namespace Vulkan
	{
		enum class QueueOperation : UInt16
		{
			Graphics = VK_QUEUE_GRAPHICS_BIT,
			Compute = VK_QUEUE_COMPUTE_BIT,
			Transfer = VK_QUEUE_TRANSFER_BIT,
			SparseBinding = VK_QUEUE_SPARSE_BINDING_BIT
		};
	}
}

#endif