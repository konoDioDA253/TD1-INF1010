#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include <memory>
#include "Film.h"
#include <vector>
#include "GestionnaireAuteurs.h"
using namespace std;

class Librairie
{
public:
    Librairie();
    Librairie(const Librairie& librairie);
    Librairie& operator=(const Librairie& librairie);
    ~Librairie();

    Film* chercherFilm(const std::string& nomFilm);
    bool chargerFilmsDepuisFichier(const std::string& nomFichier,
                                   GestionnaireAuteurs& gestionnaireAuteurs);
    bool chargerRestrictionsDepuisFichiers(const std::string& nomFichier);
    
    friend ostream& operator<<(ostream& o, const Librairie& librairie);

	Librairie& operator+=(Film* film);
    Librairie& operator-=(string nomFilm);

	const std::vector<std::unique_ptr<Film>>& getFilms() const;
    std::size_t getNbFilms() const;

private:
    void supprimerFilms();
    bool lireLigneRestrictions(const std::string& ligne);
    bool lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs);
    int trouverIndexFilm(const std::string& nomFilm) const;

    // Movies array
    vector<unique_ptr<Film>> films_;
};

#endif // LIBRAIRIE_H