#ifndef _MICRON_CORE_INFORMATION_H
#define _MICRON_CORE_INFORMATION_H

#include "Version.h"
#include "Platform.h"

namespace Micron
{
	class EngineInformation
	{
	public:
		constexpr static Version const & LatestStableVersion() noexcept { return latestStableVersion; }
		constexpr static Array<Platform, 2> const & SupportedPlatforms() noexcept { return supportedPlatforms; }
		constexpr static Platform CurrentPlatform() noexcept { return currentPlatform; }
	private:
		constexpr static Version latestStableVersion = Version(0, 0, 3);
		constexpr static Array<Platform, 2> supportedPlatforms = { Platform::Windows, Platform::Linux };
		constexpr static Platform currentPlatform = MICRON_CURRENT_PLATFORM;
	};
	
	class CoreLoggerInformation
	{
	public:
		inline static String const & Name() noexcept { return name; }
	private:
		inline static String const name = "MICRON";
	};

	struct Resolution
	{
		UInt32 width, height;
	};

	class ApplicationInformation
	{
	public:
		inline static String const & DefaultName() noexcept { return defaultName; }
		inline static String const & DefaultWindowTitle() noexcept { return defaultWindowTitle; }
		constexpr static Resolution MinimumWindowResolution() noexcept { return minimumWindowResolution; }
	private:
		inline static String const defaultName = "Nameless application";
		inline static String const defaultWindowTitle = "Titleless window";
		inline static Resolution minimumWindowResolution = { 500, 500 };
	};
}

#endif