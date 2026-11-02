// Chaque crochet de NkCanvasApp ecrit une ligne dans un journal :
// numero d'ordre, nom du crochet, image en cours, Time().
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

static const int IMAGES_AVANT_ARRET = 5;

class MonJeu : public NkCanvasApp {
public:
    MonJeu() {
        Config().title = "Les crochets";
        Config().width = 800;
        Config().height = 450;
    }

    ~MonJeu() override {
        if (mFichier) std::fclose(mFichier);
    }

protected:
    NkOptional<int> OnCommandLine(const NkVector<NkString> &args) override {
        (void)args;
        noter("OnCommandLine");
        return NkOptional<int>();
    }

    bool OnInit() override {
        noter("OnInit");
        return true;
    }

    void OnLayout(const NkLayoutInfo &layout) override {
        (void)layout;
        noter("OnLayout");
    }

    void OnUpdate(float32 deltaTime) override {
        (void)deltaTime;
        mImage++;
        noter("OnUpdate");
    }

    void OnRender(NkRenderWindow &target) override {
        (void)target;
        noter("OnRender");
        if (mImage >= IMAGES_AVANT_ARRET) Quit();
    }

    void OnShutdown() override {
        noter("OnShutdown");
    }

    bool OnEvent(const NkEvent &event) override {
        (void)event;
        noter("OnEvent");
        return false;
    }

    bool OnPointer(const NkPointer &pointer) override {
        (void)pointer;
        noter("OnPointer");
        return false;
    }

    bool OnKeyPress(const NkKeyPressEvent &event) override {
        (void)event;
        noter("OnKeyPress");
        return false;
    }

    bool OnCloseRequested() override {
        noter("OnCloseRequested");
        return true;
    }

    void OnPause() override {
        noter("OnPause");
    }

    void OnResume() override {
        noter("OnResume");
    }

private:
    // Time() n'existe pas avant la fenetre : avant OnInit on ecrit 0
    void noter(const char *nom) {
        if (!mFichier) mFichier = std::fopen("crochets-journal.txt", "a");
        if (!mFichier) return;
        std::fprintf(mFichier, "%d %s image %d t %.3f\n", ++mOrdre, nom, mImage,
                     mImage > 0 || mOrdre > 2 ? static_cast<double>(Time()) : 0.0);
        std::fflush(mFichier);
    }

    std::FILE *mFichier = nullptr;
    int mOrdre = 0;
    int mImage = 0;
};

int nkmain(const NkEntryState &state) {
    return NkCanvasApp::Run<MonJeu>(state);
}
