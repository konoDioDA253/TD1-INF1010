// TODO: Faire l'entête de fichier
/*
	INF1010 Groupe 6
	Bouh Abdillahi (matricule: 1940646) et Junior Lionel Metogo (matricule: 1935652)
	Le 11 février 2020
	Librairie.cpp
	Rôle du fichier: Définit la classe Librairie qui permet de manipuler les films de la librairie de
	CinéPoly
*/

#include "Librairie.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "debogageMemoire.h"
#include "typesafe_enum.h"

namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
} // namespace

//! Constructeur de la classe Librairie
Librairie::Librairie()
    : films_(0)
{
}
Librairie::Librairie(const Librairie& librairie) // constructeur par copie
{
   films_.reserve(librairie.films_.size());
    *this = librairie;
    
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    supprimerFilms();
}

const std::vector<std::unique_ptr<Film>>& Librairie::getFilms() const
{
    return films_;
}

//! Méthode qui retourne un film comportant le même nom que celui envoyé en paramètre
//! \param nomFilm Le nom du film à chercher
//! \return        Un pointeur vers le film. Nullptr si le film n'existe pas
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);
    if (indexFilm == FILM_INEXSISTANT)
    {
        return nullptr;
    }

    return films_[indexFilm].get();
}

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
                                          GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // Supprimers les vieux films avant de lire les nouveaux
        supprimerFilms();

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneFilm(ligne, gestionnaireAuteurs) == false)
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

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (std::size_t i = 0; i < films_.size(); i++)
        {
            films_[i]->supprimerPaysRestreints();
        }
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneRestrictions(ligne) == false)
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

//! Méthode qui retourne le nombre de films
//! \return Le nombre de films
std::size_t Librairie::getNbFilms() const
{
    return films_.size();
}

//! Méthode qui supprime tous les films
void Librairie::supprimerFilms()
{
    for (unsigned i = 0; i < films_.size(); i++)
    {
        films_[i].reset();	//On vide le unique_ptr pour éviter les leaks
        films_[i] = nullptr;
    }
    films_.clear();
}

//! Méthode qui ajoute les restrictions d'un film avec un string
//! \param ligne Le string comportant les restrictions du film
//! \return      Un bool représentant si l'opération est un succès
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    if (stream >> std::quoted(nomFilm))
    {
        Film* film = chercherFilm(nomFilm);
        if (film == nullptr)
        {
            // Film n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            film->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film
//! \param ligne                Le string comportant les attributs du film
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

    if (stream >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >>
        estRestreintParAge >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        auteur->setNbFilms(auteur->getNbFilms() + 1);
        Film* film = new Film(nomFilm,
                              anneeSortie,
                              to_enum<Film::Genre>(genreValeurEnum),
                              to_enum<Pays>(paysValeurEnum),
                              estRestreintParAge,
                              auteur);
        *this += film;
        return true;
    }
    return false;
}

//! Méthode qui retourne l'index d'un film en cherchant son nom
//! \param nomFilm Le nom du film à trouver
//! \return        L'index du film. Retourne -1 si le film n'existe pas
int Librairie::trouverIndexFilm(const std::string& nomFilm) const
{
    for (std::size_t i = 0; i < films_.size(); i++)
    {
        if (films_[i]->getNom() == nomFilm)
        {
            return (int)i;
        }
    }
    return FILM_INEXSISTANT;
}

//! Méthode qui affiche une librairie
//! \param librairie    La librairie qu'on veut afficher
//! \param o            L'ostream qui sers a afficher
//! \return o           L'ostream qui sers a afficher
ostream& operator<<(ostream& o, const Librairie& librairie)
{
    for (std::size_t i = 0; i < librairie.films_.size(); i++)
    {
        o << *(librairie.films_[i]) << endl;
    }
    return o;
}

//! Méthode qui ajoute un film a la librairie de films
//! \param film         Le film qu'on veut ajouter a la librairie de films
Librairie& Librairie::operator+=(Film* film)
{
    if (film!=nullptr)
    {
		films_.push_back(unique_ptr<Film>(film));	//Conversion explicite d'un pointeur brut en unique_ptr
    }
    return *this;
}

//! Méthode qui retire un film de la librairie de films
//! \param nomFilm         Le nom du film qu'on veut ajouter a la librairie de films
Librairie& Librairie::operator-=(std::string nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);
    if (indexFilm != FILM_INEXSISTANT)
    {
        films_[indexFilm] = move(films_.back());
        films_.pop_back();
    }   
     return *this;
}

//! Méthode qui ecrase les attributs d'une librairie par ceux de la librairie passee en parametre
//! \param librairie    La librairie qui va ecraser l'ancienne librairie
Librairie& Librairie::operator=(const Librairie& librairie)
{
    if (this != &librairie)
    {
        supprimerFilms();	//On supprime tous les fims du vector et on remet le vecteur à zéro
        films_.reserve(librairie.films_.size());
        for (unsigned i = 0; i < librairie.films_.size(); ++i)
        {
            films_.push_back(make_unique<Film>(*(librairie.films_[i])));	//Copie du contenu de unique_ptr dans le vecteur vide
        }
    }
    return *this;
}
