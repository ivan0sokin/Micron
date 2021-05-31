#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H

#include "../APIRenderer.h"

#include "VulkanInstance.h"

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
		Bool CheckNoneOfPhysicalDevicesHasGraphicsQueueFamily() const noexcept;

		Void CreateLogicalDevice() noexcept;
		Void DestroyLogicalDevice() noexcept;
		UnorderedSet<UInt32> PickQueueFamilyIndices() const noexcept;

		Void CreateSurface() noexcept;
		Void DestroySurface() noexcept;
	private:
		Box<Vulkan::Instance> instance;
		Rc<Vulkan::Surface> surface;
		Vector<Rc<Vulkan::PhysicalDevice>> physicalDevices;
		Rc<Vulkan::LogicalDevice> logicalDevice;
	private:
		constexpr static USize pickedPhysicalDeviceIndex = 0;
	};
}

#endif