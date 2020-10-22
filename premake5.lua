workspace "Nimbus"
	architecture "x64"
	startproject "Nimbus"
	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}/%{cfg.architecture}/%{prj.name}"
	
	-- Includes
	IncludeDir = {}

	IncludeDir["SpdLog"] = "Nimbus/vendor/spdlog/include"
	IncludeDir["DirectX11"] = "Nimbus/vendor/DirectX"

	group ""

	project "Nimbus"
		location "Nimbus"
		kind "WindowedApp"
		language "C++"
		cppdialect "C++17"
		
		targetdir ("%{wks.location}/bin/"..outputdir)
		objdir ("%{wks.location}/bin-int/" .. outputdir)
		debugdir("%{wks.location}/bin/"..outputdir)

		prebuildcommands {
			"md $(TargetDir)Resources/Shaders & set errorlevel=0",
			"xcopy %{prj.location}src\\Nimbus\\Resources\\Fonts\\* $(TargetDir)Resources\\Fonts\\ /Y"
		}

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
			"%{IncludeDir.SpdLog}",
			"%{IncludeDir.DirectX11}"
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
			shaderobjectfileoutput("%{wks.location}/bin/"..outputdir.."/Shaders/%{file.basename}.cso")

		filter { "files:**_p.hlsl" }
			removeflags "ExcludeFromBuild"
			shadertype "Pixel"

		filter { "files:**_v.hlsl" }
			removeflags "ExcludeFromBuild"
			shadertype "Vertex"
