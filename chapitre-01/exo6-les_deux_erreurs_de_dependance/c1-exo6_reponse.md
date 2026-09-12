## Apres avoir retirer les dependson et reconstruit, voici le message qui s'affiche :

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: pybind11                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

No source files found for project pybind11

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                       Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

No source files found for project MonEssai

## Apres avoir retirer le link et reconstruit, voici le message d'erreur qui s'affiche :
## J'ai remis  dependson  et retiré  links  : Les bibliothèques système Windows (user32, gdi32...) ne sont pas passées au linker.

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKXR                                                             Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 10 source file(s)
✓   [1/10] Compiled: NkArImu.cpp
✓   [2/10] Compiled: NkArFlow.cpp
✓   [3/10] Compiled: NkArCalibration.cpp
✓   [4/10] Compiled: NkArSession.cpp
✓   [5/10] Compiled: NkArMarker.cpp
✓   [6/10] Compiled: NkArWorld.cpp
✓   [7/10] Compiled: NkXrConfigEnv.cpp
✓   [8/10] Compiled: NkXrOpenXRBackend.cpp
✓   [9/10] Compiled: NkXrSession.cpp
✓   [10/10] Compiled: NkXrSimulatorBackend.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKXR.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 36.14s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                       Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

No source files found for project MonEssai

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NkImeTest                                                      Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

##   dependson  contrôle l'ordre de construction,  links  contrôle la résolution des symboles à l'édition de liens. Les deux sont nécessaires pour les bibliothèques du workspace.
