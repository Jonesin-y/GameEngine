workspace "Hazel"
    startproject "SandBox"

    outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    filter "system:windows"
        buildoptions { "/utf-8" }
    filter {}
    --Include directories relative to root folder (solution directory)
    IncludeDir = {}
    IncludeDir["GLFW"]= "Hazel/vendor/GLFW/include"
    IncludeDir["Glad"]= "Hazel/vendor/Glad/include"
    IncludeDir["imgui"]="Hazel/vendor/imgui"
    include "Hazel/vendor/GLFW"
    include "Hazel/vendor/Glad"
    include "Hazel/vendor/imgui"

project "Hazel"
    location "Hazel"
    kind "SharedLib"
    language "C++"
    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")
    pchheader "hzpch.h"
    pchsource "Hazel/src/Hazel/hzpch.cpp"
    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    includedirs{
        "$(SolutionDir)%{prj.name}/vendor/spdlog/include",
        "$(SolutionDir)%{prj.name}/src/Hazel",
        "$(SolutionDir)%{prj.name}/src/Platform",
        "$(SolutionDir)%{IncludeDir.GLFW}",
        "$(SolutionDir)%{IncludeDir.Glad}",
        "$(SolutionDir)%{IncludeDir.imgui}"
    }
    links{
        "imGui",
        "GLFW",
        "Glad",
        "opengl32.lib"
    }
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "off"
        systemversion "latest"
        defines{
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        postbuildcommands{
            ("IF NOT EXIST \"../bin/" ..outputdir.. "/SandBox\" mkdir \"../bin/" ..outputdir.. "/SandBox\""),
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
        }
    filter {}
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "HZ_RELEASE"
        runtime "Release"
        optimize "On"
    filter "configurations:Dist"
        defines "HZ_DIST"
        runtime "Release"
        optimize "On"
    filter{}
project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"
    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")
    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    includedirs{
        "$(SolutionDir)Hazel/vendor/spdlog/include",
        "$(SolutionDir)Hazel/src/Hazel"
    }
    links{
        "Hazel"
    }
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "off"
        systemversion "latest"
        defines{
            "HZ_PLATFORM_WINDOWS"
        }
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "HZ_RELEASE"
        runtime "Release"
        optimize "On"
    filter "configurations:Dist"
        defines "HZ_DIST"
        runtime "Release"
        optimize "On"
    filter {}