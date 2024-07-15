workspace "Smok"
    --architecture "x86_64"
    architecture "x86"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDir = {}
includeDir["GLFW"] = "Library/GLFW/include"
includeDir["Glad"] = "Library/Glad/include"
includeDir["stb"] = "Library/stb"
includeDir["glm"] = "Library/glm"
includeDir["FastDelegate"] = "Library/FastDelegate"
includeDir["entt"] = "Library/entt/src"
includeDir["meta"] = "Library/meta/src"
includeDir["ImGUI"] = "Library/imgui"

--includes the premake files
include "Library/GLFW"
include "Library/Glad"
include "Library/stb"
include "Library/ImGui"

--Smok Core is the main lib and the core of the engine
project "SmokCore"
    location "SmokCore"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    pchheader "smpch.h"
    pchsource "%{prj.name}/src/smpch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs
    {
        "%{includeDir.Glad}",
        "%{includeDir.GLFW}",
        "%{includeDir.glm}",
        "%{includeDir.stb}",
        "%{includeDir.FastDelegate}",
        "%{includeDir.entt}",
        "%{includeDir.meta}",
        "SmokCore/src"
    }
    
    links
    {
        "StbImage",
        "Glad",
        "GLFW",
        "opengl32.lib"
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build"
        }
    
    filter "configurations:Debug"
        defines "SMOK_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "SMOK_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "SMOK_DIST"
        optimize "On"

--Smok GUI handles rendering GUI elements
--Can be disabled by defining DISABLE_SMOK_GUI
project "SmokGUI"
    location "SmokGUI"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    --pchheader "smpch.h"
    --pchsource "%{prj.name}/src/smpch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs
    {
        "%{includeDir.glm}",
        "%{includeDir.FastDelegate}",
        "%{includeDir.entt}",
        "%{includeDir.Glad}",
        "%{includeDir.GLFW}",
        "%{includeDir.ImGUI}",
        "SmokCore/src",
        "SmokGUI/src"
    }
    
    links
    {
        "SmokCore",
        "ImGui"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "SMOK_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "SMOK_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "SMOK_DIST"
        optimize "On"

--Smok 2D holds all the 2D elements, not the UI though that is in core.
--Can be disabled by defining DISABLE_SMOK_2D
project "Smok2D"
    location "Smok2D"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    --pchheader "smpch.h"
    --pchsource "%{prj.name}/src/smpch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs
    {
        "%{includeDir.glm}",
        "%{includeDir.FastDelegate}",
        "%{includeDir.entt}",
        "SmokCore/src",
        "Smok2D/src"
    }
    
    links
    {
        "SmokCore"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "SMOK_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "SMOK_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "SMOK_DIST"
        optimize "On"

--Smok 3D holds all the 3D elements
--Can be disabled by defining DISABLE_SMOK_3D
project "Smok3D"
    location "Smok3D"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    --pchheader "smpch.h"
    --pchsource "%{prj.name}/src/smpch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs
    {
        "%{includeDir.glm}",
        "%{includeDir.FastDelegate}",
        "%{includeDir.entt}",
        "SmokCore/src",
        "Smok3D/src"
    }
    
    links
    {
        "SmokCore"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "SMOK_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "SMOK_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "SMOK_DIST"
        optimize "On"

--Sandbox used to test the engine
project "Sandbox"
location "Sandbox"
kind "ConsoleApp"
language "C++"

targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

--pchheader "smpch.h"
--pchsource "%{prj.name}/src/smpch.cpp"

files 
{
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.hpp",
    "%{prj.name}/src/**.c",
    "%{prj.name}/src/**.cpp"
}

includedirs
{
    "%{includeDir.glm}",
    "%{includeDir.FastDelegate}",
    "%{includeDir.entt}",
    "%{includeDir.ImGUI}",
    "SmokCore/src",
    "Smok2D/src",
    "SmokGUI/src",
    "Sandbox/src"
}

links
{
    "SmokCore",
    "Smok2D",
    "SmokGUI"
}

defines
{
    "Smok2D_Link"--,
    --"Smok3D_Link"
}

filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Window_Build",
        "GLFW_INCLUDE_NONE"
    }

filter "configurations:Debug"
    defines "SMOK_DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "SMOK_RELEASE"
    optimize "On"

filter "configurations:Dist"
    defines "SMOK_DIST"
    optimize "On"
