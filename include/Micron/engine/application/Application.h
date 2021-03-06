#ifndef _MICRON_CORE_APPLICATION_H
#define _MICRON_CORE_APPLICATION_H

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
        Void InitializeWindow() noexcept;
        Void LogEngineDescription() noexcept;
        Void LogPlatformDescription() noexcept;
        Void TryOpenTheWindowOrExtraShutdown() noexcept;
    private:
        virtual Void OnInitialize() noexcept = 0;
        virtual Void OnUserUpdate(Real32 deltaTime) noexcept = 0;
        virtual Void OnDestroy() noexcept = 0;
    protected:
        Rc<Window> GetWindow() noexcept;
    protected:
        MultibyteString name = "Something Ends, Something Begins";
    private:
        Bool isRunning = true;
        Console console;
        Rc<Window> window;
        Timer timer;
    };
}

#endif