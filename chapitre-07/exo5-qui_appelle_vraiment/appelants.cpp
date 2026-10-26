// Qui appelle Draw ? Une classe qui herite de NkDrawable et envoie quatre sommets.
#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Core/NkDrawable.h"
#include "NKCanvas/Renderer/Core/NkRenderer2DTypes.h"
#include "NKCanvas/Renderer/Targets/NkRenderTarget.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

// quatre sommets en NK_LINES : deux segments
class DeuxSegments : public NkDrawable {
public:
    void Draw(NkRenderTarget &target, const NkRenderStates &states) const override {
        NkVertex sommets[4] = {
            {100.f, 100.f, 0.f, 0.f, 255, 255, 255, 255},
            {300.f, 100.f, 0.f, 0.f, 255, 255, 255, 255},
            {100.f, 200.f, 0.f, 0.f, 255, 255, 255, 255},
            {300.f, 200.f, 0.f, 0.f, 255, 255, 255, 255},
        };
        target.Draw(sommets, 4, NkPrimitiveType::NK_LINES, states);   // <- point d'arret ici
    }
};

class Appelants : public NkCanvasApp {
public:
    Appelants() {
        Config().title = "Appelants";
        Config().width = 800;
        Config().height = 450;
    }

protected:
    void OnRender(NkRenderWindow &target) override {
        target.Draw(mObjet);
    }

private:
    DeuxSegments mObjet;
};

int nkmain(const NkEntryState &state) {
    return NkCanvasApp::Run<Appelants>(state);
}
