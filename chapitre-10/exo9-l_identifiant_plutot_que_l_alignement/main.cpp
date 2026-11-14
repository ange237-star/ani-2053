#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> planche;   // les identifiants des images, dans l'ordre de la planche
    int prochainId = 1;    // un identifiant n'est jamais reutilise
    int occasions = 0;     // suppressions et echanges qui ont eu lieu
    int repercutes = 0;    // gestes a repeter dans les tableaux paralleles
    int recherches = 0;    // recherches dans le dictionnaire

    for (int k = 0; k < n; k++) {
        string operation;
        cin >> operation;

        if (operation == "AJOUTE") {
            planche.push_back(prochainId);
            prochainId = prochainId + 1;

        } else if (operation == "SUPPRIME") {
            int c;
            cin >> c;
            vector<int> index;
            for (int j = 0; j < c; j++) {
                int i;
                cin >> i;
                index.push_back(i);
            }
            // on retire du plus grand index au plus petit
            for (int j = c - 1; j >= 0; j--) {
                planche.erase(planche.begin() + index[j]);
            }
            occasions = occasions + 1;
            repercutes = repercutes + 2 * c;

        } else if (operation == "MONTE") {
            int i;
            cin >> i;
            int j = i + 1;
            if (j < (int)planche.size()) {
                int temp = planche[i];
                planche[i] = planche[j];
                planche[j] = temp;
                occasions = occasions + 1;
                repercutes = repercutes + 2;
            }

        } else if (operation == "DESCEND") {
            int i;
            cin >> i;
            int j = i - 1;
            if (j >= 0) {
                int temp = planche[i];
                planche[i] = planche[j];
                planche[j] = temp;
                occasions = occasions + 1;
                repercutes = repercutes + 2;
            }

        } else if (operation == "DESSINE") {
            // par identifiant, chaque image presente coute une recherche
            recherches = recherches + planche.size();
        }
    }

    cout << "ORDRE";
    if (planche.size() == 0) {
        cout << " AUCUN";
    }
    for (size_t i = 0; i < planche.size(); i++) {
        cout << " " << planche[i];
    }
    cout << "\n";
    cout << "OCCASIONS " << occasions << "\n";
    cout << "REPERCUTES " << repercutes << "\n";
    cout << "RECHERCHES " << recherches << "\n";
    return 0;
}
