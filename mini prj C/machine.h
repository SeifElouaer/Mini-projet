#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

// Fonctions de gestion des Machines
int genererIdMachine();
machine creerMachine(ListePokemon* listePokemons);
void ajouterMachine(ListeMachine** liste, ListePokemon* listePokemons);
void afficherMachine(machine m, ListeCommande* listeCommandes);
void afficherMachines(ListeMachine* liste, ListeCommande* listeCommandes);
ListeMachine* rechercherMachine(ListeMachine* liste, int id);
ListeMachine* rechercherMachineParPokemon(ListeMachine* liste, int idPokemon);
void modifierMachine(ListeMachine* liste, ListePokemon* listePokemons, ListeCommande* listeCommandes);
void supprimerMachine(ListeMachine** liste);
void libererListeMachine(ListeMachine** liste);
int compterMachines(ListeMachine* liste);

// Fonctions de gestion des fichiers
void sauvegarderMachines(ListeMachine* liste, const char* nomFichier);
ListeMachine* chargerMachines(const char* nomFichier);

#endif // MACHINE_H_INCLUDED
