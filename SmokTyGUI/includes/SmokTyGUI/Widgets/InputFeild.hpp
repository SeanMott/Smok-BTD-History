#pragma once

//defines a input feild widget

#include <SmokTyGUI/Widgets/Button.hpp>

#include <string>

namespace Smok::TyGUI::Util
{
	//defines a input feild widget
	inline bool InputTextFeild(const char* label, std::string& data)
	{
		char scratchBuffer[999];
		memset(scratchBuffer, '\0', sizeof(scratchBuffer));
		strcpy(scratchBuffer, data.data());
		if (ImGui::InputText(label, scratchBuffer, sizeof(scratchBuffer)))
		{
			data.resize(strlen(scratchBuffer));
			strcpy(data.data(), scratchBuffer);
			return true;
		}

		return false;
	}
}