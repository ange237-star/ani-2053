#include <iostream>
#include <string>
#include <vector>
using namespace std;

// le modele et les deux tableaux que le programme d'affichage tient a cote
vector<string> modele;
vector<string> textures;
vector<string> sources;

// ce que chaque ligne de depart cite comme tableaux
bool ajouteTex, ajouteSrc;
bool supprimeTex, supprimeSrc;
bool echangeTex, echangeSrc;

// lit une ligne et dit si elle cite "textures" et/ou "sources"
void lireLigne(bool &citeTextures, bool &citeSources) {
    string ligne;
    getline(cin, ligne);
    citeTextures = (ligne.find("textures") != string::npos);
    citeSources = (ligne.find("sources") != string::npos);
}

// echange les cases i et j dans un tableau, seulement s'il a les deux index
void echanger(vector<string> &tableau, int i, int j) {
    int taille = tableau.size();
    if (i >= 0 && j >= 0 && i < taille && j < taille) {
        string temp = tableau[i];
        tableau[i] = tableau[j];
        tableau[j] = temp;
    }
}

int main() {
    lireLigne(ajouteTex, ajouteSrc);
    lireLigne(supprimeTex, supprimeSrc);
    lireLigne(echangeTex, echangeSrc);

    int n;
    cin >> n;
    for (int k = 0; k < n; k++) {
        string operation;
        cin >> operation;

        if (operation == "AJOUTE") {
            string nom;
            cin >> nom;
            modele.push_back(nom);
            if (ajouteTex) textures.push_back(nom);
            if (ajouteSrc) sources.push_back(nom);

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
                int i = index[j];
                modele.erase(modele.begin() + i);
                if (supprimeTex && i < (int)textures.size()) {
                    textures.erase(textures.begin() + i);
                }
                if (supprimeSrc && i < (int)sources.size()) {
                    sources.erase(sources.begin() + i);
                }
            }

        } else if (operation == "MONTE" || operation == "DESCEND") {
            int i;
            cin >> i;
            int j = i + 1;
            if (operation == "DESCEND") {
                j = i - 1;
            }
            // le modele ne change que s'il a les deux index
            int taille = modele.size();
            if (j >= 0 && j < taille) {
                echanger(modele, i, j);
                if (echangeTex) echanger(textures, i, j);
                if (echangeSrc) echanger(sources, i, j);
            }
        }
    }

    // L : la longueur du plus long des trois tableaux
    int longueur = modele.size();
    if ((int)textures.size() > longueur) longueur = textures.size();
    if ((int)sources.size() > longueur) longueur = sources.size();

    int decales = 0;
    for (int i = 0; i < longueur; i++) {
        string a = "-", b = "-", c = "-";
        if (i < (int)modele.size()) a = modele[i];
        if (i < (int)textures.size()) b = textures[i];
        if (i < (int)sources.size()) c = sources[i];
        cout << i << " " << a << " " << b << " " << c << "\n";
        // decale : une case manque, ou les noms sont differents
        if (a == "-" || b == "-" || c == "-" || a != b || a != c) {
            decales = decales + 1;
        }
    }
    cout << "DECALES " << decales << "\n";
    return 0;
}
