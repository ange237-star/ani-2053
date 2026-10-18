// Reserve de fils contre fils crees a la main : meme tache, 200 fois.
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKThreading/NkThread.h"
#include "NKThreading/NkThreadPool.h"
#include "NKTime/NkChrono.h"

using namespace nkentseu;
using namespace nkentseu::threading;

static const int NB_TACHES = 200;
static long long gResultats[NB_TACHES];   // un emplacement par tache : rien n'est partage

// la tache : additionner n entiers dans une variable locale
static void tache(int numero, long long n) {
    long long somme = 0;
    for (long long i = 0; i < n; i++) somme += i;
    gResultats[numero] = somme;
}

static double avecReserve(NkThreadPool &pool, long long n) {
    NkChrono chrono;
    for (int i = 0; i < NB_TACHES; i++) {
        pool.Enqueue([i, n]() { tache(i, n); });
    }
    pool.Join();
    return chrono.Elapsed().ToMilliseconds();
}

static double avecFils(long long n) {
    NkChrono chrono;
    NkThread fils[NB_TACHES];
    for (int i = 0; i < NB_TACHES; i++) {
        fils[i] = NkThread([i, n](void *) { tache(i, n); });
    }
    for (int i = 0; i < NB_TACHES; i++) fils[i].Join();
    return chrono.Elapsed().ToMilliseconds();
}

int nkmain(const NkEntryState &state) {
    (void)state;
    NkThreadPool pool;   // 0 = nombre d'ouvriers choisi automatiquement
    std::printf("ouvriers : %u\n", static_cast<unsigned>(pool.GetNumWorkers()));

    const long long courte = 1000;
    const long long longue = courte * 100;

    for (int essai = 1; essai <= 3; essai++) {
        double r = avecReserve(pool, courte);
        double f = avecFils(courte);
        std::printf("tache courte, essai %d : reserve %.2f ms, fils %.2f ms\n", essai, r, f);
    }

    double r = avecReserve(pool, longue);
    double f = avecFils(longue);
    std::printf("tache longue : reserve %.2f ms, fils %.2f ms\n", r, f);

    // on relit les resultats pour que le compilateur ne supprime pas le travail
    long long controle = 0;
    for (int i = 0; i < NB_TACHES; i++) controle += gResultats[i] & 1;
    std::printf("controle : %lld\n", controle);
    return 0;
}
