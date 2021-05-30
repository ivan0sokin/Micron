#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_LAYER_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_LAYER_HPP

#include "utility/VulkanUtilities.h"

namespace Micron
{
    namespace Vulkan
    {
        class Layer
        {
        public:
            inline Layer() noexcept = default;
            inline ~Layer() noexcept = default;
        
            constexpr Layer(VkLayerProperties const &layerProperties) noexcept :
                name(layerProperties.layerName), specificationVersion(Utility::ToMicronVersion(layerProperties.specVersion)), implementationVersion(layerProperties.implementationVersion), description(layerProperties.description)
            {
                TrimString(this->name);
                TrimString(this->description);
            }

            constexpr MultibyteString GetName() const noexcept { return name; }
            constexpr Version GetSpecificationVersion() const noexcept { return specificationVersion; }
            constexpr UInt32 GetImplementationVersion() const noexcept { return implementationVersion; }
            constexpr MultibyteString GetDescription() const noexcept { return description; }
        private:
            MultibyteString name;
            Version specificationVersion;
            UInt32 implementationVersion;
            MultibyteString description;
        };
    }
}

#endif