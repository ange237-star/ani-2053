#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// les images de la planche, dans l'ordre du tableau
vector<string> noms;
vector<double> xs, ys, largeurs, hauteurs, echelles;

// vrai si le point (px, py) touche l'image numero i
bool touche(int i, double px, double py) {
    double demiLargeur = largeurs[i] * echelles[i] / 2;
    double demiHauteur = hauteurs[i] * echelles[i] / 2;
    if (fabs(px - xs[i]) <= demiLargeur && fabs(py - ys[i]) <= demiHauteur) {
        return true;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string nom;
        double x, y, largeur, hauteur, echelle;
        cin >> nom >> x >> y >> largeur >> hauteur >> echelle;
        noms.push_back(nom);
        xs.push_back(x);
        ys.push_back(y);
        largeurs.push_back(largeur);
        hauteurs.push_back(hauteur);
        echelles.push_back(echelle);
    }

    int q;
    cin >> q;
    int erreurs = 0;

    for (int k = 1; k <= q; k++) {
        double px, py;
        cin >> px >> py;

        // A : a rebours, de la derniere image a la premiere
        string a = "AUCUN";
        for (int i = n - 1; i >= 0; i--) {
            if (touche(i, px, py)) {
                a = noms[i];
                break;
            }
        }

        // B : a l'endroit, de la premiere image a la derniere
        string b = "AUCUN";
        for (int i = 0; i < n; i++) {
            if (touche(i, px, py)) {
                b = noms[i];
                break;
            }
        }

        cout << "CLIC " << k << " " << a << " " << b << "\n";
        if (a != b) {
            erreurs = erreurs + 1;
        }
    }

    cout << "ERREURS " << erreurs << "\n";
    return 0;
}
