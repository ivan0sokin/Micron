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

			Vector<MultibyteString> GetAvailableInstanceLayerNames() noexcept
			{
				auto availableInstanceLayerProperties = GetAvailableInstanceLayerProperties();

				USize layerCount = availableInstanceLayerProperties.size();
				Vector<MultibyteString> availableInstanceLayerNames = Vector<MultibyteString>(layerCount);
			
				for (USize i = 0; i < layerCount; ++i)
				{
					availableInstanceLayerNames[i] = availableInstanceLayerProperties[i].layerName;
				}

				return availableInstanceLayerNames;
			}

			Bool CheckValidationLayersAreAvailable() noexcept
			{
				auto validationLayers = GetValidationLayerNames();
				auto availableLayers = GetAvailableInstanceLayerNames();

				Bool allLayersFound = true;
				for (auto const &layer : validationLayers)
				{
					if (std::find(availableLayers.begin(), availableLayers.end(), layer) != availableLayers.end())
						CoreLogger::Info("Layer \"{}\" was found", layer);
					else
					{
						CoreLogger::Error("Layer \"{}\" was not found", layer);
						allLayersFound = false;
					}
				}

				return allLayersFound;
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