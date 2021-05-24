#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_MEMORY_HEAP_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_MEMORY_HEAP_HPP

#include "utility/VulkanUtilities.h"

namespace Micron
{
	namespace Vulkan
	{
		class MemoryHeap
		{
		public:
			inline MemoryHeap() noexcept = default;
			inline ~MemoryHeap() noexcept = default;

			constexpr MemoryHeap(VkMemoryHeap const &memoryHeap) noexcept :
				heap(memoryHeap)
			{}

			constexpr USize Size() const noexcept { return heap.size; }
			constexpr Bool IsDeviceLocal() const noexcept { return static_cast<Bool>(heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT); }
			constexpr Bool IsSingleInstance() const noexcept { return !static_cast<Bool>(heap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT); }
		private:
			VkMemoryHeap heap;
		};
	}
}

#endif