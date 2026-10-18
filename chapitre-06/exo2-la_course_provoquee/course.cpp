// Huit fils incrementent le meme compteur un million de fois, sans protection.
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKThreading/NkThread.h"

using namespace nkentseu;
using namespace nkentseu::threading;

static const int NB_FILS = 8;           // mettre 1 pour l'essai "un seul fil"
static const long long PAR_FIL = 1000000;

static long long compteur = 0;          // partage, ecrit par tous les fils, sans rien

int nkmain(const NkEntryState &state) {
    (void)state;

    NkThread fils[NB_FILS];
    for (int i = 0; i < NB_FILS; i++) {
        fils[i] = NkThread([](void *) {
            for (long long k = 0; k < PAR_FIL; k++) compteur += 1;
        });
    }
    for (int i = 0; i < NB_FILS; i++) fils[i].Join();

    long long attendu = NB_FILS * PAR_FIL;
    std::printf("total : %lld, attendu : %lld, ecart : %lld\n",
                compteur, attendu, attendu - compteur);
    return 0;
}
