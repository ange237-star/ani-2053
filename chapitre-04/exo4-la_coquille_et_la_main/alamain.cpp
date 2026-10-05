*#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/App/NkCanvasApp.h"

#include "NKMath/NKMath.h"
#include "NKTime/NkTime.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Ma fenêtre";
    cfg.width  = 1280;
    cfg.height = 720;

    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    //Cible
    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_DX12;

    renderer::NkRenderWindow rendererWindow(window, desc);

    if(!rendererWindow.IsValid()){
        return 2;
    }

    math::NkRect2f carre{20, 20, 50, 50};

    // 3) Boucle principale 
    while (window.IsOpen()) {
        float32 dt = 100.f; // Vitesse par seconde

      while (NkEvent* ev = NkEvents().PollEvent()) {
        if (ev->Is<NkWindowCloseEvent>()) {
            window.Close();          // l'utilisateur veut fermer
        }
        else if (auto* kp = ev->As<NkKeyPressEvent>()) {
            if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
        }

        if (auto* kp = ev->As<NkKeyPressEvent>()) {
            if (kp->GetKey() == NkKey::NK_UP){
                carre.y -= dt;
            }
            if (kp->GetKey() == NkKey::NK_DOWN){
                carre.y += dt;
            }
            if (kp->GetKey() == NkKey::NK_RIGHT){
                carre.x += dt;
            }
            if (kp->GetKey() == NkKey::NK_LEFT){
                carre.x -= dt;
            }
        }
    }

    rendererWindow.Clear(renderer::NkColor2D(36, 36, 36, 255));
    renderer::NkRenderer2D &c2d = rendererWindow.GetRenderer2D();

    c2d.DrawFilledRect(carre, renderer::NkColor2D{255, 0, 0, 255});

    rendererWindow.Display();

    }

    return 0;

}