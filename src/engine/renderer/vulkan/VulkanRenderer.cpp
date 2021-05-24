#include "VulkanRenderer.h"

#include "../../application/Application.h"
#include "../../Engine.h"

namespace Micron
{
	Void VulkanRenderer::Initialize() noexcept
	{
		this->InitializeInstance();
		this->InitializePhysicalDevices();
		this->InitializeLogicalDevice();

		CoreLogger::Info("Vulkan renderer initialized");
	}
	
	Void VulkanRenderer::InitializeInstance() noexcept
	{
		instance = Vulkan::Instance::GetInstance();
		instance->Initialize();
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
		logicalDevice = MakeBox<Vulkan::LogicalDevice>(physicalDevices[pickedPhysicalDeviceIndex]);

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

	Void VulkanRenderer::Destroy() noexcept
	{
		this->DestroyLogicalDevice();
		this->DestroyInstance();

		CoreLogger::Info("Vulkan renderer destroyed");
	}
}