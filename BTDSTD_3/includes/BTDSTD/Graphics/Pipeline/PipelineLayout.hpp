#pragma once

//defines a pipeline layout

#include <BTDSTD/Logger.hpp>

#include <vector>
#include <vulkan/vulkan.h>

namespace BTD::Graphics::Pipeline
{
	//defines a pipeline layout create info
	struct PipelineLayoutCreateInfo
	{
		std::vector<VkPushConstantRange> pushConstants; //defines push constants
		std::vector<VkDescriptorSetLayout> descLayouts; //descriptor layouts
	};

	//defines a pipeline layout
	struct PipelineLayout
	{
		uint64 assetID = 0;

		VkPipelineLayout handle = VK_NULL_HANDLE;

		//creates a pipeline layout
		inline bool Create(VkDevice& device, const PipelineLayoutCreateInfo* info)
		{
			VkPipelineLayoutCreateInfo layoutCreateInfo{};
			layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			layoutCreateInfo.pNext = nullptr;
			
			//descriptor layouts
			layoutCreateInfo.pSetLayouts = info->descLayouts.data();
			layoutCreateInfo.setLayoutCount = (uint32)info->descLayouts.size();

			//push constants
			layoutCreateInfo.pPushConstantRanges = info->pushConstants.data();
			layoutCreateInfo.pushConstantRangeCount = (uint32)info->pushConstants.size();

			if (vkCreatePipelineLayout(device, &layoutCreateInfo, nullptr, &handle))
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Pipeline Layout", "Create", "Failed to create pipeline layout");
				return false;
			}

			return true;
		}

		//destroys the layout
		inline void Destroy(VkDevice& device)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroyPipelineLayout(device, handle, nullptr);
		}

		//binds the descriptor sets for compute
		inline void BindDescriptorSets_Compute(VkCommandBuffer& comBuffer, const std::vector<VkDescriptorSet>& sets)
		{
			vkCmdBindDescriptorSets(comBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, handle, 0, sets.size(), sets.data(), 0, nullptr);
		}

		//sends push constant data for compute shader stage
		inline void SendPushConstant_Compute(VkCommandBuffer& comBuffer, const size_t pushConstBufferMemSize, void* pushConstBuffer)
		{
			//sends push constant data
			vkCmdPushConstants(comBuffer, handle, VK_SHADER_STAGE_COMPUTE_BIT, 0, pushConstBufferMemSize, pushConstBuffer);
		}

		//sends push constant data for vertex shader stage
		inline void SendPushConstant_Vertex(VkCommandBuffer& comBuffer, const size_t pushConstBufferMemSize, void* pushConstBuffer)
		{
			//sends push constant data
			vkCmdPushConstants(comBuffer, handle, VK_SHADER_STAGE_VERTEX_BIT, 0, pushConstBufferMemSize, pushConstBuffer);
		}

		//sends push constant data for fragment shader stage
		inline void SendPushConstant_Fragment(VkCommandBuffer& comBuffer, const size_t pushConstBufferMemSize, void* pushConstBuffer)
		{
			//sends push constant data
			vkCmdPushConstants(comBuffer, handle, VK_SHADER_STAGE_FRAGMENT_BIT, 0, pushConstBufferMemSize, pushConstBuffer);
		}

		//sends push constant data for vertex-fragment shader stage
		inline void SendPushConstant_VertexFragment(VkCommandBuffer& comBuffer, const size_t pushConstBufferMemSize, void* pushConstBuffer)
		{
			//sends push constant data
			vkCmdPushConstants(comBuffer, handle, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, pushConstBufferMemSize, pushConstBuffer);
		}
	};
}