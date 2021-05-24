#include "Extensions.h"

#include "Result.hpp"

#if defined MICRON_CURRENT_PLATFORM_LINUX
	#include <vulkan/vulkan_xlib.h>
#elif defined MICRON_CURRENT_PLATFORM_WINDOWS
	#include <vulkan/vulkan_win32.h>
#elif defined MICRON_CURRENT_PLATFORM_MACOS
	#include <vulkan/vulkan_macos.h>
#endif

namespace Micron
{
	namespace Vulkan
	{
		namespace Utility
		{
			Vector<VkExtensionProperties> GetAvailableInstanceExtensionProperties() noexcept
			{
				UInt32 extensionCount = 0;
				{
					Utility::Result extensionCountRetrieve = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
					
					if (extensionCountRetrieve.Failed())
					{
						CoreLogger::Error("Failed to retrieve Vulkan instance extension count, message: {}", extensionCountRetrieve.ToString());
						return Vector<VkExtensionProperties>();
					}
				}

				Vector<VkExtensionProperties> availableInstanceExtensionProperties = Vector<VkExtensionProperties>(extensionCount);
				{
					Utility::Result instanceExtensionPropertiesEnumerate = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableInstanceExtensionProperties.data());
					
					if (instanceExtensionPropertiesEnumerate.Failed())
					{
						CoreLogger::Error("Failed to enumerate Vulkan instance extension properties, message: {}", instanceExtensionPropertiesEnumerate.ToString());
						return Vector<VkExtensionProperties>();
					}
				}

				return availableInstanceExtensionProperties;
			}

			Vector<NullTerminatedConstantString> GetPlatformDependentInstanceExtensionNames() noexcept
			{
				#if defined MICRON_CURRENT_PLATFORM_LINUX
					return { VK_KHR_XLIB_SURFACE_EXTENSION_NAME };
				#elif defined MICRON_CURRENT_PLATFORM_WINDOWS
					return { VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
				#elif defined MICRON_CURRENT_PLATFORM_MACOS
					return { VK_MVK_MACOS_SURFACE_EXTENSION_NAME };
				#endif

				_MICRON_ASSERT(false);
			}

			Vector<NullTerminatedConstantString> GetRequiredInstanceExtensionNames() noexcept
			{
				Vector<NullTerminatedConstantString> requiredInstanceExtensionNames = { VK_KHR_SURFACE_EXTENSION_NAME };

				auto platformDependentExtensionNames = GetPlatformDependentInstanceExtensionNames();
				requiredInstanceExtensionNames.insert(requiredInstanceExtensionNames.begin(), platformDependentExtensionNames.begin(), platformDependentExtensionNames.end());

				return requiredInstanceExtensionNames;
			}
		}
	}
}