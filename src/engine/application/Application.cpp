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
		CoreLogger::Info("Application \"{0}\" ver. {1}.{2}.{3} started up", name, version.major, version.minor, version.patch);

		this->LogEngineDescription();
		this->LogPlatformDescription();

		this->InitializeWindow();

		this->OnInitialize();

		this->TryOpenTheWindowOrExtraShutdown();
		Renderer::Initialize();

		timer.Reset();
		while (isRunning)
		{
			timer.Update();
			window->ProcessInputEvents();
			this->OnUserUpdate(timer.GetDeltaTime());
		}

		this->OnDestroy();

		Renderer::Destroy();
		window->Close();
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
		window = MakeRc<Window>();
	}

	Void Application::TryOpenTheWindowOrExtraShutdown() noexcept
	{
		if (!window->Open())
		{
			CoreLogger::Critical("Failed to open the window");
			_MICRON_SHUTDOWN();
		}
	}

	Rc<Window> Application::GetWindow() noexcept
	{
		if (!window)
		{
			CoreLogger::Critical("Can't pass window pointer. Window is unitialized");
			_MICRON_SHUTDOWN();
		}

		return window;
	}
}