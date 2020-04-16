// TODO: Faire l'entête de fichier
/*
	INF1010 Groupe 6
	Bouh Abdillahi (matricule: 1940646) et Junior Lionel Metogo (matricule: 1935652)
	Le 11 février 2020
	Auteur.cpp
	Rôle du fichier: Définit la classe Auteur qui permet de représenter les attributs propres à l'auteur
	d'un film de la librairie
*/

#include "Auteur.h"
#include <iostream>

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Année de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
    : nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbFilms_(0)
{
}

//! Méthode qui retourne le nom de l'auteur
//! \return Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'année de naissance de l'auteur
//! \return L'année de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Méthode qui retourne le nombre de films de l'auteur
//! \return Le nombre de films de l'auteur
unsigned int Auteur::getNbFilms() const
{
    return nbFilms_;
}

//! Méthode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbFilms(unsigned int nbFilms)
{
    nbFilms_ = nbFilms;
}

//! Méthode qui affiche les attributs d'un auteur
//! \param auteur       L'auteur qu'on veut afficher
//! \param o            L'ostream qui sers a afficher
//! \return o           L'ostream qui sers a afficher
ostream& operator<<(ostream& o, const Auteur& auteur)
{
    return o << "Nom: " << auteur.nom_ << " | Date de naissance: " << auteur.anneeDeNaissance_
             << " | Nombre de films: " << auteur.nbFilms_;
}

//! Méthode qui compare un auteur avec un string (avec l'auteur a droite de l'operateur)
//! \param nom      Le nom avec lequel on veut comparer
//! \param auteur   L'auteur avec lequel on veut comparer
//! \return         Le booleen qui indique si l'auteur et le string rentre en parametre sont identiques
bool operator==(const string& nom, const Auteur& auteur)
{
    if (auteur.nom_ == nom)
    {
        return true;
    }
    
    return false;
}

//! Méthode qui compare un auteur avec un string (avec l'auteur a gauche de l'operateur)
//! \param nom      Le nom avec lequel on veut comparer
//! \return         Le booleen qui indique si l'auteur et le string rentre en parametre sont identiques
bool Auteur::operator==(const string& nom)
{
    if (nom_==nom)
    {
        return true;
    }
    return false;
}
