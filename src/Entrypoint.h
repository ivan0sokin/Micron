#ifndef _MICRON_CORE_ENTRYPOINT_H
#define _MICRON_CORE_ENTRYPOINT_H

#include "engine/Engine.h"

using namespace Micron;

Vector<MultibyteStringView> ParseCommandLineArguments(Int32 argc, Char **argv) noexcept;

int main(Int32 argc, Char **argv)
{
    Engine micronEngine = Engine(Application::GetInstance());

    Vector<MultibyteStringView> commandLineArguments = ParseCommandLineArguments(argc, argv);
    micronEngine.Start(commandLineArguments);

    return 0;
}

Vector<MultibyteStringView> ParseCommandLineArguments(Int32 argc, Char **argv) noexcept
{
    Vector<MultibyteStringView> result;

    USize numArguments = static_cast<USize>(argc - 1);
    if (numArguments == 0)
        result.emplace_back("None");

    result.reserve(numArguments);

    for (USize i = 1; i < argc; ++i)
        result.emplace_back(argv[i]);

    return result;
}

#endif