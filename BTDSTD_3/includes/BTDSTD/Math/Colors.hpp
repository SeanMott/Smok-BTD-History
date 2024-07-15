#pragma once

//defines various color operations

#include <BTDSTD/Math/Vectors.hpp>

namespace BTD::Math
{
	//defines a color struct
	struct Color
	{
		float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;

		//converts to a vec4 useable in the renderer since we need to shuffle colors around
		inline glm::vec4 ShuffleColorsForRendering()
		{
			return { b, r, g, a };
		}

		//converts to a vec4 useable in the renderer since we need to shuffle colors around
		static inline glm::vec4 ShuffleColorsForRendering(const Color color)
		{
			return { color.b, color.r, color.g, color.a };
		}

		//converts from a GLM vec4
				 
		//converts from a BTD vec4

		//converts to a GLM vec4

		//converts to a BTD vec4

		//create color from RGBA
		inline void CreateFromRGBA(const float _r, const float _g, const float _b, const float _a)
		{
			r = _r; g = _g; b = _b; a = _a;
		}

		//creates color from CMYK

		//generates the color black

		//generates the color white

		//generates the color red

		//generates the color blue

		//generates the color green

		//generates the color yellow

		//generates the color teal

		//generates light pink
		//static inline Color LightPink() { {return { 0.100f, 0.71f, 0.76f, 0.255f };}
	};
}