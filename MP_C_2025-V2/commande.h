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


#ifndef GUI
void menuCommandeGUI(Ecran *ecranActuel);
void commandeAjoutGUI(Ecran *ecranActuel);
void commandeModifGUI(Ecran *ecranActuel);
void commandeSuppGUI(Ecran *ecranActuel);
#endif

#endif // COMMANDE_H_INCLUDED
