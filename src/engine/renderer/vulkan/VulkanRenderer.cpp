#include "VulkanRenderer.h"

#include "../../application/Application.h"
#include "../../Engine.h"

namespace Micron
{
	Void VulkanRenderer::Initialize() noexcept
	{
		this->CreateInstance();
		this->CreateSurface();
		this->InitializePhysicalDevices();
		this->InitializeLogicalDevice();

		CoreLogger::Info("Vulkan renderer initialized");
	}
	
	Void VulkanRenderer::CreateInstance() noexcept
	{
		instance = MakeBox<Vulkan::Instance>();
		instance->Create();
	}
	
	Void VulkanRenderer::DestroyInstance() noexcept
	{
		instance->Destroy();
		instance.reset();
	}
	
	Void VulkanRenderer::InitializePhysicalDevices() noexcept
	{
		auto physicalDeviceHandles = instance->GetPhysicalDeviceHandles();

		physicalDevices.reserve(physicalDeviceHandles.size());

		std::ranges::for_each(std::as_const(physicalDeviceHandles), [&](auto physicalDeviceHandle)
		{
			physicalDevices.emplace_back(new Vulkan::PhysicalDevice(physicalDeviceHandle));
			physicalDevices.back()->Initialize();
		});

		if (std::ranges::none_of(std::as_const(physicalDevices), [](auto physicalDevice) { return physicalDevice->HasGraphicsQueueFamily(); }))
		{
			CoreLogger::Critical("None of Vulkan physical devices can render");
			_MICRON_SHUTDOWN();
		}
	}
	
	Void VulkanRenderer::InitializeLogicalDevice() noexcept
	{
		this->CreateLogicalDevice();
		this->InitializeLogicalDeviceQueues();
	}
	
	Void VulkanRenderer::CreateLogicalDevice() noexcept
	{
		logicalDevice = physicalDevices[pickedPhysicalDeviceIndex]->CreateLogicalDevice();

		logicalDevice->SetEnabledLayers(instance->GetEnabledLayers());

		auto queueFamilyIndices = this->PickQueueFamilyIndices();
		logicalDevice->SetQueueFamilyIndices(queueFamilyIndices);

		logicalDevice->Create();
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

	Void VulkanRenderer::InitializeLogicalDeviceQueues() noexcept
	{
		logicalDevice->InitializeQueues();
	}
	
	Void VulkanRenderer::DestroyLogicalDevice() noexcept
	{
		logicalDevice->Destroy();
		logicalDevice.reset();
	}
	
	Void VulkanRenderer::CreateSurface() noexcept
	{
		surface = instance->CreateSurface();
		surface->Create();
	}
	
	Void VulkanRenderer::DestroySurface() noexcept
	{
		surface->Destroy();
		surface.reset();
	}

	Void VulkanRenderer::Destroy() noexcept
	{
		this->DestroyLogicalDevice();
		this->DestroySurface();
		this->DestroyInstance();

		CoreLogger::Info("Vulkan renderer destroyed");
	}
}