#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

vector<int> octets;        // les octets du fichier
unsigned long position = 0;
bool tronque = false;      // devient vrai s'il manque un octet

// lit un octet non signe
int lireU8() {
    if (position >= octets.size()) {
        tronque = true;
        return 0;
    }
    int valeur = octets[position];
    position = position + 1;
    return valeur;
}

// lit un entier non signe de quatre octets, petit-boutiste :
// le premier octet lu est le poids faible
unsigned int lireU32() {
    if (position + 4 > octets.size()) {
        tronque = true;
        position = octets.size();
        return 0;
    }
    unsigned int valeur = 0;
    for (int i = 0; i < 4; i++) {
        unsigned int octet = octets[position + i];
        valeur = valeur | (octet << (8 * i));
    }
    position = position + 4;
    return valeur;
}

// lit un nombre a virgule de quatre octets : on lit les bits comme un u32
// puis on les recopie dans un float
float lireF32() {
    unsigned int bits = lireU32();
    float valeur;
    memcpy(&valeur, &bits, 4);
    return valeur;
}

// saute des octets (les octets source d'une image)
void sauter(unsigned int combien) {
    if (position + (unsigned long)combien > octets.size()) {
        tronque = true;
        position = octets.size();
        return;
    }
    position = position + combien;
}

// deux chiffres apres la virgule, sans jamais ecrire -0.00
string deuxChiffres(float v) {
    char tampon[100];
    snprintf(tampon, sizeof(tampon), "%.2f", (double)v);
    string texte = tampon;
    if (texte == "-0.00") {
        texte = "0.00";
    }
    return texte;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        string mot;
        if (!(cin >> mot)) {
            break;
        }
        octets.push_back(stoi(mot, nullptr, 16));
    }

    // on garde les lignes de sortie : si le fichier est refuse, on n'affiche qu'une ligne
    vector<string> sortie;

    // les quatre premiers octets : N K R F
    int a = lireU8();
    int b = lireU8();
    int c = lireU8();
    int d = lireU8();
    if (tronque) {
        cout << "TRONQUE\n";
        return 0;
    }
    if (a != 0x4E || b != 0x4B || c != 0x52 || d != 0x46) {
        cout << "PAS_UNE_PLANCHE\n";
        return 0;
    }

    unsigned int version = lireU32();
    if (tronque) {
        cout << "TRONQUE\n";
        return 0;
    }
    if (version != 1) {
        cout << "VERSION_INCONNUE " << version << "\n";
        return 0;
    }

    // la vue
    float cx = lireF32();
    float cy = lireF32();
    float zoom = lireF32();
    sortie.push_back("VUE " + deuxChiffres(cx) + " " + deuxChiffres(cy) + " " + deuxChiffres(zoom));

    int theme = lireU8();
    int grille = lireU8();
    lireU8();   // remplissage
    lireU8();   // remplissage
    if (theme != 0) {
        sortie.push_back("THEME SOMBRE");
    } else {
        sortie.push_back("THEME CLAIR");
    }
    if (grille == 0) {
        sortie.push_back("GRILLE AFFICHEE");
    } else {
        sortie.push_back("GRILLE CACHEE");
    }

    // les images
    unsigned int nbImages = lireU32();
    sortie.push_back("IMAGES " + to_string(nbImages));
    for (unsigned int k = 1; k <= nbImages && !tronque; k++) {
        float x = lireF32();
        float y = lireF32();
        float echelle = lireF32();
        float rotation = lireF32();
        float opacite = lireF32();
        int miroirX = lireU8();
        int miroirY = lireU8();
        lireU8();   // ignore
        lireU8();   // ignore
        unsigned int largeur = lireU32();
        unsigned int hauteur = lireU32();
        unsigned int taille = lireU32();
        sauter(taille);   // les octets source ne nous interessent pas
        if (tronque) {
            break;
        }
        string ligne = "IMAGE " + to_string(k) + " " + deuxChiffres(x) + " " + deuxChiffres(y);
        ligne = ligne + " " + deuxChiffres(echelle) + " " + deuxChiffres(rotation) + " " + deuxChiffres(opacite);
        ligne = ligne + " " + to_string(miroirX != 0 ? 1 : 0) + " " + to_string(miroirY != 0 ? 1 : 0);
        ligne = ligne + " " + to_string(largeur) + " " + to_string(hauteur) + " " + to_string(taille);
        sortie.push_back(ligne);
    }

    // les traits
    unsigned int nbTraits = 0;
    if (!tronque) {
        nbTraits = lireU32();
        sortie.push_back("TRAITS " + to_string(nbTraits));
    }
    for (unsigned int k = 1; k <= nbTraits && !tronque; k++) {
        int r = lireU8();
        int g = lireU8();
        int bleu = lireU8();
        int alpha = lireU8();
        float epaisseur = lireF32();
        unsigned int nbPoints = lireU32();
        if (tronque) {
            break;
        }
        string ligne = "TRAIT " + to_string(k) + " " + to_string(r) + " " + to_string(g);
        ligne = ligne + " " + to_string(bleu) + " " + to_string(alpha);
        ligne = ligne + " " + deuxChiffres(epaisseur) + " " + to_string(nbPoints);
        sortie.push_back(ligne);
        for (unsigned int p = 0; p < nbPoints && !tronque; p++) {
            float px = lireF32();
            float py = lireF32();
            if (tronque) {
                break;
            }
            sortie.push_back("POINT " + deuxChiffres(px) + " " + deuxChiffres(py));
        }
    }

    if (tronque) {
        cout << "TRONQUE\n";
        return 0;
    }
    for (size_t i = 0; i < sortie.size(); i++) {
        cout << sortie[i] << "\n";
    }
    return 0;
}
