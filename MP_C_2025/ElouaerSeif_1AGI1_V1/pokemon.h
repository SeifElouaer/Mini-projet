#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

#include "headers.h"

typedef struct pokemon{
    int id;
    char nom[20];
    float prix;
    char type[];
}pokemon;

/********Declaration fonctions POKEMON************/
ETUDIANT saisirEtud();
void AfficherEtudiant(ETUDIANT e);
void modifier_etudiant(ETUDIANT *etd);

int AjouterEtudiant(ETUDIANT TabEtud[],int last_index, int taille);
void afficherTabEtudiant(ETUDIANT TabEtud[],int n);

int rechercherId(ETUDIANT TabEtud[],int n);
int rechercherEtudiantNom(ETUDIANT TabEtud[], int n, char nom[]);
void supprimer_etudiant(ETUDIANT TabEtud[],int *N, int pos);

#endif // POKEMON_H_INCLUDED
