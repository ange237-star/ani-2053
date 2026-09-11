from Jenga import * 
from jengaconfig import *
import os


with project("NkAgentEcsDemo"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["src/main.cpp"])

    nkentseudependson(
        ["Noge", "NKAgent", "NKRL", "NKTensor", "NKRenderer", "NKRHI", "NKSL", "NKCollision", "NKPhysics",
         "NKSerialization", "NKFileSystem", "NKFont", "NKImage", "NKGlad",
         "NKECS", "NKEvent", "NKWindow", "NKMath", "NKTime", "NKLogger",
         "NKContainers", "NKMemory", "NKCore", "NKPlatform", "NKThreading"],
        extra_includes=["src", "%{Noge.location}/src"]
                       + ([VULKAN_INCLUDE] if VULKAN_INCLUDE else []),
    )

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
        usetoolchain(TC_WINDOWS)
        defines(["WIN32_LEAN_AND_MEAN", "_UNICODE", "UNICODE"])
        if VULKAN_LIB:
            libdirs([VULKAN_LIB])
        links(["user32", "gdi32", "opengl32", "dwmapi", "shell32",
               "d3d11", "d3d12", "dxgi", "dxguid", "d3dcompiler", "uuid", "ole32"])
