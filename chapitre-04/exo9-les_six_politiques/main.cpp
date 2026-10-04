#include <iostream>
#include <string>

typedef long long ll;

// arrondi de a / b, la moitie monte
static ll arrondi(ll a, ll b) {
    return (2 * a + b) / (2 * b);
}

struct Resultat {
    std::string nom;
    ll vx, vy, vw, vh, mw, mh;
};

int main() {
    ll RW, RH, AW, AH, W, H;
    std::cin >> RW >> RH >> AW >> AH >> W >> H;

    bool reference = (RW > 0 && RH > 0);

    Resultat r[6];
    const char *noms[6] = {"FOLLOW_WINDOW", "STRETCH", "FIT_LETTERBOX",
                           "INTEGER_SCALE", "FIT_CROP", "MANUAL"};
    for (int i = 0; i < 6; i++) r[i].nom = noms[i];

    // FOLLOW_WINDOW
    r[0].vx = 0; r[0].vy = 0; r[0].vw = W; r[0].vh = H; r[0].mw = W; r[0].mh = H;

    // STRETCH
    r[1] = r[0];
    r[1].nom = "STRETCH";
    if (reference) { r[1].mw = RW; r[1].mh = RH; }

    // FIT_LETTERBOX
    r[2] = r[0];
    r[2].nom = "FIT_LETTERBOX";
    if (reference) {
        ll vw, vh;
        if (W * RH <= H * RW) {
            vw = W;
            vh = arrondi(RH * W, RW);
        } else {
            vh = H;
            vw = arrondi(RW * H, RH);
        }
        r[2].vw = vw; r[2].vh = vh;
        r[2].vx = (W - vw) / 2;
        r[2].vy = (H - vh) / 2;
        r[2].mw = RW; r[2].mh = RH;
    }

    // INTEGER_SCALE
    r[3] = r[2];
    r[3].nom = "INTEGER_SCALE";
    if (reference && W >= RW && H >= RH) {
        ll kx = W / RW, ky = H / RH;
        ll k = kx < ky ? kx : ky;
        ll vw = RW * k, vh = RH * k;
        r[3].vw = vw; r[3].vh = vh;
        r[3].vx = (W - vw) / 2;
        r[3].vy = (H - vh) / 2;
    }

    // FIT_CROP
    r[4] = r[0];
    r[4].nom = "FIT_CROP";
    if (reference) {
        if (W * RH > H * RW) {
            r[4].mw = RW;
            r[4].mh = arrondi(RW * H, W);
        } else {
            r[4].mw = arrondi(RH * W, H);
            r[4].mh = RH;
        }
    }

    // MANUAL
    r[5].nom = "MANUAL";
    r[5].vx = 0; r[5].vy = 0; r[5].vw = AW; r[5].vh = AH;
    r[5].mw = AW; r[5].mh = AH;

    int bandes = 0;
    for (int i = 0; i < 6; i++) {
        std::cout << r[i].nom << " " << r[i].vx << " " << r[i].vy << " "
                  << r[i].vw << " " << r[i].vh << " "
                  << r[i].mw << " " << r[i].mh << "\n";
        if (r[i].vw < W || r[i].vh < H) bandes++;
    }

    std::cout << "BANDES " << bandes << "\n";
    bool deformation = reference && (W * RH != H * RW);
    std::cout << "DEFORMATION " << (deformation ? "OUI" : "NON") << "\n";
    return 0;
}
