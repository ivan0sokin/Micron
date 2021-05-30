#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_EXTENSION_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_EXTENSION_HPP

#include "utility/VulkanUtilities.h"

namespace Micron
{
    namespace Vulkan
    {
        class Extension
        {
        public:
            inline Extension() noexcept = default;
            inline ~Extension() noexcept = default;

            constexpr Extension(VkExtensionProperties const &extensionProperties) noexcept :
                name(extensionProperties.extensionName), specificationVersion(extensionProperties.specVersion)
            {
                TrimString(this->name);
            }

            constexpr MultibyteString GetName() const noexcept { return name; }
            constexpr UInt32 GetSpecificationVersion() const noexcept { return specificationVersion; }
        private:
            MultibyteString name;
            UInt32 specificationVersion;
        };
    }
}

#endif