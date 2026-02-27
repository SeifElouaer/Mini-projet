#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

// Valeur initiale de la caisse (modifiable ici)
#define CAISSE_INITIALE 1000.0f
#define FICHIER_POKEMONS "pokemons.txt"
#define FICHIER_MACHINES "machines.txt"
#define FICHIER_CLIENTS "clients.txt"
#define FICHIER_COMMANDES "commandes.txt"
#define FICHIER_CAISSE "caisse.txt"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gui.h"
#include "raylib.h"
#include "gui_elements.h"
#include "gui_context.h"

// Forward declarations
typedef struct pokemon pokemon;
typedef struct machine machine;
typedef struct client client;
typedef struct commande commande;

typedef struct ListePokemon ListePokemon;
typedef struct ListeMachine ListeMachine;
typedef struct ListeClient ListeClient;
typedef struct ListeCommande ListeCommande;

// Structures principales
struct pokemon {
    int id;
    char nom[20];
    float prix;
    char type[20];
};

struct commande {
    int id;
    int matriculeClient;
    int idPokemon;
    int quantite;
    int quantiteProduite;  // Nouveau champ pour suivre la production
    char dateHeure[50];
    int etat; // 0=En attente, 1=En cours, 2=Realisee
};

struct machine {
    int id;
    char nom[20];
    int idPokemon;
    int tempsProd;
    int nbMax;
    int compteur;
    float coutMaint;
    int etat; // 0=Libre, 1=Occupee, 2=En attente de maintenance
    int idCommande;
    time_t dateDisponibilite; // Timestamp de disponibilité
};

struct client {
    int matricule;
    char nom[20];
    ListeCommande* commandes;
};

// Structures de listes chaînées
struct ListePokemon {
    pokemon data;
    ListePokemon* next;
};

struct ListeMachine {
    machine data;
    ListeMachine* next;
};

struct ListeClient {
    client data;
    ListeClient* next;
};

struct ListeCommande {
    commande data;
    ListeCommande* next;
};

// Variables globales
extern float caisse;

// Fonctions Pokemon
#include "pokemon.h"

// Fonctions Machine
#include "machine.h"

// Fonctions Client
#include "client.h"

// Fonctions Commande
#include "commande.h"

// Fonctions Menu
#include "menu.h"




// Fonctions supplémentaires Version 2
void finaliserProduction(ListeCommande** listeCommandes, ListeMachine** listeMachines, int idCommande);
void realiserCommande(ListeCommande** listeCommandes, ListeMachine** listeMachines,
                      ListePokemon* listePokemons, int idCommande);
void entretenirMachine(ListeMachine** listeMachines, int idMachine);
void afficherTempsRestant(machine m);
void afficherClassementPokemons(ListeCommande* listeCommandes, ListePokemon* listePokemons);
void sauvegarderCaisse();

void menuClientGUI(Ecran *ecranActuel);
void clientAjoutGUI(Ecran *ecranActuel);
void clientModifGUI(Ecran *ecranActuel);
void clientSuppGUI(Ecran *ecranActuel);
void clientAffGUI(Ecran *ecranActuel);
void menuCommandeGUI(Ecran *ecranActuel);
void commandeAjoutGUI(Ecran *ecranActuel);
void commandeModifGUI(Ecran *ecranActuel);
void commandeSuppGUI(Ecran *ecranActuel);
void commandeAffGUI(Ecran *ecranActuel);
void menuProductionGUI(Ecran *ecranActuel);

// Export CSV
#include "export.h"

// Camembert console
void afficherCamembertConsole(ListeCommande* listeCommandes, ListePokemon* listePokemons);
void prodRealiserGUI(Ecran *ecranActuel);
void prodEntretenirGUI(Ecran *ecranActuel);
void prodEtatGUI(Ecran *ecranActuel);
void menuClientGUI(Ecran *ecranActuel);
void menuEtatUsineGUI(Ecran *ecranActuel);
void menuClassementGUI(Ecran *ecranActuel);
void afficherCaisse();
#endif // HEADERS_H_INCLUDED
