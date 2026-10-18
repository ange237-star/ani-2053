// Le compteur partage, corrige de trois facons, et ce que chacune coute.
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKCore/NkAtomic.h"
#include "NKThreading/NkMutex.h"
#include "NKThreading/NkThread.h"
#include "NKTime/NkChrono.h"

using namespace nkentseu;
using namespace nkentseu::threading;

static const int NB_FILS = 8;
static const long long PAR_FIL = 1000000;

static long long gSansProtection = 0;
static long long gMutex = 0;
static NkMutex gVerrou;
static NkAtomicInt gAtomique{0};         // int 32 bits : 8 millions y tiennent
static long long gLocaux[NB_FILS];       // une case par fil : rien n'est partage

template <typename Corps>
static double lancer(Corps corps) {
    NkChrono chrono;
    NkThread fils[NB_FILS];
    for (int i = 0; i < NB_FILS; i++) {
        fils[i] = NkThread([corps, i](void *) { corps(i); });
    }
    for (int i = 0; i < NB_FILS; i++) fils[i].Join();
    return chrono.Elapsed().ToMilliseconds();
}

static double mediane(double a, double b, double c) {
    if ((a <= b && b <= c) || (c <= b && b <= a)) return b;
    if ((b <= a && a <= c) || (c <= a && a <= b)) return a;
    return c;
}

int nkmain(const NkEntryState &state) {
    (void)state;
    double t[4][3];
    long long totaux[4] = {0, 0, 0, 0};

    for (int essai = 0; essai < 3; essai++) {
        gSansProtection = 0;
        gMutex = 0;
        gAtomique.Store(0);

        t[0][essai] = lancer([](int) {
            for (long long k = 0; k < PAR_FIL; k++) gSansProtection += 1;
        });

        t[1][essai] = lancer([](int) {
            for (long long k = 0; k < PAR_FIL; k++) {
                NkScopedLockMutex garde(gVerrou);   // verrou de portee
                gMutex += 1;
            }
        });

        t[2][essai] = lancer([](int) {
            for (long long k = 0; k < PAR_FIL; k++) gAtomique.FetchAdd(1);
        });

        t[3][essai] = lancer([](int numero) {
            long long local = 0;
            for (long long k = 0; k < PAR_FIL; k++) local += 1;
            gLocaux[numero] = local;
        });

        totaux[0] = gSansProtection;
        totaux[1] = gMutex;
        totaux[2] = gAtomique.Load();
        totaux[3] = 0;
        for (int i = 0; i < NB_FILS; i++) totaux[3] += gLocaux[i];

        std::printf("essai %d : sans %lld (%.2f ms), mutex %lld (%.2f ms), atomique %lld (%.2f ms), local %lld (%.2f ms)\n",
                    essai + 1, totaux[0], t[0][essai], totaux[1], t[1][essai],
                    totaux[2], t[2][essai], totaux[3], t[3][essai]);
    }

    const char *noms[4] = {"Sans protection", "Mutex", "Atomique", "Local"};
    for (int v = 0; v < 4; v++)
        std::printf("%s : total %lld, mediane %.2f ms\n", noms[v], totaux[v], mediane(t[v][0], t[v][1], t[v][2]));
    std::printf("attendu : %lld\n", NB_FILS * PAR_FIL);
    return 0;
}
