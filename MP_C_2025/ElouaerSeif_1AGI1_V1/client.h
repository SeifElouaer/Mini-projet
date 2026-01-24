#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED


#include "headers.h"

typedef struct client{
    int matricule;
    char nom[20];
    commande liste[];
}client;

/********Declaration fonctions CLIENT************/
void ajouterClient(client c[], int *n);
void afficherClients(client c[], int n);
void modifierClient(client c[], int n);
void supprimerClient(client c[], int *n);

#endif // CLIENT_H_INCLUDED
