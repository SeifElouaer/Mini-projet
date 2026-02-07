#include "headers.h"

static int compteurMatricule = 0;

int genererMatricule() {
    return ++compteurMatricule;
}

client creerClient() {
    client c;
    c.matricule = genererMatricule();
    printf("Nom du client: ");
    scanf("%s", c.nom);
    c.commandes = NULL;
    return c;
}

void ajouterClient(ListeClient** liste) {
    ListeClient* nouveau = (ListeClient*)malloc(sizeof(ListeClient));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }
    
    nouveau->data = creerClient();
    nouveau->next = *liste;
    *liste = nouveau;
    printf("Client ajoute avec succes.\n");
}

void afficherClient(client c) {
    printf("- Matricule: %d | Nom: %s\n", c.matricule, c.nom);
    
    int nbCommandes = compterCommandes(c.commandes);
    printf("  Nombre de commandes: %d\n", nbCommandes);
    
    if (c.commandes != NULL) {
        printf("  Commandes du client:\n");
        ListeCommande* current = c.commandes;
        while (current != NULL) {
            printf("    - ID=%d, Pokemon=%d, Quantite=%d\n",
                   current->data.id, current->data.idPokemon, current->data.quantite);
            current = current->next;
        }
    }
}

void afficherClients(ListeClient* liste) {
    if (liste == NULL) {
        printf("Aucun client.\n");
        return;
    }
    
    ListeClient* current = liste;
    int count = 1;
    while (current != NULL) {
        printf("#### Client %d ####\n", count++);
        afficherClient(current->data);
        current = current->next;
    }
}

ListeClient* rechercherClient(ListeClient* liste, int matricule) {
    ListeClient* current = liste;
    while (current != NULL) {
        if (current->data.matricule == matricule) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifierClient(ListeClient* liste, ListePokemon* listePokemons) {
    if (liste == NULL) {
        printf("Aucun client.\n");
        return;
    }
    
    int mat, choix, op;
    printf("Matricule du client a modifier: ");
    scanf("%d", &mat);
    
    ListeClient* node = rechercherClient(liste, mat);
    if (node == NULL) {
        printf("Client introuvable.\n");
        return;
    }
    
    do {
        printf("\n===== Modifier Client %d =====\n", node->data.matricule);
        printf("1. Nom\n");
        printf("2. Liste de commandes\n");
        printf("0. Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                printf("Nouveau nom: ");
                scanf("%s", node->data.nom);
                break;
            case 2:
                printf("\n=== Gestion des commandes du client ===\n");
                printf("1. Ajouter commande\n");
                printf("2. Modifier commande\n");
                printf("3. Supprimer commande\n");
                printf("0. Retour\n");
                printf("Choix: ");
                scanf("%d", &op);
                
                switch (op) {
                    case 1:
                        ajouterCommande(&(node->data.commandes), listePokemons);
                        break;
                    case 2:
                        modifierCommande(node->data.commandes, listePokemons);
                        break;
                    case 3:
                        supprimerCommande(&(node->data.commandes));
                        break;
                    case 0:
                        printf("Retour.\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
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

void supprimerClient(ListeClient** liste) {
    if (*liste == NULL) {
        printf("Aucun client a supprimer.\n");
        return;
    }
    
    int mat;
    printf("Matricule du client a supprimer: ");
    scanf("%d", &mat);
    
    ListeClient* current = *liste;
    ListeClient* prev = NULL;
    
    while (current != NULL && current->data.matricule != mat) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Client introuvable.\n");
        return;
    }
    
    // Libérer les commandes du client
    libererListeCommande(&(current->data.commandes));
    
    if (prev == NULL) {
        *liste = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    printf("Client supprime avec succes.\n");
}

void libererListeClient(ListeClient** liste) {
    ListeClient* current = *liste;
    while (current != NULL) {
        ListeClient* temp = current;
        current = current->next;
        libererListeCommande(&(temp->data.commandes));
        free(temp);
    }
    *liste = NULL;
}

int compterClients(ListeClient* liste) {
    int count = 0;
    ListeClient* current = liste;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Fonctions de gestion des fichiers
void sauvegarderClients(ListeClient* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }
    
    ListeClient* current = liste;
    while (current != NULL) {
        // Sauvegarder les infos du client
        fprintf(fichier, "%d;%s;", current->data.matricule, current->data.nom);
        
        // Compter et sauvegarder le nombre de commandes
        int nbCommandes = compterCommandes(current->data.commandes);
        fprintf(fichier, "%d", nbCommandes);
        
        // Sauvegarder les IDs des commandes
        ListeCommande* cmd = current->data.commandes;
        while (cmd != NULL) {
            fprintf(fichier, ";%d", cmd->data.id);
            cmd = cmd->next;
        }
        fprintf(fichier, "\n");
        
        current = current->next;
    }
    
    fclose(fichier);
    printf("Clients sauvegardes dans %s\n", nomFichier);
}

ListeClient* chargerClients(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier %s non trouve. Demarrage avec liste vide.\n", nomFichier);
        return NULL;
    }
    
    ListeClient* liste = NULL;
    char ligne[1000];
    
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        client c;
        c.commandes = NULL;
        
        char* token = strtok(ligne, ";");
        if (token == NULL) continue;
        c.matricule = atoi(token);
        
        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strcpy(c.nom, token);
        
        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int nbCommandes = atoi(token);
        
        // Les IDs des commandes seront chargés plus tard si nécessaire
        // Pour l'instant on les ignore
        
        ListeClient* nouveau = (ListeClient*)malloc(sizeof(ListeClient));
        if (nouveau != NULL) {
            nouveau->data = c;
            nouveau->next = liste;
            liste = nouveau;
            
            if (c.matricule > compteurMatricule) {
                compteurMatricule = c.matricule;
            }
        }
    }
    
    fclose(fichier);
    printf("Clients charges depuis %s\n", nomFichier);
    return liste;
}
