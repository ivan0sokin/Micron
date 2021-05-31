#include "VulkanRenderer.h"

#include "../../application/Application.h"
#include "../../Engine.h"

namespace Micron
{
	Void VulkanRenderer::Initialize() noexcept
	{
		this->InitializeInstance();

		instance->InitializeSurface();
		this->CreateSurface();
		
		instance->InitializePhysicalDevices();
		this->InitializePhysicalDevices();

		if (this->CheckNoneOfPhysicalDevicesHasGraphicsQueueFamily())
		{
			CoreLogger::Critical("None of Vulkan physical devices can render");
			_MICRON_SHUTDOWN();
		}

		if (!physicalDevices[pickedPhysicalDeviceIndex]->SupportExtensions({ Vulkan::Surface::GetExtensionName() }))
		{
			CoreLogger::Critical("Vulkan physical device does not support surface extension");
			_MICRON_SHUTDOWN();
		}

		this->CreateLogicalDevice();
		logicalDevice->InitializeQueues();
		
		CoreLogger::Info("Vulkan renderer initialized");
	}
	
	Void VulkanRenderer::InitializeInstance() noexcept
	{
		instance = MakeBox<Vulkan::Instance>();
		
		instance->InitializeLayers();
		instance->InitializeExtensions();
		
		instance->CreateHandle();
	}
	
	Void VulkanRenderer::DestroyInstance() noexcept
	{
		instance->DestroyHandle();
		instance.reset();
	}
	
	Void VulkanRenderer::CreateSurface() noexcept
	{
		surface = instance->GetSurface();
		surface->CreateHandle();
	}
	
	Void VulkanRenderer::DestroySurface() noexcept
	{
		surface->DestroyHandle();
		surface.reset();
	}

	Void VulkanRenderer::InitializePhysicalDevices() noexcept
	{
		physicalDevices = instance->GetPhysicalDevices();

		std::ranges::for_each(physicalDevices, [&](auto physicalDevice)
		{
			physicalDevice->Initialize();
			physicalDevice->InitializeMemory();
			physicalDevice->InitializeQueueFamilies();
			physicalDevice->InitializeExtensions();
		});
	}
	
	Bool VulkanRenderer::CheckNoneOfPhysicalDevicesHasGraphicsQueueFamily() const noexcept
	{
		return std::ranges::none_of(std::as_const(physicalDevices), [](auto physicalDevice)
		{
			return physicalDevice->HasGraphicsQueueFamily();
		});
	}
	
	Void VulkanRenderer::CreateLogicalDevice() noexcept
	{
		auto queueFamilyIndices = this->PickQueueFamilyIndices();
		logicalDevice = physicalDevices[pickedPhysicalDeviceIndex]->CreateLogicalDevice(queueFamilyIndices);

		logicalDevice->CreateHandle({ Vulkan::Surface::GetExtensionName().c_str() });
	}
	
	Void VulkanRenderer::DestroyLogicalDevice() noexcept
	{
		logicalDevice->DestroyHandle();
		logicalDevice.reset();
	}

	UnorderedSet<UInt32> VulkanRenderer::PickQueueFamilyIndices() const noexcept
	{
		auto queueFamilies = physicalDevices[pickedPhysicalDeviceIndex]->GetQueueFamilies();

		Rc<Vulkan::QueueFamily> graphicsQueueFamily, presentationQueueFamily;

		std::ranges::for_each(std::as_const(queueFamilies), [&](auto queueFamily)
		{
			if (queueFamily->SupportOperation(Vulkan::QueueOperation::Graphics) && !graphicsQueueFamily)
				graphicsQueueFamily = queueFamily;
			if (queueFamily->SupportPresentationToSurface(this->surface) && !presentationQueueFamily)
				presentationQueueFamily = queueFamily;
		});

		return { graphicsQueueFamily->Index(), presentationQueueFamily->Index() };
	}
	
	Void VulkanRenderer::Destroy() noexcept
	{
		this->DestroyLogicalDevice();
		this->DestroySurface();
		this->DestroyInstance();

		CoreLogger::Info("Vulkan renderer destroyed");
	}
}