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