include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Hazel"
	architecture "x86_64"
	startproject "HazelEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Hazel/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Hazel/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Hazel/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Hazel/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Hazel/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Hazel/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Hazel/vendor/ImGuizmo"
IncludeDir["Box2D"] = "%{wks.location}/Hazel/vendor/Box2D/include"

group "Dependencies"
	include "vendor/premake"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
	include "Hazel/vendor/imgui"
	include "Hazel/vendor/yaml-cpp"
	include "Hazel/vendor/Box2D"
group ""

include "Hazel"
include "Sandbox"
include "HazelEditor"