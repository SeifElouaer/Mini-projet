#include "headers.h"

static int compteurIdMachine = 0;

int genererIdMachine() {
    return ++compteurIdMachine;
}

machine creerMachine(ListePokemon* listePokemons) {
    machine m;
    m.id = genererIdMachine();
    
    printf("Nom de la machine: ");
    scanf("%s", m.nom);
    
    do {
        printf("ID du Pokemon produit: ");
        scanf("%d", &m.idPokemon);
        if (rechercherPokemon(listePokemons, m.idPokemon) == NULL) {
            printf("Pokemon inexistant. Veuillez reessayer.\n");
        }
    } while (rechercherPokemon(listePokemons, m.idPokemon) == NULL);
    
    printf("Temps de production d'une figurine (en minutes): ");
    scanf("%d", &m.tempsProd);
    
    printf("Nombre maximum de figurines avant maintenance: ");
    scanf("%d", &m.nbMax);
    
    m.compteur = 0;
    
    printf("Cout de maintenance: ");
    scanf("%f", &m.coutMaint);
    
    m.etat = 0; // Libre
    m.idCommande = 0; // Aucune commande
    m.dateDisponibilite = 0; // Disponible immédiatement
    
    return m;
}

void ajouterMachine(ListeMachine** liste, ListePokemon* listePokemons) {
    ListeMachine* nouveau = (ListeMachine*)malloc(sizeof(ListeMachine));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }
    
    nouveau->data = creerMachine(listePokemons);
    nouveau->next = *liste;
    *liste = nouveau;
    printf("Machine ajoutee avec succes.\n");
}

void afficherMachine(machine m, ListeCommande* listeCommandes) {
    printf("- ID: %d | Nom: %s | Pokemon: %d\n", m.id, m.nom, m.idPokemon);
    printf("  Temps prod: %d min | Max: %d | Compteur: %d\n", 
           m.tempsProd, m.nbMax, m.compteur);
    printf("  Cout maint: %.2f | Etat: ", m.coutMaint);
    
    switch (m.etat) {
        case 0: 
            printf("Libre\n"); 
            break;
        case 1: 
            printf("Occupee");
            if (m.dateDisponibilite > 0) {
                time_t maintenant = time(NULL);
                double secondesRestantes = difftime(m.dateDisponibilite, maintenant);
                if (secondesRestantes > 0) {
                    int minutesRestantes = (int)(secondesRestantes / 60);
                    printf(" (disponible dans %d minutes)", minutesRestantes);
                } else {
                    printf(" (production terminee)");
                }
            }
            printf("\n");
            break;
        case 2: 
            printf("En attente de maintenance\n"); 
            break;
        default: 
            printf("Inconnu\n");
    }
    
    if (m.idCommande == 0) {
        printf("  Aucune commande en cours\n");
    } else {
        ListeCommande* cmd = rechercherCommande(listeCommandes, m.idCommande);
        if (cmd != NULL) {
            printf("  Commande en cours: ID=%d, Quantite=%d\n", 
                   cmd->data.id, cmd->data.quantite);
        }
    }
}

void afficherMachines(ListeMachine* liste, ListeCommande* listeCommandes) {
    if (liste == NULL) {
        printf("Aucune machine.\n");
        return;
    }
    
    ListeMachine* current = liste;
    int count = 1;
    while (current != NULL) {
        printf("#### Machine %d ####\n", count++);
        afficherMachine(current->data, listeCommandes);
        current = current->next;
    }
}

ListeMachine* rechercherMachine(ListeMachine* liste, int id) {
    ListeMachine* current = liste;
    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

ListeMachine* rechercherMachineParPokemon(ListeMachine* liste, int idPokemon) {
    ListeMachine* current = liste;
    while (current != NULL) {
        if (current->data.idPokemon == idPokemon) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifierMachine(ListeMachine* liste, ListePokemon* listePokemons, ListeCommande* listeCommandes) {
    if (liste == NULL) {
        printf("Aucune machine.\n");
        return;
    }
    
    int id, choix;
    printf("ID de la machine a modifier: ");
    scanf("%d", &id);
    
    ListeMachine* node = rechercherMachine(liste, id);
    if (node == NULL) {
        printf("Machine introuvable.\n");
        return;
    }
    
    do {
        printf("\n===== Modifier Machine %d =====\n", node->data.id);
        printf("1. Nom de la machine\n");
        printf("2. Pokemon produit\n");
        printf("3. Temps de production\n");
        printf("4. Nombre maximum de figurines\n");
        printf("5. Cout de maintenance\n");
        printf("6. Etat de la machine\n");
        printf("7. Commande en cours\n");
        printf("0. Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                printf("Nouveau nom: ");
                scanf("%s", node->data.nom);
                break;
            case 2:
                do {
                    printf("Nouveau Pokemon produit: ");
                    scanf("%d", &node->data.idPokemon);
                    if (rechercherPokemon(listePokemons, node->data.idPokemon) == NULL) {
                        printf("Pokemon inexistant. Reessayez.\n");
                    }
                } while (rechercherPokemon(listePokemons, node->data.idPokemon) == NULL);
                break;
            case 3:
                printf("Nouveau temps de production: ");
                scanf("%d", &node->data.tempsProd);
                break;
            case 4:
                printf("Nouveau nombre max: ");
                scanf("%d", &node->data.nbMax);
                break;
            case 5:
                printf("Nouveau cout de maintenance: ");
                scanf("%f", &node->data.coutMaint);
                break;
            case 6:
                printf("Nouvel etat (0=Libre, 1=Occupee, 2=Maintenance): ");
                scanf("%d", &node->data.etat);
                break;
            case 7:
                do {
                    printf("Nouvelle commande en cours (0 pour aucune): ");
                    scanf("%d", &node->data.idCommande);
                    if (node->data.idCommande != 0 && 
                        rechercherCommande(listeCommandes, node->data.idCommande) == NULL) {
                        printf("Commande inexistante. Reessayez.\n");
                    }
                } while (node->data.idCommande != 0 && 
                         rechercherCommande(listeCommandes, node->data.idCommande) == NULL);
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

void supprimerMachine(ListeMachine** liste) {
    if (*liste == NULL) {
        printf("Aucune machine a supprimer.\n");
        return;
    }
    
    int id;
    printf("ID de la machine a supprimer: ");
    scanf("%d", &id);
    
    ListeMachine* current = *liste;
    ListeMachine* prev = NULL;
    
    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Machine introuvable.\n");
        return;
    }
    
    if (prev == NULL) {
        *liste = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    printf("Machine supprimee avec succes.\n");
}

void libererListeMachine(ListeMachine** liste) {
    ListeMachine* current = *liste;
    while (current != NULL) {
        ListeMachine* temp = current;
        current = current->next;
        free(temp);
    }
    *liste = NULL;
}

int compterMachines(ListeMachine* liste) {
    int count = 0;
    ListeMachine* current = liste;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Fonctions de gestion des fichiers
void sauvegarderMachines(ListeMachine* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }
    
    ListeMachine* current = liste;
    while (current != NULL) {
        fprintf(fichier, "%d;%s;%d;%d;%d;%d;%.2f;%d;%d;%ld\n",
                current->data.id,
                current->data.nom,
                current->data.idPokemon,
                current->data.tempsProd,
                current->data.nbMax,
                current->data.compteur,
                current->data.coutMaint,
                current->data.etat,
                current->data.idCommande,
                (long)current->data.dateDisponibilite);
        current = current->next;
    }
    
    fclose(fichier);
    printf("Machines sauvegardees dans %s\n", nomFichier);
}

ListeMachine* chargerMachines(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier %s non trouve. Demarrage avec liste vide.\n", nomFichier);
        return NULL;
    }
    
    ListeMachine* liste = NULL;
    machine m;
    long dateDisp;
    
    while (fscanf(fichier, "%d;%[^;];%d;%d;%d;%d;%f;%d;%d;%ld\n",
                  &m.id, m.nom, &m.idPokemon, &m.tempsProd,
                  &m.nbMax, &m.compteur, &m.coutMaint,
                  &m.etat, &m.idCommande, &dateDisp) == 10) {
        m.dateDisponibilite = (time_t)dateDisp;
        ListeMachine* nouveau = (ListeMachine*)malloc(sizeof(ListeMachine));
        if (nouveau != NULL) {
            nouveau->data = m;
            nouveau->next = liste;
            liste = nouveau;
            
            if (m.id > compteurIdMachine) {
                compteurIdMachine = m.id;
            }
        }
    }
    
    fclose(fichier);
    printf("Machines chargees depuis %s\n", nomFichier);
    return liste;
}
