#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

// la camera : le centre et le zoom
double cx = 0;
double cy = 0;
double zoom = 1;

// ecrit un nombre avec deux chiffres apres la virgule, sans jamais ecrire -0.00
string deuxChiffres(double v) {
    char tampon[100];
    snprintf(tampon, sizeof(tampon), "%.2f", v);
    string texte = tampon;
    if (texte == "-0.00") {
        texte = "0.00";
    }
    return texte;
}

int main() {
    double W, H;
    cin >> W >> H;   // la taille de la fenetre n'est pas stockee dans la camera

    string commande;
    while (cin >> commande) {
        if (commande == "VERS_MONDE") {
            double px, py;
            cin >> px >> py;
            double x = cx + (px - W / 2) / zoom;
            double y = cy + (py - H / 2) / zoom;
            cout << "MONDE " << deuxChiffres(x) << " " << deuxChiffres(y) << "\n";
        } else if (commande == "VERS_PIXEL") {
            double mx, my;
            cin >> mx >> my;
            double x = (mx - cx) * zoom + W / 2;
            double y = (my - cy) * zoom + H / 2;
            cout << "PIXEL " << deuxChiffres(x) << " " << deuxChiffres(y) << "\n";
        } else if (commande == "DEPLACE") {
            double dx, dy;
            cin >> dx >> dy;
            cx = cx - dx / zoom;
            cy = cy - dy / zoom;
        } else if (commande == "ZOOM") {
            double f, px, py;
            cin >> f >> px >> py;
            // on note le point du monde sous le curseur AVANT de changer le zoom
            double ax = cx + (px - W / 2) / zoom;
            double ay = cy + (py - H / 2) / zoom;
            zoom = zoom * f;
            if (zoom < 0.02) {
                zoom = 0.02;
            }
            if (zoom > 64) {
                zoom = 64;
            }
            // puis on recentre pour que ce point reste sous le curseur
            cx = ax - (px - W / 2) / zoom;
            cy = ay - (py - H / 2) / zoom;
        } else if (commande == "GRILLE") {
            double m;
            cin >> m;
            double s = 1;
            while (s * zoom < m) {
                s = s * 2;
            }
            while (s * 0.5 * zoom >= m) {
                s = s / 2;
            }
            char tampon[100];
            snprintf(tampon, sizeof(tampon), "%.6f", s);
            cout << "GRILLE " << tampon << "\n";
        } else if (commande == "ORIGINE") {
            cx = 0;
            cy = 0;
            zoom = 1;
        }
    }

    cout << "CENTRE " << deuxChiffres(cx) << " " << deuxChiffres(cy) << "\n";
    cout << "ZOOM " << deuxChiffres(zoom) << "\n";
    return 0;
}
