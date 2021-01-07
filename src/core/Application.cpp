#include "Application.h"

namespace Micron
{
	Void Application::StartUp() noexcept
	{
		this->InitializeCoreLogger();
		this->LogIfDescriptionHasAnError();

		CoreLogger->Info("Application \"{}\" started up", applicationDescription.name);

		this->LogEngineDescription();
		this->LogPlatformDescription();

		this->InitializeWindow();

		this->TryOpenTheWindowOrExtraShutDown();
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
		if (applicationDescription.name.empty())
			CoreLogger->Warn("Application name is empty");

		if (applicationDescription.windowTitle.empty())
			CoreLogger->Warn("Window title is empty");

		UInt32 const minimumWindowWidth = ApplicationInformation::MinimumWindowResolution().width;
		UInt32 const minimumWindowHeight = ApplicationInformation::MinimumWindowResolution().height;

		if (applicationDescription.windowResolution.width < minimumWindowWidth || applicationDescription.windowResolution.height < minimumWindowHeight)
		{
			CoreLogger->Error("Invalid window resolution. Resetting to minimum values");
			applicationDescription.windowResolution = ApplicationInformation::MinimumWindowResolution();
		}
	}

	Void Application::InitializeCoreLogger() noexcept
	{
		CoreLogger = MakeBox<Logger>(CoreLoggerInformation::Name());
	}

	Void Application::LogEngineDescription() noexcept
	{
		Version const engineVersion = EngineInformation::LatestStableVersion();

		CoreLogger->Info
		(
			"Current Micron version: {0}.{1}.{2}",
			engineVersion.major, engineVersion.minor, engineVersion.patch
		);
	}

	Void Application::LogPlatformDescription() noexcept
	{
		CoreLogger->Info
		(
			"Current platform: {}",
			ToString(EngineInformation::CurrentPlatform())
		);
	}

	Void Application::InitializeWindow() noexcept
	{
		window = MakeBox<Window>(applicationDescription.windowTitle, applicationDescription.windowResolution);
	}

	Void Application::TryOpenTheWindowOrExtraShutDown() noexcept
	{
		if (!window->Open())
		{
			CoreLogger->Critical("Failed to open the window");
			MICRON_EXTRA_SHUTDOWN();
		}
	}

	Void Application::SetApplicationName(StringView name) noexcept
	{
		if (name.empty())
			CoreLogger->Warn("Application name is empty");

		applicationDescription.name = name;
	}

	Void Application::SetWindowTitle(StringView title) noexcept
	{
		if (title.empty())
			CoreLogger->Warn("Window title is empty");

		applicationDescription.windowTitle = title;
		window->SetTitle(applicationDescription.windowTitle);
		CoreLogger->Info("Window title changed to \"{}\"", applicationDescription.windowTitle);
	}

	Void Application::SetWindowWidth(UInt32 width) noexcept
	{
		UInt32 const minimumWindowWidth = ApplicationInformation::MinimumWindowResolution().width;

		if (width < minimumWindowWidth)
		{
			CoreLogger->Error("Invalid window width");

			if (applicationDescription.windowResolution.width < minimumWindowWidth)
			{
				CoreLogger->Info("Setting window width to minimum value");
				applicationDescription.windowResolution.width = ApplicationInformation::MinimumWindowResolution().width;
			}
			else
				CoreLogger->Info("Window width has not changed");
		}

		applicationDescription.windowResolution.width = width;
		window->SetWidth(applicationDescription.windowResolution.width);
		CoreLogger->Info("Window width changed to {} pixels", applicationDescription.windowResolution.width);
	}

	Void Application::SetWindowHeight(UInt32 height) noexcept
	{
		UInt32 const minimumWindowHeight = ApplicationInformation::MinimumWindowResolution().height;

		if (height < minimumWindowHeight)
		{
			CoreLogger->Error("Invalid window height");

			if (applicationDescription.windowResolution.height < minimumWindowHeight)
			{
				CoreLogger->Info("Setting window height to minimum value");
				applicationDescription.windowResolution.height = ApplicationInformation::MinimumWindowResolution().height;
			}
			else
				CoreLogger->Info("Window height has not changed");
		}

		applicationDescription.windowResolution.height = height;
		window->SetHeight(applicationDescription.windowResolution.height);
		CoreLogger->Info("Window height changed to {} pixels", applicationDescription.windowResolution.height);
	}

	Void Application::SetWindowResolution(Resolution const &resolution) noexcept
	{
		this->SetWindowWidth(resolution.width);
		this->SetWindowHeight(resolution.height);
		window->SetResolution(resolution);
	}

	Void Application::ResetApplicationDescriptionToDefault() noexcept
	{
		applicationDescription = ApplicationDescription::Default();
		window->SetTitle(applicationDescription.windowTitle);
		window->SetWidth(applicationDescription.windowResolution.width);
		window->SetHeight(applicationDescription.windowResolution.height);
	}
}