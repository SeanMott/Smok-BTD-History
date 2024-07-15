#pragma once

//defines a render manager that handles the frames and render targets

#include <BTDSTD/Graphics/GPU.hpp>

#include <BTDSTD/Graphics/SyncObjects.hpp>
#include <BTDSTD/Vender/vk_mem_alloc.h>


namespace BTD::Renderer
{
#define MAX_POTENCIAL_SYNC_OBJECTS 2

	//defines a frame
	struct RenderManager_Frame
	{
		bool isValid = false;

		uint32 currentFrameIndex;
		VkFence currentFrame_renderFence;
		VkSemaphore currentFrame_swapchainSemaphore;
		VkSemaphore currentFrame_renderSemaphore;
		BTD::Graphics::Buffer::CommandBuffer* comBuffer;
		uint32 swapchainImageIndex;
		VkImage currentFrame_swapchainImage;
		VkImageView currentFrame_swapchainImageView;
	};

	//defines a render manager
	class RenderManager
	{
		//vars
	private:

		bool isInDedicatedRenderPassMode = false;

		uint32 currentFrame = 0;
		uint32 maxFramesInFlight = 0;

		BTD::Graphics::Image::Image renderTarget;
		BTD::Graphics::Image::Image depthRenderTarget;

		BTD::Graphics::Buffer::CommandPool commandPools[MAX_POTENCIAL_SYNC_OBJECTS];
		BTD::Graphics::Buffer::CommandBuffer comBuffers[MAX_POTENCIAL_SYNC_OBJECTS];

		BTD::Graphics::Sync::Semaphore swapchainSemaphores[MAX_POTENCIAL_SYNC_OBJECTS], renderSemaphores[MAX_POTENCIAL_SYNC_OBJECTS];
		BTD::Graphics::Sync::Fence renderFences[MAX_POTENCIAL_SYNC_OBJECTS];

		//methods
	public:

		//inits the render manaager for dedicated render passes
		inline bool DedicatedRenderPassMode_Init(Graphics::GPU* GPU, VmaAllocator& allocator, const Math::UI32Vec2& windowSize, const uint32& _framesInFlightMax)
		{
			maxFramesInFlight = _framesInFlightMax;

			bool failedToCreateObjects = false;

			for (uint32 i = 0; i < maxFramesInFlight; i++)
			{
				//create command pool and allocate command buffer
				if (!commandPools[i].Create(GPU, true))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "DedicatedRenderPassMode_Init", "Failed to create command pool");
					failedToCreateObjects = true;
					break;
				}

				if (!commandPools[i].AllocateCommandBuffers(GPU, &(comBuffers[i]), 1, true))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "DedicatedRenderPassMode_Init", "Failed to allocate command buffer");
					failedToCreateObjects = true;
					break;
				}

				//create sync objects
				if (!renderFences[i].Create(GPU->device))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "DedicatedRenderPassMode_Init", "Failed to create render fence sync object");
					failedToCreateObjects = true;
					break;
				}

				if (!swapchainSemaphores[i].Create(GPU->device))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "DedicatedRenderPassMode_Init", "Failed to create swapchain semaphores sync object");
					failedToCreateObjects = true;
					break;
				}

				if (!renderSemaphores[i].Create(GPU->device))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "DedicatedRenderPassMode_Init", "Failed to create render semaphores sync object");
					failedToCreateObjects = true;
					break;
				}
			}

			//if it failed, clean up anything
			if (failedToCreateObjects)
			{
				DedicatedRenderPassMode_Shutdown(GPU, allocator);
				return false;
			}

			return true;
		}

		//shutsdown the render manager for dedicated render passes
		inline void DedicatedRenderPassMode_Shutdown(Graphics::GPU* GPU, VmaAllocator& allocator)
		{
			//cleans up commands and syncs
			for (int i = 0; i < maxFramesInFlight; i++)
			{
				renderSemaphores[i].Destroy(GPU->device);
				swapchainSemaphores[i].Destroy(GPU->device);
				renderFences[i].Destroy(GPU->device);
				commandPools[i].Destroy(GPU);
			}
		}

		//gets the next frame for dedicated render passes
		inline RenderManager_Frame DedicatedRenderPassMode_GetFrame(Graphics::GPU* GPU, Graphics::DesktopSwapchain* swapchain)
		{
			RenderManager_Frame frame;
			frame.currentFrameIndex = currentFrame % maxFramesInFlight;
			frame.currentFrame_renderFence = renderFences[frame.currentFrameIndex].handle;
			frame.currentFrame_swapchainSemaphore = swapchainSemaphores[frame.currentFrameIndex].handle;
			frame.currentFrame_renderSemaphore = renderSemaphores[frame.currentFrameIndex].handle;
			frame.comBuffer = &comBuffers[frame.currentFrameIndex];

			//wait for the GPU to finish any work from the last frame
			if (vkWaitForFences(GPU->device, 1, &frame.currentFrame_renderFence, true, 1000000000) != VK_SUCCESS)
			{
				//BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "GetNextFrame", "Failed to wait with the render sync fence");
				return frame;
			}

			//request a image from the swapchain
			if (vkAcquireNextImageKHR(GPU->device, swapchain->swapchain, 1000000000, frame.currentFrame_swapchainSemaphore, nullptr, &frame.swapchainImageIndex) != VK_SUCCESS)
			{
				//BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "GetNextFrame", "Failed to retrive a swapchain image for the current frame");
				return frame;
			}
			frame.currentFrame_swapchainImage = swapchain->swapchainImages[frame.swapchainImageIndex];
			frame.currentFrame_swapchainImageView = swapchain->swapchainImageViews[frame.swapchainImageIndex];

			if (vkResetFences(GPU->device, 1, &frame.currentFrame_renderFence) != VK_SUCCESS)
			{
				//BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "GetNextFrame", "Failed to reset render sync fence");
				return frame;
			}

			frame.isValid = true;
			return frame;
		}

		//submits a frame for dedicated render passes
		inline void DedicatedRenderPassMode_SubmitFrame(VkCommandBuffer& comBuffer, 
			RenderManager_Frame& frame, VkQueue& graphicsQueue, VkQueue& presentQueue,
			VkSwapchainKHR* swapchain)
		{
			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

			VkSemaphore waitSemaphores[] = { frame.currentFrame_swapchainSemaphore };
			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = waitSemaphores;
			submitInfo.pWaitDstStageMask = waitStages;

			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &comBuffer;

			VkSemaphore signalSemaphores[] = { frame.currentFrame_renderSemaphore };
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = signalSemaphores;

			if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, frame.currentFrame_renderFence) != VK_SUCCESS) {
				throw std::runtime_error("failed to submit draw command buffer!");
			}

			VkSubpassDependency dependency{};
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0;

			dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask = 0;

			dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

			VkRenderPassCreateInfo renderPassInfo{};
			renderPassInfo.dependencyCount = 1;
			renderPassInfo.pDependencies = &dependency;

			VkPresentInfoKHR presentInfo{};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = signalSemaphores;

			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = swapchain;
			presentInfo.pImageIndices = &frame.swapchainImageIndex;

			presentInfo.pResults = nullptr; // Optional

			vkQueuePresentKHR(graphicsQueue, &presentInfo);

		}

		//gets the render fences
		inline BTD::Graphics::Sync::Fence* GetRenderFences() { return renderFences; }

		//gets the swapchain semaphores
		inline BTD::Graphics::Sync::Semaphore* GetSwapchainSemaphores() { return swapchainSemaphores; }

		//gets the command buffers
		inline BTD::Graphics::Buffer::CommandBuffer* GetCommandBuffers() { return comBuffers; }

	private:

		//creates a render target
		inline bool CreateRenderTarget(VkDevice& device, VmaAllocator& allocator, const Math::UI32Vec2& windowSize)
		{
			//render target size will match the window
			renderTarget.size = {
				windowSize.x,
				windowSize.y,
				1
			};

			//hardcoding the draw format to 32 bit float
			renderTarget.imageFormat = VK_FORMAT_R16G16B16A16_SFLOAT;

			VkImageUsageFlags drawImageUsages{};
			drawImageUsages |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
			drawImageUsages |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			drawImageUsages |= VK_IMAGE_USAGE_STORAGE_BIT;
			drawImageUsages |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			VkImageCreateInfo rimg_info = BTD::Graphics::Image::GenerateInfoStruct_ImageCreateInfo(renderTarget.imageFormat, drawImageUsages, renderTarget.size);

			//for the draw image, we want to allocate it from gpu local memory
			VmaAllocationCreateInfo rimg_allocinfo = {};
			rimg_allocinfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
			rimg_allocinfo.requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			//allocate and create the image
			if (vmaCreateImage(allocator, &rimg_info, &rimg_allocinfo, &renderTarget.image, &renderTarget.allocation, nullptr) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Renderer", "CreateRenderTarget", "Failed to create render target image");
				return false;
			}

			//build a image-view for the draw image to use for rendering
			VkImageViewCreateInfo rview_info = BTD::Graphics::Image::GenerateInfoStruct_ImageViewCreateInfo(renderTarget.imageFormat, renderTarget.image, VK_IMAGE_ASPECT_COLOR_BIT);

			if (vkCreateImageView(device, &rview_info, nullptr, &renderTarget.imageView) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Renderer", "CreateRenderTarget", "Failed to create render target view");
				return false;
			}

			return true;
		}

		//creates a depth render target
		inline bool CreateDepthRenderTarget(VkDevice& device, VmaAllocator& allocator, const Math::UI32Vec2& windowSize)
		{
			//render target size will match the window
			depthRenderTarget.size = {
				windowSize.x,
				windowSize.y,
				1
			};

			//hardcoding the draw format to double 32 bit float
			depthRenderTarget.imageFormat = VK_FORMAT_D32_SFLOAT;

			VkImageUsageFlags drawImageUsages = { 0 };
			drawImageUsages |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

			VkImageCreateInfo rimg_info = BTD::Graphics::Image::GenerateInfoStruct_ImageCreateInfo(depthRenderTarget.imageFormat,
				drawImageUsages, depthRenderTarget.size);

			//for the draw image, we want to allocate it from gpu local memory
			VmaAllocationCreateInfo rimg_allocinfo = {};
			rimg_allocinfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
			rimg_allocinfo.requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			//allocate and create the image
			if (vmaCreateImage(allocator, &rimg_info, &rimg_allocinfo, &depthRenderTarget.image, &depthRenderTarget.allocation, nullptr) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Renderer", "Init", "Failed to create depth render target image");
				return false;
			}

			//build a image-view for the draw image to use for rendering
			VkImageViewCreateInfo rview_info = BTD::Graphics::Image::GenerateInfoStruct_ImageViewCreateInfo(depthRenderTarget.imageFormat, depthRenderTarget.image, VK_IMAGE_ASPECT_DEPTH_BIT);

			if (vkCreateImageView(device, &rview_info, nullptr, &depthRenderTarget.imageView) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Renderer", "Init", "Failed to create depth render target view");
				return false;
			}

			return true;
		}

		//inits the render manager
		inline bool Init(Graphics::GPU* GPU, VmaAllocator& allocator, const Math::UI32Vec2& windowSize, const uint32& _framesInFlightMax)
		{
			maxFramesInFlight = _framesInFlightMax;

			bool failedToCreateObjects = false;

			for (uint32 i = 0; i < maxFramesInFlight; i++)
			{
				//create command pool and allocate command buffer
				if (!commandPools[i].Create(GPU, true))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "Init", "Failed to create command pool");
					failedToCreateObjects = true;
					break;
				}

				if (!commandPools[i].AllocateCommandBuffers(GPU, &(comBuffers[i]), 1, true))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "Init", "Failed to allocate command buffer");
					failedToCreateObjects = true;
					break;
				}

				//create sync objects
				if (!renderFences[i].Create(GPU->device))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "Init", "Failed to create render fence sync object");
					failedToCreateObjects = true;
					break;
				}

				if (!swapchainSemaphores[i].Create(GPU->device))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "Init", "Failed to create swapchain semaphores sync object");
					failedToCreateObjects = true;
					break;
				}

				if (!renderSemaphores[i].Create(GPU->device))
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTD STD", "Render Manager", "Init", "Failed to create render semaphores sync object");
					failedToCreateObjects = true;
					break;
				}
			}

			//if it failed, clean up anything
			if (failedToCreateObjects)
			{
				Shutdown(GPU, allocator);
				return false;
			}

			//--allocates a render targets
			if (!CreateRenderTarget(GPU->device, allocator, windowSize) || !CreateDepthRenderTarget(GPU->device, allocator, windowSize))
			{
				Shutdown(GPU, allocator);
				return false;
			}
		
			return true;
		}

		//shutsdown the render manager
		inline void Shutdown(Graphics::GPU* GPU, VmaAllocator& allocator)
		{
			//cleans up depth render target
			if (depthRenderTarget.imageView != VK_NULL_HANDLE)
				vkDestroyImageView(GPU->device, depthRenderTarget.imageView, nullptr);

			if (depthRenderTarget.image != VK_NULL_HANDLE)
				vmaDestroyImage(allocator, depthRenderTarget.image, depthRenderTarget.allocation);

			//cleans up render target
			if(renderTarget.imageView != VK_NULL_HANDLE)
				vkDestroyImageView(GPU->device, renderTarget.imageView, nullptr);
			
			if (renderTarget.image != VK_NULL_HANDLE)
				vmaDestroyImage(allocator, renderTarget.image, renderTarget.allocation);

			//cleans up commands and syncs
			for (int i = 0; i < maxFramesInFlight; i++)
			{
				renderSemaphores[i].Destroy(GPU->device);
				swapchainSemaphores[i].Destroy(GPU->device);
				renderFences[i].Destroy(GPU->device);
				commandPools[i].Destroy(GPU);
			}
		}

		//recreates a render target
		inline void RecreateRenderTarget(Graphics::GPU* GPU, VmaAllocator& allocator, const Math::UI32Vec2& size)
		{
			//cleans up depth render target
			if (depthRenderTarget.imageView != VK_NULL_HANDLE)
				vkDestroyImageView(GPU->device, depthRenderTarget.imageView, nullptr);

			if (depthRenderTarget.image != VK_NULL_HANDLE)
				vmaDestroyImage(allocator, depthRenderTarget.image, depthRenderTarget.allocation);

			//cleans up render target
			if (renderTarget.imageView != VK_NULL_HANDLE)
				vkDestroyImageView(GPU->device, renderTarget.imageView, nullptr);

			if (renderTarget.image != VK_NULL_HANDLE)
				vmaDestroyImage(allocator, renderTarget.image, renderTarget.allocation);

			//render target size will match the window
			renderTarget.size = {
				size.x,
				size.y,
				1
			};

			//hardcoding the draw format to 32 bit float
			renderTarget.imageFormat = VK_FORMAT_R16G16B16A16_SFLOAT;

			VkImageUsageFlags drawImageUsages{};
			drawImageUsages |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
			drawImageUsages |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			drawImageUsages |= VK_IMAGE_USAGE_STORAGE_BIT;
			drawImageUsages |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			VkImageCreateInfo rimg_info = BTD::Graphics::Image::GenerateInfoStruct_ImageCreateInfo(renderTarget.imageFormat, drawImageUsages, renderTarget.size);

			//for the draw image, we want to allocate it from gpu local memory
			VmaAllocationCreateInfo rimg_allocinfo = {};
			rimg_allocinfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
			rimg_allocinfo.requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			//allocate and create the image
			if (vmaCreateImage(allocator, &rimg_info, &rimg_allocinfo, &renderTarget.image, &renderTarget.allocation, nullptr) != VK_SUCCESS)
			{
				//Shutdown(GPU, allocator);

				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Renderer", "Init", "Failed to create render target image");
				//return false;
			}

			//build a image-view for the draw image to use for rendering
			VkImageViewCreateInfo rview_info = BTD::Graphics::Image::GenerateInfoStruct_ImageViewCreateInfo(renderTarget.imageFormat, renderTarget.image, VK_IMAGE_ASPECT_COLOR_BIT);

			if (vkCreateImageView(GPU->device, &rview_info, nullptr, &renderTarget.imageView) != VK_SUCCESS)
			{
				//Shutdown(GPU, allocator);

				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Renderer", "Init", "Failed to create render target view");
				//return false;
			}
		}

		//gets the next frame
		inline RenderManager_Frame GetNextFrame(Graphics::GPU* GPU, Graphics::DesktopSwapchain* swapchain)
		{
			RenderManager_Frame frame;
			frame.currentFrameIndex = currentFrame % maxFramesInFlight;
			frame.currentFrame_renderFence = renderFences[frame.currentFrameIndex].handle;
			frame.currentFrame_swapchainSemaphore = swapchainSemaphores[frame.currentFrameIndex].handle;
			frame.currentFrame_renderSemaphore = renderSemaphores[frame.currentFrameIndex].handle;
			frame.comBuffer = &comBuffers[frame.currentFrameIndex];

			//wait for the GPU to finish any work from the last frame
			if (vkWaitForFences(GPU->device, 1, &frame.currentFrame_renderFence, true, 1000000000) != VK_SUCCESS)
			{
				//BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "GetNextFrame", "Failed to wait with the render sync fence");
				return frame;
			}

			//request a image from the swapchain
			if (vkAcquireNextImageKHR(GPU->device, swapchain->swapchain, 1000000000, frame.currentFrame_swapchainSemaphore, nullptr, &frame.swapchainImageIndex) != VK_SUCCESS)
			{
				//BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "GetNextFrame", "Failed to retrive a swapchain image for the current frame");
				return frame;
			}
			frame.currentFrame_swapchainImage = swapchain->swapchainImages[frame.swapchainImageIndex];
			frame.currentFrame_swapchainImageView = swapchain->swapchainImageViews[frame.swapchainImageIndex];

			if (vkResetFences(GPU->device, 1, &frame.currentFrame_renderFence) != VK_SUCCESS)
			{
				//BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "GetNextFrame", "Failed to reset render sync fence");
				return frame;
			}

			frame.isValid = true;
			return frame;
		}

		//submits the next frame
		inline bool SubmitFrame(RenderManager_Frame& frame, Graphics::GPU* GPU, Graphics::DesktopSwapchain* swapchain)
		{
			//prepare the submission to the queue. 
			//we want to wait on the _presentSemaphore, as that semaphore is signaled when the swapchain is ready
			//we will signal the _renderSemaphore, to signal that rendering has finished

			VkCommandBufferSubmitInfo cmdInfo = Graphics::Buffer::GenerateInfoStruct_CommandBufferSubmit(frame.comBuffer->handle);
			VkSemaphoreSubmitInfo waitInfo = Graphics::Sync::GenerateInfoStruct_SemaphoreSubmit(frame.currentFrame_swapchainSemaphore,
				VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR, 0, 1);
			VkSemaphoreSubmitInfo signalInfo = Graphics::Sync::GenerateInfoStruct_SemaphoreSubmit(frame.currentFrame_renderSemaphore, VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT,
				0, 1);

			VkSubmitInfo2 submit = Graphics::Sync::GenerateInfoStruct_Submit(&waitInfo, &signalInfo, &cmdInfo);

			//submit command buffer to the queue and execute it.
			// _renderFence will now block until the graphic commands finish execution
			if (vkQueueSubmit2(GPU->graphicsQueue, 1, &submit, frame.currentFrame_renderFence) != VK_SUCCESS)
			{
				//BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "SubmitFrame", "Failed to submit render commands for the current frame");
				return false;
			}

			//prepare present
			// this will put the image we just rendered to into the visible window.
			// we want to wait on the _renderSemaphore for that, 
			// as its necessary that drawing commands have finished before the image is displayed to the user
			VkPresentInfoKHR presentInfo = Graphics::Sync::GenerateInfoStruct_Present(&swapchain->swapchain, &frame.swapchainImageIndex, &frame.currentFrame_renderSemaphore);

			if (vkQueuePresentKHR(GPU->graphicsQueue, &presentInfo) != VK_SUCCESS)
			{
				//BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "SubmitFrame", "Failed to present swapchain image for the current frame");
				return false;
			}

			//increase the number of frames drawn
			currentFrame++;
			
			return true;
		}
	};
}