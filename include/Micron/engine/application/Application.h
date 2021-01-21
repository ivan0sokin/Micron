#ifndef _MICRON_CORE_APPLICATION_H
#define _MICRON_CORE_APPLICATION_H

#include "../core/Core.h"
#include "Console.h"
#include "../window/Window.h"

namespace Micron
{
    class Application
    {
        friend class ::Micron::Console;
        friend class ::Micron::Input;
    public:
        inline Application() noexcept = default;
        virtual ~Application() noexcept = default;

        Void ProcessPreLaunchCommandLineArguments(Vector<MultibyteStringView> const &arguments) noexcept;
        Void Launch() noexcept;
        constexpr Void Shutdown() noexcept { isRunning = false; }

        static Rc<Application> GetInstance() noexcept;
    private:
        Void InitializeConsole() noexcept;
        Void LogIfDescriptionHasAnError() noexcept;
        Void LogEngineDescription() noexcept;
        Void LogPlatformDescription() noexcept;
        Void InitializeWindow() noexcept;
        Void TryOpenTheWindowOrExtraShutdown() noexcept;
        Bool CheckWindowIsInitializedOrError(MultibyteStringView errorMessage) noexcept;
    private:
        virtual Void OnInitialize() noexcept = 0;
        virtual Void OnUserUpdate() noexcept = 0;
        virtual Void OnDestroy() noexcept = 0;
    protected:
        Bool SetWindowTitle(UnicodeStringView title) noexcept;
        Bool SetWindowResolution(Resolution const &resolution) noexcept;
        Bool SetWindowPosition(Position const &position) noexcept;
        Bool SetWindowPositionCentered() noexcept;
        Void SetWindowMinimumResolution(Resolution const &resolution) noexcept;
        Void SetWindowMaximumResolution(Resolution const &resolution) noexcept;
        Void SetWindowMaximumPosition(Position const &position) noexcept;

        Void ResetWindowPropertiesToDefaults() noexcept;
    protected:
        MultibyteString name = "Something Ends, Something Begins";
        UnicodeString initialWindowTitle = L"Loose ends";
        Resolution initialWindowResolution = { 0, 0 };
    private:
        Bool isRunning = true;
        Console console;
        Box<Window> window;
    };
}

#endif