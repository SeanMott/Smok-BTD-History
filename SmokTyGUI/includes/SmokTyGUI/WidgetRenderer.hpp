#pragma once

//defines a widget renderer for debug ImGUI

#include <SmokGraphics/Core/GraphicContext.hpp>
#include <SmokGraphics/Core/GPU.h>

#include <SmokGraphics/Pools/CommandPool.h>
#include <SmokGraphics/RenderCommands/RenderPass.h>

#include <SmokWindow/Desktop/DesktopWindow.h>

namespace Smok::TyGUI::Widget
{
	//defines settings for the widget renderer
	struct WidgetRendererSettings
	{
		bool isDockingEnabled = false; //is docking enabled
		bool isSeprateViewportsEnabled = false; //lets widgets be dragged outsided the window

		//the platform for the widgets
	};

	//defines a widget renderer
	struct WidgetRenderer
	{
		SMWindow_Desktop_Swapchain* swapchain = nullptr;
		SMWindow_Desktop_Window* window = nullptr;

		VkRenderPass renderPass;
		VkDescriptorPool pool;
		VkDevice device;

		SMGraphics_RenderCommands_RenderPass GUIRenderPassSettings;

		bool isDockingEnabled = false; //is docking enabled
		bool isSeprateViewportsEnabled = false; //lets widgets be dragged outsided the window

		//the widget names
		//the widgets drawn, any new ones are drawn

		//inits the widget renderer
		void Init(Smok::Graphics::Core::GraphicsContext* GContex, SMGraphics_Core_GPU* _GPU,
			SMWindow_Desktop_Window* _window, SMWindow_Desktop_Swapchain* _swapchain, SMGraphics_Pool_CommandPool* comPool,
			const WidgetRendererSettings& settings);
		//shutsdown the widget renderer
		void Shutdown();

		//starts a new frame for ImGUI data
		void StartFrame(VkCommandBuffer& comBuffer,
			VkFramebuffer& framebuffer, const BTD_Math_U32Vec2& frameSize);
		//submits the frame into a command buffer
		void SubmitFrame(VkCommandBuffer& comBuffer);

		//starts a dock space
		void StartDockSpace();
		//ends a dock space
		void EndDockSpace();
	};
}