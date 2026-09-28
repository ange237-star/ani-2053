#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    // A CHANGER ENTRE LES DEUX ESSAIS 
     bool useCapture = false;   

    bool dragging = false;

    std::cout << " Essai " << (useCapture ? "AVEC" : "SANS")
              << " capture de la souris " << std::endl;

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
                else if(kp->GetKey()== NkKey::NK_C){
                    useCapture = !useCapture;
                    std::cout <<" /n Mode : " << (useCapture ?  "Active" : "Desactive") <<std::endl;
                }
            }
            
            // --- Debut du glisser : appui bouton gauche ---
            else if (auto* mp = ev->As<NkMouseButtonPressEvent>()) {
                if (mp->GetButton() == NkMouseButton::NK_MB_LEFT) {
                    dragging = true;
                    if (useCapture) {
                        window.CaptureMouse(true);
                    }
                    std::cout << "[APPUI] bouton gauche a ("
                              << mp->GetX() << ", " << mp->GetY() << ")" << std::endl;
                }
            }
            // Pendant le glisser : mouvements 
            else if (auto* mm = ev->As<NkMouseMoveEvent>()) {
                if (dragging) {
                    std::cout << "[GLISSE] client=(" << mm->GetX() << ", " << mm->GetY()
                              << ")  ecran=(" << mm->GetScreenX() << ", "
                              << mm->GetScreenY() << ")" << std::endl;
                }
            }
            // Fin du glisser : relachement bouton gauche
            else if (auto* mr = ev->As<NkMouseButtonReleaseEvent>()) {
                if (mr->GetButton() == NkMouseButton::NK_MB_LEFT) {
                    std::cout << "[RELACHE] bouton gauche a ("
                              << mr->GetX() << ", " << mr->GetY() << ")" << std::endl;
                    dragging = false;
                    if (useCapture) {
                        window.CaptureMouse(false);
                    }
                }
            }
          
        }
    }

    return 0;
}