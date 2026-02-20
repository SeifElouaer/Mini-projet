#include "headers.h"


/****************Fonctions Développées**************************/

    static int matriculeAuto = 1;

int genererMat(){
    return matriculeAuto++;
}

client creerClient(){
    client c;
    c.matricule = genererMat();
    printf("Nom du client : ");
    scanf("%s", c.nom);
    c.commandes = NULL;
    return c;
}

void ajouterClient(ListeClient** liste) {
    ListeClient* nouveau = (ListeClient*)malloc(sizeof(ListeClient));
    if (nouveau == NULL) {
        printf("ERREUR\n");
        return;
    }

    nouveau->cl = creerClient();
    nouveau->suivant = *liste;
    *liste = nouveau;
    printf("Client ajoute avec succes\n");
}

void afficherClient(client c) {
    printf(" - Matricule: %d | Nom: %s\n", c.matricule, c.nom);

    int nbCommandes = compterCommandes(c.commandes);
    printf("  Nombre de commandes: %d\n", nbCommandes);

    if (c.commandes != NULL) {
        printf("  Commandes du client:\n");
        ListeCommande* courant = c.commandes;
        while (courant != NULL) {
            printf("     - ID= %d, Pokemon= %d, Quantite= %d\n",
                   courant->cm.id, courant->cm.idPokemon, courant->cm.quantite);
            courant = courant->suivant;
        }
    }
    else{
        printf("Aucune commande commandee\n");
    }
}

void afficherClients(ListeClient* liste) {
    if (liste == NULL) {
        printf("Aucun client\n");
        return;
    }

    ListeClient* courant = liste;
    int i = 1;
    while (courant != NULL) {
        printf("# Client %d :\n", i++);
        afficherClient(courant->cl);
        courant = courant->suivant;
    }
}

ListeClient* rechercherClient(ListeClient* liste, int matricule) {
    ListeClient* courant = liste;
    while (courant != NULL) {
        if (courant->cl.matricule == matricule) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

void modifierClient(ListeClient* liste, ListePokemon* listePokemons) {
    if (liste == NULL) {
        printf("Aucun client\n");
        return;
    }

    int mat, choix, op;
    printf("Matricule du client a modifier: ");
    scanf("%d", &mat);

    ListeClient* noeud = rechercherClient(liste, mat);
    if (noeud == NULL) {
        printf("Client introuvable\n");
        return;
    }

    do {
        printf("\n=============================\n");
        printf("===== Modifier Client %d =====\n", noeud->cl.matricule);
        printf("=============================\n");
        printf("1) Nom\n");
        printf("2) Liste de commandes\n");
        printf("0) Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nouveau nom: ");
                scanf("%s", noeud->cl.nom);
                break;
            case 2:
                printf("\n======================================\n");
                printf("=== Gestion des commandes du client ===\n");
                printf("======================================\n");
                printf("1) Ajouter commande\n");
                printf("2) Modifier commande\n");
                printf("3) Supprimer commande\n");
                printf("0) Retour\n");
                printf("Choix: ");
                scanf("%d", &op);

                switch (op) {
                    case 1:
                        ajouterCommande(&(noeud->cl.commandes), listePokemons, listeClients);
                        break;
                    case 2:
                        modifierCommande(noeud->cl.commandes, listePokemons);
                        break;
                    case 3:
                        supprimerCommande(&(noeud->cl.commandes));
                        break;
                    case 0:
                        printf("Retour\n");
                        break;
                    default:
                        printf("Choix invalide\n");
                }
                break;
            case 0:
                printf("Retour au menu precedent.\n");
                break;
            default:
                printf("Choix invalide\n");
        }
    } while (choix != 0);

    printf("Modification reussie\n");
}

void supprimerClient(ListeClient** liste) {
    if (*liste == NULL) {
        printf("Aucun client a supprimer\n");
        return;
    }

    int mat;
    printf("Matricule du client a supprimer: ");
    scanf("%d", &mat);

    ListeClient* courant = *liste;
    ListeClient* precedent = NULL;

    while (courant != NULL && courant->cl.matricule != mat) {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Client introuvable\n");
        return;
    }

    // Libérer les commandes du client
    libererListeCommande(&(courant->cl.commandes));

    if (precedent == NULL) {
        *liste = courant->suivant;
    } else {
        precedent->suivant = courant->suivant;
    }

    free(courant);
    printf("Client supprime avec succes\n");
}

void libererListeClient(ListeClient** liste) {
    ListeClient* courant = *liste;
    while (courant != NULL) {
        ListeClient* temp = courant;
        courant = courant->suivant;
        libererListeCommande(&(temp->cl.commandes));
        free(temp);
    }
    *liste = NULL;
}

int compterClients(ListeClient* liste) {
    int count = 0;
    ListeClient* courant = liste;
    while (courant != NULL) {
        count++;
        courant = courant->suivant;
    }
    return count;
}




void sauvegarderClients(ListeClient* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListeClient* courant = liste;
    while (courant != NULL) {
        // Sauvegarder les infos du client
        fprintf(fichier, "%d;%s;", courant->cl.matricule, courant->cl.nom);

        // Compter et sauvegarder le nombre de commandes
        int nbCommandes = compterCommandes(courant->cl.commandes);
        fprintf(fichier, "%d", nbCommandes);

        // Sauvegarder les IDs des commandes
        ListeCommande* cmd = courant->cl.commandes;
        while (cmd != NULL) {
            fprintf(fichier, ";%d", cmd->cm.id);
            cmd = cmd->suivant;
        }
        fprintf(fichier, "\n");

        courant = courant->suivant;
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

        char* token = strtok(ligne, ";");  //extraire un à un les elts
        if (token == NULL) continue;
        c.matricule = atoi(token);  //atoi : convert str to int

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strcpy(c.nom, token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int nbCommandes = atoi(token);

        // Les IDs des commandes seront chargés plus tard si nécessaire

        ListeClient* nouveau = (ListeClient*)malloc(sizeof(ListeClient));
        if (nouveau != NULL) {
            nouveau->cl = c;
            nouveau->suivant = liste;
            liste = nouveau;

            if (c.matricule > matriculeAuto) {
                matriculeAuto = c.matricule;
            }
        }
    }

    fclose(fichier);
    printf("Clients charges depuis %s\n", nomFichier);
    return liste;
}
