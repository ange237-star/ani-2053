// Meme carre rouge, mais avec la fenetre, la cible et la boucle ecrites a la main.
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKTime/NkClock.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "Carre (a la main)";
    cfg.width = 800;
    cfg.height = 450;
    cfg.centered = true;
    cfg.resizable = true;

    NkWindow window;
    if (!window.Create(cfg)) return -1;          // verification 1 : la fenetre

    NkContextDesc desc = NkContextDesc::MakeSoftware();
    NkRenderWindow target(window, desc);
    if (!target.IsValid()) {                      // verification 2 : le contexte
        window.Close();
        return -2;
    }

    bool running = true;
    auto &events = NkEvents();
    events.AddEventCallback<NkWindowCloseEvent>([&](NkWindowCloseEvent *) { running = false; });

    NkClock clock;
    float32 x = 0.f;

    while (running && window.IsOpen()) {
        float32 dt = clock.Tick().delta;
        if (dt > 0.1f) dt = 0.1f;

        while (NkEvent *ev = events.PollEvent()) {
            (void)ev;
        }

        x += 100.f * dt;
        if (x > 800.f) x = -50.f;

        target.Clear(NkColor2D{18, 18, 24, 255});
        target.GetRenderer2D().DrawFilledRect({x, 200.f, 50.f, 50.f}, NkColor2D::Red);
        target.Display();
    }

    window.Close();
    return 0;
}
