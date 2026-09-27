# Exercice — Le titre qui dit tout

## Objectif
Afficher dans le titre de la fenêtre : le nom du document, un astérisque s'il
est modifié, et la taille courante de la fenêtre. Le titre doit être mis à
jour au bon moment (lors d'un vrai changement), pas à chaque image.

## Code utilisé

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKLogger/NkLog.h"
#include "NKContainers/String/NkString.h"
#include "NKEvent/NkEventSystem.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 800;
    cfg.height = 600;

    cfg.resizable      = false;
    cfg.movable        = true;
    cfg.closable       = true;
    cfg.minimizable    = false;
    cfg.maximizable    = true;
    cfg.canFullscreen  = false;
    cfg.fullscreen     = false;

    NkWindow window(cfg);

    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    // Declare une seule fois, avant la boucle
    bool estModifie = false;
    auto& events = NkEvents();

    auto mettreAJourTitre = [&]() {
        auto taille = window.GetSize();
        NkString title = cfg.title;
        if (estModifie) {
            title += "*";
        }
        title += " - ";
        title += NkString::Fmtf("%u", taille.x);
        title += " x ";
        title += NkString::Fmtf("%u", taille.y);
        window.SetTitle(title);
    };

    mettreAJourTitre(); // titre initial

    // Callbacks enregistres une seule fois, avant la boucle
    events.AddEventCallback<NkWindowResizeEvent>(
        [&](NkWindowResizeEvent*) {
            // Le redimensionnement met a jour la taille affichee,
            // mais ne modifie pas l'etat "document modifie"
            mettreAJourTitre();
        }
    );

    events.AddEventCallback<NkKeyPressEvent>(
        [&](NkKeyPressEvent* kp) {
            if (kp->GetKey() == NkKey::NK_M) {
                estModifie = !estModifie;
                mettreAJourTitre();
            }
        }
    );

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

## Stratégie de mise à jour "au bon moment"

Le titre n'est reconstruit et réappliqué (`SetTitle`) que dans deux cas précis :
- lorsqu'un événement `NkWindowResizeEvent` est reçu (la taille a changé) ;
- lorsque la touche `M` est pressée, simulant une bascule de l'état "modifié"
  du document.

Il n'y a **aucun appel à `SetTitle()` dans la boucle principale** : celle-ci ne
fait que consommer les événements de fermeture et la touche Échap. Le titre
n'est donc jamais reconstruit "à chaque image" ou "à chaque tour de boucle",
uniquement au moment réel où l'information affichée change.

Point de vigilance corrigé pendant l'exercice : la déclaration de `estModifie`,
de la lambda `mettreAJourTitre`, et l'enregistrement des callbacks doivent se
faire **une seule fois, avant la boucle `while`** — les placer à l'intérieur de
la boucle d'événements aurait pour effet de réinitialiser l'état à chaque
passage et d'empiler un nouveau callback à chaque événement reçu.

## Résultat

- Au lancement : titre affichant `Ma fenetre - 800 x 600`
- Après appui sur `M` : `Ma fenetre* - 800 x 600`
- Après redimensionnement : la taille affichée dans le titre se met à jour et
  reflète la nouvelle taille de la fenêtre, sans que l'état "modifié" ne soit
  affecté par ce redimensionnement.

## Conclusion

Le titre reflète fidèlement l'état du programme (nom, modification, taille)
et n'est mis à jour que lors d'un changement réel de cet état, grâce à
l'utilisation de callbacks dédiés (`AddEventCallback`) plutôt qu'un appel
systématique à `SetTitle()` dans la boucle principale.

## PREUVE compilatiom
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
│  ✓ Build Successful                                                             Time: 7.75s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           7.75s
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
  ◀  FIN D'EXECUTION  —  termine normalement  (35.35s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```