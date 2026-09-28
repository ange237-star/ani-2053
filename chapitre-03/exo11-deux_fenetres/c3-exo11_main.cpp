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