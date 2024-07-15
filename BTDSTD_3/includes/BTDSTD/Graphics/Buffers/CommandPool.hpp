#pragma once

//defines command pools and buffers

#include <BTDSTD/Graphics/GPU.hpp>
#include <BTDSTD/Graphics/SyncObjects.hpp>

#include <functional>

namespace BTD::Graphics::Buffer
{
	//defines a command buffer that tracks state and if it's recording
	struct CommandBuffer
	{
		VkCommandBuffer handle = VK_NULL_HANDLE;
		bool isRecording = false;
	
		//starts recording
		inline bool StartRecording(bool isSingleUse = false)
		{
			VkCommandBufferBeginInfo commandBufferStartRecordingInfo = {};
			commandBufferStartRecordingInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			commandBufferStartRecordingInfo.pNext = nullptr;

			commandBufferStartRecordingInfo.pInheritanceInfo = nullptr;
			commandBufferStartRecordingInfo.flags = (isSingleUse == true ? VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT : 0);

			//start the command buffer recording
			isRecording = (vkBeginCommandBuffer(handle, &commandBufferStartRecordingInfo) != VK_SUCCESS ? false : true);
			return isRecording;
		}

		//stops recording
		inline bool StopRecording()
		{
			if (!isRecording)
				return true;

			return (vkEndCommandBuffer(handle) != VK_SUCCESS ? false : true);
		}
	};

	//defines a command pool
	struct CommandPool
	{
		uint32 commandBufferAllocatedCount_NonTracking = 0, //the current number of state non-tracking command buffers allocated
			commandBufferAllocatedCount_Tracking = 0;//the current number of state tracking command buffers allocated

		VkCommandPool handle = VK_NULL_HANDLE;

		//creates a command pool
		inline bool Create(GPU* gpu, bool canBeReset = false)
		{
			//create a command pool for commands submitted to the graphics queue.
			//we also want the pool to allow for resetting of individual command buffers
			VkCommandPoolCreateInfo commandPoolInfo = {};
			commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			commandPoolInfo.pNext = nullptr;
			commandPoolInfo.flags = (canBeReset == true ? VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT : 0);
			commandPoolInfo.queueFamilyIndex = gpu->graphicsQueueFamily;

			if (vkCreateCommandPool(gpu->device, &commandPoolInfo, nullptr, &handle) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogFatalErrorToConsole("BTDSTD", "Windows", "Command Pool", "Create", "Failed to create a command pool");
				return false;
			}

			return true;
		}

		//destroys a command pool
		inline void Destroy(GPU* gpu)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroyCommandPool(gpu->device, handle, nullptr);
		}

		//resets the command pool

		//allocates command buffers
		inline bool AllocateCommandBuffers(GPU* gpu, CommandBuffer* commandBuffers, uint32 commandBufferCount = 1, bool isPrimary = true)
		{
			VkCommandBufferAllocateInfo cmdAllocInfo = {};
			cmdAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			cmdAllocInfo.pNext = nullptr;
			cmdAllocInfo.commandPool = handle;
			cmdAllocInfo.commandBufferCount = commandBufferCount;
			cmdAllocInfo.level = (isPrimary == true ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY);

			//if it's only one
			if (commandBufferCount == 1)
			{
				if (vkAllocateCommandBuffers(gpu->device, &cmdAllocInfo, &commandBuffers->handle) != VK_SUCCESS)
				{
					BTD::Util::Logger::LogFatalErrorToConsole("BTDSTD", "Windows", "Command Pool", "AllocateCommandBuffers", "Failed to create a command buffer");
					return false;
				}
			}

			//if it's more then one
			else
			{

			}

			return true;
		}
	};

	//generates a command buffer submit info
	inline VkCommandBufferSubmitInfo GenerateInfoStruct_CommandBufferSubmit(VkCommandBuffer& comBuffer, uint32 deviceMask = 0)
	{
		VkCommandBufferSubmitInfo cmdInfo{};
		cmdInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
		cmdInfo.pNext = nullptr;
		cmdInfo.commandBuffer = comBuffer;
		cmdInfo.deviceMask = deviceMask;
		return cmdInfo;
	}

	//starts a immediate submit of commands
	static inline bool ImmediateSubmitCommands_Start(VkDevice& device, VkFence* fence, Graphics::Buffer::CommandBuffer& comBuffer)
	{
		//resets data
		if (vkResetFences(device, 1, fence) != VK_SUCCESS)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to reset sync fence");
			return false;
		}

		if (vkResetCommandBuffer(comBuffer.handle, 0) != VK_SUCCESS)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to reset command buffer");
			return false;
		}

		//starts recording
		if (!comBuffer.StartRecording(true))
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to start recording");
			return false;
		}

		return true;
	}

	//ends a immediate submit of commands and sends them
	static inline bool ImmediateSubmitCommands_End(Graphics::GPU* GPU, VkFence& fence, Graphics::Buffer::CommandBuffer& comBuffer)
	{
		if (!comBuffer.StopRecording())
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to start recording");
			return false;
		}

		VkCommandBufferSubmitInfo cmdInfo = Graphics::Buffer::GenerateInfoStruct_CommandBufferSubmit(comBuffer.handle);
		VkSubmitInfo2 submit = Graphics::Sync::GenerateInfoStruct_Submit(nullptr, nullptr, &cmdInfo);

		// submit command buffer to the queue and execute it.
		//  _renderFence will now block until the graphic commands finish execution
		if (vkQueueSubmit2(GPU->graphicsQueue, 1, &submit, fence) != VK_SUCCESS)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands_End", "Failed to submit render commands for Immediate Submit");
			return false;
		}

		if (vkWaitForFences(GPU->device, 1, &fence, true, 9999999999) != VK_SUCCESS)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands_End", "Failed to wait with the fence for Immediate SubmitCommands");
			return false;
		}

		return true;
	}

	//performs a all in one Immediate submit
	inline bool ImmediateSubmit_AllInOne(std::function<void()>&& function, VkDevice& device, VkQueue& graphicsQueue, VkFence& fence, Graphics::Buffer::CommandBuffer& comBuffer)
	{
		//resets data
		if (vkResetFences(device, 1, &fence) != VK_SUCCESS)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to reset sync fence");
			return false;
		}

		if (vkResetCommandBuffer(comBuffer.handle, 0) != VK_SUCCESS)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to reset command buffer");
			return false;
		}

		//starts recording
		if (!comBuffer.StartRecording(true))
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to start recording");
			return false;
		}

		function();

		if (!comBuffer.StopRecording())
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to start recording");
			return false;
		}

		VkCommandBufferSubmitInfo cmdInfo = Graphics::Buffer::GenerateInfoStruct_CommandBufferSubmit(comBuffer.handle);
		VkSubmitInfo2 submit = Graphics::Sync::GenerateInfoStruct_Submit(nullptr, nullptr, &cmdInfo);

		// submit command buffer to the queue and execute it.
		//  _renderFence will now block until the graphic commands finish execution
		if (vkQueueSubmit2(graphicsQueue, 1, &submit, fence) != VK_SUCCESS)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands_End", "Failed to submit render commands for Immediate Submit");
			return false;
		}

		if (vkWaitForFences(device, 1, &fence, true, 9999999999) != VK_SUCCESS)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands_End", "Failed to wait with the fence for Immediate SubmitCommands");
			return false;
		}

		return true;
	}

	////performs a all in one Immediate submit
	//inline bool ImmediateSubmit_AllInOne_Param(std::function<void(VkCommandBuffer cmd)>&& function, VkDevice& device, VkQueue& graphicsQueue, VkFence& fence, Graphics::Buffer::CommandBuffer& comBuffer)
	//{
	//	//resets data
	//	if (vkResetFences(device, 1, &fence) != VK_SUCCESS)
	//	{
	//		BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to reset sync fence");
	//		return false;
	//	}

	//	if (vkResetCommandBuffer(comBuffer.handle, 0) != VK_SUCCESS)
	//	{
	//		BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to reset command buffer");
	//		return false;
	//	}

	//	//starts recording
	//	if (!comBuffer.StartRecording(true))
	//	{
	//		BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to start recording");
	//		return false;
	//	}

	//	function(cmd);

	//	if (!comBuffer.StopRecording())
	//	{
	//		BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands", "Failed to start recording");
	//		return false;
	//	}

	//	VkCommandBufferSubmitInfo cmdInfo = Graphics::Buffer::GenerateInfoStruct_CommandBufferSubmit(comBuffer.handle);
	//	VkSubmitInfo2 submit = Graphics::Sync::GenerateInfoStruct_Submit(nullptr, nullptr, &cmdInfo);

	//	// submit command buffer to the queue and execute it.
	//	//  _renderFence will now block until the graphic commands finish execution
	//	if (vkQueueSubmit2(graphicsQueue, 1, &submit, fence) != VK_SUCCESS)
	//	{
	//		BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands_End", "Failed to submit render commands for Immediate Submit");
	//		return false;
	//	}

	//	if (vkWaitForFences(device, 1, &fence, true, 9999999999) != VK_SUCCESS)
	//	{
	//		BTD::Util::Logger::LogErrorToConsole("BTD STD", "Render Manager", "ImmediateSubmitCommands_End", "Failed to wait with the fence for Immediate SubmitCommands");
	//		return false;
	//	}

	//	return true;
	//}
}