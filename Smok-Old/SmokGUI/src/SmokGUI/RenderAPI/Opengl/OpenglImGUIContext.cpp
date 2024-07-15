#include "OpenglImGUIContext.h"

#include <imgui.h>

#include <examples\imgui_impl_opengl3.h>

#include <Renderer\Display.h>

#include <SmokGUI\ImGUIBuild.h>

#include ImGUIPlatformIncludePath

void OpenglImGUIContext::Init()
{
	ImGUIPlatformInit(DisplayI.GetWindow());
	ImGui_ImplOpenGL3_Init("#version 410");
}

void OpenglImGUIContext::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGUIPlatformDestroy;
	ImGui::DestroyContext();
}

void OpenglImGUIContext::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGUIPlatformNewFrame;
	ImGui::NewFrame();
}

void OpenglImGUIContext::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
