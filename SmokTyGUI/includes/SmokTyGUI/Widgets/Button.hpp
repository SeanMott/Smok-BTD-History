#pragma once

//small wrapper around a button to get the name consisnly

#include <string>

#include <imgui.h>

namespace Smok::TyGUI::Util
{
	//calculates the width and height of a label
	inline ImVec2 CalculateLabelSize(const std::string& label, const float& baseWidth = 10, const float& baseHeight = 25)
	{
		return { baseWidth * label.size(), baseHeight };
	}

	//defines a button wrapper that stores the length of the lable and recalculates it when it's remade
	struct Button
	{
		float letterWidth = 10.0f, letterHeight = 25.0f;
		ImVec2 size;
		bool isDirty = true;

		std::string label = "";
		size_t labelLength = 0;

		//sets the label
		inline void SetLabel(const std::string& _label)
		{
			label = _label; labelLength = label.size(); isDirty = true;
		}

		//sets the base width

		//sets the base height

		//sets the base width and height
		inline void SetBaseLetterSize(const float& baseWidth, const float& baseHeight)
		{
			letterWidth = baseWidth; letterWidth = baseHeight; isDirty = true;
		}

		//draws the button
		inline void Draw()
		{
			if (isDirty)
			{
				size = { letterWidth * labelLength, letterHeight };
			}
		}
	};

	//creates a button
	static inline Button CreateButton(const std::string& label, const size_t& baseWidth = 10, const size_t& baseHeight = 25)
	{
		Button b; b.SetBaseLetterSize(baseWidth, baseHeight);
		b.SetLabel(label);
		return b;
	}
}