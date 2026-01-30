#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED


#include "headers.h"
#include "commande.h"

struct commande;

typedef struct client{
    int matricule;
    char nom[20];
    int nbrCommande;
    commande liste[MAX_TAILLE];
}client;

/********Declaration fonctions CLIENT************/

int genererMat();
client creerClient();
void ajouterClient(client c[],int *n);
void afficherClient(client c);
void afficherClients(client c[], int n);
int chercherClient(client c[], int n, int id);
void modifierClient(client c[], pokemon p[], int n, int nbPokemons);
void supprimerClient(client c[], int *n);

#endif // CLIENT_H_INCLUDED
