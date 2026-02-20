#ifndef PRODUCTION_H_INCLUDED
#define PRODUCTION_H_INCLUDED

#include "headers.h"

void finaliserProduction(ListeCommande** listeCommandes, ListeMachine** listeMachines, int idCommande);
void realiserCommande(ListeCommande** listeCommandes, ListeMachine** listeMachines,
                      ListePokemon* listePokemons, int idCommande);
void entretenirMachine(ListeMachine** listeMachines, int idMachine);
void afficherTempsRestant(machine m);



#endif // PRODUCTION_H_INCLUDED
