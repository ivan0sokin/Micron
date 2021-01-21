#ifndef _MICRON_ENGINE_ENGINE_H
#define _MICRON_ENGINE_ENGINE_H

#include "application/Application.h"

namespace Micron
{
	class Engine
	{
	public:
		inline Engine(Rc<Application> application) noexcept :
			application{ application }
		{}

		Void Start(Vector<MultibyteStringView> const &preLaunchCommandLineArguments) noexcept;

		constexpr static Version LatestStableVersion() noexcept { return Version { 0, 0, 3 }; }
		constexpr static Version DevelopingVersion() noexcept { return Version{ 0, 0, 4 }; }
		constexpr static Array<Platform, 1> SupportedPlatforms() noexcept { return { Platform::Windows }; }
		constexpr static Platform CurrentPlatform() noexcept { return MICRON_CURRENT_PLATFORM; }
	private:
		Rc<Application> application;
	};
}

#endif