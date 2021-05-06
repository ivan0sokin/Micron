#include "Renderer.h"

#include "vulkan/VulkanRenderer.h"

namespace Micron
{
	Void Renderer::SetGraphicsAPI(API const &api) noexcept
	{
		Renderer::api = api;
	}

	Void Renderer::Initialize() noexcept
	{
		if (apiRenderer)
		{
			CoreLogger::Critical("API Renderer is already initialized");
			return;
		}

		switch (api)
		{
		case API::Vulkan:
			apiRenderer = MakeBox<VulkanRenderer>();
			break;
		case API::DirectX:
			break;
		default:
			break;
		}

		apiRenderer->Initialize();
	}

	Void Renderer::Destroy() noexcept
	{
		if (!apiRenderer)
		{
			CoreLogger::Critical("API Renderer is not initialized yet");
			return;
		}

		apiRenderer->Destroy();
	}
}