#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

// Fonctions de gestion des Clients
int genererMatricule();
client creerClient();
void ajouterClient(ListeClient** liste);
void afficherClient(client c);
void afficherClients(ListeClient* liste);
ListeClient* rechercherClient(ListeClient* liste, int matricule);
void modifierClient(ListeClient* liste, ListePokemon* listePokemons);
void supprimerClient(ListeClient** liste);
void libererListeClient(ListeClient** liste);
int compterClients(ListeClient* liste);

// Fonctions de gestion des fichiers
void sauvegarderClients(ListeClient* liste, const char* nomFichier);
ListeClient* chargerClients(const char* nomFichier);

#endif // CLIENT_H_INCLUDED
