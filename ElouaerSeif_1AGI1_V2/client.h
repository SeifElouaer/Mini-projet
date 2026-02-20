#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED


#include "headers.h"
#include "commande.h"


typedef struct client{
    int matricule;
    char nom[20];
    int nbrCommande;
    ListeCommande* commandes;
}client;

struct ListeClient {
    client cl;
    ListeClient* suivant;
};

/********Declaration fonctions CLIENT************/

int genererMat();
client creerClient();
void ajouterClient(ListeClient** liste);
void afficherClient(client c);
void afficherClients(ListeClient* liste);
ListeClient* rechercherClient(ListeClient* liste, int id);
void modifierClient(ListeClient* liste, ListePokemon* listePokemons);
void supprimerClient(ListeClient** liste);
void libererListeClient(ListeClient** liste);
int compterClients(ListeClient* liste);


void sauvegarderClients(ListeClient* liste, const char* nomFichier);
ListeClient* chargerClients(const char* nomFichier);

#endif // CLIENT_H_INCLUDED
