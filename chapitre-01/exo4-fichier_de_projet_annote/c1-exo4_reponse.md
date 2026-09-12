## Import du systeme jenga
from Jenga import * 
## Import de la configuration 
from jengaconfig import *
## ??
import os

## Declaration du projet
with project("NkAgentEcsDemo"):
   ## type de projet
    consoleapp()
   ## Langage de compilation
    language("C++")
## standart c++
    cppdialect("C++17")
## dossier du projet
    location(".")
## sources
    files(["src/main.cpp"])
## raccourci maison
    nkentseudependson(
        ["Noge", "NKAgent", "NKRL", "NKTensor", "NKRenderer", "NKRHI", "NKSL", "NKCollision", "NKPhysics",
         "NKSerialization", "NKFileSystem", "NKFont", "NKImage", "NKGlad",
         "NKECS", "NKEvent", "NKWindow", "NKMath", "NKTime", "NKLogger",
         "NKContainers", "NKMemory", "NKCore", "NKPlatform", "NKThreading"],
## inclusion supplementaires
        extra_includes=["src", "%{Noge.location}/src"]
## ??
                       + ([VULKAN_INCLUDE] if VULKAN_INCLUDE else []),
    )
## fichier intermediaire
    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
## resultat final: l'executable ici
    targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
## flitre
    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
## chaine de compilation
        usetoolchain(TC_WINDOWS)
## macros preprocesseur
        defines(["WIN32_LEAN_AND_MEAN", "_UNICODE", "UNICODE"])
## ??
        if VULKAN_LIB:
            libdirs([VULKAN_LIB])
## bibliotheques systeme windows
        links(["user32", "gdi32", "opengl32", "dwmapi", "shell32",
               "d3d11", "d3d12", "dxgi", "dxguid", "d3dcompiler", "uuid", "ole32"])
