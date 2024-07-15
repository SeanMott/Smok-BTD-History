#pragma once

//defines a mesh component for rendering

#include <SmokECS/Interfaces/IComponent.hpp>

#include <BTDSTD/IO/YAML.hpp>

#include <vector>
#include <string>

namespace Smok::ECS::Component
{
	//defines a mesh render component
	struct Mesh : public Interface::ICompoenent
	{
		bool isEnabled = true; //should this mesh render

		//the asset IDs
		uint64 staticMeshAssetID = 0,
			graphicsPipelineAssetID = 0,
			graphicsShaderAssetID = 0,
			textureAssetID = 0,
			samplerAssetID = 0;

		//the names for the assets
		std::string staticMeshName = "", //the static mesh
			graphicsPipelineName = "",
			graphicsShaderName = "",
			textureName = "",
			samplerName = "";

		std::vector<uint32> meshIndexsToRender; //the individual meshes of the larger mesh to render

		//updates if the mesh is enabled
		inline void SetIsEnabled(const bool& _isEnabled) {isEnabled = _isEnabled;}

		//updates the static mesh
		inline void SetStaticMesh(const uint64& assetID, const std::string assetName)
		{
			staticMeshName = assetName;
			staticMeshAssetID = assetID;
		}

		//updates the mesh indexes for rendering
		inline void SetMeshIndexes(const std::vector<uint32> meshIndexes) { meshIndexsToRender = meshIndexes; }

		//updates the graphics pipeline
		inline void SetGraphicsPipeline(const uint64& assetID, const std::string assetName)
		{
			graphicsPipelineName = assetName;
			graphicsPipelineAssetID = assetID;
		}

		//updates the graphics shader
		inline void SetGraphicsShader(const uint64& assetID, const std::string assetName)
		{
			graphicsShaderName = assetName;
			graphicsShaderAssetID = assetID;
		}

		//updates the texture
		inline void SetTexture(const uint64& assetID, const std::string assetName)
		{
			textureName = assetName;
			textureAssetID = assetID;
		}

		//updates the sampler
		inline void SetSampler(const uint64& assetID, const std::string assetName)
		{
			samplerName = assetName;
			samplerAssetID = assetID;
		}
	};

	//converts this Component into YAML data
	inline void Mesh_ConvertToYAML(YAML::Emitter& emitter, Mesh* component)
	{
		emitter << YAML::Key << "MeshComp" << YAML::Value << YAML::BeginMap;
		
		emitter << YAML::Key << "isEnabled" << YAML::Value << component->isEnabled;

		//std::vector<uint32> meshIndexsToRender; //the individual meshes of the larger mesh to render

		emitter << YAML::Key << "staticMeshName" << YAML::DoubleQuoted << component->staticMeshName;
		emitter << YAML::Key << "graphicsPipelineName" << YAML::DoubleQuoted << component->graphicsPipelineName;
		emitter << YAML::Key << "graphicsShaderName" << YAML::DoubleQuoted << component->graphicsShaderName;
		emitter << YAML::Key << "textureName" << YAML::DoubleQuoted << component->textureName;
		emitter << YAML::Key << "samplerName" << YAML::DoubleQuoted << component->samplerName;

		emitter << YAML::EndMap;
	}

	//converts YAML data into this Component
	inline void Mesh_ConvertFromYAML(Mesh* component, YAML::Node& data)
	{
		auto comp = data["MeshComp"];
		if (comp)
		{
			component->isEnabled = comp["isEnabled"].as<bool>();
		
			//std::vector<uint32> meshIndexsToRender; //the individual meshes of the larger mesh to render
		
			component->staticMeshName = comp["staticMeshName"].as<std::string>();
			component->graphicsPipelineName = comp["graphicsPipelineName"].as<std::string>();
			component->graphicsShaderName = comp["graphicsShaderName"].as<std::string>();
			component->textureName = comp["textureName"].as<std::string>();
			component->samplerName = comp["samplerName"].as<std::string>();
		}
	}
}