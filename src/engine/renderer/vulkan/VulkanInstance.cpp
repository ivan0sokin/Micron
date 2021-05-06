#include "VulkanInstance.h"

#include "../../application/Application.h"
#include "../../Engine.h"

namespace Micron
{
	namespace Vulkan
	{
		Void Instance::Initialize() noexcept
		{
			auto applicationInstance = Application::GetInstance();

			VkApplicationInfo applicationInfo = {};
			applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			applicationInfo.pApplicationName = applicationInstance->GetName().data();
			applicationInfo.applicationVersion = Utility::ToVulkanVersion(applicationInstance->GetVersion());
			applicationInfo.pEngineName = Engine::Name().data();
			applicationInfo.engineVersion = Utility::ToVulkanVersion(Engine::DevelopingVersion());
			applicationInfo.apiVersion = VK_API_VERSION_1_2;

			auto enabledExtensions = this->PickEnabledExtensions();
			auto enabledLayers = this->PickEnabledLayers();

			VkInstanceCreateInfo instanceCreateInfo = {};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &applicationInfo;
			instanceCreateInfo.enabledExtensionCount = static_cast<UInt32>(enabledExtensions.size());
			instanceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();
			instanceCreateInfo.enabledLayerCount = static_cast<UInt32>(enabledLayers.size());
			instanceCreateInfo.ppEnabledLayerNames = enabledLayers.data();
			
			Utility::Result instanceCreate = vkCreateInstance(&instanceCreateInfo, nullptr, &this->instance);

			if (instanceCreate.Succeeded())
			{
				CoreLogger::Info("Vulkan instance initialized");
				return;
			}
			
			CoreLogger::Critical("Failed to initialize Vulkan instance, message: {}", instanceCreate.ToString());
			_MICRON_SHUTDOWN();
		}

		Vector<NullTerminatedConstantString> Instance::PickEnabledExtensions() noexcept
		{
			if (Utility::CheckRequiredExtensionsAreUnavailable())
			{
				CoreLogger::Critical("Required Vulkan instance extensions are unavailable");
				_MICRON_SHUTDOWN();
			}

			Vector<NullTerminatedConstantString> requiredExtensions = Utility::GetRequiredInstanceExtensionNames();

			Vector<NullTerminatedConstantString> enabledExtensions;
			enabledExtensions.insert(enabledExtensions.begin(), requiredExtensions.begin(), requiredExtensions.end());

			return enabledExtensions;
		}

		Vector<NullTerminatedConstantString> Instance::PickEnabledLayers() noexcept
		{
			Vector<NullTerminatedConstantString> validationLayers;
			if (Utility::ValidationLayersEnabled() && Utility::CheckValidationLayersAreAvailable())
				validationLayers = Utility::GetValidationLayerNames();

			Vector<NullTerminatedConstantString> enabledLayers;
			enabledLayers.insert(enabledLayers.begin(), validationLayers.begin(), validationLayers.end());

			return enabledLayers;
		}

		Void Instance::Destroy() noexcept
		{
			vkDestroyInstance(this->instance, nullptr);
		}
	}
}