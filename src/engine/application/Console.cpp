#include "Console.h"
#include "Application.h"

namespace Micron
{
	Void Micron::Console::Initialize() noexcept
	{
		application = Application::GetInstance();
	}

	Void Micron::Console::ExecuteCommand(MultibyteStringView command) noexcept
	{

	}
}