#include "VulkanRenderer.h"

#include "../../application/Application.h"
#include "../../Engine.h"

namespace Micron
{
	Void VulkanRenderer::Initialize() noexcept
	{
		instance.Initialize();

		CoreLogger::Info("Vulkan Renderer initialized");
	}

	Void VulkanRenderer::Destroy() noexcept
	{
		CoreLogger::Info("Vulkan Renderer destroyed");
	}
}