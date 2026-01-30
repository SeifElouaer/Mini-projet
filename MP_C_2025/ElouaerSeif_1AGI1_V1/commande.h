#ifndef COMMANDE_H_INCLUDED
#define COMMANDE_H_INCLUDED

#include "headers.h"
#include<time.h>
#include "client.h"
#include "pokemon.h"


struct pokemon ;
struct client ;

typedef struct commande{
    int id;
    int matriculeClient;
    int idPokemon;
    int quantite;
    char dateHeure[50];
    int etat;
}commande;

/********Declaration fonctions COMMANDE************/

int genererIdCommande();
commande creerCommande(pokemon p[], int nbPokemons);
void ajouterCommande(commande c[],pokemon p[], int nbPokemons, int *n);
void afficherCommande(commande c);
void afficherCommandes(commande c[], int n);
int chercherCommande(commande c[], int n, int id);
void modifierCommande(commande c[], pokemon p[], int n, int nbPokemons);
void supprimerCommande(commande c[], int *n);

#endif // COMMANDE_H_INCLUDED
