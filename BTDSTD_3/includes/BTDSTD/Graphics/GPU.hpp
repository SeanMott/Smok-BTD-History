#pragma once

//defines a GPU

#include <BTDSTD/Vender/VkBootstrap.h>

#include <BTDSTD/Graphics/Window.hpp>

namespace BTD::Graphics
{
	//defines a GPU create info
	struct GPU_CreateInfo
	{
		bool isDebug = false; //is it in debug mode

		//feature set
		VkPhysicalDeviceVulkan13Features* features13 = nullptr;
		VkPhysicalDeviceVulkan12Features* features12 = nullptr;

		const char* appName = "";
	};

	//defines a GPU
	struct GPU
	{
		VkInstance vulkanInstance = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT vulkanDebugLogger = VK_NULL_HANDLE;
		
		VkDevice device = VK_NULL_HANDLE;
		VkPhysicalDevice chosenGPU = VK_NULL_HANDLE;

		VkQueue graphicsQueue = VK_NULL_HANDLE, presentQueue = VK_NULL_HANDLE;
		uint32_t graphicsQueueFamily = 0, presentQueueFamily = 0;

		//creates the GPU
		inline bool Create(DesktopWindow* window, const GPU_CreateInfo* info)
		{
			//creates a vulakn instance
			vkb::InstanceBuilder instanceBuilder;
			vkb::Instance vkbInst = instanceBuilder.set_app_name(info->appName)
				.request_validation_layers(info->isDebug)
				.use_default_debug_messenger()
				.require_api_version(1, 3, 0).build().value();
			if (vkbInst.instance == VK_NULL_HANDLE)
			{
				BTD::Util::Logger::LogFatalErrorToConsole("BTDSTD", "Windows", "GPU", "Create", "Failed to init Vulkan instance");
				return false;
			}
			vulkanInstance = vkbInst.instance;
			vulkanDebugLogger = vkbInst.debug_messenger;

			//creates the surface
			if (!window->CreateSurface(vulkanInstance))
			{
				//clean up instance
				vkb::destroy_debug_utils_messenger(vulkanInstance, vulkanDebugLogger);
				vkDestroyInstance(vulkanInstance, nullptr);
				return false;
			}

			//use vkbootstrap to select a gpu. 
			vkb::PhysicalDeviceSelector selector{ vkbInst };
			selector = selector.set_minimum_version(1, 3);
				
			if (info->features13)
				selector = selector.set_required_features_13(*(info->features13));
			if (info->features12)
				selector = selector.set_required_features_12(*(info->features12));

			vkb::PhysicalDevice physicalDevice = selector.set_surface(window->surface).select().value();

			//create the final vulkan device
			vkb::DeviceBuilder deviceBuilder{ physicalDevice };

			vkb::Device vkbDevice = deviceBuilder.build().value();
			if (vkbDevice.device == VK_NULL_HANDLE)
			{
				window->DestroySurface(vulkanInstance);

				//clean up instance
				vkb::destroy_debug_utils_messenger(vulkanInstance, vulkanDebugLogger);
				vkDestroyInstance(vulkanInstance, nullptr);

				BTD::Util::Logger::LogFatalErrorToConsole("BTDSTD", "Windows", "GPU", "Create", "Failed to get GPU");
				return false;
			}

			// Get the VkDevice handle used in the rest of a vulkan application
			device = vkbDevice.device;
			chosenGPU = physicalDevice.physical_device;

			// use vkbootstrap to get a Graphics queue
			graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
			graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

			return true;
		}

		//destroys the GPU
		inline void Destroy(BTD::Graphics::DesktopWindow* window)
		{
			//destroys a GPU
			if(device != VK_NULL_HANDLE)
				vkDestroyDevice(device, nullptr);

			window->DestroySurface(vulkanInstance);

			//clean up instance
			if (vulkanInstance != VK_NULL_HANDLE)
			{
				vkb::destroy_debug_utils_messenger(vulkanInstance, vulkanDebugLogger);
				vkDestroyInstance(vulkanInstance, nullptr);
			}
		}
	};
}