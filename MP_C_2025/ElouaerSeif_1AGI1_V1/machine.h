#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

#include "headers.h"
#include "pokemon.h"

struct pokemon;
struct commande;

typedef struct machine{
    int id;
    char nom[20];
    int idPokemon;
    int tempsProd;
    int nbMax;
    int compteur;
    float coutMaint;
    int etat;
    int idCommande;
}machine;

/********Declaration fonctions MACHINE************/

int genererId();
machine creerMachine(pokemon p[], int nbPokemons);
void ajouterMachine(machine m[],pokemon p[], int nbPokemons, int *n);
void afficherMachine(machine m ,commande Tab_Commande[], int n);
void afficherMachines(machine m[], commande Tab_Commande[], int n);
int chercherMachine(machine m[],int *n,int id);
void modifierMachine(machine m[],pokemon p[], commande c[], int n, int nbPokemons, int nbCommandes);
void supprimerMachine(machine m[], int *n);

#endif // MACHINE_H_INCLUDED
