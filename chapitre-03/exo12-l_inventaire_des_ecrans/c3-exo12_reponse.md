# EXERCICE 12: Écrivez un programme qui affiche, pour chaque écran branché : sa taille, sa position, son facteur d'échelle, et lequel porte votre fenêtre. Déplacez la fenêtre d'un écran à l'autre et vérifiez que les valeurs suivent.

## Mon programme
```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

void ListMonitors(const NkWindow& window) {
    NkVector<NkDisplayInfo> monitors = window.EnumerateMonitors();
    std::cout << "Connected monitors: " << monitors.size() << std::endl;
    for (const auto& monitor : monitors) {
        float dpi = monitor.dpiScale;
        std::cout << "Monitor: " << monitor.name
                  << ", Size: " << monitor.width << "x" << monitor.height
                  << ", Position: " << monitor.posX << "x" << monitor.posY
                  << ", Primary: " << (monitor.isPrimary ? "Yes" : "No")
                  << ", DPI: " << dpi << std::endl;
    }
}
int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

   ListMonitors(window);
    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
            }

            
        }
    }

    return 0;
}
```
## Analyse
 **Grace a le fonction `ListMonitors` qui va permettre d'affiche la taille, la position, le facteur d'echelle, le nombre de moniteur connectes, et de savoir s'il s'agir du moniteur primaire ou non:**
```cpp
void ListMonitors(const NkWindow& window) {
    NkVector<NkDisplayInfo> monitors = window.EnumerateMonitors();
    std::cout << "Connected monitors: " << monitors.size() << std::endl;
    for (const auto& monitor : monitors) {
        float dpi = monitor.dpiScale;
        std::cout << "Monitor: " << monitor.name
                  << ", Size: " << monitor.width << "x" << monitor.height
                  << ", Position: " << monitor.posX << "x" << monitor.posY
                  << ", Primary: " << (monitor.isPrimary ? "Yes" : "No")
                  << ", DPI: " << dpi << std::endl;
    }
}
 ```
 **Apres avoir compiler ce programme avec jenga build et executer avec jenga r, il apparait dans mon terminal les informations demandees:**
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
│  ✓ Build Successful                                                            Time: 16.94s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           16.94s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

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

Connected monitors: 1
Monitor: \\.\DISPLAY7, Size: 1920x1080, Position: 0x0, Primary: Yes, DPI: 1.5

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (76.42s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 ```
 **Les informations sont :**
  ```bash
  Connected monitors: 1
  Monitor: \\.\DISPLAY7, Size: 1920x1080, Position: 0x0, Primary: Yes, DPI: 1.5

   ```
   ## Conclusion
   Il ya un moniteur connectee, Le moniteur est primaire avec une taille de 1920x1080, une position de 0x0 et un facteur d'echelle de 1,5 soit 150%.