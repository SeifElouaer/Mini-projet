#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

#include "headers.h"

typedef struct machine{
    int id;
    char nom[20];
    pokemon p;
    int temps;
    int nb;
    int compteur;
    float c_maint;
    char etat[];
    commande c;
}machine;

/********Declaration fonctions MACHINE************/
ETUDIANT saisirEtud();
void AfficherEtudiant(ETUDIANT e);
void modifier_etudiant(ETUDIANT *etd);

int AjouterEtudiant(ETUDIANT TabEtud[],int last_index, int taille);
void afficherTabEtudiant(ETUDIANT TabEtud[],int n);

int rechercherId(ETUDIANT TabEtud[],int n);
int rechercherEtudiantNom(ETUDIANT TabEtud[], int n, char nom[]);
void supprimer_etudiant(ETUDIANT TabEtud[],int *N, int pos);

#endif // MACHINE_H_INCLUDED
