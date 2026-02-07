#include "headers.h"

static int compteurIdCommande = 0;

int genererIdCommande() {
    return ++compteurIdCommande;
}

commande creerCommande(ListePokemon* listePokemons) {
    commande c;
    c.id = genererIdCommande();
    
    printf("ID du client: ");
    scanf("%d", &c.matriculeClient);
    
    do {
        printf("ID du pokemon: ");
        scanf("%d", &c.idPokemon);
        if (rechercherPokemon(listePokemons, c.idPokemon) == NULL) {
            printf("Pokemon inexistant. Veuillez reessayer.\n");
        }
    } while (rechercherPokemon(listePokemons, c.idPokemon) == NULL);
    
    printf("Quantite: ");
    scanf("%d", &c.quantite);
    
    c.quantiteProduite = 0; // Initialiser à 0
    
    time_t t;
    time(&t);
    strcpy(c.dateHeure, ctime(&t));
    c.dateHeure[strlen(c.dateHeure) - 1] = '\0'; // Enlever le \n
    
    c.etat = 0; // En attente
    printf("Date et heure d'emission: %s\n", c.dateHeure);
    
    return c;
}

void ajouterCommande(ListeCommande** liste, ListePokemon* listePokemons) {
    ListeCommande* nouveau = (ListeCommande*)malloc(sizeof(ListeCommande));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }
    
    nouveau->data = creerCommande(listePokemons);
    nouveau->next = *liste;
    *liste = nouveau;
    printf("Commande ajoutee avec succes.\n");
}

void afficherCommande(commande c) {
    printf("- ID: %d | Client: %d | Pokemon: %d | Quantite: %d/%d\n", 
           c.id, c.matriculeClient, c.idPokemon, c.quantiteProduite, c.quantite);
    printf("  Date/Heure: %s | Etat: ", c.dateHeure);
    switch (c.etat) {
        case 0: printf("En attente\n"); break;
        case 1: printf("En cours\n"); break;
        case 2: printf("Realisee\n"); break;
        default: printf("Inconnu\n");
    }
}

void afficherCommandes(ListeCommande* liste) {
    if (liste == NULL) {
        printf("Aucune commande.\n");
        return;
    }
    
    ListeCommande* current = liste;
    int count = 1;
    while (current != NULL) {
        printf("#### Commande %d ####\n", count++);
        afficherCommande(current->data);
        current = current->next;
    }
}

ListeCommande* rechercherCommande(ListeCommande* liste, int id) {
    ListeCommande* current = liste;
    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifierCommande(ListeCommande* liste, ListePokemon* listePokemons) {
    if (liste == NULL) {
        printf("Aucune commande.\n");
        return;
    }
    
    int id, choix;
    printf("ID de la commande a modifier: ");
    scanf("%d", &id);
    
    ListeCommande* node = rechercherCommande(liste, id);
    if (node == NULL) {
        printf("Commande introuvable.\n");
        return;
    }
    
    do {
        printf("\n===== Modifier Commande %d =====\n", node->data.id);
        printf("1. ID du pokemon commande\n");
        printf("2. Quantite\n");
        printf("3. Etat de la commande\n");
        printf("0. Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                do {
                    printf("Nouveau ID du Pokemon: ");
                    scanf("%d", &node->data.idPokemon);
                    if (rechercherPokemon(listePokemons, node->data.idPokemon) == NULL) {
                        printf("Pokemon inexistant. Reessayez.\n");
                    }
                } while (rechercherPokemon(listePokemons, node->data.idPokemon) == NULL);
                break;
            case 2:
                printf("Nouvelle quantite: ");
                scanf("%d", &node->data.quantite);
                break;
            case 3:
                printf("Nouvel etat (0=En attente, 1=En cours, 2=Realisee): ");
                scanf("%d", &node->data.etat);
                break;
            case 0:
                printf("Retour au menu precedent.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);
    
    printf("Modification reussie.\n");
}

void supprimerCommande(ListeCommande** liste) {
    if (*liste == NULL) {
        printf("Aucune commande a supprimer.\n");
        return;
    }
    
    int id;
    printf("ID de la commande a supprimer: ");
    scanf("%d", &id);
    
    ListeCommande* current = *liste;
    ListeCommande* prev = NULL;
    
    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Commande introuvable.\n");
        return;
    }
    
    if (prev == NULL) {
        *liste = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    printf("Commande supprimee avec succes.\n");
}

void libererListeCommande(ListeCommande** liste) {
    ListeCommande* current = *liste;
    while (current != NULL) {
        ListeCommande* temp = current;
        current = current->next;
        free(temp);
    }
    *liste = NULL;
}

int compterCommandes(ListeCommande* liste) {
    int count = 0;
    ListeCommande* current = liste;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Fonctions de gestion des fichiers
void sauvegarderCommandes(ListeCommande* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }
    
    ListeCommande* current = liste;
    while (current != NULL) {
        fprintf(fichier, "%d;%d;%d;%d;%d;%s;%d\n",
                current->data.id,
                current->data.matriculeClient,
                current->data.idPokemon,
                current->data.quantite,
                current->data.quantiteProduite,
                current->data.dateHeure,
                current->data.etat);
        current = current->next;
    }
    
    fclose(fichier);
    printf("Commandes sauvegardees dans %s\n", nomFichier);
}

ListeCommande* chargerCommandes(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier %s non trouve. Demarrage avec liste vide.\n", nomFichier);
        return NULL;
    }
    
    ListeCommande* liste = NULL;
    commande c;
    
    while (fscanf(fichier, "%d;%d;%d;%d;%d;%[^;];%d\n",
                  &c.id, &c.matriculeClient, &c.idPokemon,
                  &c.quantite, &c.quantiteProduite, c.dateHeure, &c.etat) == 7) {
        ListeCommande* nouveau = (ListeCommande*)malloc(sizeof(ListeCommande));
        if (nouveau != NULL) {
            nouveau->data = c;
            nouveau->next = liste;
            liste = nouveau;
            
            if (c.id > compteurIdCommande) {
                compteurIdCommande = c.id;
            }
        }
    }
    
    fclose(fichier);
    printf("Commandes chargees depuis %s\n", nomFichier);
    return liste;
}
