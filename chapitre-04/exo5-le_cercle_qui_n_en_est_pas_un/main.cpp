#include <iostream>
#include <cmath>

int main() {
    const double pi = 3.141592653589793;
    int n = 0;
    std::cin >> n;
    int visibles = 0, refuses = 0;

    for (int i = 0; i < n; i++) {
        long long r, seg;
        std::cin >> r >> seg;

        if (seg < 3) {
            std::cout << r << " " << seg << " REFUSE\n";
            refuses++;
            continue;
        }

        double g = r * (1.0 - std::cos(pi / static_cast<double>(seg)));
        long long ecart = static_cast<long long>(std::floor(g * 1000.0));

        if (g == 0.0) {
            std::cout << r << " " << seg << " " << ecart << " JAMAIS\n";
            continue;
        }

        long long zoom = static_cast<long long>(std::ceil(100.0 / g));
        if (zoom <= 100) {
            std::cout << r << " " << seg << " " << ecart << " " << zoom << " VISIBLE\n";
            visibles++;
        } else {
            std::cout << r << " " << seg << " " << ecart << " " << zoom << " INVISIBLE\n";
        }
    }

    std::cout << "VISIBLES " << visibles << "\n";
    std::cout << "REFUSES " << refuses << "\n";
    return 0;
}
