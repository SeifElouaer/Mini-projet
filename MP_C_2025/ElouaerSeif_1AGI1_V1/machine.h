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
    char etat[];
    int idCommande;
}machine;

/********Declaration fonctions MACHINE************/

void ajouterMachine(machine m[], int *n);
void afficherMachines(machine m[], int n);
void modifierMachine(machine m[], int n);
void supprimerMachine(machine m[], int *n);

#endif // MACHINE_H_INCLUDED
