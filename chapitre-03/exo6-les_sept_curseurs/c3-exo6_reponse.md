# Exercice 6 : Les sept curseurs

##  Objectif
Diviser la largeur de la fenêtre en **7 zones égales** et changer dynamiquement l'apparence du curseur de la souris en fonction de la zone survolée, en utilisant les types de curseurs fournis par l'API `NkWindow`.

## Programme
 ```cpp
 #include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

// Les 7 types de curseurs
const NkWindow::NkCursorType cursors[7] = {
    NkWindow::NkCursorType::Arrow,
    NkWindow::NkCursorType::TextInput,
    NkWindow::NkCursorType::Hand,
    NkWindow::NkCursorType::ResizeNS,
    NkWindow::NkCursorType::ResizeWE,
    NkWindow::NkCursorType::ResizeNWSE,
    NkWindow::NkCursorType::ResizeNESW
};

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo6 - Les sept curseurs";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    int currentZone = -1; // aucune zone au depart

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
            // Detection du deplacement de la souris
            else if (auto* mm = ev->As<NkMouseMoveEvent>()) {
                float mouseY = static_cast<float>(mm->GetY());
                float windowHeigth = static_cast<float>(window.GetSize().y);

                // Decoupage en 7 zones egales
                float zHeight = windowHeigth / 7.0f;
                int newZone = static_cast<int>(mouseY / zHeight);

                if (newZone < 0) newZone = 0;
                if (newZone > 6) newZone = 6;

                // Application du nouveau curseur lors du changement de zone
                if (newZone != currentZone) {
                    currentZone = newZone;
                    window.SetCursor(cursors[currentZone]);
                    std::cout << "Survol Zone " << currentZone
                              << " -> Curseur modifie." << std::endl;
                }
            }
        }
    }

    return 0;
}
 ```

## Tableau des 7 curseurs

| Zone | Forme demandee| Forme obtenue |
| --- | --- | --- |
| **0** | `Arrow` | Flèche standard |
| **1** | `TextInput` | I-beam |
| **2** | `Hand` | Main ouverte |
| **3** | `ResizeNS` | Flèche double verticale |
| **4** | `ResizeWE` | Flèche double horizontale  |
| **5** | `ResizeNWSE` | Flèche double diagonale ↘ |
| **6** | `ResizeNESW` | Flèche double diagonale ↙ |

## Analyse du code fonctionnel (7 zones dynamiques)

Le premier extrait de code est la solution correcte. Voici pourquoi il fonctionne :

1. **Tableau de mappage** : Un tableau constant `cursors[7]` associe chaque indice (0 à 6) à un type de curseur spécifique.
2. **Détection du mouvement** : L'événement `NkMouseMoveEvent` est écouté dans la boucle principale, ce qui permet de connaître la position `X` de la souris en temps réel.
3. **Calcul de la zone** : 
```cpp
   float zWidth = windowWidth / 7.0f;
   int newZone = static_cast<int>(mouseX / zWidth);
```
   La division par `7.0f` (flottant) garantit un calcul précis, et le cast en `int` donne un indice de tableau valide.
4. **Sécurisation (Bornage)** : Les conditions `if (newZone < 0)` et `if (newZone > 6)` empêchent tout débordement de tableau (out-of-bounds).
5. **Optimisation** : Le curseur n'est mis à jour (`window.SetCursor`) **que si la zone change** (`newZone != currentZone`). Cela évite d'appeler l'API graphique inutilement à chaque pixel de déplacement.

##  Analyse du code à "un seul appel" 
 
 ```cpp
 #include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

// Les 7 types de curseurs
const NkWindow::NkCursorType cursors[7] = {
    NkWindow::NkCursorType::Arrow,
    NkWindow::NkCursorType::TextInput,
    NkWindow::NkCursorType::Hand,
    NkWindow::NkCursorType::ResizeNS,
    NkWindow::NkCursorType::ResizeWE,
    NkWindow::NkCursorType::ResizeNWSE,
    NkWindow::NkCursorType::ResizeNESW
};

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo6 - Les sept curseurs";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    window.SetCursor(NkWindow::NkCursorType::Arrow); // Curseur initial

    int currentZone = -1; // aucune zone au depart

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
            /* 
            // Detection du deplacement de la souris
            else if (auto* mm = ev->As<NkMouseMoveEvent>()) {
                float mouseY = static_cast<float>(mm->GetY());
                float windowHeigth = static_cast<float>(window.GetSize().y);

                // Decoupage en 7 zones egales
                float zHeight = windowHeigth / 7.0f;
                int newZone = static_cast<int>(mouseY / zHeight);

                if (newZone < 0) newZone = 0;
                if (newZone > 6) newZone = 6;

                // Application du nouveau curseur lors du changement de zone
                if (newZone != currentZone) {
                    currentZone = newZone;
                    window.SetCursor(cursors[currentZone]);
                    std::cout << "Survol Zone " << currentZone
                              << " -> Curseur modifie." << std::endl;
                }
            }
                */
        }
    }

    return 0;
}
 ```

Le second extrait de code laisse le curseur identique (flèche standard) pour les raisons suivantes :

1. **Absence d'écoute du mouvement** : Le bloc `else if (auto* mm = ev->As<NkMouseMoveEvent>())` est totalement absent. Le programme est "aveugle" au déplacement de la souris.
2. **Appel unique et statique** : `window.SetCursor(NkWindow::NkCursorType::Arrow);` n'est exécuté qu'une seule fois, avant la boucle `while`.
3. **Variable inerte** : Bien que `currentZone` soit déclarée, elle n'est jamais calculée, mise à jour ou comparée.

## PREUVE
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
│  ✓ Build Successful                                                             Time: 4.74s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           4.74s
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

Survol Zone 0 -> Curseur modifie.
Survol Zone 1 -> Curseur modifie.
Survol Zone 0 -> Curseur modifie.
Survol Zone 1 -> Curseur modifie.
Survol Zone 2 -> Curseur modifie.
Survol Zone 3 -> Curseur modifie.
Survol Zone 4 -> Curseur modifie.
Survol Zone 5 -> Curseur modifie.
Survol Zone 6 -> Curseur modifie.
Survol Zone 5 -> Curseur modifie.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (26.78s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\Administrator\Chute\FirstWindow>


                                             jenga build

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
│  ✓ Build Successful                                                             Time: 5.00s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           5.00s
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


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (35.56s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\Administrator\Chute\FirstWindow> 
```