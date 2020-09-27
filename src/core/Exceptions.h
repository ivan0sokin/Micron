#ifndef _MICRON_EXCEPTIONS_H
#define _MICRON_EXCEPTIONS_H

#include <string>
#include <string_view>

namespace Micron
{
    class Exception
    {
    public:
        Exception(std::string const &prefix = "Basic exception") noexcept;
        Exception(std::string_view message, std::string const &prefix = "Basic exception") noexcept;
        virtual ~Exception() noexcept = default;

        std::string_view What() const noexcept;
    protected:
        std::string message;
    };

    class CoreException : public Exception
    {
    public:
        CoreException() noexcept;
        CoreException(std::string_view message) noexcept;
        virtual ~CoreException() noexcept override = default;
    };
}

#endif