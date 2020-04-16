#ifndef AUTEUR_H
#define AUTEUR_H

#include <string>
#include <iostream>

using namespace std;

class Auteur
{
public:
    Auteur() = default;
    Auteur(const std::string& nom, unsigned int anneeDeNaissance);

    void afficher(std::ostream& stream) const;

    const std::string& getNom() const;
    unsigned int getAnneeDeNaissance() const;
    unsigned int getNbFilms() const;

    void setNbFilms(unsigned int nbFilms);
    friend ostream& operator<<(ostream& o, const Auteur& auteur);
    friend bool operator==(const string& nom, const Auteur& auteur);
    bool operator==(const string& nom);

private:
    std::string nom_;
    unsigned int anneeDeNaissance_;
    unsigned int nbFilms_;
};
#endif // AUTEUR_H