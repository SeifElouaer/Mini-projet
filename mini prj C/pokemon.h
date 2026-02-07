#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

// Fonctions de gestion des Pokémons
int genererIdP();
pokemon creerPokemon();
void ajouterPokemon(ListePokemon** liste);
void afficherPokemon(pokemon p);
void afficherPokemons(ListePokemon* liste);
ListePokemon* rechercherPokemon(ListePokemon* liste, int id);
void modifierPokemon(ListePokemon* liste);
void supprimerPokemon(ListePokemon** liste);
void libererListePokemon(ListePokemon** liste);
int compterPokemons(ListePokemon* liste);

// Fonctions de gestion des fichiers
void sauvegarderPokemons(ListePokemon* liste, const char* nomFichier);
ListePokemon* chargerPokemons(const char* nomFichier);

#endif // POKEMON_H_INCLUDED
