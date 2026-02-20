#ifndef COMMANDE_H_INCLUDED
#define COMMANDE_H_INCLUDED

#include "headers.h"
#include<time.h>

struct client;

typedef struct commande{
    int id;
    int matriculeClient;
    int idPokemon;
    int quantite;
    int quantiteProduite;
    char dateHeure[50];
    int etat;     // 0=En attente ; 1=En cours ; 2=Realisee
}commande;

struct ListeCommande {
    commande cm;
    ListeCommande* suivant;
};

/********Declaration fonctions COMMANDE************/

int genererIdCommande();
commande creerCommande(ListePokemon* listePokemons, ListeClient* listeClients);
void ajouterCommande(ListeCommande** liste, ListePokemon* listePokemons, ListeClient* ListeClients);
void afficherCommande(commande c);
void afficherCommandes(ListeCommande* liste);
ListeCommande* rechercherCommande(ListeCommande* liste, int id);
void modifierCommande(ListeCommande* liste, ListePokemon* listePokemons);
void supprimerCommande(ListeCommande** liste);
void libererListeCommande(ListeCommande** liste);
int compterCommandes(ListeCommande* liste);



void sauvegarderCommandes(ListeCommande* liste, const char* nomFichier);
ListeCommande* chargerCommandes(const char* nomFichier);

#endif // COMMANDE_H_INCLUDED
