#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

#include "headers.h"

typedef struct pokemon{
    int id;
    char nom[20];
    float prix;
    char type[20];
}pokemon;

/********Declaration fonctions POKEMON************/

int genererIdP();
pokemon creerPokemon();
void afficherpokemon(pokemon p);
void afficherPokemons(pokemon p[], int n);
void ajouterPokemon(pokemon p[], int *n);
int rechercherPokemon(pokemon p[], int n, int id);
void modifierPokemon(pokemon p[], int n);
void supprimerPokemon(pokemon p[], int *n);

#endif // POKEMON_H_INCLUDED
