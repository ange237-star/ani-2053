#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

int main() {
    ll D, C;
    int N = 0;
    std::cin >> D >> C >> N;

    std::vector<ll> t(N);
    for (ll &v : t) std::cin >> v;

    ll voixMax = 0, retardMax = 0;
    int coupes = 0;
    ll finChargement = 0;

    for (int i = 0; i < N; i++) {
        // voix encore actives a l'instant t[i] (une lecture qui finit pile a fini)
        ll voix = 0;
        for (int j = 0; j <= i; j++)
            if (t[j] + D > t[i]) voix++;

        // les chargements s'enchainent, chacun bloque le programme
        ll debut = t[i];
        if (i > 0) debut = std::max(t[i], finChargement);
        finChargement = debut + C;
        ll retard = finChargement - t[i];

        bool coupe = (i + 1 < N) && (t[i + 1] < t[i] + D);

        std::cout << t[i] << " " << voix << " " << retard << " "
                  << (coupe ? "COUPE" : "ENTIER") << "\n";

        voixMax = std::max(voixMax, voix);
        retardMax = std::max(retardMax, retard);
        if (coupe) coupes++;
    }

    std::cout << "VOIX_MAX " << voixMax << "\n";
    std::cout << "RETARD_MAX " << retardMax << "\n";
    std::cout << "COUPES " << coupes << "\n";
    return 0;
}
