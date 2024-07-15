#pragma once

//defines a window for both desktop and mobile

#include <BTDSTD/OS.hpp>
#include <BTDSTD/Math/Vectors.hpp>
#include <BTDSTD/Logger.hpp>


#include <vulkan/vulkan.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace BTD::Graphics
{
	//defines a desktop window create info
	struct DesktopWindow_CreateInfo
	{
		BTD::Math::I32Vec2 size = { 800, 600 }; //the size of the window, ignored if full screen
		bool isFullScreen = false; //should it started full screened

		//the callbacks
		GLFWwindowclosefun onWindowCloseCallback = nullptr;
		GLFWframebuffersizefun onWindowResizeCallback = nullptr;

		const char* name = "Test"; //the name of the window
	};

	//defines a desktop window
	struct DesktopWindow
	{
		BTD::Math::I32Vec2 size = { 800, 600 }; //the size of the window
		
		bool hasBeenResized = false; //has the window been resized
		bool isFullScreen = false; //is the window full screened
		bool isRunning = false; //is the window active

		GLFWwindow* window = nullptr; //window pointer
		VkSurfaceKHR surface = VK_NULL_HANDLE; //surface pointer

		//creates a window
		inline bool Create(const DesktopWindow_CreateInfo* info)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

			window = glfwCreateWindow(info->size.x, info->size.y, info->name, NULL, NULL);
			if (!window)
			{
				BTD::Util::Logger::LogFatalErrorToConsole("BTDSTD", "Windows", "Desktop Window", "Create", "Failed to create a window");
				return false;
			}

			//sets the callbacks
			if (info->onWindowCloseCallback)
				glfwSetWindowCloseCallback(window, info->onWindowCloseCallback);
			if (info->onWindowResizeCallback)
				glfwSetFramebufferSizeCallback(window, info->onWindowResizeCallback);
			//if (info->onWindowKeyboardInputCallback)
			//	glfwSetKeyCallback(window, info->onWindowKeyboardInputCallback);

			//stores a window pointer
			isRunning = true;
			glfwSetWindowUserPointer(window, this);

			return true;
		}

		//shutsdown the window
		inline void Shutdown()
		{
			//we're already closed
			if (!isRunning)
				return;

			glfwSetWindowShouldClose(window, true);
			isRunning = false;
		}
		
		//destroys the window
		inline void Destroy()
		{
			//if the window is running we shut it down
			if (isRunning)
				Shutdown();

			if (window)
			{
				glfwDestroyWindow(window); window = nullptr;
			}
		}

		//creates surface
		inline bool CreateSurface(VkInstance& vulkanInstance)
		{
			if (glfwCreateWindowSurface(vulkanInstance, window, nullptr, &surface) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogFatalErrorToConsole("BTDSTD", "Windows", "Desktop Window", "CreateSurface", "Failed to create window surface");
				return false;
			}

			return true;
		}

		//destroys surface
		inline void DestroySurface(VkInstance& vulkanInstance)
		{
			if (surface == VK_NULL_HANDLE)
				return;

			vkDestroySurfaceKHR(vulkanInstance, surface, nullptr);
		}

		//resizes the window
		inline void Resize(const int32 width, const int32 height)
		{
			size = { width, height }; hasBeenResized = true;
		}
	};
}