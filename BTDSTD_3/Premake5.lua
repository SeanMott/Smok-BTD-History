configurations
    {
        "Debug",
        "Release",
        "Dist" --,

        --"Desktop_Debug",
        --"Desktop_Release",
        --"Desktop_Dist",

        --"Android_Debug",
        --"Android_Release",
        --"Android_Dist",

        --"IOS_Debug",
        --"IOS_Release",
        --"IOS_Dist",
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}"

include "C:/GameDev//BTDSTD-Deps/yaml-cpp"
include "C:/GameDev//BTDSTD-Deps/glfw"

project "BTDSTD"
kind "StaticLib"
language "C++"

targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")


files 
{
    "includes/**.h",
    "src/**.c",
    "includes/**.hpp",
    "src/**.cpp",


	--ImGUI file includes
	"C:/GameDev//BTDSTD-Deps/imgui/imgui.h",
	"C:/GameDev//BTDSTD-Deps/imgui/imgui.cpp",
	"C:/GameDev//BTDSTD-Deps/imgui/imgui_demo.cpp",
	"C:/GameDev//BTDSTD-Deps/imgui/imgui_draw.cpp",
	"C:/GameDev//BTDSTD-Deps/imgui/imgui_widgets.cpp",
	"C:/GameDev//BTDSTD-Deps/imgui/imgui_tables.cpp",
	"C:/GameDev//BTDSTD-Deps/imgui/backends/imgui_impl_vulkan.h",
	"C:/GameDev//BTDSTD-Deps/imgui/backends/imgui_impl_vulkan.cpp",
	"C:/GameDev//BTDSTD-Deps/imgui/backends/imgui_impl_glfw.h",
	"C:/GameDev//BTDSTD-Deps/imgui/backends/imgui_impl_glfw.cpp",

}

includedirs
{
    "includes",


	"C:/GameDev//BTDSTD-Deps/glfw/include",
	"C:/GameDev//BTDSTD-Deps/yaml-cpp/include",
	"C:/VulkanSDK/1.3.275.0/include",
	"C:/GameDev//BTDSTD-Deps/glm",
	"C:/GameDev//BTDSTD-Deps/imgui",
	"C:/GameDev//BTDSTD-Deps/imgui/backends",
}

links 
{
	"yaml-cpp",
	"GLFW",
	"C:/VulkanSDK/1.3.275.0/Lib/vulkan-1.lib",
}

defines 
{
	"GLFW_INCLUDE_NONE",
	"GLM_FORCE_RADIANS",
	"GLM_FORCE_DEPTH_ZERO_TO_ONE",
	"GLM_ENABLE_EXPERIMENTAL",
}

flags
{
    "NoRuntimeChecks",
    "MultiProcessorCompile"
}

filter "system:windows"
    cppdialect "C++20"
    --cdialect "C99"
    staticruntime "On"
    systemversion "latest"

defines 
{
	"Window_Build",
	"Desktop_Build",
}

filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"

links 
{
	"C:/GameDev//BTDSTD-Deps/Assimp_DLLs_Libs/lib/RelWithDebInfo/assimp-vc143-mt.lib",
	"C:/GameDev//BTDSTD-Deps/Assimp_DLLs_Libs/lib/RelWithDebInfo/draco.lib",
}

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

links 
{
	"C:/GameDev//BTDSTD-Deps/Assimp_DLLs_Libs/lib/RelWithDebInfo/assimp-vc143-mt.lib",
	"C:/GameDev//BTDSTD-Deps/Assimp_DLLs_Libs/lib/RelWithDebInfo/draco.lib",
}

filter "configurations:Dist"
    defines "BTD_DIST"
    optimize "On"

defines 
{
	"NDEBUG",
}

links 
{
	"C:/GameDev//BTDSTD-Deps/Assimp_DLLs_Libs/lib/Release/assimp-vc143-mt.lib",
	"C:/GameDev//BTDSTD-Deps/Assimp_DLLs_Libs/lib/Release/draco.lib",
}

