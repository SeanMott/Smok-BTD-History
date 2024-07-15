//stores data need for the ImGUI build

#ifndef ImGUIBuild_h
#define ImGUIBuild_h

#ifdef Window_Build

#define ImGUIPlatformIncludePath <examples\imgui_impl_glfw.h>
#define ImGUIPlatformBuildPath <examples\imgui_impl_glfw.cpp>

#define ImGUIPlatformInit(window) ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window, true)
#define ImGUIPlatformNewFrame ImGui_ImplGlfw_NewFrame()
#define ImGUIPlatformDestroy ImGui_ImplGlfw_Shutdown()
#define ImGUIPlatformContextType GLFWwindow*
#define ImGUIPlatformGetContext glfwGetCurrentContext()
#define ImGUIPlatformMakeContext(context) glfwMakeContextCurrent(context)

#endif

#endif