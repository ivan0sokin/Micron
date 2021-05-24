#ifndef _MICRON_ENTRYPOINT_H
#define _MICRON_ENTRYPOINT_H

#include "engine/Engine.h"

using namespace Micron;

auto CollectCommandLineArguments(Int32 argc, NullTerminatedString *argv) noexcept -> Vector<MultibyteStringView>;

auto main(Int32 argc, NullTerminatedString *argv) -> signed
{
    Engine micronEngine = Engine(Application::GetInstance());

    Vector<MultibyteStringView> commandLineArguments = CollectCommandLineArguments(argc, argv);
    micronEngine.Start(commandLineArguments);
    
    return 0;
}

auto CollectCommandLineArguments(Int32 argc, NullTerminatedString *argv) noexcept -> Vector<MultibyteStringView>
{
    Vector<MultibyteStringView> result;

    USize argumentCount = static_cast<USize>(argc) - 1;
    if (argumentCount == 0)
        result.emplace_back("None");

    result.reserve(argumentCount);

    std::ranges::for_each(argv, argv + argumentCount, [&](auto argument)
    {
        result.emplace_back(argument);
    });


    return result;
}

#endif