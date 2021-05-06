#ifndef _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_RESULT_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_UTILITY_RESULT_HPP

#include "VkResultToString.hpp"

namespace Micron
{
	namespace Vulkan
	{
		namespace Utility
		{
			class Result
			{
			public:
				inline Result() noexcept = default;
				inline ~Result() noexcept = default;

				constexpr Result(VkResult const &result) noexcept { wrappedValue = result; }

				inline Bool Succeeded() const noexcept { return wrappedValue == VK_SUCCESS; }
				inline Bool Failed() const noexcept { return static_cast<Int32>(wrappedValue) < 0; }

				inline MultibyteString ToString() const noexcept { return Utility::ToString(wrappedValue); }
			private:
				VkResult wrappedValue;
			};
		}
	}
}

#endif