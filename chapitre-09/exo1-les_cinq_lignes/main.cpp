#include <iostream>
#include <string>
#include <cctype>

// Les cinq membres, dans l'ordre d'affichage
enum Membre { DESTRUCTEUR, COPIE, AFFECTATION_COPIE, DEPLACEMENT, AFFECTATION_DEPLACEMENT, NB_MEMBRES };

static const char *NOMS[NB_MEMBRES] = {
    "DESTRUCTEUR", "COPIE", "AFFECTATION_COPIE", "DEPLACEMENT", "AFFECTATION_DEPLACEMENT"
};

// retire toutes les espaces (et tabulations, retours chariot)
static std::string sansEspaces(const std::string &s) {
    std::string r;
    for (char c : s)
        if (!std::isspace(static_cast<unsigned char>(c))) r += c;
    return r;
}

static bool commencePar(const std::string &s, const std::string &debut) {
    return s.compare(0, debut.size(), debut) == 0;
}

static bool finitPar(const std::string &s, const std::string &fin) {
    return s.size() >= fin.size() && s.compare(s.size() - fin.size(), fin.size(), fin) == 0;
}

// vrai si la ligne commence par debut et que le caractere suivant n'est pas un second '&'
static bool commenceSansDoubleEt(const std::string &s, const std::string &debut) {
    if (!commencePar(s, debut)) return false;
    return !(s.size() > debut.size() && s[debut.size()] == '&');
}

int main() {
    std::string classe;
    std::getline(std::cin, classe);
    classe = sansEspaces(classe);

    // etat de chaque membre : "ABSENT" tant qu'il n'a pas ete reconnu
    std::string etat[NB_MEMBRES];
    for (int i = 0; i < NB_MEMBRES; i++) etat[i] = "ABSENT";

    std::string ligne;
    while (std::getline(std::cin, ligne)) {
        size_t commentaire = ligne.find("//");
        if (commentaire != std::string::npos) ligne = ligne.substr(0, commentaire);
        ligne = sansEspaces(ligne);
        if (ligne.empty()) continue;

        int membre = -1;
        if (ligne.find("~" + classe + "(") != std::string::npos)
            membre = DESTRUCTEUR;
        else if (commenceSansDoubleEt(ligne, classe + "(const" + classe + "&"))
            membre = COPIE;
        else if (commenceSansDoubleEt(ligne, classe + "&operator=(const" + classe + "&"))
            membre = AFFECTATION_COPIE;
        else if (commencePar(ligne, classe + "(" + classe + "&&"))
            membre = DEPLACEMENT;
        else if (commencePar(ligne, classe + "&operator=(" + classe + "&&"))
            membre = AFFECTATION_DEPLACEMENT;
        if (membre < 0) continue;

        if (finitPar(ligne, "=delete;")) etat[membre] = "SUPPRIME";
        else if (finitPar(ligne, "=default;")) etat[membre] = "DEFAUT";
        else etat[membre] = "ECRIT";
    }

    bool declare[NB_MEMBRES];
    int nbDeclares = 0;
    for (int i = 0; i < NB_MEMBRES; i++) {
        declare[i] = (etat[i] != "ABSENT");
        if (declare[i]) nbDeclares++;
    }

    bool deplacement = declare[DEPLACEMENT] || declare[AFFECTATION_DEPLACEMENT];
    std::string regle;
    if (nbDeclares == 0) regle = "ZERO";
    else if (nbDeclares == NB_MEMBRES) regle = "CINQ";
    else if (declare[DESTRUCTEUR] && declare[COPIE] && declare[AFFECTATION_COPIE] && !deplacement)
        regle = "TROIS";
    else regle = "INCOMPLETE";

    for (int i = 0; i < NB_MEMBRES; i++)
        std::cout << NOMS[i] << " " << etat[i] << "\n";
    std::cout << "REGLE " << regle << "\n";

    if (regle == "INCOMPLETE") {
        // avec un deplacement declare, on cite les cinq membres absents ;
        // sinon seulement les absents parmi les trois premiers
        int limite = deplacement ? NB_MEMBRES : AFFECTATION_COPIE + 1;
        for (int i = 0; i < limite; i++)
            if (!declare[i]) std::cout << "MANQUE " << NOMS[i] << "\n";
    }

    std::cout << "POSSEDE " << (etat[DESTRUCTEUR] == "ECRIT" ? "OUI" : "NON") << "\n";
    bool unique = (etat[COPIE] == "SUPPRIME") &&
                  (etat[DEPLACEMENT] == "ECRIT" || etat[DEPLACEMENT] == "DEFAUT");
    std::cout << "UNIQUE " << (unique ? "OUI" : "NON") << "\n";
    return 0;
}
