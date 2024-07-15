#pragma once

//defines a genaric buffer for GPU data

#include <BTDSTD/Logger.hpp>

#include <vulkan/vulkan.h>
#include <BTDSTD/Vender/vk_mem_alloc.h>

namespace BTD::Graphics::Buffer
{
	//defines a buffer
	struct Buffer
	{
		VkBuffer buffer;
		VmaAllocation allocation;
		VmaAllocationInfo info;

		//creates a buffer
		inline bool Create(VmaAllocator& allocator,
			size_t allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage)
		{
			// allocate buffer
			VkBufferCreateInfo bufferInfo = { .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
			bufferInfo.pNext = nullptr;
			bufferInfo.size = allocSize;

			bufferInfo.usage = usage;

			VmaAllocationCreateInfo vmaallocInfo = {};
			vmaallocInfo.usage = memoryUsage;
			vmaallocInfo.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;

			// allocate the buffer
			if (vmaCreateBuffer(allocator, &bufferInfo, &vmaallocInfo, &buffer, &allocation,
				&info) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Buffer", "Create", "Failed to create buffer");
				return false;
			}

			return true;
		}

		//destroys a buffer
		inline void Destroy(VmaAllocator& allocator)
		{
			vmaDestroyBuffer(allocator, buffer, allocation);
		}
	};

	//gets the address pointer of a buffer
	inline VkDeviceAddress GetBufferAddressPointer(VkDevice& device, VkBuffer& buffer)
	{
		VkBufferDeviceAddressInfo deviceAdressInfo{ .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,.buffer = buffer };
		return vkGetBufferDeviceAddress(device, &deviceAdressInfo);
	}

	//copies one buffer into another
	inline void CopyBufferToBuffer(VkCommandBuffer& comBuffer,
		Buffer& sourceBuffer, const VkDeviceSize& sourceOffset,
		Buffer& dstBuffer, const VkDeviceSize& dstOffset,
		const VkDeviceSize& copyMemSize)
	{
		VkBufferCopy vertexCopy{ 0 };
		vertexCopy.dstOffset = dstOffset;
		vertexCopy.srcOffset = sourceOffset;
		vertexCopy.size = copyMemSize;

		vkCmdCopyBuffer(comBuffer, sourceBuffer.buffer, dstBuffer.buffer, 1, &vertexCopy);
	}

	//defines a vertex buffer

	//draws a vertex buffer

	//binds a vertex buffer

	//binds a index buffer
	inline void IndexBuffer_Bind(VkCommandBuffer& comBuffer, Buffer& indexBuffer, const VkDeviceSize startOffset = 0)
	{
		vkCmdBindIndexBuffer(comBuffer, indexBuffer.buffer, startOffset, VK_INDEX_TYPE_UINT32);
	}

	//draws a index buffer
	inline void IndexBuffer_Draw(VkCommandBuffer& comBuffer, const uint32& indexCount, 
		const uint32& currentInstanceCount, const uint32& totalInstanceCount,
		const uint32 startIndex = 0, const uint32 vertexOffset = 0)
	{
		vkCmdDrawIndexed(comBuffer, indexCount, totalInstanceCount, startIndex, vertexOffset, currentInstanceCount);
	}
}