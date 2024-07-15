 configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include "C:\\SmokSDK\\SmokGraphics"
    include "C:\\SmokSDK\\SmokWindow"

project "SmokTyGUI"
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
            
            files 
            {
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/imgui.h",
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/imgui.cpp",
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/imgui_demo.cpp",
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/imgui_draw.cpp",
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/imgui_widgets.cpp",
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/imgui_tables.cpp",
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/backends/imgui_impl_vulkan.h",
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/backends/imgui_impl_vulkan.cpp",
              "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/backends/imgui_impl_glfw.h",
             "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/backends/imgui_impl_glfw.cpp",
            }
        
            includedirs
            {
                "includes",
                
                "C:\\SmokSDK\\SmokGraphics\\includes",
                "C:\\SmokSDK\\SmokWindow\\includes",
                "C:\\SmokSDK\\Libraries\\BTD-Libs\\glm",
                "C:\\SmokSDK\\Libraries\\BTD-Libs\\glfw\\include",
    
                "C:\\VulkanSDK\\1.3.275.0\\Include",
                "C:\\SmokSDK\\Libraries\\SmokGraphics-Lib\\VulkanMemoryAllocator\\include",

                "C:\\SmokSDK\\BTDSTD\\BTDSTD\\includes",
                "C:\\SmokSDK\\BTDSTD\\BTDSTD_C\\includes",

                "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui",
                "C:\\SmokSDK\\Libraries\\SmokTyGUI-Libs\\imgui/backends",
            }
            
            links
            {
                "SmokGraphics",
                "SmokWindow"
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
             
                }
            
            filter "configurations:Release"
                defines "SMOK_RELEASE"
                optimize "On"
            
                flags
                {
                    "LinkTimeOptimization"
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
                   
                }