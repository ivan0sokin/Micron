#include "Application.h"
#include "../Engine.h"

namespace Micron
{
	Void Application::ProcessPreLaunchCommandLineArguments(Vector<MultibyteStringView> const &arguments) noexcept
	{
		this->InitializeConsole();
		std::for_each(arguments.begin(), arguments.end(), [&](auto argument){ console.ExecuteCommand(argument); });
	}

	Void Application::InitializeConsole() noexcept
	{
		console.Initialize();
	}

	Void Application::Launch() noexcept
	{
		this->LogIfDescriptionHasAnError();

		CoreLogger::Info("Application \"{}\" started up", name);

		this->LogEngineDescription();
		this->LogPlatformDescription();

		this->InitializeWindow();

		this->TryOpenTheWindowOrExtraShutdown();
		this->OnInitialize();

		Timer::Reset();
		while (isRunning)
		{
			Timer::Update();
			window->ProcessInputEvents();
			this->OnUserUpdate();
		}

		this->OnDestroy();
		window->Close();
	}

	Void Application::LogIfDescriptionHasAnError() noexcept
	{
		if (name.empty())
			CoreLogger::Warn("Application name is empty");

		if (initialWindowTitle.empty())
			CoreLogger::Warn("Window title is empty");

		/*if (initialWindowResolution.width == 0 || initialWindowResolution.height < minimumWindowResolution.height)
		{
			CoreLogger::Critical("Invalid initial window resolution");
			MICRON_EXTRA_SHUTDOWN();
		}*/
	}

	Void Application::LogEngineDescription() noexcept
	{
		Version const engineVersion = Engine::LatestStableVersion();

		CoreLogger::Info
		(
			"Current Micron version: {0}.{1}.{2}",
			engineVersion.major, engineVersion.minor, engineVersion.patch
		);
	}

	Void Application::LogPlatformDescription() noexcept
	{
		CoreLogger::Info
		(
			"Current platform: {}",
			ToString(Engine::CurrentPlatform())
		);
	}

	Void Application::InitializeWindow() noexcept
	{
		window = MakeBox<Window>(initialWindowTitle, initialWindowResolution);
	}

	Void Application::TryOpenTheWindowOrExtraShutdown() noexcept
	{
		if (!window->Open())
		{
			CoreLogger::Critical("Failed to open the window");
			MICRON_EXTRA_SHUTDOWN();
		}
	}

	Bool Application::CheckWindowIsInitializedOrError(MultibyteStringView errorMessage) noexcept
	{
		if (!window)
		{
			CoreLogger::Error(errorMessage);
			return false;
		}

		return true;
	}

	Bool Application::SetWindowTitle(UnicodeStringView title) noexcept
	{
		if (title.empty())
			CoreLogger::Warn("Window title is empty");

		Bool windowTitleChanged = window->SetTitle(title);
		if (windowTitleChanged)
			CoreLogger::Info("Window title changed");
	
		return windowTitleChanged;
	}
	
	Bool Application::SetWindowResolution(Resolution const &resolution) noexcept
	{
		Bool windowResolutionChanged = window->SetResolution(resolution);
		if (windowResolutionChanged)
			CoreLogger::Info("Window resolution changed to {0}x{1}", resolution.width, resolution.height);

		return windowResolutionChanged;
	}

	Bool Application::SetWindowPosition(Position const &position) noexcept
	{
		Bool windowPositionChanged = window->SetPosition(position);
		if (windowPositionChanged)
			CoreLogger::Info("Window position chaned to ({0}, {1})", position.x, position.y);

		return windowPositionChanged;
	}

	Bool Application::SetWindowPositionCentered() noexcept
	{
		Bool windowPositionCentered = window->SetPositionCentered();
		if (windowPositionCentered)
			CoreLogger::Info("Window position centered");

		return windowPositionCentered;
	}

	Void Application::SetWindowMinimumResolution(Resolution const &resolution) noexcept
	{
		if (CheckWindowIsInitializedOrError("Unable to set minimum window resolution. Window is uninitialized"))
			window->SetMinimumResolution(resolution);
	}

	Void Application::SetWindowMaximumResolution(Resolution const &resolution) noexcept
	{
		if (CheckWindowIsInitializedOrError("Unable to set maximum window resolution. Window is uninitialized"))
			window->SetMaximumResolution(resolution);
	}

	Void Application::SetWindowMaximumPosition(Position const &position) noexcept
	{
		if (CheckWindowIsInitializedOrError("Unable to set maximum window position. Window is uninitialized"))
			window->SetMaximumPosition(position);
	}

	Void Application::ResetWindowPropertiesToDefaults() noexcept
	{
		if (CheckWindowIsInitializedOrError("Unable to reset window properties to default. Window is uninitialized"))
		{
			window->SetTitle(Window::DefaultTitle());
			window->SetResolution(Window::DefaultResolution());
			window->SetPositionCentered();
			CoreLogger::Info("Window properties reset to default");
		}
	}
}