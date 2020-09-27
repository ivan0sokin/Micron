#include "Exceptions.h"

namespace Micron
{
    Exception::Exception(std::string const &prefix) noexcept :
        message(prefix + "Unknown exception")
    {}

    Exception::Exception(std::string_view message, std::string const &prefix) noexcept :
        message(prefix + message.data())
    {}

    std::string_view Exception::What() const noexcept
    {
        return message;
    }

    CoreException::CoreException() noexcept :
        Exception(std::string("Core exception: "))
    {}
    CoreException::CoreException(std::string_view message) noexcept :
        Exception(message, "Core exception: ")
    {}
}