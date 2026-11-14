#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    int restent = 0; 
    int changes = 0;
    int place = 0;

    for (int k = 1; k <= n; k++) {
        // on lit les treize mots de la ligne, meme ceux qui ne changent jamais
        long long id;
        string x, y, echelle, rotation, opacite, miroirX, miroirY, largeur, hauteur;
        int selectionne;
        string chemin;
        long long octets;
        cin >> id >> x >> y >> echelle >> rotation >> opacite;
        cin >> miroirX >> miroirY >> largeur >> hauteur;
        cin >> selectionne >> chemin >> octets;


        if (octets == 0) {
            cout << "ITEM " << k << " SAUTE\n";
            continue;
        }

        place = place + 1;
        restent = restent + 1;

        
        string noms = "";
        int nombre = 0;
        if (id != 0) {
            noms = noms + " id";
            nombre = nombre + 1;
        }
        if (selectionne == 1) {
            noms = noms + " selected";
            nombre = nombre + 1;
        }
        if (chemin != "-") {
            noms = noms + " sourcePath";
            nombre = nombre + 1;
        }

        cout << "ITEM " << k << " " << place;
        if (nombre == 0) {
            cout << " AUCUN";
        } else {
            cout << noms;
        }
        cout << "\n";
        changes = changes + nombre;
    }

    cout << "RESTENT " << restent << "\n";
    cout << "CHANGES " << changes << "\n";
    return 0;
}
