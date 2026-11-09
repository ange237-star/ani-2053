#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Methode {
    std::string nom;
    bool constDeclaree = false;
    bool modifie = false;
    std::vector<int> appelees;
    int pourrait = -1;          // -1 : pas encore calcule, 0 : non, 1 : oui
};

static std::vector<Methode> methodes;

// une methode pourrait etre const si elle ne modifie rien
// et si chaque methode qu'elle appelle est const ou pourrait l'etre
static bool pourraitEtreConst(int i) {
    Methode &m = methodes[i];
    if (m.pourrait != -1) return m.pourrait == 1;
    bool ok = !m.modifie;
    for (size_t k = 0; ok && k < m.appelees.size(); k++) {
        const Methode &appelee = methodes[m.appelees[k]];
        if (!appelee.constDeclaree && !pourraitEtreConst(m.appelees[k])) ok = false;
    }
    m.pourrait = ok ? 1 : 0;
    return ok;
}

static void afficher(const char *titre, const std::vector<int> &liste) {
    std::cout << titre;
    if (liste.empty()) std::cout << " AUCUN";
    for (int i : liste) std::cout << " " << methodes[i].nom;
    std::cout << "\n";
}

int main() {
    int n = 0;
    std::cin >> n;
    methodes.resize(n);
    std::map<std::string, int> indice;

    // premiere lecture : les noms (les appelees sont resolues apres)
    std::vector<std::vector<std::string>> noms(n);
    for (int i = 0; i < n; i++) {
        std::string decl;
        int modifie = 0, k = 0;
        std::cin >> methodes[i].nom >> decl >> modifie >> k;
        methodes[i].constDeclaree = (decl == "const");
        methodes[i].modifie = (modifie != 0);
        noms[i].resize(k);
        for (int j = 0; j < k; j++) std::cin >> noms[i][j];
        indice[methodes[i].nom] = i;
    }
    for (int i = 0; i < n; i++)
        for (const std::string &nom : noms[i]) methodes[i].appelees.push_back(indice[nom]);

    // POURRAIT : non declaree const, mais pourrait l'etre, dans l'ordre de lecture
    std::vector<int> pourrait;
    for (int i = 0; i < n; i++)
        if (!methodes[i].constDeclaree && pourraitEtreConst(i)) pourrait.push_back(i);

    // RACINES : celles de POURRAIT dont toutes les appelees sont DEJA declarees const
    std::vector<int> racines;
    for (int i : pourrait) {
        bool racine = true;
        for (int a : methodes[i].appelees)
            if (!methodes[a].constDeclaree) racine = false;
        if (racine) racines.push_back(i);
    }

    // PASSES : a chaque passe, toutes les methodes pretes sont declarees en meme temps
    std::vector<bool> estConst(n);
    for (int i = 0; i < n; i++) estConst[i] = methodes[i].constDeclaree;
    std::vector<int> reste = pourrait;
    int passes = 0;
    while (!reste.empty()) {
        std::vector<int> pretes, suivantes;
        for (int i : reste) {
            bool prete = true;
            for (int a : methodes[i].appelees)
                if (!estConst[a]) prete = false;
            (prete ? pretes : suivantes).push_back(i);
        }
        if (pretes.empty()) break;            // ne devrait pas arriver avec une entree valide
        for (int i : pretes) estConst[i] = true;
        reste = suivantes;
        passes++;
    }

    afficher("POURRAIT", pourrait);
    afficher("RACINES", racines);
    std::cout << "PASSES " << passes << "\n";
    return 0;
}
