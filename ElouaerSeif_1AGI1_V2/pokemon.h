#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

#include "headers.h"

typedef struct pokemon{
    int id;
    char nom[20];
    float prix;
    char type[20];
}pokemon;

struct ListePokemon {
    pokemon p;
    struct ListePokemon* suivant;
};

/********Declaration fonctions POKEMON************/

int genererIdP();
pokemon creerPokemon();
void afficherpokemon(pokemon p);
void afficherPokemons(ListePokemon* liste);
void ajouterPokemon(ListePokemon** liste);
ListePokemon* rechercherPokemon(ListePokemon* liste, int id);
void modifierPokemon(ListePokemon* liste);
void supprimerPokemon(ListePokemon** liste);
void libererListePokemon(ListePokemon** liste);
int compterPokemons(ListePokemon* liste);


void sauvegarderPokemons(ListePokemon* liste, const char* nomFichier);
ListePokemon* chargerPokemons(const char* nomFichier);

#endif // POKEMON_H_INCLUDED
