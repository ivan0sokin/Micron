#ifndef _MICRON_CORE_APPLICATION_H
#define _MICRON_CORE_APPLICATION_H

#include "types/BasicTypes.h"
#include "../window/Window.h"

namespace Micron
{
    struct ApplicationDescription
    {
        StringView name;
        StringView windowTitle;
        Resolution windowResolution;

        inline static ApplicationDescription Default() noexcept
        {
            return ApplicationDescription
            {
                ApplicationInformation::DefaultName(), ApplicationInformation::DefaultWindowTitle(),
                ApplicationInformation::MinimumWindowResolution()
            };
        }
    };

    class Application
    {
        friend class ::Micron::Input;
    public:

    public:
        inline Application() noexcept = default;
        virtual ~Application() noexcept = default;

        Void StartUp() noexcept;
        constexpr Void ShutDown() noexcept { isRunning = false; }

        inline ApplicationDescription const & GetDescription() noexcept { return applicationDescription; }

        static Rc<Application> GetInstance() noexcept;
    private:
        Void LogIfDescriptionHasAnError() noexcept;
        Void InitializeCoreLogger() noexcept;
        Void LogEngineDescription() noexcept;
        Void LogPlatformDescription() noexcept;
        Void InitializeWindow() noexcept;
        Void TryOpenTheWindowOrExtraShutDown() noexcept;
    private:
        virtual Void OnInitialize() noexcept = 0;
        virtual Void OnUserUpdate() noexcept = 0;
        virtual Void OnDestroy() noexcept = 0;
    protected:
        inline Void InitializeApplicationDescription(ApplicationDescription const &applicationDescription) noexcept { this->applicationDescription = applicationDescription; }

        Void SetApplicationName(StringView name) noexcept;
        Void SetWindowTitle(StringView title) noexcept; // TODO: Finish those functions
        Void SetWindowWidth(UInt32 width) noexcept; 
        Void SetWindowHeight(UInt32 height) noexcept;
        Void SetWindowResolution(Resolution const &resolution) noexcept;
        Void ResetApplicationDescriptionToDefault() noexcept;
    private:
        Bool isRunning = true;
        ApplicationDescription applicationDescription;
        Box<Window> window;
    };
}

#endif