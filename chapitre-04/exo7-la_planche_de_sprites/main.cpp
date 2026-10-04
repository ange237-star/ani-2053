#include <iostream>

int main() {
    long long C, R, W, H, F, D, P;
    std::cin >> C >> R >> W >> H >> F >> D >> P;
    int n = 0;
    std::cin >> n;

    long long caseCourante = 0, accumule = 0;
    long long avances = 0, plafonnes = 0;

    for (int i = 0; i < n; i++) {
        long long dt;
        std::cin >> dt;

        if (dt > P) {
            dt = P;
            plafonnes++;
        }
        accumule += dt;

        // on retire D (pas de remise a zero) pour garder le reste
        while (accumule >= D) {
            accumule -= D;
            caseCourante = (caseCourante + 1) % F;
            avances++;
        }

        long long x = (caseCourante % C) * W;
        long long y = (caseCourante / C) * H;
        std::cout << caseCourante << " " << x << " " << y << " " << W << " " << H << "\n";
    }

    std::cout << "AVANCES " << avances << "\n";
    std::cout << "PLAFONNES " << plafonnes << "\n";
    return 0;
}
