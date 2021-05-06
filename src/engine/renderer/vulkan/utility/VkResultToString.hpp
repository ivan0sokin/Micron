#ifndef _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_VKRESULT_TO_STRING_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_VKRESULT_TO_STRING_HPP

#include "../../../core/Core.h"

#include <vulkan/vulkan.hpp>

namespace Micron
{
	namespace Vulkan
	{
        namespace Utility
        {
            inline MultibyteString ToString(VkResult const &vkResult) noexcept
            {
                switch (vkResult)
                {
                case VK_SUCCESS:
                    return "Success";
                case VK_NOT_READY:
                    return "Not ready";
                case VK_TIMEOUT:
                    return "Timeout";
                case VK_EVENT_SET:
                    return "Event set";
                case VK_EVENT_RESET:
                    return "Event reset";
                case VK_INCOMPLETE:
                    return "Incomplete";
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                    return "Error { out of host memory }";
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    return "Error { out of device memory }";
                case VK_ERROR_INITIALIZATION_FAILED:
                    return "Error { initialization failed}";
                case VK_ERROR_DEVICE_LOST:
                    return "Error { device lost }";
                case VK_ERROR_MEMORY_MAP_FAILED:
                    return "Error { memory map failed }";
                case VK_ERROR_LAYER_NOT_PRESENT:
                    return "Error { layer not present }";
                case VK_ERROR_EXTENSION_NOT_PRESENT:
                    return "Error { extension not present }";
                case VK_ERROR_FEATURE_NOT_PRESENT:
                    return "Error { feature not present }";
                case VK_ERROR_INCOMPATIBLE_DRIVER:
                    return "Error { incompatible driver }";
                case VK_ERROR_TOO_MANY_OBJECTS:
                    return "Error { too many objects}";
                case VK_ERROR_FORMAT_NOT_SUPPORTED:
                    return "Error { format not supported }";
                case VK_ERROR_FRAGMENTED_POOL:
                    return "Error { fragmented pool }";
                case VK_ERROR_UNKNOWN:
                    return "Error { unknown }";
                case VK_ERROR_OUT_OF_POOL_MEMORY:
                    return "Error { out of pool memory }";
                case VK_ERROR_INVALID_EXTERNAL_HANDLE:
                    return "Error { invalid external handle }";
                case VK_ERROR_FRAGMENTATION:
                    return "Error { fragmentation }";
                case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
                    return "Error { invalid opaque capture adress }";
                case VK_ERROR_SURFACE_LOST_KHR:
                    return "Error { surface lost }";
                case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
                    return "Error { native window in use }";
                case VK_SUBOPTIMAL_KHR:
                    return "Suboptimal";
                case VK_ERROR_OUT_OF_DATE_KHR:
                    return "Error { out of date }";
                case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
                    return "Error { incompatible display }";
                case VK_ERROR_VALIDATION_FAILED_EXT:
                    return "Error { validation failed }";
                case VK_ERROR_INVALID_SHADER_NV:
                    return "Error { invalid shared nv }";
                case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
                    return "Error { invalid drm format modifier plane layout }";
                case VK_ERROR_NOT_PERMITTED_EXT:
                    return "Error { not permitted }";
                case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
                    return "Error { fullscreen exclusive mode lost }";
                case VK_THREAD_IDLE_KHR:
                    return "Thread idle";
                case VK_THREAD_DONE_KHR:
                    return "Thread done";
                case VK_OPERATION_DEFERRED_KHR:
                    return "Operation deffered";
                case VK_OPERATION_NOT_DEFERRED_KHR:
                    return "Operation not deferred";
                case VK_PIPELINE_COMPILE_REQUIRED_EXT:
                    return "Pipeline compile required";
                default:
                    return "Undefined";
                }

                _MICRON_ASSERT(false);
            }
		}
	}
}

#endif