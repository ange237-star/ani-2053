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