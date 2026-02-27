#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED
#include "gui.h"
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

#ifndef GUI
void menuPokemonGUI(Ecran *ecranActuel);
void pokemonAjoutGUI(Ecran *ecranActuel);
void pokemonModifGUI(Ecran *ecranActuel);
void pokemonSuppGUI(Ecran *ecranActuel);
void pokemonAffGUI(Ecran *ecranActuel);
void RefreshPokemonList();
void InitPokemonUI();
void AjouterPokemonGUI();
void SupprimerPokemonGUI();
void ModifierPokemonGUI();
#endif

#endif // POKEMON_H_INCLUDED
