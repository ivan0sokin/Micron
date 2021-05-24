#include "Layers.h"

#include "Result.hpp"

namespace Micron
{
	namespace Vulkan
	{
		namespace Utility
		{
			Vector<VkLayerProperties> GetAvailableInstanceLayerProperties() noexcept
			{
				UInt32 layerCount = 0;
				{
					Utility::Result layerCountRetrieve = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

					if (layerCountRetrieve.Failed())
					{
						CoreLogger::Error("Failed to retrieve Vulkan instance layer count, message: {}", layerCountRetrieve.ToString());
						return Vector<VkLayerProperties>();
					}
				}

				Vector<VkLayerProperties> availableInstanceLayerProperties = Vector<VkLayerProperties>(layerCount);
				{
					Utility::Result instanceLayerPropertiesEnumerate = vkEnumerateInstanceLayerProperties(&layerCount, availableInstanceLayerProperties.data());

					if (instanceLayerPropertiesEnumerate.Failed())
					{
						CoreLogger::Error("Failed to enumerate Vulkan instance layer properties, message: {}", instanceLayerPropertiesEnumerate.ToString());
						return Vector<VkLayerProperties>();
					}
				}

				return availableInstanceLayerProperties;
			}
			
			Vector<NullTerminatedConstantString> GetValidationLayerNames() noexcept
			{
				return
				{
					"VK_LAYER_KHRONOS_validation"
				};
			}
		}
	}
}