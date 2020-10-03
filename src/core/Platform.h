#ifndef _MICRON_PLATFORM_H
#define _MICRON_PLATFORM_H

#define MICRON_PLATFORM_LINUX 0
#define MICRON_PLATFORM_WINDOWS 1
#define MICRON_PLATFORM_MACOS 2

#if defined(__linux__) && !defined(__ANDROID__)
    #define MICRON_PLATFORM MICRON_PLATFORM_LINUX
    #define MICRON_PLATOFRM_STRING "Linux"
#elif defined(_WIN32) || defined(_WIN64)
    #define MICRON_PLATFORM MICRON_PLATFORM_WINDOWS
    #define MICRON_PLATFORM_STRING "Windows"
#elif defined(__APPLE__)
    #define MICRON_PLATFORM MICRON_PLATFORM_MACOS
    #define MICRON_PLATFORM_STRING "Mac OS"
#else
    #error "Current platform is not supported"
#endif

#endif