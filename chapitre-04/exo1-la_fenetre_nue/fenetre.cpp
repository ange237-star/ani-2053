#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

// NKCanvas
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/App/NkCanvasApp.h"


 class Fenetre : public nkentseu::renderer::NkCanvasApp {
    public:

      Fenetre() {
        Config().title = "Fenetre";
        Config().width = 800;
        Config().height = 600;
        //Config().backend = nkentseu::NkGraphicsApi::NK_GFX_API_DX12;
        Config().clearColor = nkentseu::renderer::NkColor2D{255, 50, 50, 0};
    }
    bool OnInit() override {
		return true;
	}

 };

 int nkmain(const nkentseu::NkEntryState &state) {
    return nkentseu::renderer::NkCanvasApp::Run<Fenetre>(state);
 }