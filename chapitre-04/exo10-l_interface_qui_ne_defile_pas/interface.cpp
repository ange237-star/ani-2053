// Un monde qui defile sous une barre d'interface qui, elle, ne bouge pas.
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKCanvas/Renderer/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Core/NKRenderer2D.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

class InterfaceFixe : public NkCanvasApp {
public:
    InterfaceFixe() {
        Config().title = "Interface qui ne defile pas";
        Config().width = 800;
        Config().height = 450;
    }

protected:
    bool OnInit() override {
        mPolice.LoadFromFile(*Target().GetRenderer(), "assets/Roboto-Regular.ttf");
        return true;
    }

    void OnUpdate(float32 dt) override {
        mCentreX += 120.f * dt;     // la camera avance avec dt, pas avec un compteur
    }

    void OnRender(NkRenderWindow &target) override {
        NkRenderer2D &r = target.GetRenderer2D();

        // le monde, vu par une camera qui se deplace
        NkView2D vue = target.GetDefaultView();
        vue.center = {mCentreX, vue.center.y};
        target.SetView(vue);
        for (int i = 0; i < 40; i++) {
            r.DrawFilledRect({i * 120.f, 200.f, 60.f, 60.f}, NkColor2D{80, 160, 220, 255});
        }

        // la vue est un etat du renderer : sans cette ligne la barre suit la camera
        target.ResetView();
        // target.ResetView();   <- version fautive : on retire cette ligne (sans.png)

        r.DrawFilledRect({0.f, 0.f, 800.f, 40.f}, NkColor2D{40, 40, 60, 255});
        NkText titre(mPolice, "Barre d'interface", 20);
        titre.SetFillColor(NkColor2D::White);
        titre.SetPosition({10.f, 28.f});          // ligne de base du texte
        r.Draw(titre);

        // une ligne de journal par seconde environ, a recopier dans journal.txt
        if (static_cast<int>(mCentreX) % 120 < 2) {
            NkVec2i barre = target.MapCoordsToPixel({0.f, 0.f});
            std::printf("reset : oui, centre_x : %d, barre_x : %d\n",
                        static_cast<int>(mCentreX), barre.x);
        }
    }

private:
    NkFont mPolice;
    float32 mCentreX = 400.f;
};

int nkmain(const NkEntryState &state) {
    return NkCanvasApp::Run<InterfaceFixe>(state);
}
