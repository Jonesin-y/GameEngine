workspace "Hazel"
    outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    filter "system:windows"
        buildoptions { "/utf-8" }
    filter {}
    --Include directories relative to root folder (solution directory)
    IncludeDir = {}
    IncludeDir["GLFW"]= "Hazel/vendor/GLFW/include"
    include "Hazel/vendor/GLFW"
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
        "$(SolutionDir)%{IncludeDir.GLFW}"
    }
    links{
        "GLFW",
        "opengl32.lib"
    }
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        defines{
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL"
        }
        postbuildcommands{
            ("IF NOT EXIST \"../bin/" ..outputdir.. "/SandBox\" mkdir \"../bin/" ..outputdir.. "/SandBox\""),
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
        }
    filter {}
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        buildoptions "/MDd"
        symbols "On"
    filter "configurations:Release"
        defines "HZ_RELEASE"
        buildoptions "/MD"
        optimize "On"
    filter "configurations:Dist"
        defines "HZ_DIST"
        buildoptions "/MD"
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
        staticruntime "On"
        systemversion "latest"
        defines{
            "HZ_PLATFORM_WINDOWS"
        }
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        buildoptions "/MDd"
        symbols "On"
    filter "configurations:Release"
        defines "HZ_RELEASE"
        buildoptions "/MD"
        optimize "On"
    filter "configurations:Dist"
        defines "HZ_DIST"
        buildoptions "/MD"
        optimize "On"
    filter {}