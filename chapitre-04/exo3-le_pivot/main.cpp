#include <iostream>
#include <string>
#include <algorithm>

int main() {
    int n = 0;
    std::cin >> n;
    int refuses = 0;

    for (int i = 0; i < n; i++) {
        std::string nom;
        long long w, h, px, py, ox, oy, sx, sy, angle;
        std::cin >> nom >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angle;

        if (angle % 90 != 0) {
            std::cout << nom << " ANGLE REFUSE\n";
            refuses++;
            continue;
        }

        // en C++, -90 % 360 donne -90 : on ramene dans [0, 360[
        long long a = ((angle % 360) + 360) % 360;
        long long c = 0, s = 0;
        if (a == 0)        { c = 1;  s = 0; }
        else if (a == 90)  { c = 0;  s = 1; }
        else if (a == 180) { c = -1; s = 0; }
        else               { c = 0;  s = -1; }

        long long lx[4] = {0, w, w, 0};
        long long ly[4] = {0, 0, h, h};
        long long mx[4], my[4];

        for (int k = 0; k < 4; k++) {
            long long ax = (lx[k] - ox) * sx;
            long long ay = (ly[k] - oy) * sy;
            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;
            mx[k] = px + rx;
            my[k] = py + ry;
        }

        std::cout << nom << " COINS";
        for (int k = 0; k < 4; k++) std::cout << " " << mx[k] << " " << my[k];
        std::cout << "\n";

        long long minx = *std::min_element(mx, mx + 4);
        long long maxx = *std::max_element(mx, mx + 4);
        long long miny = *std::min_element(my, my + 4);
        long long maxy = *std::max_element(my, my + 4);
        std::cout << nom << " BOITE " << minx << " " << miny << " "
                  << maxx << " " << maxy << "\n";
    }

    std::cout << "REFUSES " << refuses << "\n";
    return 0;
}
