#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkSystemEvent.h"
#include "NKLogger/NkLog.h"
#include "NKContainers/String/NkString.h"
#include "NKEvent/NkEventSystem.h"
using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 800;
    cfg.height = 600;

    //cfg.minHeight = 200;
    //cfg.minWidth = 200;

    // les 7 droits
    cfg.resizable = false; 
    cfg.movable = true;  
    cfg.closable = true;  
    cfg.minimizable = false;  
    cfg.maximizable = true;  
    cfg.canFullscreen = false; 
    cfg.fullscreen = false; 

    NkWindow window(cfg);

    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    /*
    
    auto afficherComparaison = [&]() {
        auto size = window.GetSize();
        auto displaySize = window.GetDisplaySize();
        float32 scale = window.GetDpiScale();
        logger.Info(
            "Window: {}x{} | Display: {}x{} | DPI Scale: {}",
            size.x, size.y,
            displaySize.x, displaySize.y,
            scale
        );
    };
    

    // Affichage initial
    afficherComparaison();
    */

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

            
     bool EstModifie = false;
     auto& events = NkEvents();
     auto MettreAJourTitre = [&]() {
         auto taille = window.GetSize();

          NkString title = cfg.title;

          if (EstModifie)
             title += "*";

             title += " - ";
             title += NkString::Fmtf("%u", taille.x);
             title += " x ";
             title += NkString::Fmtf("%u", taille.y);

            window.SetTitle(title);
        };

         MettreAJourTitre();

         events.AddEventCallback<NkWindowResizeEvent>(
              [&](NkWindowResizeEvent *) {
              MettreAJourTitre();
        }
        );

        events.AddEventCallback<NkKeyPressEvent>(
            [&](NkKeyPressEvent *kp) {
                if (kp->GetKey() == NkKey::NK_M) {
                    EstModifie = !EstModifie;
                    MettreAJourTitre();
                }
            }
        );
            /* Réaffiche à chaque redimensionnement
            if (ev->As<NkWindowResizeEvent>()) {
                afficherComparaison();
            }

            // Réaffiche si l'échelle DPI change (changement d'écran ou réglage système)
            if (auto* disp = ev->As<NkSystemDisplayEvent>()) {
                if (disp->IsDpiChange()) {
                    afficherComparaison();
                }
            }
                */
        }
    }

    return 0;
}