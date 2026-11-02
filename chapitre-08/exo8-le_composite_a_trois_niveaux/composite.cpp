// Un composite a trois niveaux : parent, parent, sprite.
// Chaque niveau compose le transform recu avec le sien avant de dessiner son enfant.
// Deux sondes ecrivent ou arrive l'origine : l'une compose, l'autre jette l'etat recu.
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Core/NkDrawable.h"
#include "NKCanvas/Renderer/Core/NkTransform.h"
#include "NKCanvas/Renderer/Core/NkTransformable.h"
#include "NKCanvas/Renderer/Targets/NkRenderTarget.h"
#include "NKCanvas/Renderer/Resources/NkSprite.h"     // chemin a verifier dans ton kit

using namespace nkentseu;
using namespace nkentseu::renderer;

// Un niveau : il se place (NkTransformable) et se dessine (NkDrawable).
// Il garde quelques enfants et leur passe l'etat compose.
class Niveau : public NkTransformable, public NkDrawable {
public:
    void Ajouter(const NkDrawable &enfant) {
        if (mNb < 4) mEnfants[mNb++] = &enfant;
    }

    void Draw(NkRenderTarget &target, const NkRenderStates &states) const override {
        NkRenderStates local = states;
        local.transform *= GetTransform();            // compose notre transform avec celui recu
        for (int i = 0; i < mNb; i++) mEnfants[i]->Draw(target, local);
    }

private:
    const NkDrawable *mEnfants[4] = {nullptr, nullptr, nullptr, nullptr};
    int mNb = 0;
};

// Une sonde, placee comme le sprite, qui ecrit ou arrive son origine une fois composee.
// Si "jette" est vrai, elle ignore l'etat recu : c'est le defaut qu'avait le sprite.
class Sonde : public NkTransformable, public NkDrawable {
public:
    Sonde(const char *nom, bool jette) : mNom(nom), mJette(jette) {}

    void Draw(NkRenderTarget &target, const NkRenderStates &states) const override {
        (void)target;
        if (mEcrit) return;                           // une seule ligne par lancement
        mEcrit = true;

        NkTransform composee;                         // identite au depart
        if (!mJette) composee = states.transform;     // on part de l'etat recu...
        composee *= GetTransform();                   // ...et on ajoute le notre
        NkVec2f p = composee.TransformPoint({0.f, 0.f});

        std::FILE *f = std::fopen("composite-sondes.txt", "a");
        if (!f) return;
        std::fprintf(f, "%s : %.3f %.3f\n", mNom, static_cast<double>(p.x), static_cast<double>(p.y));
        std::fclose(f);
    }

private:
    const char *mNom;
    bool mJette;
    mutable bool mEcrit = false;
};

class Composite : public NkCanvasApp {
public:
    Composite() {
        Config().title = "Composite";
        Config().width = 800;
        Config().height = 450;
        Config().clearColor = NkColor2D{36, 36, 36, 255};

        // Niveau 1 : parent en (100, 50), sans rotation
        mNiveau1.SetPosition({100.f, 50.f});
        // Niveau 2 : parent en (40, 20), tourne de 90 degres
        mNiveau2.SetPosition({40.f, 20.f});
        mNiveau2.SetRotation(math::NkAngle(90.f));
        // Niveau 3 : le sprite et les deux sondes, tous en (30, 10) dans le niveau 2
        mSprite.SetPosition({30.f, 10.f});
        mSondeComposee.SetPosition({30.f, 10.f});
        mSondeJetee.SetPosition({30.f, 10.f});

        mNiveau1.Ajouter(mNiveau2);
        mNiveau2.Ajouter(mSprite);
        mNiveau2.Ajouter(mSondeComposee);
        mNiveau2.Ajouter(mSondeJetee);
    }

protected:
    void OnRender(NkRenderWindow &target) override {
        target.Draw(mNiveau1);
    }

private:
    Niveau mNiveau1;
    Niveau mNiveau2;
    NkSprite mSprite;                    // la texture se pose ici avec l'API de ton NkSprite.h
    Sonde mSondeComposee{"sonde composee", false};
    Sonde mSondeJetee{"sonde jetee", true};
};

int nkmain(const NkEntryState &state) {
    return NkCanvasApp::Run<Composite>(state);
}
