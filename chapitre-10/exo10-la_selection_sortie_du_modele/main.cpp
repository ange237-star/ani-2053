#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---- conception 1 : chaque image porte un drapeau qui la suit partout ----
vector<string> aNoms;
vector<bool> aChoisi;

// ---- conception 2 : l'interface garde des index ----
vector<string> bNoms;
vector<int> bIndex;

// ---- conception 3 : l'interface garde des noms ----
vector<string> cNoms;
vector<string> cGardes;

bool dans(const vector<int> &liste, int valeur) {
    for (size_t i = 0; i < liste.size(); i++) {
        if (liste[i] == valeur) return true;
    }
    return false;
}

bool danss(const vector<string> &liste, const string &valeur) {
    for (size_t i = 0; i < liste.size(); i++) {
        if (liste[i] == valeur) return true;
    }
    return false;
}

void echanger(vector<string> &noms, int i, int j) {
    string temp = noms[i];
    noms[i] = noms[j];
    noms[j] = temp;
}

// ecrit "CONCEPTION TITRE nom nom ..." ou AUCUN
void ecrire(const string &conception, const string &titre, const vector<string> &noms) {
    cout << conception << " " << titre;
    if (noms.size() == 0) {
        cout << " AUCUN";
    }
    for (size_t i = 0; i < noms.size(); i++) {
        cout << " " << noms[i];
    }
    cout << "\n";
}

// les noms choisis, dans l'ordre de la planche, pour chaque conception
vector<string> selectionA() {
    vector<string> r;
    for (size_t i = 0; i < aNoms.size(); i++) {
        if (aChoisi[i]) r.push_back(aNoms[i]);
    }
    return r;
}

vector<string> selectionB() {
    vector<string> r;
    for (size_t i = 0; i < bNoms.size(); i++) {
        if (dans(bIndex, (int)i)) r.push_back(bNoms[i]);
    }
    return r;
}

vector<string> selectionC() {
    vector<string> r;
    for (size_t i = 0; i < cNoms.size(); i++) {
        if (danss(cGardes, cNoms[i])) r.push_back(cNoms[i]);
    }
    return r;
}

int main() {
    string operation;
    while (cin >> operation) {
        int taille;

        if (operation == "AJOUTE") {
            string nom;
            cin >> nom;
            aNoms.push_back(nom);
            aChoisi.push_back(false);
            bNoms.push_back(nom);
            cNoms.push_back(nom);

        } else if (operation == "CLIC") {
            int i;
            cin >> i;
            // la selection se vide d'abord, meme si i n'existe pas
            for (size_t k = 0; k < aChoisi.size(); k++) aChoisi[k] = false;
            bIndex.clear();
            cGardes.clear();
            taille = aNoms.size();
            if (i >= 0 && i < taille) aChoisi[i] = true;
            taille = bNoms.size();
            if (i >= 0 && i < taille) bIndex.push_back(i);
            taille = cNoms.size();
            if (i >= 0 && i < taille) cGardes.push_back(cNoms[i]);

        } else if (operation == "AJOUTE_SEL") {
            int i;
            cin >> i;
            taille = aNoms.size();
            if (i >= 0 && i < taille) aChoisi[i] = true;
            taille = bNoms.size();
            if (i >= 0 && i < taille && !dans(bIndex, i)) bIndex.push_back(i);
            taille = cNoms.size();
            if (i >= 0 && i < taille && !danss(cGardes, cNoms[i])) cGardes.push_back(cNoms[i]);

        } else if (operation == "ECHANGE") {
            int i, j;
            cin >> i >> j;
            taille = aNoms.size();
            if (i >= 0 && j >= 0 && i < taille && j < taille) {
                echanger(aNoms, i, j);
                bool temp = aChoisi[i];
                aChoisi[i] = aChoisi[j];
                aChoisi[j] = temp;
            }
            taille = bNoms.size();
            if (i >= 0 && j >= 0 && i < taille && j < taille) echanger(bNoms, i, j);
            taille = cNoms.size();
            if (i >= 0 && j >= 0 && i < taille && j < taille) echanger(cNoms, i, j);

        } else if (operation == "RETIRE") {
            int i;
            cin >> i;
            taille = aNoms.size();
            if (i >= 0 && i < taille) {
                aNoms.erase(aNoms.begin() + i);
                aChoisi.erase(aChoisi.begin() + i);
            }
            taille = bNoms.size();
            if (i >= 0 && i < taille) bNoms.erase(bNoms.begin() + i);
            taille = cNoms.size();
            if (i >= 0 && i < taille) cNoms.erase(cNoms.begin() + i);

        } else if (operation == "SUPPRIME") {
            // les images choisies sortent de la planche, puis la selection se vide
            for (int i = (int)aNoms.size() - 1; i >= 0; i--) {
                if (aChoisi[i]) {
                    aNoms.erase(aNoms.begin() + i);
                    aChoisi.erase(aChoisi.begin() + i);
                }
            }
            for (int i = (int)bNoms.size() - 1; i >= 0; i--) {
                if (dans(bIndex, i)) bNoms.erase(bNoms.begin() + i);
            }
            bIndex.clear();
            for (int i = (int)cNoms.size() - 1; i >= 0; i--) {
                if (danss(cGardes, cNoms[i])) cNoms.erase(cNoms.begin() + i);
            }
            cGardes.clear();
        }
    }

    vector<string> selA = selectionA();
    vector<string> selB = selectionB();
    vector<string> selC = selectionC();

    ecrire("DANS_ITEM", "PLANCHE", aNoms);
    ecrire("DANS_ITEM", "SELECTION", selA);
    ecrire("PAR_INDEX", "PLANCHE", bNoms);
    ecrire("PAR_INDEX", "SELECTION", selB);
    ecrire("PAR_ID", "PLANCHE", cNoms);
    ecrire("PAR_ID", "SELECTION", selC);

    // les conceptions qui different de DANS_ITEM
    vector<string> faux;
    if (bNoms != aNoms || selB != selA) faux.push_back("PAR_INDEX");
    if (cNoms != aNoms || selC != selA) faux.push_back("PAR_ID");
    cout << "FAUX";
    if (faux.size() == 0) {
        cout << " AUCUN";
    }
    for (size_t i = 0; i < faux.size(); i++) {
        cout << " " << faux[i];
    }
    cout << "\n";
    return 0;
}
