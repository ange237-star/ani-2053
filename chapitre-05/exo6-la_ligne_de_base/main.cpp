#include <iostream>
#include <map>
#include <string>
#include <algorithm>

typedef long long ll;

struct Glyphe {
    ll avance, x0, y0, x1, y1;
};

int main() {
    int G = 0;
    std::cin >> G;
    std::map<char, Glyphe> table;
    for (int i = 0; i < G; i++) {
        std::string c;
        Glyphe g;
        std::cin >> c >> g.avance >> g.x0 >> g.y0 >> g.x1 >> g.y1;
        table[c[0]] = g;
    }

    int K = 0;
    std::cin >> K;
    std::map<std::string, ll> crenage;
    for (int i = 0; i < K; i++) {
        std::string paire;
        ll k;
        std::cin >> paire >> k;
        crenage[paire] = k;
    }

    std::string texte;
    ll ox, oy;
    std::cin >> texte >> ox >> oy;

    ll x = ox;
    bool dessine = false;
    ll minx = 0, miny = 0, maxx = 0, maxy = 0;
    int absents = 0;

    for (size_t i = 0; i < texte.size(); i++) {
        char c = texte[i];
        auto it = table.find(c);
        if (it == table.end()) {
            std::cout << c << " ABSENT\n";
            absents++;
            continue;                      // pas d'avance, pas de crenage
        }
        const Glyphe &g = it->second;
        std::cout << c << " " << x << "\n";

        if (g.x1 > g.x0 && g.y1 > g.y0) {
            ll rx0 = x + g.x0, ry0 = oy + g.y0;
            ll rx1 = x + g.x1, ry1 = oy + g.y1;
            if (!dessine) {
                minx = rx0; miny = ry0; maxx = rx1; maxy = ry1;
                dessine = true;
            } else {
                minx = std::min(minx, rx0);
                miny = std::min(miny, ry0);
                maxx = std::max(maxx, rx1);
                maxy = std::max(maxy, ry1);
            }
        }

        x += g.avance;
        if (i + 1 < texte.size()) {
            std::string paire;
            paire += c;
            paire += texte[i + 1];
            auto k = crenage.find(paire);
            if (k != crenage.end()) x += k->second;
        }
    }

    std::cout << "CURSEUR " << x << "\n";
    if (!dessine) {
        std::cout << "BOITE AUCUNE\n";
        std::cout << "MONTE 0\n";
        std::cout << "DESCEND 0\n";
        std::cout << "ECRAN RIEN\n";
    } else {
        std::cout << "BOITE " << minx << " " << miny << " " << maxx << " " << maxy << "\n";
        std::cout << "MONTE " << (miny < oy ? oy - miny : 0) << "\n";
        std::cout << "DESCEND " << (maxy > oy ? maxy - oy : 0) << "\n";
        if (maxy <= 0) std::cout << "ECRAN HORS\n";
        else if (miny < 0) std::cout << "ECRAN COUPE\n";
        else std::cout << "ECRAN VISIBLE\n";
    }
    std::cout << "ABSENTS " << absents << "\n";
    return 0;
}
