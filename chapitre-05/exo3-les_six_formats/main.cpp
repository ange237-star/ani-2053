#include <iostream>
#include <string>

struct Format {
    const char *nom;
    long long octets;
    bool couleur, transparence, flottants;
};

static const Format FORMATS[] = {
    {"GRAY8",    1,  false, false, false},
    {"GRAY_A16", 2,  false, true,  false},
    {"RGB24",    3,  true,  false, false},
    {"RGBA32",   4,  true,  true,  false},
    {"RGB96F",   12, true,  false, true},
    {"RGBA128F", 16, true,  true,  true},
};

static const Format *chercher(const std::string &nom) {
    for (const Format &f : FORMATS)
        if (nom == f.nom) return &f;
    return nullptr;
}

int main() {
    long long w, h;
    int n = 0;
    std::cin >> w >> h >> n;

    long long total = 0;
    int sansPerte = 0, refuses = 0;

    for (int i = 0; i < n; i++) {
        std::string src, cible;
        std::cin >> src >> cible;

        const Format *a = chercher(src);
        const Format *b = chercher(cible);
        if (!a || !b) {
            std::cout << src << " " << cible << " REFUSE\n";
            refuses++;
            continue;
        }

        long long memSrc = w * h * a->octets;
        long long memCible = w * h * b->octets;

        std::string pertes;
        if (a->transparence && !b->transparence) pertes += "TRANSPARENCE";
        if (a->couleur && !b->couleur) {
            if (!pertes.empty()) pertes += "+";
            pertes += "COULEUR";
        }
        if (a->flottants && !b->flottants) {
            if (!pertes.empty()) pertes += "+";
            pertes += "ETENDUE";
        }
        if (pertes.empty()) {
            pertes = "AUCUNE";
            sansPerte++;
        }

        total += memCible;
        std::cout << src << " " << cible << " " << memSrc << " " << memCible
                  << " " << pertes << "\n";
    }

    std::cout << "TOTAL " << total << "\n";
    std::cout << "SANS_PERTE " << sansPerte << "\n";
    std::cout << "REFUSES " << refuses << "\n";
    return 0;
}
