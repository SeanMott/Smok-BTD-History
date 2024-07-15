configurations
{
    "Debug",
    "Release",
    "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "C:\\GameDev\\SmokLibraries\\Engine\\SmokMesh"
include "C:\\GameDev\\SmokLibraries\\Engine\\SmokRenderers"

    project "SmokACT"
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
    }
    
    includedirs
    {
        "%{prj.location}/includes",

        "C:\\GameDev\\Libraries\\yaml-cpp\\include",
        "C:\\GameDev\\Libraries\\glm",
        "C:\\GameDev\\Libraries\\glfw\\include",
        
        "C:\\VulkanSDK\\1.3.239.0\\Include",
        "C:\\GameDev\\Libraries\\VulkanMemoryAllocator\\include",
    
        "C:\\GameDev\\BTDSTD/includes",
        "C:\\GameDev\\BTDSTD_C/includes",

        "C:\\GameDev\\Libraries/Assimp",

        "C:\\GameDev\\SmokLibraries\\Engine\\SmokGraphics\\includes",
        "C:\\GameDev\\SmokLibraries\\Engine\\SmokMesh\\includes",
        "C:\\GameDev\\SmokLibraries\\Engine\\SmokTexture\\includes",
        "C:\\GameDev\\SmokLibraries\\Engine\\SmokRenderers\\includes",
    }
    
    links
    {
        "SmokMesh",
        "SmokRenderers"
    }
        
        defines
        {
            "GLFW_STATIC",
            "GLFW_INCLUDE_NONE",
        }
        
        flags
        {
            --"LinkTimeOptimization",
            "NoRuntimeChecks",
            "MultiProcessorCompile"
        }

        --platforms
        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"
        
            defines
            {
                "Window_Build",
                "Desktop_Build"
            }
        
        --configs
        filter "configurations:Debug"
            defines "SMOK_DEBUG"
            symbols "On"
        
            links
            {
                "C:/GameDev/Libraries/Assimp/Debug-x64/assimp-vc142-mtd.lib",
            }
        
        filter "configurations:Release"
            defines "SMOK_RELEASE"
            optimize "On"
        
            flags
            {
                "LinkTimeOptimization"
            }

            links
            {
                "C:/GameDev/Libraries/Assimp/Release-x64/assimp-vc142-mt.lib",
            }
        
        filter "configurations:Dist"
            defines "SMOK_DIST"
            optimize "On"
        
            defines
            {
                "NDEBUG"
            }
        
            flags
            {
                "LinkTimeOptimization"
            }
        
            links
            {
                "C:/GameDev/Libraries/Assimp/Release-x64/assimp-vc142-mt.lib",
            }