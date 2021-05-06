#ifndef _MICRON_ENGINE_RENDERER_RENDERER_H
#define _MICRON_ENGINE_RENDERER_RENDERER_H

#include "APIRenderer.h"

namespace Micron
{
	class Renderer
	{
	public:
		static Void SetGraphicsAPI(API const &api) noexcept;
		static Void Initialize() noexcept;
		static Void Destroy() noexcept;
	private:
		inline static API api = API::None;
		inline static Box<APIRenderer> apiRenderer;
	};
}

#endif