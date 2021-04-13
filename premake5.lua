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

include "Variant/Vender/GLFW"

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
      "GLFW"
   }

   includedirs
   {
      "%{wks.location}/Variant/Vender/spdlog/include",
      "%{wks.location}/%{prj.name}/src",
      "%{includeDirs.GLFW}"
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
        "VR_WINDOWS"
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
       "%{wks.location}/Variant/src"
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