#include "VulkanRenderer.h"

#include "../../application/Application.h"
#include "../../Engine.h"

namespace Micron
{
	Void VulkanRenderer::Initialize() noexcept
	{
		this->CreateInstance();
		this->InitializePhysicalDevices();
		this->InitializeLogicalDevice();
		this->CreateSurface();

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

		if (std::ranges::none_of(std::as_const(physicalDevices), [](auto physicalDevice) { return physicalDevice->HasGraphicsQueue(); }))
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
		logicalDevice = MakeBox<Vulkan::LogicalDevice>(physicalDevices[pickedPhysicalDeviceIndex], instance->GetEnabledLayers());

		auto queueFamilies = physicalDevices[pickedPhysicalDeviceIndex]->GetQueueFamilies();
		logicalDevice->SetQueueFamilyIndices(
		{
			(*std::ranges::find_if(std::as_const(queueFamilies), [](auto const &queueFamily)
			{
				return queueFamily->SupportOperation(Vulkan::QueueOperation::Graphics);
			}))->Index()
		});

		logicalDevice->Create();
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
		this->DestroySurface();
		this->DestroyLogicalDevice();
		this->DestroyInstance();

		CoreLogger::Info("Vulkan renderer destroyed");
	}
}