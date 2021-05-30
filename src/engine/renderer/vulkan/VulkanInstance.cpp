#include "VulkanInstance.h"

#include "../../Engine.h"

namespace Micron
{
	namespace Vulkan
	{
		Void Instance::InitializeLayers() noexcept
		{
			auto availableLayerProperties = this->GetAvailableLayerProperties();

			availableLayers.reserve(availableLayerProperties.size());

			std::ranges::for_each(std::as_const(availableLayerProperties), [&](auto const &layerProperties)
			{
				availableLayers.emplace_back(new Layer(layerProperties));
			});
		}
		
		Vector<VkLayerProperties> Instance::GetAvailableLayerProperties() const noexcept
		{
			UInt32 layerCount = this->GetAvailableLayerCount();

			Vector<VkLayerProperties> availableLayerProperties = Vector<VkLayerProperties>(layerCount);

			Utility::Result layerPropertiesEnumerate = vkEnumerateInstanceLayerProperties(&layerCount, availableLayerProperties.data());

			if (layerPropertiesEnumerate.Failed())
			{
				CoreLogger::Error("Failed to enumerate Vulkan instance layer properties, message: {}", layerPropertiesEnumerate.ToString());
				return Vector<VkLayerProperties>();
			}

			return availableLayerProperties;
		}
		
		UInt32 Instance::GetAvailableLayerCount() const noexcept
		{
			UInt32 layerCount = 0;

			Utility::Result layerCountRetrieve = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			if (layerCountRetrieve.Failed())
			{
				CoreLogger::Error("Failed to retrieve Vulkan instance layer count, message: {}", layerCountRetrieve.ToString());
				return -1;
			}

			return layerCount;
		}

		Void Instance::InitializeExtensions() noexcept
		{
			auto availableExtensionProperties = this->GetAvailableExtensionProperties();

			availableExtensions.reserve(availableExtensionProperties.size());

			std::ranges::for_each(std::as_const(availableExtensionProperties), [&](auto const &extensionProperties)
			{
				availableExtensions.emplace_back(new Extension(extensionProperties));
			});
		}
	
		Vector<VkExtensionProperties> Instance::GetAvailableExtensionProperties() const noexcept
		{
			UInt32 extensionCount = this->GetAvailableExtensionCount();

			Vector<VkExtensionProperties> availableExtensionProperties = Vector<VkExtensionProperties>(extensionCount);
				
			Utility::Result extensionPropertiesEnumerate = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensionProperties.data());
			
			if (extensionPropertiesEnumerate.Failed())
			{
				CoreLogger::Error("Failed to enumerate Vulkan instance extension properties, message: {}", extensionPropertiesEnumerate.ToString());
				return Vector<VkExtensionProperties>();
			}
				
			return availableExtensionProperties;
		}
		
		UInt32 Instance::GetAvailableExtensionCount() const noexcept
		{
			UInt32 extensionCount = 0;
				
			Utility::Result extensionCountRetrieve = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
			
			if (extensionCountRetrieve.Failed())
			{
				CoreLogger::Error("Failed to retrieve Vulkan instance extension count, message: {}", extensionCountRetrieve.ToString());
				return -1;
			}

			return extensionCount;
		}

		Void Instance::Create() noexcept
		{
			VkInstanceCreateInfo instanceCreateInfo = {};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

			VkApplicationInfo applicationInfo = this->PickApplicationInfo();
			instanceCreateInfo.pApplicationInfo = &applicationInfo;

			this->InitializeEnabledLayerNames();
			instanceCreateInfo.enabledLayerCount = static_cast<UInt32>(enabledLayerNames.size());
			instanceCreateInfo.ppEnabledLayerNames = enabledLayerNames.data();

			this->InitializeEnabledExtensionNames();
			instanceCreateInfo.enabledExtensionCount = static_cast<UInt32>(enabledExtensionNames.size());
			instanceCreateInfo.ppEnabledExtensionNames = enabledExtensionNames.data();

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

		Void Instance::InitializeEnabledLayerNames() noexcept
		{
			if (Instance::validationLayersEnabled && this->CheckValidationLayersAreAvailable())
				enabledLayerNames.insert(enabledLayerNames.cbegin(), Instance::validationLayerNames.cbegin(), Instance::validationLayerNames.cend());
		}
		
		Bool Instance::CheckValidationLayersAreAvailable() const noexcept
		{
			auto availableLayerNames = this->GetAvailableLayerNames();

			return std::ranges::all_of(std::as_const(Instance::validationLayerNames), [&](auto layerName)
			{
				Bool layerFound = std::ranges::find(std::as_const(availableLayerNames), layerName) != availableLayerNames.cend();

				if (!layerFound)
					CoreLogger::Error("Layer \"{}\" was not found", layerName);

				return layerFound;
			});
		}
		
		Vector<MultibyteString> Instance::GetAvailableLayerNames() const noexcept
		{
			Vector<MultibyteString> availableLayerNames;
			
			availableLayerNames.reserve(availableLayers.size());

			std::ranges::for_each(std::as_const(availableLayers), [&](auto layer)
			{
				availableLayerNames.emplace_back(layer->GetName());
			});

			return availableLayerNames;
		}

		Void Instance::InitializeEnabledExtensionNames() noexcept
		{
			if (!this->CheckRequiredExtensionsAreAvailable())
			{
				CoreLogger::Critical("Required Vulkan instance extensions are unavailable");
				_MICRON_SHUTDOWN();
			}

			enabledExtensionNames.insert(enabledExtensionNames.cbegin(), Instance::requiredExtensionNames.cbegin(), Instance::requiredExtensionNames.cend());
		}
		
		Bool Instance::CheckRequiredExtensionsAreAvailable() const noexcept
		{
			auto availableExtensionNames = this->GetAvailableExtensionNames();

			return std::ranges::all_of(std::as_const(Instance::requiredExtensionNames), [&](auto const &extensionName)
			{
				Bool extensionFound = std::ranges::find(std::as_const(availableExtensionNames), extensionName) != availableExtensionNames.cend();

				if (!extensionFound)
					CoreLogger::Error("Extension \"{}\" was not found", extensionName);

				return extensionFound;
			});
		}
		
		Vector<MultibyteString> Instance::GetAvailableExtensionNames() const noexcept
		{
			Vector<MultibyteString> availableInstanceExtensionNames;

			availableInstanceExtensionNames.reserve(availableExtensions.size());

			std::ranges::for_each(std::as_const(availableExtensions), [&](auto const &extension)
			{
				availableInstanceExtensionNames.emplace_back(extension->GetName());
			});

			return availableInstanceExtensionNames;
		}
		
		Vector<Rc<PhysicalDevice>> Instance::GetPhysicalDevices() const noexcept
		{
			auto physicalDeviceHandles = this->GetPhysicalDeviceHandles();

			Vector<Rc<PhysicalDevice>> physicalDevices;

			physicalDevices.reserve(physicalDeviceHandles.size());

			std::ranges::for_each(std::as_const(physicalDeviceHandles), [&](auto physicalDeviceHandle)
			{
				physicalDevices.emplace_back(new PhysicalDevice(physicalDeviceHandle));
			});

			return physicalDevices;
		}

		Vector<VkPhysicalDevice> Instance::GetPhysicalDeviceHandles() const noexcept
		{
			UInt32 physicalDeviceCount = this->GetPhysicalDeviceCount();
			
			if (physicalDeviceCount == 0)
			{
				CoreLogger::Critical("Failed to find physical devices with Vulkan support");
				_MICRON_SHUTDOWN();
			}

			Vector<VkPhysicalDevice> physicalDeviceHandles = Vector<VkPhysicalDevice>(physicalDeviceCount);

			Utility::Result physicalDeviceEnumerate = vkEnumeratePhysicalDevices(this->handle, &physicalDeviceCount, physicalDeviceHandles.data());

			if (physicalDeviceEnumerate.Failed())
			{
				CoreLogger::Error("Failed to enumerate physical devices, message: {}", physicalDeviceEnumerate.ToString());
				return Vector<VkPhysicalDevice>();
			}

			return physicalDeviceHandles;
		}

		UInt32 Instance::GetPhysicalDeviceCount() const noexcept
		{
			UInt32 physicalDeviceCount = 0;
			
			Utility::Result physicalDeviceCountRetrieve = vkEnumeratePhysicalDevices(this->handle, &physicalDeviceCount, nullptr);

			if (physicalDeviceCountRetrieve.Failed())
			{
				CoreLogger::Error("Failed to retrieve physical device count, message: {}", physicalDeviceCountRetrieve.ToString());
				return -1;
			}

			return physicalDeviceCount;
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