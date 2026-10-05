#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/App/NkCanvasApp.h"

#include "NKMath/NKMath.h"
#include "NKTime/NkTime.h"

using namespace nkentseu::renderer;
using namespace nkentseu;

class FenetreCoquille : public NkCanvasApp{
    private :
    nkentseu::math::NkRect2f square{20, 20, 50, 50};
    float32 deltaTime = 100.f;

    public :
        FenetreCoquille() {
            Config().title = "Fenetre nue";
            Config().width = 1200;
            Config().height = 600;
            Config().clearColor = NkColor2D{36, 36, 36, 255};
        }

        bool OnInit() override {
            
            return true;
        }

        void OnUpdate(float32 deltaTime) override{
			
		}

        void OnRender(NkRenderWindow &target) override {
			NkRenderer2D &c2d = target.GetRenderer2D();
            c2d.DrawFilledRect(square, NkColor2D{255, 0, 0, 255});
		}

        bool OnEvent(const NkEvent &event) override {
			if (auto* kp = event.As<NkKeyPressEvent>()) {
            if (kp->GetKey() == NkKey::NK_UP){
                square.y -= deltaTime;
            }
            if (kp->GetKey() == NkKey::NK_DOWN){
                square.y += deltaTime;
            }
            if (kp->GetKey() == NkKey::NK_RIGHT){
                square.x += deltaTime;
            }
            if (kp->GetKey() == NkKey::NK_LEFT){
                square.x -= deltaTime;
            }
        }
			return false;
		}
};

int nkmain(const NkEntryState &state){
    return NkCanvasApp::Run<FenetreCoquille>(state);
}