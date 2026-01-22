#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED


#include "headers.h"

typedef struct client{
    int matricule;
    char nom[20];
    commande liste[];
}client;

/********Declaration fonctions CLIENT************/
ETUDIANT saisirEtud();
void AfficherEtudiant(ETUDIANT e);
void modifier_etudiant(ETUDIANT *etd);

int AjouterEtudiant(ETUDIANT TabEtud[],int last_index, int taille);
void afficherTabEtudiant(ETUDIANT TabEtud[],int n);

int rechercherId(ETUDIANT TabEtud[],int n);
int rechercherEtudiantNom(ETUDIANT TabEtud[], int n, char nom[]);
void supprimer_etudiant(ETUDIANT TabEtud[],int *N, int pos);

#endif // CLIENT_H_INCLUDED
