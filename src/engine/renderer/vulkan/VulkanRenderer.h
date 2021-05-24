#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H

#include "../APIRenderer.h"

#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"

namespace Micron
{
	class VulkanRenderer : public APIRenderer
	{
	public:
		inline VulkanRenderer() noexcept = default;
		inline ~VulkanRenderer() noexcept = default;

		Void Initialize() noexcept override;
		Void Destroy() noexcept override;

		constexpr API GetAPI() const noexcept override { return API::Vulkan; }
	private:
		Void InitializeInstance() noexcept;
		Void DestroyInstance() noexcept;

		Void InitializePhysicalDevices() noexcept;

		Void InitializeLogicalDevice() noexcept;
		Void CreateLogicalDevice() noexcept;
		Void InitializeLogicalDeviceQueues() noexcept;
		Void DestroyLogicalDevice() noexcept;
	private:
		Rc<Vulkan::Instance> instance;
		Vector<Rc<Vulkan::PhysicalDevice>> physicalDevices;
		USize pickedPhysicalDeviceIndex = 0;
		Box<Vulkan::LogicalDevice> logicalDevice;
	};
}

#endif