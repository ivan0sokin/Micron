#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H

#include "../APIRenderer.h"
#include "VulkanInstance.h"

namespace Micron
{
	class VulkanRenderer : public APIRenderer
	{
	public:
		inline VulkanRenderer() noexcept = default;
		inline ~VulkanRenderer() noexcept = default;

		Void Initialize() noexcept override;
		Void Destroy() noexcept override;

		constexpr API GetAPI() const noexcept override { return API::Vulkan; }
	private:
		Vulkan::Instance instance;
	};
}

#endif