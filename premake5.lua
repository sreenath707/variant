workspace "Variant"
   architecture "x64"

   configurations
   {
       "Debug",
       "Release",
       "Dist"
   }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"  

includeDirs ={}
includeDirs["GLFW"] = "%{wks.location}/Variant/Vender/GLFW/include"
includeDirs["glad"] = "%{wks.location}/Variant/vender/glad/include"
includeDirs["imgui"] = "%{wks.location}/Variant/vender/imgui"


include "Variant/Vender/GLFW"
include "Variant/Vender/glad"
include "Variant/Vender/imgui"

project "Variant"
   location "Variant"
   language "C++"
   kind "SharedLib"

    targetdir ("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputDir .. "/%{prj.name}")

   files 
   {
       "%{prj.name}/src/**.cpp",
       "%{prj.name}/src/**.h"
   }

   links
   {
      "GLFW",
      "glad",
      "imgui"
   }

   includedirs
   {
      "%{wks.location}/Variant/Vender/spdlog/include",
      "%{wks.location}/%{prj.name}/src",
      "%{includeDirs.GLFW}",
      "%{includeDirs.glad}",
      "%{includeDirs.imgui}"
   }

   postbuildcommands
   {
       ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputDir .."/SandBox")
   }

   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "10.0.18362.0"

      defines
      {
        "VR_DLL",
        "VR_WINDOWS",
        "GLFW_INCLUDE_NONE"
      }

      pchheader "vrpch.h"
      pchsource "Variant/src/vrpch.cpp"


    filter "configurations:Debug"
        defines
        {
           "VR_DEBUG",
           symbols "On"
        }


    filter "configurations:Release"
        defines
        {
           "VR_RELEASE",
            optimize "On"
        }

    filter "configurations:Dist"
        defines
        {
           "VR_DIST",
            optimize "On"
        }

    
project "SandBox"
   location "SandBox"
   language "C++"
   kind "consoleApp"

   targetdir ("%{wks.location}/bin/" ..outputDir .."/%{prj.name}")
   objdir ("%{wks.location}/bin/" ..outputDir .."/%{prj.name}")
   
   files 
   {
       "%{prj.name}/src/**.cpp",
       "%{prj.name}/src/**.h"
   }
   
   includedirs
   {
       "%{wks.location}/Variant/Vender/spdlog/include",  
       "%{wks.location}/Variant/src",
       "%{includeDirs.GLFW}",
       "%{includeDirs.glad}",
       "%{includeDirs.imgui}"
   }
   
   links
   {
       "Variant"
   }

   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "10.0.18362.0"
   
      defines
      {
        "VR_WINDOWS"
      }
   
    filter "configurations:Debug"
        defines
        {
           "VR_DEBUG",
           symbols "On"
        }
   
    filter "configurations:Release"
        defines
        {
           "VR_RELEASE",
            optimize "On"
        }
   
    filter "configurations:Dist"
        defines
        {
           "VR_DIST",
            optimize "On"
        }