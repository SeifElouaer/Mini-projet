#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

#include "headers.h"

typedef struct pokemon{
    int id;
    char nom[30];
    float prix;
    char type[20];
}pokemon;

/********Declaration fonctions POKEMON************/

void afficherPokemons(pokemon tab[], int n);
void ajouterPokemon(pokemon tab[], int *n);
void modifierPokemon(pokemon tab[], int n);
void supprimerPokemon(pokemon tab[], int *n);

#endif // POKEMON_H_INCLUDED
