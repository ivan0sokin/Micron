#include "Engine.h"

namespace Micron
{
	Void Engine::Start(Vector<MultibyteStringView> const &preLaunchCommandLineArguments) noexcept
	{
		_MICRON_DEBUG_LOG("Command line arguments: {}", fmt::join(preLaunchCommandLineArguments, " "));
		application->ProcessPreLaunchCommandLineArguments(preLaunchCommandLineArguments);
		application->Launch();
	}	
}