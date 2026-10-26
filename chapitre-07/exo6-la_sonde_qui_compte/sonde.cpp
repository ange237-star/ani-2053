// Sonde : compter les passages de OnRender pendant dix secondes.
// On change ces deux constantes puis on recompile, pour les quatre lancements :
//   IMAGES_PAR_SECONDE : 60 (cadence par defaut) ou 0 (aucun plafond)
//   AVEC_LIGNE         : true (une ligne de journal par passage) ou false (compteur seul)
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

static const int  IMAGES_PAR_SECONDE = 60;
static const bool AVEC_LIGNE = true;
static const float DUREE = 10.0f;

class Sonde : public NkCanvasApp {
public:
    Sonde() {
        Config().title = "Sonde";
        Config().width = 800;
        Config().height = 450;
        Config().imagesParSeconde = IMAGES_PAR_SECONDE;
    }

protected:
    void OnRender(NkRenderWindow &target) override {
        (void)target;
        mCompte++;

        if (AVEC_LIGNE) {
            std::printf("passage %d a %.3f s\n", mCompte, static_cast<double>(Time()));
        }

        if (!mFini && Time() >= DUREE) {
            mFini = true;
            ecrireCompte();
            Quit();     // arrete le programme a la fin de l'image en cours
        }
    }

private:
    void ecrireCompte() {
        std::FILE *f = std::fopen("sonde-compte.txt", "a");
        if (!f) return;
        std::fprintf(f, "plafond : %d, ligne : %s, passages : %d, duree : %.3f s\n",
                     IMAGES_PAR_SECONDE, AVEC_LIGNE ? "oui" : "non",
                     mCompte, static_cast<double>(Time()));
        std::fclose(f);
    }

    int mCompte = 0;
    bool mFini = false;
};

int nkmain(const NkEntryState &state) {
    return NkCanvasApp::Run<Sonde>(state);
}
