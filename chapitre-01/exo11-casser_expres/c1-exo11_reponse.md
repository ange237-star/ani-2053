## Apres avoir retirer le point virgule a la ligne 70 du fichier NKVect.h qui se trouve dans le projet NKMath, voici l'erreur qui s'affiche apres avoir tape la commande jenga build --projet NKMath --cofig DEbug :

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMath                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 12 source file(s)
✓   [1/12] Compiled: NkAngle.cpp
✓   [2/12] Compiled: NkEulerAngle.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkColor.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkColor.cpp:18:        ║
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkColor.h:82:          ║
║ C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkVec.h:70:15: error: expected ';' at end of ║
║ declaration list                                                                             ║
║    70 |                                                                 T x, y               ║
║       |                                                                       ^              ║
║       |                                                                       ;              ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkColor.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: NkMat.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkMat.cpp:1:           ║
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath/NkMat.h:36:            ║
║ C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkVec.h:70:15: error: expected ';' at end of ║
║ declaration list                                                                             ║
║    70 |                                                                 T x, y               ║
║       |                                                                       ^              ║
║       |                                                                       ;              ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkMat.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkQuat.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkQuat.cpp:21:         ║
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkQuat.h:40:           ║
║ C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkVec.h:70:15: error: expected ';' at end of ║
║ declaration list                                                                             ║
║    70 |                                                                 T x, y               ║
║       |                                                                       ^              ║
║       |                                                                       ;              ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkQuat.cpp
✓   [6/12] Compiled: NkFunctions.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkRandom.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRandom.cpp:21:       ║
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkRandom.h:37:         ║
║ C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkVec.h:70:15: error: expected ';' at end of ║
║ declaration list                                                                             ║
║    70 |                                                                 T x, y               ║
║       |                                                                       ^              ║
║       |                                                                       ;              ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRandom.cpp
✓   [8/12] Compiled: NkRange.cpp
✓   [9/12] Compiled: NkSIMD.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                              Compilation Error: NkRectangle.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle.cpp:24:    ║
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkRectangle.h:32:      ║
║ C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkVec.h:70:15: error: expected ';' at end of ║
║ declaration list                                                                             ║
║    70 |                                                                 T x, y               ║
║       |                                                                       ^              ║
║       |                                                                       ;              ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: NkVec.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkVec.cpp:13:          ║
║ C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkVec.h:70:15: error: expected ';' at end of ║
║ declaration list                                                                             ║
║    70 |                                                                 T x, y               ║
║       |                                                                       ^              ║
║       |                                                                       ;              ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkVec.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkSegment.cpp                               ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkSegment.cpp:21:      ║
║ In file included from C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkSegment.h:31:        ║
║ C:\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkVec.h:70:15: error: expected ';' at end of ║
║ declaration list                                                                             ║
║    70 |                                                                 T x, y               ║
║       |                                                                       ^              ║
║       |                                                                       ;              ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkSegment.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                Time: 24.46s  │
│ Errors: 14  | Failed files: 7                                                                │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  9/213
Failed:         1
Not reached:    203  (arret au premier echec — voir --keep-going)
Errors:         14
Time:           5m5.9s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ NKMath

## Apres avoir remis le point virgule et reconstruire , voici le resultat:

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMath                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 12 source file(s)
✓   [6/12] Compiled: NkQuat.cpp
✓   [7/12] Compiled: NkMat.cpp
✓   [8/12] Compiled: NkRandom.cpp
✓   [9/12] Compiled: NkRectangle.cpp
✓   [10/12] Compiled: NkSegment.cpp
✓   [11/12] Compiled: NkColor.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMath.lib
