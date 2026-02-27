#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

// Déclaration des variables globales des listes
extern ListePokemon* listePokemons;
extern ListeMachine* listeMachines;
extern ListeClient* listeClients;
extern ListeCommande* listeCommandes;

// Menus
void menuPrincipal();
void menuPokemon();
void menuMachine();
void menuClient();
void menuCommande();
void menuProduction();
void menuEtatUsine();

// Fonctions statistiques
void afficherStatistiques(ListePokemon* listePokemons, ListeMachine* listeMachines,
                         ListeClient* listeClients, ListeCommande* listeCommandes);

#endif // MENU_H_INCLUDED
