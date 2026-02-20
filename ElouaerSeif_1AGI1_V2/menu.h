#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



// variables globales
extern ListePokemon* listePokemons;
extern ListeMachine* listeMachines;
extern ListeClient* listeClients;
extern ListeCommande* listeCommandes;


void menuPrincipal();
void menuPokemon();
void menuMachine();
void menuClient();
void menuCommande();
void menuProduction();
void menuEtatUsine();

void afficherClassementPokemons(ListeCommande* listeCommandes, ListePokemon* listePokemons);

void afficherStatistiques(ListePokemon* listePokemons, ListeMachine* listeMachines,
                         ListeClient* listeClients, ListeCommande* listeCommandes);



#endif // MENU_H_INCLUDED
