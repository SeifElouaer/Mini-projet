#ifndef COMMANDE_H_INCLUDED
#define COMMANDE_H_INCLUDED

#include "headers.h"
#include<time.h>

typedef struct commande{
    int id;
    int matriculeClient;
    int idPokemon;
    int quantité;
    time_t date;
    char etat[];
}commande;

/********Declaration fonctions COMMANDE************/

void ajouterCommande(commande c[], int *n);
void afficherCommandes(commande c[], int n);
void modifierCommande(commande c[], int n);
void supprimerCommande(commande c[], int *n);

#endif // COMMANDE_H_INCLUDED
