#include <iostream>
#include <string>

int main() {
    long long v = 0;
    int n = 0;
    std::cin >> v >> n;

    bool space = false, left = false, right = false;
    long long xe = 0, xi = 0;
    int sautsEv = 0, sautsInt = 0, manques = 0;

    for (int i = 1; i <= n; i++) {
        int k = 0;
        std::cin >> k;
        int spacesCetteImage = 0;

        for (int j = 0; j < k; j++) {
            std::string ev;
            std::cin >> ev;
            bool appui = (ev[0] == '+');
            std::string nom = ev.substr(1);

            if (nom == "SPACE") {
                space = appui;
                if (appui) { sautsEv++; spacesCetteImage++; }
            } else if (nom == "RIGHT") {
                right = appui;
                if (appui) xe += v;
            } else if (nom == "LEFT") {
                left = appui;
                if (appui) xe -= v;
            }
        }

        // interrogation : une seule fois, apres tous les evenements
        if (space) sautsInt++;
        if (right) xi += v;
        if (left) xi -= v;

        if (!space) manques += spacesCetteImage;

        std::cout << i << " " << xe << " " << xi << "\n";
    }

    std::cout << "SAUTS EVENEMENTS " << sautsEv << "\n";
    std::cout << "SAUTS INTERROGATION " << sautsInt << "\n";
    std::cout << "MANQUES " << manques << "\n";
    return 0;
}
