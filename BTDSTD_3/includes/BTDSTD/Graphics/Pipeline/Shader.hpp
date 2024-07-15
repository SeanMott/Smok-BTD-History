#pragma once

//defines a shader

#include <BTDSTD/IO/File.hpp>

#include <vulkan/vulkan.h>

namespace BTD::Graphics::Pipeline
{
	//defines a shader stage flag
	enum class ShaderStageFlag
	{
		Vertex = VK_SHADER_STAGE_VERTEX_BIT,
		Fragment = VK_SHADER_STAGE_FRAGMENT_BIT,

		Compute = VK_SHADER_STAGE_COMPUTE_BIT,

		Count = VK_SHADER_STAGE_ALL
	};

	//converts a shader stage flag to a string
	inline const char* ShaderStageFlagToStr(const ShaderStageFlag& flag)
	{
		switch (flag)
		{
		case ShaderStageFlag::Vertex:
			return "Vertex";

		case ShaderStageFlag::Fragment:
			return "Fragment";

		case ShaderStageFlag::Compute:
			return "Compute";

		default:
			return "UNKNOWN SHADER STAGE!!!!";
		}
	}

	//converts a string to a shader stage flag
	inline ShaderStageFlag StrToShaderStageFlag(const char* str)
	{
		//vertex
		if (!strcmp(str, "Vertex"))
			return ShaderStageFlag::Vertex;

		//fragment
		else if (!strcmp(str, "Fragment"))
			return ShaderStageFlag::Fragment;

		//compute
		else if (!strcmp(str, "Compute"))
			return ShaderStageFlag::Compute;

		return ShaderStageFlag::Count;
	}

	//defines decl data for a shader
	struct DeclData_Shader
	{
		ShaderStageFlag stage = ShaderStageFlag::Vertex; //what stage is this shader

		std::string entryFuncName = "main", //defines the entry func name
			SPRVFilePath = "", //path to the compiled shader
			sourceCodeFilePath = ""; //path to the source code of the shader (dev only thing)

		//writes decl data to a file

		//loads decl data from a file
	};

	//defines a shader
	struct Shader
	{
		VkShaderModule handle = VK_NULL_HANDLE;

		std::vector<uint32> byteCode;

		//loads the byte code of a shader
		inline bool LoadByteCode(const char* filePath)
		{
			BTD::IO::File file;
			if (!file.Open(filePath, BTD::IO::FileOP::BinaryRead_OpenExisting))
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Shader", "LoadByteCode", std::string(std::string("Failed to load shader byte code from path: ") + std::string(filePath)).c_str());
				return false;
			}
			file.ReadSPRVByteCode(byteCode);
			file.Close();

			return true;
		}

		//clears the stored internal byte code of a shader
		inline void ClearByteCode() { byteCode.clear(); }

		//creates a shader handle using previously loaded byte code
		inline bool Create(VkDevice& device)
		{
			// create a new shader module, using the buffer we loaded
			VkShaderModuleCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.pNext = nullptr;

			// codeSize has to be in bytes, so multply the ints in the buffer by size of
			// int to know the real size of the buffer
			createInfo.codeSize = byteCode.size() * sizeof(uint32_t);
			createInfo.pCode = byteCode.data();

			// check that the creation goes well.
			if (vkCreateShaderModule(device, &createInfo, nullptr, &handle) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Shader", "Create", "Failed to create shader");
				return false;
			}

			return true;
		}

		//destroys a shader handle
		inline void Destroy(VkDevice& device)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroyShaderModule(device, handle, nullptr); handle = VK_NULL_HANDLE;
		}

		//loads shader byte code and creates a shader
		inline bool LoadAndCreate(const char* filePath, VkDevice& device)
		{
			return (!LoadByteCode(filePath) || !Create(device) ? false : true);
		}
	};

	//generates shader stage info for a pipeline
	VkPipelineShaderStageCreateInfo GenerateInfoStruct_ShaderStage(VkShaderStageFlagBits stage, VkShaderModule shaderModule,
		const char* entryFunc = "main")
	{
		VkPipelineShaderStageCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		info.pNext = nullptr;

		info.stage = stage;// shader stage
		info.module = shaderModule;// module containing the code for this shader stage
		info.pName = entryFunc;// the entry point of the shader

		return info;
	}
}