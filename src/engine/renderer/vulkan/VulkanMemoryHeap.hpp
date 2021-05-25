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
				size(memoryHeap.size), isDeviceLocal(static_cast<Bool>(memoryHeap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)), multiInstance(static_cast<Bool>(memoryHeap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT))
			{}

			constexpr USize Size() const noexcept { return size; }
			constexpr Bool IsDeviceLocal() const noexcept { return isDeviceLocal; }
			constexpr Bool MultiInstance() const noexcept { return multiInstance; }
		private:
			USize size;
			Bool isDeviceLocal;
			Bool multiInstance;
		};
	}
}

#endif