#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

#include "headers.h"


typedef struct machine{
    int id;
    char nom[20];
    int idPokemon;
    int tempsProd;
    int nbMax;
    int compteur;
    float coutMaint;
    int etat;      // 0=Libre ; 1=Occupee ; 2=En attente de maintenance
    int idCommande;
    time_t dateDisponibilite;
}machine;

struct ListeMachine {
    machine m;
    ListeMachine* suivant;
};

/********Declaration fonctions MACHINE************/

int genererId();
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



void sauvegarderMachines(ListeMachine* liste, const char* nomFichier);
ListeMachine* chargerMachines(const char* nomFichier);

#endif // MACHINE_H_INCLUDED
