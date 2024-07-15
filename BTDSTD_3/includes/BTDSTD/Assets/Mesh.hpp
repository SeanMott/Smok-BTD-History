#pragma once

//defines the mesh

#include <BTDSTD/Graphics/Buffers/Buffer.hpp>
#include <BTDSTD/Graphics/Buffers/CommandPool.hpp>

#include <glm/glm.hpp>
#include <vector>

#include <yaml-cpp/yaml.h>

namespace BTD::Asset
{
	//defines a vertex || interleaf the data so it's compact
	struct Vertex
	{
		glm::vec4 position;
		//glm::vec3 normal;
		glm::vec4 color;

		//the w components of the position and color vectors are
		//used for the UVs
	};

	//defines a vertices and indices pack
	struct Vertex_Index_Pack
	{
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
	};

	//defines a memory blob entry that stores the data of a vertex or index in one
	struct Vertex_Index_MemoryBlobEntry
	{
		bool isVertex = false;

		uint32 index;
		Vertex vertex;

		Vertex_Index_MemoryBlobEntry() {}
		Vertex_Index_MemoryBlobEntry(Vertex _vertex) { vertex = _vertex; isVertex = true; }
		Vertex_Index_MemoryBlobEntry(uint32 _index) { index = _index; isVertex = false; }
	};

	//defines decl data for a mesh
	struct DeclData_Mesh
	{
		uint32 vertexCount = 0, indexCount = 0;
		std::vector<Vertex_Index_MemoryBlobEntry> dataBlob;
	};

	//defines a mesh
	struct Mesh
	{
		uint32 vertexCount = 0, indexCount = 0;
		
		//the raw vertex data
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;

		//the blocks of memory
		BTD::Graphics::Buffer::Buffer indexBuffer;
		BTD::Graphics::Buffer::Buffer vertexBuffer;
		VkDeviceAddress vertexBufferAddress;

		//creates a mesh
		inline void Create(VmaAllocator& allocator, Graphics::GPU* GPU,
			VkFence& immediateSubmitFence, Graphics::Buffer::CommandBuffer& immediateSubmitComBuffer,
			const std::vector<Vertex>& _vertices, const std::vector<uint32>& _indices)
		{
			vertices = _vertices; indices = _indices;
			vertexCount = vertices.size(); indexCount = indices.size();
			const size_t vertexBufferSize = vertexCount * sizeof(Vertex);
			const size_t indexBufferSize = indexCount * sizeof(uint32);

			//create vertex buffer
			vertexBuffer.Create(allocator, vertexBufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
				VMA_MEMORY_USAGE_GPU_ONLY);

			//find the adress of the vertex buffer
			vertexBufferAddress = BTD::Graphics::Buffer::GetBufferAddressPointer(GPU->device, vertexBuffer.buffer);

			//create index buffer
			indexBuffer.Create(allocator, indexBufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
				VMA_MEMORY_USAGE_GPU_ONLY);

			BTD::Graphics::Buffer::Buffer staging; 
			staging.Create(allocator, vertexBufferSize + indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_ONLY);

			void* data = staging.allocation->GetMappedData();

			// copy vertex buffer
			memcpy(data, vertices.data(), vertexBufferSize);
			// copy index buffer
			memcpy((char*)data + vertexBufferSize, indices.data(), indexBufferSize);

			//copies data
			BTD::Graphics::Buffer::ImmediateSubmitCommands_Start(GPU->device, &immediateSubmitFence, immediateSubmitComBuffer);

			// copy vertex buffer
			BTD::Graphics::Buffer::CopyBufferToBuffer(immediateSubmitComBuffer.handle,
				staging, 0, vertexBuffer, 0, vertexBufferSize);

			// copy index buffer
			BTD::Graphics::Buffer::CopyBufferToBuffer(immediateSubmitComBuffer.handle,
				staging, vertexBufferSize, indexBuffer, 0, indexBufferSize);

			BTD::Graphics::Buffer::ImmediateSubmitCommands_End(GPU, immediateSubmitFence, immediateSubmitComBuffer);

			//cleans up staging buffer
			staging.Destroy(allocator);
		}

		//destroys a mesh
		inline void Destroy(VmaAllocator& allocator)
		{
			vertexBufferAddress = 0;
			indexBuffer.Destroy(allocator);
			vertexBuffer.Destroy(allocator);
		}

		//generates decl data for this sub mesh
		inline DeclData_Mesh GenerateDeclData()
		{
			DeclData_Mesh decl;

			//generates stats
			std::vector<Vertex_Index_MemoryBlobEntry> blob;
			decl.vertexCount = vertexCount;
			decl.indexCount = indexCount;
			decl.dataBlob.reserve(vertexCount + indexCount);

			//writes vertex data
			for (uint32 i = 0; i < vertexCount; ++i)
				decl.dataBlob.emplace_back(Vertex_Index_MemoryBlobEntry(vertices[i]));

			//writex index data
			for (uint32 i = 0; i < indexCount; ++i)
				decl.dataBlob.emplace_back(Vertex_Index_MemoryBlobEntry(indices[i]));

			return decl;
		}
	};

	//defines the version for the decl and static mesh data
#define BTD_ASSET_STATIC_MESH_DECL_DATA_VER "1.0"

	//defines the file extension for static mesh decl file names
#define BTD_ASSET_STATIC_MESH_DECL_TEXT_FILE_EXTENSION ".BTDSMESHDECL"

	//defines the file extension for static mesh binary data file names
#define BTD_ASSET_STATIC_MESH_DECL_BINARY_FILE_EXTENSION ".BTDSMESH"

	//defines decl data for a static mesh
	struct DeclData_StaticMesh
	{
		std::string assetName = "";

		std::vector<DeclData_Mesh> subMeshes;

		////writes decl data
		//inline void WriteDeclData(const std::string outputDir)
		//{
		//	//preps for the massive binary blob
		//	const size_t subMeshCount = subMeshes.size();
		//	std::vector<size_t> subMeshStartOffset; subMeshStartOffset.resize(subMeshCount);
		//	std::vector<Vertex_Index_MemoryBlobEntry> blob; blob.reserve(subMeshCount * 256);
		//	size_t startOffsetIndex = 0;

		//	//preps for decl file
		//	YAML::Emitter emitter;
		//	emitter << YAML::BeginMap;

		//	//stores version string
		//	emitter << YAML::Key << "BTDAssetDeclVer" << YAML::DoubleQuoted << BTD_ASSET_STATIC_MESH_DECL_DATA_VER;
		//	//stores asset name
		//	emitter << YAML::Key << assetName << YAML::Value << YAML::BeginSeq;

		//	//generates the blob
		//	for (uint32 i = 0; i < subMeshCount; ++i)
		//	{
		//		emitter << YAML::Key << std::to_string(i) << YAML::Value << YAML::BeginSeq;

		//		//writes vertex data
		//		emitter << YAML::Key << "vertexStartIndex" << YAML::Value << startOffsetIndex;
		//		for (uint32 v = 0; v < subMeshes[i].vertexCount; ++v)
		//			blob.emplace_back(subMeshes[i].dataBlob[v]);
		//		startOffsetIndex += subMeshes[i].vertexCount;

		//		//writes index data
		//		emitter << YAML::Key << "indexStartIndex" << YAML::Value << subMeshes[i].vertexCount;
		//		for (uint32 v = subMeshes[i].vertexCount; v < subMeshes[i].dataBlob.size(); ++v)
		//			blob.emplace_back(subMeshes[i].dataBlob[v]);
		//		startOffsetIndex += subMeshes[i].indexCount;

		//		emitter << YAML::EndSeq;
		//	}

		//	//ends the decl file
		//	emitter << YAML::EndSeq;
		//	emitter << YAML::EndMap;

		//	//writes binary blob
		//	BTD::IO::File file;

		//	//writes decl file
		//	file.Open(std::string(outputDir + "//" + assetName + BTD_ASSET_STATIC_MESH_DECL_TEXT_FILE_EXTENSION).c_str());
		//	file.WriteText(emitter.c_str());
		//	file.Close();
		//}

		//loads decl data
	};

	//defiines a static mesh
	struct StaticMesh
	{
		uint64 assetID = 0; //the asset ID

		std::vector<Mesh> meshes; //the mesh data

		//creates sub meshes and loads meshes
		inline void CreateStaticMeshFromMeshData(const std::vector<BTD::Asset::Vertex_Index_Pack>& meshData,
			VmaAllocator& allocator, Graphics::GPU* GPU,
			VkFence& immediateSubmitFence, Graphics::Buffer::CommandBuffer& immediateSubmitComBuffer)
		{
			const size_t meshDataCount = meshData.size();
			meshes.resize(meshDataCount);
			for (uint32 i = 0; i < meshDataCount; ++i)
				meshes[i].Create(allocator, GPU,
					immediateSubmitFence, immediateSubmitComBuffer,
					meshData[i].vertices, meshData[i].indices);
		}

		//destroys the static mesh
		inline void Destroy(VmaAllocator& allocator)
		{
			for (uint32 i = 0; i < meshes.size(); ++i)
				meshes[i].Destroy(allocator);
			meshes.clear();

			assetID = 0;
		}

		//generates decl data for the static mesh
		inline DeclData_StaticMesh GenerateDeclData(const std::string& assetName)
		{
			DeclData_StaticMesh decl;

			//gets the name from it's ID
			decl.assetName = assetName;
			printf("Asset Name: %s\n", decl.assetName.c_str());

			//goes through the meshes and adds it's data
			const size_t meshCount = meshes.size();
			decl.subMeshes.resize(meshCount);
			for (uint32 i = 0; i < meshCount; ++i)
				meshes[i].GenerateDeclData();

			return decl;
		}
	};
}