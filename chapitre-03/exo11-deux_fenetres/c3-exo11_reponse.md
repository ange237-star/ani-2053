#  EXERCICE 11: Ouvrez deux fenêtres et affichez, pour chaque clic, laquelle l'a reçu. Dites ensuite ce qui vous manquerait pour dessiner dans les deux.

## Mon programme
```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;


int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg1;
    cfg1.title = "F1";
    cfg1.width  = 800;
    cfg1.height = 600;
    cfg1.x = 400;
    cfg1.y = 300;

    NkWindowConfig cfg2;
    cfg2.title  = "F2";
    cfg2.width  = 800;
    cfg2.height = 600;
    cfg2.x      = 300;
    cfg2.y      = 200;

    NkWindow win1(cfg1);

    NkWindow win2(cfg2);

    if (!win1.IsOpen() || !win2.IsOpen()) {
        return -1;
    }

    while (win1.IsOpen() || win2.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                if (ev->GetWindowId() == win1.GetId()) {
                    std::cout << "\n[Fermeture] F1 fermee.";
                    win1.Close();
                }
                else if (ev->GetWindowId() == win2.GetId()) {
                    std::cout << "\n[Fermeture] F2 fermee.";
                    win2.Close();
                }
            }
            
            else if (auto* bp = ev->As<NkKeyPressEvent>()) {
                if (bp->GetKey() == NkKey::NK_ESCAPE) {
                    win1.Close();
                    win2.Close();
                }
            }
            
            else if (auto* br = ev->As<NkMouseButtonPressEvent>()) {
                if (ev->GetWindowId() == win1.GetId()) {
                    std::cout << "\n[CHARGE] Recu par F1 (bouton: " 
                              << static_cast<int>(br->GetButton()) 
                              << ", X: " << br->GetX() << ", Y: " << br->GetY() << ")";
                }
                else if (ev->GetWindowId() == win2.GetId()) {
                    std::cout << "\n[CHARGE] Recu par F2 (bouton: " 
                              << static_cast<int>(br->GetButton()) 
                              << ", X: " << br->GetX() << ", Y: " << br->GetY() << ")";
                }
            }
        }
    }

    return 0;
}
```
## Analyse
**Programme qui affiche deux fenetre F1 et F2 grace a `win1 `et `win2`. et dire quelle fenetre a recu un clic grace a `ev->GetWindowId()` et retourne dans le terminal les differente position de la fenetre qui recoit le clic**

## Resultat

```bash
PS C:\Users\Administrator\Chute\FirstWindow> jenga build

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Window [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Window                                                         Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Window\Window.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 17.68s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           17.70s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\Users\Administrator\Chute\FirstWindow> 
PS C:\Users\Administrator\Chute\FirstWindow> jenga r    

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Window.exe
     C:\Users\Administrator\Chute\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


[CHARGE] Recu par F2 (bouton: 1, X: 762, Y: 436)
[CHARGE] Recu par F2 (bouton: 1, X: 726, Y: 361)
[CHARGE] Recu par F1 (bouton: 1, X: 286, Y: 123)
[CHARGE] Recu par F1 (bouton: 1, X: 288, Y: 356)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (84.93s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```