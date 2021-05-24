#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_QUEUE_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_QUEUE_HPP

#include "utility/VulkanUtilities.h"

namespace Micron
{
    namespace Vulkan
    {
        class Queue
        {
        public: 
            inline Queue() noexcept = default;
            inline ~Queue() noexcept = default;

            Queue(VkQueue queueHandle) noexcept :
                handle(queueHandle)
            {}
        private:
            VkQueue handle;
        };
    }
}

#endif