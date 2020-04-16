// TODO: Faire l'entête de fichier
/*
	INF1010 Groupe 6
	Bouh Abdillahi (matricule: 1940646) et Junior Lionel Metogo (matricule: 1935652)
	Le 11 février 2020
	GestionnaireAuteurs.cpp
	Rôle du fichier: Définit la classe GestionnaireAuteurs qui permet de gérer les auteurs de la
	librairie de CinéPoly
*/

#include "GestionnaireAuteurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur de la classe GestionnaireAuteurs
GestionnaireAuteurs::GestionnaireAuteurs()
    : auteurs_(std::vector<Auteur>(NB_AUTEURS_MAX)) // ne pas changer. le vecteur doit etre initialiser a 16 ici
{
}



//! Méhode qui cherche un auteur par son nom complet
//! \param nomAuteur Le nom de l'auteur à trouver
//! \return          Un pointeur vers l'auteur. Le pointeur est nullptr si l'auteur n'existe pas.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur)
{
    for (std::size_t i = 0; i < auteurs_.size() ; i++)
    {
        if (auteurs_[i] == nomAuteur)
        {
            return &auteurs_[i];
        }
    }

    return nullptr;
}

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool représentant si le chargement a été un succès
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        auteurs_.clear();
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneAuteur(ligne) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}



//! Méthode qui retourne le nombre d'auteurs
//! \return Le nombre d'auteurs
std::size_t GestionnaireAuteurs::getNbAuteurs() const
{
    return auteurs_.size();
}

//! Méthode qui ajoute un auteur avec un string
//! \param ligne Le string qui comporte tous les attributs de l'auteur
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomAuteur;
    unsigned int age;

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

    if (stream >> std::quoted(nomAuteur) >> age)
    {
        bool succes = *this += (Auteur(nomAuteur, age));
        return succes;
    }
    return false;
}

//! Méthode qui affiche un gestionnaire auteur
//! \param gestionnaireAuteur         Le gestionnaire d'auteur qu'on veut afficher
//! \param o                          L'ostream qui sers a afficher
//! \return o                         L'ostream qui sers a afficher
ostream& operator<<(ostream & o , const GestionnaireAuteurs& gestionnaireAuteur)
{
    for (std::size_t i = 0; i < gestionnaireAuteur.auteurs_.size(); i++)
    {
        o << gestionnaireAuteur.auteurs_[i];
    }
	return o;
}

//! Méthode qui ajoute un auteur au gestionnaire d'auteurs
//! \param auteur       L'auteur qu'on veut ajouter au gestionnaire d'auteur
//! \return             Un booleen qui indique si l'operation a reussi
bool GestionnaireAuteurs::operator+=(Auteur auteur)
{
    if (auteurs_.size() < NB_AUTEURS_MAX)
    {
        auteurs_.push_back(auteur);
        return true;
    }
    return false;
}