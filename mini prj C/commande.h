#ifndef COMMANDE_H_INCLUDED
#define COMMANDE_H_INCLUDED

// Fonctions de gestion des Commandes
int genererIdCommande();
commande creerCommande(ListePokemon* listePokemons);
void ajouterCommande(ListeCommande** liste, ListePokemon* listePokemons);
void afficherCommande(commande c);
void afficherCommandes(ListeCommande* liste);
ListeCommande* rechercherCommande(ListeCommande* liste, int id);
void modifierCommande(ListeCommande* liste, ListePokemon* listePokemons);
void supprimerCommande(ListeCommande** liste);
void libererListeCommande(ListeCommande** liste);
int compterCommandes(ListeCommande* liste);

// Fonctions de gestion des fichiers
void sauvegarderCommandes(ListeCommande* liste, const char* nomFichier);
ListeCommande* chargerCommandes(const char* nomFichier);

#endif // COMMANDE_H_INCLUDED
