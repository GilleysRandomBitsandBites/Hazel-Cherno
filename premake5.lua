workspace "Hazel"
    architecture "x64"

	configurations
	{
	     "Debug",
		 "Release",
		 "Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazel"
    location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" ..outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Hazel/src/pch.cpp"

	files
	{
	    "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
	    "%{prj.name}/src",
	    "%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
	    cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

     defines
	 {
           "HZ_PLATFORM_WINDOWS",
		   "HZ_BUILD_DLL"
	 }

	 postbuildcommands
	 {
	     ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir .. "/Sandbox")
	 }

	 filter "configuration.Debug"
	     defines "HZ_DEBUG"
		 symbols "On"

	 filter "configuration.Release"
	     defines "HZ_RELEASE"
		 optimize "On"

	 filter "configuration.Dist"
	     defines "HZ_DIST"
		 optimize "On"

project "Sandbox"
    location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" ..outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir .. "/%{prj.name}")

	files
	{
	    "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
	    "Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	links
	{
	    "Hazel"
	}

	filter "system:windows"
	    cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

     defines
	 {
           "HZ_PLATFORM_WINDOWS"
	 }

	
	 filter "configuration.Debug"
	     defines "HZ_DEBUG"
		 symbols "On"

	 filter "configuration.Release"
	     defines "HZ_RELEASE"
		 optimize "On"

	 filter "configuration.Dist"
	     defines "HZ_DIST"
		 optimize "On"