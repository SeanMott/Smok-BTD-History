#pragma once

#include <string>

#include <imgui.h>

//defines a pop up prompt to input a string
namespace Smok::TyGUI::Util
{
	//draws the window for a text input
	static bool DrawStringInputPromptWindow(const char* windowName, char* buffer, std::string data)
	{
		ImGui::Begin(windowName);

		strcpy(buffer, data.data());
		if (ImGui::InputText(windowName, buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			strcpy(data.data(), buffer);
			ImGui::End();
			return true;
		}

		ImGui::End();
		return false;
	}
}