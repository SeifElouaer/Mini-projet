#ifndef COMMANDE_H_INCLUDED
#define COMMANDE_H_INCLUDED

#include "headers.h"
#include<time.h>

typedef struct commande{
    int id;
    client cl;
    pokemon p;
    int quantité;

    char etat[];
}commande;

/********Declaration fonctions COMMANDE************/
ETUDIANT saisirEtud();
void AfficherEtudiant(ETUDIANT e);
void modifier_etudiant(ETUDIANT *etd);

int AjouterEtudiant(ETUDIANT TabEtud[],int last_index, int taille);
void afficherTabEtudiant(ETUDIANT TabEtud[],int n);

int rechercherId(ETUDIANT TabEtud[],int n);
int rechercherEtudiantNom(ETUDIANT TabEtud[], int n, char nom[]);
void supprimer_etudiant(ETUDIANT TabEtud[],int *N, int pos);

#endif // COMMANDE_H_INCLUDED
