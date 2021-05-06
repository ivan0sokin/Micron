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
					Utility::Result eExtensionCountRetrieve = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
					
					if (eExtensionCountRetrieve.Failed())
					{
						CoreLogger::Error("Failed to retrieve Vulkan instance extension count, message: {}", eExtensionCountRetrieve.ToString());
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

			Vector<MultibyteString> GetAvailableInstanceExtensionNames() noexcept
			{
				auto availableInstanceExtensionProperties = GetAvailableInstanceExtensionProperties();

				USize extensionCount = availableInstanceExtensionProperties.size();
				Vector<MultibyteString> availableInstanceExtensionNames = Vector<MultibyteString>(extensionCount);

				for (USize i = 0; i < extensionCount; ++i)
				{
					availableInstanceExtensionNames[i] = availableInstanceExtensionProperties[i].extensionName;
				}

				return availableInstanceExtensionNames;
			}

			Bool CheckRequiredExtensionsAreUnavailable() noexcept
			{
				auto requiredExtensions = GetRequiredInstanceExtensionNames();
				auto availableExtensions = GetAvailableInstanceExtensionNames();

				Bool allExtensionsFound = true;
				for (auto const &extension : requiredExtensions)
				{
					if (std::find(availableExtensions.begin(), availableExtensions.end(), extension) != availableExtensions.end())
						CoreLogger::Info("Extension \"{}\" was found", extension);
					else
					{
						CoreLogger::Error("Extension \"{}\" was not found", extension);
						allExtensionsFound = false;
					}
				}

				return !allExtensionsFound;
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
				requiredInstanceExtensionNames.reserve(platformDependentExtensionNames.size());

				for (auto &&extension : platformDependentExtensionNames)
				{
					requiredInstanceExtensionNames.emplace_back(extension);
				}

				return requiredInstanceExtensionNames;
			}
		}
	}
}