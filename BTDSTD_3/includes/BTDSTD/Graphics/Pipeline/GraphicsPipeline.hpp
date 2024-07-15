#pragma once

//defines a graphics pipeline

#include <BTDSTD/Graphics/Pipeline/PipelineLayout.hpp>
#include <BTDSTD/Graphics/Pipeline/Shader.hpp>

namespace BTD::Graphics::Pipeline
{
	//defines a graphics pipeline create info
	struct GraphicsPipeline_CreateInfo
	{
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

		VkPipelineInputAssemblyStateCreateInfo inputAssembly;
		VkPipelineRasterizationStateCreateInfo rasterizer;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineMultisampleStateCreateInfo multisampling;
		VkPipelineDepthStencilStateCreateInfo depthStencil;
		VkPipelineRenderingCreateInfo renderInfo;
		VkFormat colorAttachmentformat;

		//restets all values to 0 but keeps STypes
		inline void Reset()
		{
			inputAssembly = { .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };

			rasterizer = { .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };

			colorBlendAttachment = {};

			multisampling = { .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };

			depthStencil = { .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };

			renderInfo = { .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO };

			shaderStages.clear();
		}

		//sets the shaders
		inline void SetShaders(VkShaderModule vertexShader, VkShaderModule fragmentShader)
		{
			shaderStages.clear();

			shaderStages.push_back(GenerateInfoStruct_ShaderStage(VK_SHADER_STAGE_VERTEX_BIT, vertexShader));
			shaderStages.push_back(GenerateInfoStruct_ShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, fragmentShader));
		}

		//sets the topology
		inline void SetInputTopology(VkPrimitiveTopology topology)
		{
			inputAssembly.topology = topology;
			// we are not going to use primitive restart on the entire tutorial so leave
			// it on false
			inputAssembly.primitiveRestartEnable = VK_FALSE;
		}

		//sets rasterizer polygon mode
		inline void SetPolygonMode(VkPolygonMode mode)
		{
			rasterizer.polygonMode = mode;
			rasterizer.lineWidth = 1.f;
		}

		//sets the culling for back and front faces
		inline void SetCullMode(VkCullModeFlags cullMode, VkFrontFace frontFace)
		{
			rasterizer.cullMode = cullMode;
			rasterizer.frontFace = frontFace;
		}

		//disables multisampling
		inline void MultiSampling_Disable()
		{
			multisampling.sampleShadingEnable = VK_FALSE;
			// multisampling defaulted to no multisampling (1 sample per pixel)
			multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
			multisampling.minSampleShading = 1.0f;
			multisampling.pSampleMask = nullptr;
			//no alpha to coverage either
			multisampling.alphaToCoverageEnable = VK_FALSE;
			multisampling.alphaToOneEnable = VK_FALSE;
		}

		//disables blending
		inline void Blending_Disable()
		{
			//default write mask
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			//no blending
			colorBlendAttachment.blendEnable = VK_FALSE;
		}

		//makes blending additive
		inline void Blending_Enable_Additive()
		{
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_DST_ALPHA;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
		}

		//makes blending alpha mixing/blending
		inline void Blending_Enable_Mix()
		{
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_DST_ALPHA;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
		}

		//sets the color attachment
		inline void SetColorAttachmentFormat(VkFormat format)
		{
			colorAttachmentformat = format;
			//connect the format to the renderInfo  structure
			renderInfo.colorAttachmentCount = 1;
			renderInfo.pColorAttachmentFormats = &colorAttachmentformat;
		}

		//sets the depth format
		inline void SetDepthFormat(VkFormat format) { renderInfo.depthAttachmentFormat = format; }

		//disables depth testing
		inline void DepthTesting_Disable()
		{
			depthStencil.depthTestEnable = VK_FALSE;
			depthStencil.depthWriteEnable = VK_FALSE;
			depthStencil.depthCompareOp = VK_COMPARE_OP_NEVER;
			depthStencil.depthBoundsTestEnable = VK_FALSE;
			depthStencil.stencilTestEnable = VK_FALSE;
			depthStencil.front = {};
			depthStencil.back = {};
			depthStencil.minDepthBounds = 0.f;
			depthStencil.maxDepthBounds = 1.f;
		}

		//enables depth testing
		inline void DepthTesting_Enable(bool depthWriteEnable, VkCompareOp op)
		{
			depthStencil.depthTestEnable = VK_TRUE;
			depthStencil.depthWriteEnable = depthWriteEnable;
			depthStencil.depthCompareOp = op;
			depthStencil.depthBoundsTestEnable = VK_FALSE;
			depthStencil.stencilTestEnable = VK_FALSE;
			depthStencil.front = {};
			depthStencil.back = {};
			depthStencil.minDepthBounds = 0.f;
			depthStencil.maxDepthBounds = 1.f;
		}
	};

	//defines a graphics pipeline
	struct GraphicsPipeline
	{
		uint64 assetID = 0;

		VkViewport viewport = {0.0f};
		VkRect2D scissor = {};

		VkPipeline handle = VK_NULL_HANDLE;

		//creates a graphics pipeline
		inline bool Create(VkDevice& device, VkPipelineLayout& layout, const GraphicsPipeline_CreateInfo* info)
		{
			// make viewport state from our stored viewport and scissor.
			// at the moment we wont support multiple viewports or scissors
			VkPipelineViewportStateCreateInfo viewportState = {};
			viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewportState.pNext = nullptr;

			viewportState.viewportCount = 1;
			viewportState.scissorCount = 1;

			// setup dummy color blending. We arent using transparent objects yet
			// the blending is just "no blend", but we do write to the color attachment
			VkPipelineColorBlendStateCreateInfo colorBlending = {};
			colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			colorBlending.pNext = nullptr;

			colorBlending.logicOpEnable = VK_FALSE;
			colorBlending.logicOp = VK_LOGIC_OP_COPY;
			colorBlending.attachmentCount = 1;
			colorBlending.pAttachments = &info->colorBlendAttachment;

			//completely clear VertexInputStateCreateInfo, as we have no need for it
			VkPipelineVertexInputStateCreateInfo _vertexInputInfo = { .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

			// build the actual pipeline
			// we now use all of the info structs we have been writing into into this one
			// to create the pipeline
			VkGraphicsPipelineCreateInfo pipelineInfo = { .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
			//connect the renderInfo to the pNext extension mechanism
			pipelineInfo.pNext = &info->renderInfo;

			pipelineInfo.stageCount = (uint32_t)info->shaderStages.size();
			pipelineInfo.pStages = info->shaderStages.data();
			pipelineInfo.pVertexInputState = &_vertexInputInfo;
			pipelineInfo.pInputAssemblyState = &info->inputAssembly;
			pipelineInfo.pViewportState = &viewportState;
			pipelineInfo.pRasterizationState = &info->rasterizer;
			pipelineInfo.pMultisampleState = &info->multisampling;
			pipelineInfo.pColorBlendState = &colorBlending;
			pipelineInfo.pDepthStencilState = &info->depthStencil;
			pipelineInfo.layout = layout;

			//dynamic state
			VkDynamicState state[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

			VkPipelineDynamicStateCreateInfo dynamicInfo = { .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
			dynamicInfo.pDynamicStates = &state[0];
			dynamicInfo.dynamicStateCount = 2;

			pipelineInfo.pDynamicState = &dynamicInfo;

			// its easy to error out on create graphics pipeline, so we handle it a bit
			// better than the common VK_CHECK case
			if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo,
				nullptr, &handle) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Graphics Pipeline", "Create", "Failed to create graphics pipeline");
				return false;
			}
			
			return true;
		}

		//destroys a graphics pipeline
		inline void Destroy(VkDevice& device)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroyPipeline(device, handle, nullptr);
		}

		//binds the pipeline
		inline void Bind(VkCommandBuffer& comBuffer)
		{
			vkCmdBindPipeline(comBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, handle);
		}

		//sets the viewport size
		inline void SetViewportSize(const float width, const float height)
		{
			viewport.width = width;
			viewport.height = height;
		}

		//sets the viewport size
		inline void SetViewportSize(const BTD::Math::FVec2 size)
		{
			SetViewportSize(size.x, size.y);
		}

		//sets the viewport position
		inline void SetViewportPosition(const float x, const float y)
		{
			viewport.x = x;
			viewport.y = y;
		}

		//sets the viewport position
		inline void SetViewportPosition(const BTD::Math::FVec2 position)
		{
			SetViewportPosition(position.x, position.y);
		}

		//sets the viewport depth
		inline void SetViewportDepth(const float min, const float max)
		{
			viewport.minDepth = min;
			viewport.maxDepth = max;
		}

		//sets the viewport depth
		inline void SetViewportDepth(const BTD::Math::FVec2& depth)
		{
			SetViewportDepth(depth.x, depth.y);
		}

		//updates the viewport
		inline void UpdateViewport(VkCommandBuffer& comBuffer)
		{
			vkCmdSetViewport(comBuffer, 0, 1, &viewport);
		}

		//sets the scissor size
		inline void SetScissorSize(const float width, const float height)
		{
			scissor.extent.width = width;
			scissor.extent.height = height;
		}

		//sets the scissor size
		inline void SetScissorSize(const BTD::Math::FVec2& size)
		{
			SetScissorSize(size.x, size.y);
		}

		//sets the scissor position
		inline void SetScissorPosition(const float x, const float y)
		{
			scissor.offset.x = 0;
			scissor.offset.y = 0;
		}

		//sets the scissor position
		inline void SetScissorPosition(const BTD::Math::FVec2& position)
		{
			SetScissorPosition(position.x, position.y);
		}

		//updates the scissor
		inline void UpdateScissor(VkCommandBuffer& comBuffer)
		{
			vkCmdSetScissor(comBuffer, 0, 1, &scissor);
		}
	};
}