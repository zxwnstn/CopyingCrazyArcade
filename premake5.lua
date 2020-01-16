workspace "CopyingGameProject"
	configurations
	{
		"Debug",
		"Release"
	}

	platforms
	{
		"x86",
		"x64"
	}
	characterset ("MBCS")


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "CrazyArcade"
	location "CrazyArcade"
	kind "WindowedApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"