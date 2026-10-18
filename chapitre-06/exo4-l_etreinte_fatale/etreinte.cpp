// Deux fils, deux verrous : l'etreinte fatale, puis sa correction.
#include <cstdio>
#include "NKWindow/NKMain.h"
#include "NKThreading/NkMutex.h"
#include "NKThreading/NkThread.h"
#include "NKTime/NkChrono.h"

using namespace nkentseu;
using namespace nkentseu::threading;

static NkMutex m1;
static NkMutex m2;

static void filA(void *) {
    NkScopedLockMutex v1(m1);
    std::printf("fil a : j'ai m1\n");
    NkChrono::SleepMilliseconds(100);
    NkScopedLockMutex v2(m2);
    std::printf("fil a : j'ai m1 et m2\n");
}

// ---- Version qui se fige : le fil b prend m2 puis m1 (ordre inverse de a) ----
// static void filB(void *) {
//     NkScopedLockMutex v2(m2);
//     std::printf("fil b : j'ai m2\n");
//     NkChrono::SleepMilliseconds(100);
//     NkScopedLockMutex v1(m1);
//     std::printf("fil b : j'ai m2 et m1\n");
// }

// ---- Version corrigee : le fil b prend m1 puis m2, comme a ----
static void filB(void *) {
    NkScopedLockMutex v1(m1);
    std::printf("fil b : j'ai m1\n");
    NkChrono::SleepMilliseconds(100);
    NkScopedLockMutex v2(m2);
    std::printf("fil b : j'ai m1 et m2\n");
}

int nkmain(const NkEntryState &state) {
    (void)state;
    NkThread a(filA);
    NkThread b(filB);
    a.Join();
    b.Join();
    std::printf("termine\n");
    return 0;
}
