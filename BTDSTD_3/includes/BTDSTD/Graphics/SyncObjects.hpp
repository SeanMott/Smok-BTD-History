#pragma once

//defines sync objects

#include <vulkan/vulkan.h>

namespace BTD::Graphics::Sync
{
	//defines a fence
	struct Fence
	{
		VkFence handle = VK_NULL_HANDLE;

		//creates a fence
		inline bool Create(VkDevice& device, bool canBeSingledInstantly = true)
		{
			VkFenceCreateInfo fenceInfo = {};
			fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceInfo.pNext = nullptr;

			fenceInfo.flags = (canBeSingledInstantly == true ? VK_FENCE_CREATE_SIGNALED_BIT : 0);

			return (vkCreateFence(device, &fenceInfo, nullptr, &handle) != VK_SUCCESS ? false : true);
		}

		//destroys a fence
		inline void Destroy(VkDevice& device)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroyFence(device, handle, nullptr);
		}
	};

	//defines a semaphore
	struct Semaphore
	{
		VkSemaphore handle = VK_NULL_HANDLE;

		//creates a semaphore
		inline bool Create(VkDevice& device)
		{
			VkSemaphoreCreateInfo semaphoreInfo = {};
			semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			semaphoreInfo.pNext = nullptr;
			semaphoreInfo.flags = 0;

			return (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &handle) != VK_SUCCESS ? false : true);
		}

		//destroys a semaphore
		inline void Destroy(VkDevice& device)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroySemaphore(device, handle, nullptr);
		}
	};

	//generates a semaphore submit info
	inline VkSemaphoreSubmitInfo GenerateInfoStruct_SemaphoreSubmit(VkSemaphore& semaphore, const VkPipelineStageFlags2& stageMask,
		const uint32& deviceIndex, const uint64& value)
	{
		VkSemaphoreSubmitInfo info{};
		info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
		info.pNext = nullptr;
		info.semaphore = semaphore;
		info.stageMask = stageMask;
		info.deviceIndex = deviceIndex;
		info.value = value;
		return info;
	}

	//generates a submit info
	inline VkSubmitInfo2 GenerateInfoStruct_Submit(VkSemaphoreSubmitInfo* waitInfo, VkSemaphoreSubmitInfo* signalInfo, VkCommandBufferSubmitInfo* cmdInfo)
	{
		VkSubmitInfo2 submit = {};
		submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
		submit.pNext = nullptr;

		submit.waitSemaphoreInfoCount = (waitInfo == nullptr ? 0 : 1);
		submit.pWaitSemaphoreInfos = waitInfo;

		submit.signalSemaphoreInfoCount = (signalInfo == nullptr ? 0 : 1);
		submit.pSignalSemaphoreInfos = signalInfo;

		submit.commandBufferInfoCount = (cmdInfo == nullptr ? 0 : 1);
		submit.pCommandBufferInfos = cmdInfo;
		return submit;
	}

	//generates a present info
	inline VkPresentInfoKHR GenerateInfoStruct_Present(VkSwapchainKHR* swapchain, uint32* swapchainImageIndex, VkSemaphore* renderSemaphore)
	{
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.pNext = nullptr;
		presentInfo.pSwapchains = swapchain;
		presentInfo.swapchainCount = 1;

		presentInfo.pWaitSemaphores = renderSemaphore;
		presentInfo.waitSemaphoreCount = 1;

		presentInfo.pImageIndices = swapchainImageIndex;
		return presentInfo;
	}
}