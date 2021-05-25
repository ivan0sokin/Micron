#include "VulkanInstance.h"

#include "../../Engine.h"

namespace Micron
{
	namespace Vulkan
	{
		Void Instance::Create() noexcept
		{
			VkInstanceCreateInfo instanceCreateInfo = {};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

			VkApplicationInfo applicationInfo = this->PickApplicationInfo();
			instanceCreateInfo.pApplicationInfo = &applicationInfo;

			this->InitializeEnabledLayers();
			instanceCreateInfo.enabledLayerCount = static_cast<UInt32>(enabledLayers.size());
			instanceCreateInfo.ppEnabledLayerNames = enabledLayers.data();

			this->InitializeEnabledExtensions();
			instanceCreateInfo.enabledExtensionCount = static_cast<UInt32>(enabledExtensions.size());
			instanceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();

			Utility::Result instanceCreate = vkCreateInstance(&instanceCreateInfo, nullptr, &this->handle);

			if (instanceCreate.Failed())
			{
				CoreLogger::Critical("Failed to initialize Vulkan instance, message: {}", instanceCreate.ToString());
				_MICRON_SHUTDOWN();
			}

			CoreLogger::Info("Vulkan instance created");
		}

		VkApplicationInfo Instance::PickApplicationInfo() const noexcept
		{
			auto applicationInstance = Application::GetInstance();
			
			VkApplicationInfo applicationInfo = {};
			applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			applicationInfo.pApplicationName = applicationInstance->GetName().data();
			applicationInfo.applicationVersion = Utility::ToVulkanVersion(applicationInstance->GetVersion());
			applicationInfo.pEngineName = Engine::Name().data();
			applicationInfo.engineVersion = Utility::ToVulkanVersion(Engine::DevelopingVersion());
			applicationInfo.apiVersion = VK_API_VERSION_1_2;

			return applicationInfo;
		}

		Void Instance::InitializeEnabledLayers() noexcept
		{
			Vector<NullTerminatedConstantString> validationLayers;
			if (Utility::ValidationLayersEnabled() && this->CheckValidationLayersAreAvailable())
				validationLayers = Utility::GetValidationLayerNames();

			enabledLayers.insert(enabledLayers.cbegin(), validationLayers.cbegin(), validationLayers.cend());
		}
		
		Bool Instance::CheckValidationLayersAreAvailable() const noexcept
		{
			auto validationLayers = Utility::GetValidationLayerNames();
			auto availableLayers = this->GetAvailableLayerNames();

			return std::ranges::all_of(std::as_const(validationLayers), [&](auto const &layer)
			{
				Bool layerFound = std::ranges::find(std::as_const(availableLayers), layer) != availableLayers.cend();

				if (!layerFound)
					CoreLogger::Error("Layer \"{}\" was not found", layer);

				return layerFound;
			});
		}
		
		Vector<MultibyteString> Instance::GetAvailableLayerNames() const noexcept
		{
			auto availableInstanceLayerProperties = Utility::GetAvailableInstanceLayerProperties();

			Vector<MultibyteString> availableLayerNames;

			availableLayerNames.reserve(availableInstanceLayerProperties.size());

			std::ranges::for_each(std::as_const(availableInstanceLayerProperties), [&](auto const &layerProperties)
			{
				availableLayerNames.emplace_back(layerProperties.layerName);
			});

			return availableLayerNames;
		}

		Void Instance::InitializeEnabledExtensions() noexcept
		{
			if (!this->CheckRequiredExtensionsAreAvailable())
			{
				CoreLogger::Critical("Required Vulkan instance extensions are unavailable");
				_MICRON_SHUTDOWN();
			}

			Vector<NullTerminatedConstantString> requiredExtensions = Utility::GetRequiredInstanceExtensionNames();

			enabledExtensions.insert(enabledExtensions.cbegin(), requiredExtensions.cbegin(), requiredExtensions.cend());
		}
		
		Bool Instance::CheckRequiredExtensionsAreAvailable() const noexcept
		{
			auto requiredExtensions = Utility::GetRequiredInstanceExtensionNames();
			auto availableExtensions = this->GetAvailableExtensionNames();

			return std::ranges::all_of(std::as_const(requiredExtensions), [&](auto const &extension)
			{
				Bool extensionFound = std::ranges::find(std::as_const(availableExtensions), extension) != availableExtensions.cend();

				if (!extensionFound)
					CoreLogger::Error("Extension \"{}\" was not found", extension);

				return extensionFound;
			});
		}
		
		Vector<MultibyteString> Instance::GetAvailableExtensionNames() const noexcept
		{
			auto availableInstanceExtensionProperties = Utility::GetAvailableInstanceExtensionProperties();

			Vector<MultibyteString> availableInstanceExtensionNames;

			availableInstanceExtensionNames.reserve(availableInstanceExtensionProperties.size());

			std::ranges::for_each(std::as_const(availableInstanceExtensionProperties), [&](auto const &extensionProperties)
			{
				availableInstanceExtensionNames.emplace_back(extensionProperties.extensionName);
			});

			return availableInstanceExtensionNames;
		}
		
		Vector<VkPhysicalDevice> Instance::GetPhysicalDeviceHandles() const noexcept
		{
			UInt32 physicalDeviceCount = 0;
			{
				Utility::Result physicalDeviceCountRetrieve = vkEnumeratePhysicalDevices(this->handle, &physicalDeviceCount, nullptr);

				if (physicalDeviceCountRetrieve.Failed())
				{
					CoreLogger::Error("Failed to retrieve physical device count, message: {}", physicalDeviceCountRetrieve.ToString());
					return Vector<VkPhysicalDevice>();
				}
			}
			
			if (physicalDeviceCount == 0)
			{
				CoreLogger::Critical("Failed to find physical devices with Vulkan support");
				_MICRON_SHUTDOWN();
			}

			Vector<VkPhysicalDevice> physicalDeviceHandles = Vector<VkPhysicalDevice>(physicalDeviceCount);
			{
				Utility::Result physicalDeviceEnumerate = vkEnumeratePhysicalDevices(this->handle, &physicalDeviceCount, physicalDeviceHandles.data());

				if (physicalDeviceEnumerate.Failed())
				{
					CoreLogger::Error("Failed to enumerate physical devices, message: {}", physicalDeviceEnumerate.ToString());
					return Vector<VkPhysicalDevice>();
				}
			}

			return physicalDeviceHandles;
		}
		
		Rc<Surface> Instance::CreateSurface() const noexcept
		{
			switch (Engine::CurrentPlatform())
			{
			case Platform::Linux:
				return this->CreateLinuxSurface();
			case Platform::Windows:
				return this->CreateWindowsSurface();
			case Platform::MacOS:
				return this->CreateMacOSSurface();
			default:
				return MakeRc<Surface>();
			}

			_MICRON_ASSERT(false);
		}

		Rc<LinuxSurface> Instance::CreateLinuxSurface() const noexcept
		{
			#if defined MICRON_CURRENT_PLATFORM_LINUX
				auto linuxWindow = DynamicPointerCast<IOLinuxWindow>(this->GetPlatformWindow());
				return MakeRc<LinuxSurface>();
			#endif

			return MakeRc<LinuxSurface>();
		}
		
		Rc<WindowsSurface> Instance::CreateWindowsSurface() const noexcept
		{
			#if defined MICRON_CURRENT_PLATFORM_WINDOWS
				auto win32Window = DynamicPointerCast<IOWin32Window>(this->GetPlatformWindow());
				return MakeRc<WindowsSurface>(this->handle, win32Window->GetWindowHandle(), GetModuleHandle(nullptr));
			#endif

			return MakeRc<WindowsSurface>();
		}
		
		Rc<MacOSSurface> Instance::CreateMacOSSurface() const noexcept
		{
			#if defined MICRON_CURRENT_PLATFORM_MACOS
				auto macOSWindow = DynamicPointerCast<IOMacOSWindow>(this->GetPlatformWindow());
				return MakeRc<MacOSSurface>();
			#endif

			return MakeRc<MacOSSurface>();
		}
		
		Rc<IOPlatformWindow> Instance::GetPlatformWindow() const noexcept
		{
			return Application::GetInstance()->GetWindow()->GetInternalWindow()->GetPlatformWindow();
		}

		Void Instance::Destroy() noexcept
		{
			if (this->handle == nullptr)
			{
				CoreLogger::Error("Can not destroy Vulkan instance, because it is not created");
				return;
			}

			vkDestroyInstance(this->handle, nullptr);
		}
	
	}
}