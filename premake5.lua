workspace "Nimbus"
	architecture "x64"
	startproject "Nimbus"
	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
	
	-- Includes
	IncludeDir = {}

	IncludeDir["SpdLog"] = "Nimbus/vendor/spdlog/include"

	group ""

	project "Nimbus"
		location "Nimbus"
		kind "WindowedApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		
		
		targetdir ("bin/"..outputdir)
		objdir ("bin-int/" .. outputdir)
		debugdir "$(OutDir)"

		pchheader "pch.h"
		pchsource "Nimbus/src/pch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.hlsl",
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{IncludeDir.SpdLog}"
		}

		links
		{
			"includes/libs/x64/%{cfg.buildcfg}/*"
		}

		filter "system:windows"
			systemversion "latest"

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
			

		filter "configurations:Release"
			runtime "Release"
			optimize "on"


		filter { "files:**.hlsl" }
			shadermodel "5.0"
			flags("ExcludeFromBuild")
			shaderobjectfileoutput("$(OutDir)%{file.basename}.cso")

		filter { "files:**_p.hlsl" }
			removeflags "ExcludeFromBuild"
			shadertype "Pixel"

		filter { "files:**_v.hlsl" }
			removeflags "ExcludeFromBuild"
			shadertype "Vertex"