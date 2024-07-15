#pragma once

//defines various materials

#include <BTDSTD/Graphics/Pipeline/GraphicsPipeline.hpp>

namespace BTD::Asset
{
	//defines a unlit material
	struct UnlitMaterial
	{
		uint64 assetID = 0;

		//the pipeline data
		uint64 pipelineLayoutAssetID = 0,
			pipelineAssetID = 0;

		//the textures
	};
}