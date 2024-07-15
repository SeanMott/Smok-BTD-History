#pragma once

//defines a compute pipeline

#include <BTDSTD/Graphics/Pipeline/PipelineLayout.hpp>
#include <BTDSTD/Graphics/Pipeline/Shader.hpp>

namespace BTD::Graphics::Pipeline
{
	//defines a compute pipeline
	struct ComputePipeline
	{
		VkPipeline handle = VK_NULL_HANDLE;

		//creates a pipeline
		inline bool Create(VkDevice& device, VkPipelineLayout& pipelineLayout, VkShaderModule& shader)
		{
			VkPipelineShaderStageCreateInfo stageinfo{};
			stageinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			stageinfo.pNext = nullptr;
			stageinfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
			stageinfo.module = shader;
			stageinfo.pName = "main";

			VkComputePipelineCreateInfo computePipelineCreateInfo{};
			computePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
			computePipelineCreateInfo.pNext = nullptr;
			computePipelineCreateInfo.layout = pipelineLayout;
			computePipelineCreateInfo.stage = stageinfo;

			if (vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &computePipelineCreateInfo, nullptr, &handle))
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Compute Pipeline", "Create", "Failed to create compute pipeline");
				return false;
			}
		}

		//destroys the pipeline
		inline void Destroy(VkDevice& device)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroyPipeline(device, handle, nullptr);
		}

		//binds the pipeline
		inline void Bind(VkCommandBuffer& comBuffer)
		{
			vkCmdBindPipeline(comBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, handle);
		}
	};
}