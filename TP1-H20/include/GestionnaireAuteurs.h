#ifndef GESTIONNAIREAUTEURS_H
#define GESTIONNAIREAUTEURS_H

#include <string>
#include "Auteur.h"
#include <vector>

class GestionnaireAuteurs
{
public:
    GestionnaireAuteurs();

    Auteur* chercherAuteur(const std::string& nomAuteur);
    bool chargerDepuisFichier(const std::string& nomFichier);
    friend ostream& operator<<(ostream& o, const GestionnaireAuteurs& gestionnaireAuteur);
    bool operator+=(Auteur auteur);

    std::size_t getNbAuteurs() const;

    static constexpr std::size_t NB_AUTEURS_MAX = 16;

private:
    bool lireLigneAuteur(const std::string& ligne);
    vector<Auteur> auteurs_;
};

#endif // GESTIONNAIREAUTEURS_H