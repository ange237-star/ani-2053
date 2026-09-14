## Explication du fichier NKMath.jenga de NKentseu:
from Jenga import *
from jengaconfig import *

with project("NKMath"):
    language("C++")
    cppdialect("C++17")
    location(".")

    nkentseudependson(
        ["NKCore", "NKPlatform", "NKContainers", "NKMemory"],
        selfexport="NKMath",
        extra_includes=["src", "pch"],
    )

    pchheader("pch/pch.h")
    pchsource("pch/pch.cpp")

    files([
        "src/NKMath/**.cpp",
        "src/NKMath/**.h",
    ])

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")

    with filter("system:Windows && options:windows-runtime=uwp"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-uwp")

    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
        usetoolchain(TC_WINDOWS)
    with filter("system:UWP || system:Windows && options:windows-runtime=uwp"):
        usetoolchain("xbox-clang")
    with filter("system:macOS"):
        usetoolchain("clang-native")
    with filter("system:Android"):
        # Workaround: disable PCH on Android (NDK r27 + clang 18 + libc++)
        pchheader("")
        pchsource("")
        usetoolchain("android-ndk")
    with filter("system:HarmonyOS"):
        # PCH desactive (NDK OHOS clang, meme contrainte qu'Android)
        pchheader("")
        pchsource("")
        usetoolchain("ohos-ndk")
    with filter("system:Web"):
        usetoolchain("emscripten")
    with filter("system:XboxSeries || system:XboxOne"):
        usetoolchain("xbox-clang")

    with filter("config:Debug"):
        defines(["_DEBUG", "DEBUG"])
        optimize("Off")
        symbols(True)
    with filter("config:Release"):
        defines(["NDEBUG"])
        optimize("Speed")
        symbols(False)

    # Tests unitaires/benchmarks (desktop uniquement)
    with filter("(system:Linux || system:macOS || (system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne)) && !system:Android && !system:iOS || system:Web"):
        with test():
            testfiles(["tests/**.cpp"])

## Structure de la présentation

 Voici un fichier de projet Jenga. Ce n'est pas un fichier de configuration — c'est un programme Python. Tout ce qui est indenté sous `with project()` appartient à ce projet.

### 2. Ce qu'il déclare 

```python
with project("NKMath"):
    language("C++")           # Langage
    cppdialect("C++17")       # Standard C++
    location(".")             # Dossier du projet
```

**Explication :**
- `location(".")` : tout est relatif au dossier du projet
- Pas de `staticlib()` ici — le type vient du registre via `nkentseudependson`

---

### 3. Ce qu'il filtre 

Montrez les blocs `with filter` :

```python
    with filter("system:Windows && options:windows-runtime=uwp"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-uwp")

    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
        usetoolchain(TC_WINDOWS)
    with filter("system:UWP || system:Windows && options:windows-runtime=uwp"):
        usetoolchain("xbox-clang")
    with filter("system:macOS"):
        usetoolchain("clang-native")
    with filter("system:Android"):
        # Workaround: disable PCH on Android (NDK r27 + clang 18 + libc++)
        pchheader("")
        pchsource("")
        usetoolchain("android-ndk")
    with filter("system:HarmonyOS"):
        # PCH desactive (NDK OHOS clang, meme contrainte qu'Android)
        pchheader("")
        pchsource("")
        usetoolchain("ohos-ndk")
    with filter("system:Web"):
        usetoolchain("emscripten")
    with filter("system:XboxSeries || system:XboxOne"):
        usetoolchain("xbox-clang")

    with filter("config:Debug"):
        defines(["_DEBUG", "DEBUG"])
        optimize("Off")
        symbols(True)
    with filter("config:Release"):
        defines(["NDEBUG"])
        optimize("Speed")
        symbols(False)

```

**Explication**
- Un filtre = une condition ; le contenu ne s'applique que si elle est vraie
- `system:Windows` = uniquement sous Windows
- `system:Android` = uniquement sous Android
- `system:macOS` = uniquement sous macOS
- `config:Debug` vs `config:Release` = deux configurations de build
- Les variables `%{cfg.buildcfg}` et `%{cfg.system}` dans les chemins

---

### 4. Ce qu'il délègue 

Montrez l'appel au registre :

```python
nkentseudependson(
    ["NKCore", "NKPlatform", "NKContainers", "NKMemory"],
    selfexport="NKMath",
    extra_includes=["src", "pch"],
)
```

**Explication :**
- Cette fonction vient de `jengaconfig` — c'est du code maison, pas de Jenga
- Elle remplace 30 lignes de `includedirs` + `links` + `dependson`
- Elle résout les dépendances **transitives** automatiquement
- Le bénéfice : un fichier court, lisible, maintenable
- Le coût : il faut aller lire `config/modules.jenga` pour comprendre
