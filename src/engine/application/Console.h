#ifndef _MICRON_ENGINE_APPLICATION_CONSOLE_H
#define _MICRON_ENGINE_APPLICATION_CONSOLE_H

#include "../core/Core.h"

namespace Micron
{
	class Application;

	class Console
	{
	public:
		Void Initialize() noexcept;
		Void ExecuteCommand(MultibyteStringView command) noexcept;
	private:
		Rc<Application> application;
	};
}

#endif