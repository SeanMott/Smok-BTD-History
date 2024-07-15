#pragma once

//defines functions for loading raw meshes and turning them into BTD ones

#include <BTDSTD/Assets/Mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <BTDSTD/Math/Colors.hpp>

//#include "../assimp/include/assimp/Importer.hpp"
//#include "../assimp/include/assimp/scene.h"
//#include "../assimp/include/assimp/postprocess.h"
//
namespace BTD::Asset::Loader
{
	//processes a single mesh
	static inline Vertex_Index_Pack ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		Vertex_Index_Pack data; data.vertices.reserve(15); data.indices.reserve(25);
		//std::vector<Texture> textures;

		for (uint32 i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			
			//process the postion
			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;

			//process the normals
			//vertex.normal.x = mesh->mNormals[i].x;
			//vertex.normal.y = mesh->mNormals[i].y;
			//vertex.normal.z = mesh->mNormals[i].z;
			//vertex.normal = { 100.0f, 75.0f, 100.0f };

			//process the colors
			//if (mesh->mColors[0])
			//{
			//	vertex.color.r = mesh->mColors[0]->r;
			//	vertex.color.g = mesh->mColors[0]->g;
			//	vertex.color.b = mesh->mColors[0]->b;
			//	vertex.color.a = mesh->mColors[0]->a;
			//}
			//else
			//{
		//	vertex.color = BTD::Math::Color::ShuffleColorsForRendering(BTD::Math::Color::LightPink());

			//process texture coordinates
			//if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			//{
			//	vertex.position.w = mesh->mTextureCoords[0][i].x;
			//	vertex.color.w = mesh->mTextureCoords[0][i].y;
			//	
			//}
			//else
			//{
			//	vertex.position.w = 0;
			//	vertex.color.w = 0;
			//}

			data.vertices.push_back(vertex);
		}

		// process indices
		for (uint32 i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32 j = 0; j < face.mNumIndices; j++)
				data.indices.push_back(face.mIndices[j]);
		}

		//// process material
		//if (mesh->mMaterialIndex >= 0)
		//{
		//	[...]
		//}

		return data;
	}

	//processes a mesh node
	static inline void processMeshNode(aiNode* node, const aiScene* scene, std::vector<Vertex_Index_Pack>& meshData)
	{
		// process all the node's meshes (if any)
		for (uint32 i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshData.push_back(ProcessMesh(mesh, scene));
		}

		// then do the same for each of its children
		for (uint32 i = 0; i < node->mNumChildren; i++)
		{
			processMeshNode(node->mChildren[i], scene, meshData);
		}
	}

	//loads a static mesh
	inline bool LoadMesh_StaticMesh(const std::string& path, std::vector<Vertex_Index_Pack>& meshDatas)
	{
		//loads a mesh
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes);// | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			BTD::Util::Logger::LogErrorToConsole("BTD STD", "Static Mesh Loading", "LoadMesh_StaticMesh",
				std::string("Failed to load static mesh from \"" + path + "\"").c_str());
			BTD::Util::Logger::LogErrorToConsole("Assimp", "Static Mesh Loading", "LoadMesh_StaticMesh",
				importer.GetErrorString());
			return false;
		}

		//process the mesh nodes
		meshDatas.reserve(5);
		processMeshNode(scene->mRootNode, scene, meshDatas);

		//compress and optimize the mesh data

		return true;
	}
}