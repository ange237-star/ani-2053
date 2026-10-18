// Charger une grande image dans un autre fil pendant que la fenetre dessine.
// VERSION_GET = true  : on appelle Get() tout de suite (la fenetre se fige)
// VERSION_GET = false : on demande IsReady() a chaque trame
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKImage/Core/NkImage.h"
#include "NKThreading/NkFuture.h"
#include "NKThreading/NkPromise.h"
#include "NKThreading/NkThreadPool.h"
#include "NKTime/NkChrono.h"

using namespace nkentseu;
using namespace nkentseu::renderer;
using namespace nkentseu::threading;

static const bool VERSION_GET = false;
static const char *CHEMIN_IMAGE = "grande-photo.png";   // a remplacer par ta plus grosse image
static const int TRAME_DE_DEPART = 60;

static long taillePossedee(const char *chemin) {
    std::FILE *f = std::fopen(chemin, "rb");
    if (!f) return -1;
    std::fseek(f, 0, SEEK_END);
    long taille = std::ftell(f);
    std::fclose(f);
    return taille;
}

class FenetreFutur : public NkCanvasApp {
public:
    FenetreFutur() {
        Config().title = VERSION_GET ? "Futur : Get" : "Futur : IsReady";
        Config().width = 800;
        Config().height = 450;
        Config().clearColor = NkColor2D{36, 36, 36, 255};
    }

protected:
    void OnUpdate(float32) override {
        // duree de la trame qui vient de finir (Reset lit puis remet a zero)
        double ms = mChrono.Reset().ToMilliseconds();
        mTrame++;
        mX += 1.f;                              // le carre avance d'un pixel par trame
        if (mX > 800.f) mX = 0.f;

        if (mEtat == AVANT && mTrame >= TRAME_DE_DEPART) lancer();
        else if (mEtat == CHARGEMENT) {
            if (ms > mPlusLongue) mPlusLongue = ms;
            if (VERSION_GET) {
                attendre();                      // bloque ici jusqu'a la fin du chargement
            } else {
                mTramesPendant++;
                if (mFutur.IsReady()) attendre();   // Get seulement quand c'est pret
            }
        } else if (mEtat == FINI && ++mApres >= 120) {
            Quit();
        }
    }

    void OnRender(NkRenderWindow &target) override {
        target.GetRenderer2D().DrawFilledRect({mX, 200.f, 40.f, 40.f}, NkColor2D{255, 0, 0, 255});
    }

private:
    enum Etat { AVANT, CHARGEMENT, FINI };

    void lancer() {
        mFutur = mPromesse.GetFuture();
        mEtat = CHARGEMENT;
        mPool.Enqueue([this]() {
            NkChrono chrono;
            NkImage img;
            img.Load(CHEMIN_IMAGE);
            mDureeChargement = chrono.Elapsed().ToMilliseconds();   // ecrit avant SetValue
            mPromesse.SetValue(nkentseu::traits::NkMove(img));
        });
    }

    void attendre() {
        NkImage img = mFutur.Get();
        mEtat = FINI;
        // l'image est recue : on affiche les mesures a recopier dans cadence.txt
        std::printf("version : %s\n", VERSION_GET ? "Get" : "IsReady");
        std::printf("image : %s, %ld octets sur disque, chargee en %.1f ms\n",
                    CHEMIN_IMAGE, taillePossedee(CHEMIN_IMAGE), mDureeChargement);
        std::printf("trame la plus longue : %.1f ms\n", mPlusLongue);
        std::printf("trames pendant le chargement : %d\n", mTramesPendant);
    }

    NkChrono mChrono;
    NkThreadPool mPool;
    NkPromise<NkImage> mPromesse;
    NkFuture<NkImage> mFutur;
    Etat mEtat = AVANT;
    int mTrame = 0;
    int mTramesPendant = 0;
    int mApres = 0;
    float32 mX = 0.f;
    double mPlusLongue = 0.0;
    double mDureeChargement = 0.0;
};

int nkmain(const NkEntryState &state) {
    return NkCanvasApp::Run<FenetreFutur>(state);
}
