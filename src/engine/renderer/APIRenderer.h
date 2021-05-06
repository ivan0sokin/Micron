#ifndef _MICRON_ENGINE_RENDERER_API_RENDERER_H
#define _MICRON_ENGINE_RENDERER_API_RENDERER_H

#include "../core/Core.h"

namespace Micron
{
	enum class API : UInt16
	{
		None = 0,
		Vulkan,
		DirectX
	};

	class APIRenderer
	{
	public:
		APIRenderer() noexcept = default;
		virtual ~APIRenderer() noexcept = default;

		virtual Void Initialize() noexcept = 0;
		virtual Void Destroy() noexcept = 0;

		virtual constexpr API GetAPI() const noexcept { return API::None; }
	};
}

#endif