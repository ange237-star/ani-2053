#include <NkWindow/NKMain.h>
#include <NkWindow/NKWindow.h>
#include <NkCanvas/Core/NKContextDesc.h>
#include <NkCanvas/Core/NKCanvas.h>
#include <NkCanvas/Core/NKDrawable.h>
#include <NkCanvas/Core/NKImage.h>
#include <NkCanvas/Core/NKTexture.h>
#include <NkCanvas/Core/NKGraphicsApi.h>
#include <NkCanvas/Renderer/Targets/NKRenderWindow.h>
#i 


int nkmain(const nkentseu::NkEntryState &state) {
    nkentseu::NkWindow window;
    window.setTitle("Calcul et Mesure");
    window.setSize(800, 600);
    window.show();

    renderwindow.Display();
    return 0;
}