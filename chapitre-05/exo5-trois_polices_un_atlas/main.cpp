#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef long long ll;

struct Groupe {
    std::string police;
    ll n, w, h;
    ll x1, y1, x2, y2;
};

// tente de ranger tous les glyphes dans une texture W x H
static bool essayer(std::vector<Groupe> &groupes, ll P, ll W, ll H) {
    ll x = P, y = P, e = 0;
    for (Groupe &g : groupes) {
        for (ll k = 0; k < g.n; k++) {
            ll rw = g.w + P;
            ll rh = g.h + P;
            if (x + rw > W - P) {
                x = P;
                y = y + e + P;
                e = 0;
                if (x + rw > W - P) return false;
            }
            if (y + rh > H - P) return false;
            if (k == 0) { g.x1 = x; g.y1 = y; }
            g.x2 = x;
            g.y2 = y;
            x += rw;
            e = std::max(e, rh);
        }
    }
    return true;
}

int main() {
    ll P, L;
    int G = 0;
    std::cin >> P >> L >> G;

    std::vector<Groupe> groupes(G);
    for (Groupe &g : groupes) std::cin >> g.police >> g.n >> g.w >> g.h;

    if (G == 0) {
        std::cout << "AUCUN\n";
        return 0;
    }

    ll W = L;
    if (L == 0) {
        W = 512;
        ll besoin = 0;
        for (const Groupe &g : groupes) besoin += g.n * (g.w + P) * (g.h + P);
        while (W * W < 2 * besoin && W < 4096) W *= 2;
    }
    ll H = W;

    int essais = 0;
    bool reussi = false;
    while (essais < 8 && !reussi) {
        essais++;
        reussi = essayer(groupes, P, W, H);
        if (!reussi) {
            if (W == H) W *= 2;
            else H = W;
        }
    }

    std::cout << "ESSAIS " << essais << "\n";
    if (!reussi) {
        std::cout << "ECHEC\n";
        return 0;
    }

    std::cout << "TEXTURE " << W << " " << H << "\n";
    ll occupe = 0;
    for (const Groupe &g : groupes) {
        std::cout << g.police << " " << g.x1 << " " << g.y1 << " " << g.x2 << " " << g.y2 << "\n";
        occupe += g.n * g.w * g.h;
    }
    ll aire = W * H;
    std::cout << "OCCUPE " << occupe << "\n";
    std::cout << "PERDU " << (aire - occupe) * 100 / aire << "\n";
    return 0;
}
