#include "headers.h"

/****************Fonctions Développées**************************/

static int idAuto = 1;

int genererIdCommande(){
    return idAuto++;
}

commande creerCommande(ListePokemon* listePokemons, ListeClient* listeClients){
    commande c;
    c.id = genererIdCommande();
    do{
        printf("ID du client: ");
    scanf("%d", &c.matriculeClient);
    }while (rechercherClient(listeClients, c.matriculeClient) == NULL);


    do {
        printf("ID du pokemon: ");
        scanf("%d", &c.idPokemon);
        if (rechercherPokemon(listePokemons, c.idPokemon) == NULL) {
            printf("Pokemon inexistant - reessayer\n");
        }
    } while (rechercherPokemon(listePokemons, c.idPokemon) == NULL);

    printf("Quantite: ");
    scanf("%d", &c.quantite);

    c.quantiteProduite = 0;
    time_t t;
    time(&t); // obtient le timestamp actuel
    strcpy(c.dateHeure, ctime(&t));
    c.dateHeure[strlen(c.dateHeure) - 1] = '\0';
    printf("date et heure d’emission de la commande: %s", c.dateHeure);
    c.etat = 0; //en attente
    return c;
}

void ajouterCommande(ListeCommande** liste, ListePokemon* listePokemons,ListeClient* listeClients) {
    ListeCommande* nouveau = (ListeCommande*)malloc(sizeof(ListeCommande));
    if (nouveau == NULL) {
        printf("ERREUR\n");
        return;
    }

    nouveau->cm = creerCommande(listePokemons, listeClients);
    nouveau->suivant = *liste;
    *liste = nouveau;
    printf("Commande ajoutee avec succes.\n");
}

void afficherCommande(commande c){
    printf(" ID Commande: %d", c.id);
    printf(" | ID Client: %d", c.matriculeClient);
    printf(" | ID Pokemon: %d", c.idPokemon);
    printf(" | Quantite: %d", c.quantite);
    printf(" | Date/Heure: %s", c.dateHeure);
    printf(" | Etat: ");
    switch (c.etat) {
        case 0:
            printf("En attente\n");
            break;
        case 1:
            printf("En cours\n");
            break;
        case 2:
            printf("Realisee\n");
            break;
        default:
            printf("Inconnu\n");
    }
}

void afficherCommandes(ListeCommande* liste) {
    if (liste == NULL) {
        printf("Aucune commande\n");
        return;
    }

    ListeCommande* courant = liste;
    int i = 1;
    while (courant != NULL) {
        printf("# Commande %d :", i++);
        afficherCommande(courant->cm);
        courant = courant->suivant;
    }
}

ListeCommande* rechercherCommande(ListeCommande* liste, int id) {
    ListeCommande* courant = liste;
    while (courant != NULL) {
        if (courant->cm.id == id) {
            return courant;
        }
        courant = courant->suivant;
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

    ListeCommande* noeud = rechercherCommande(liste, id);
    if (noeud == NULL) {
        printf("Commande introuvable\n");
        return;
    }

    do {
        printf("\n==============================\n");
        printf("===== Modifier Commande %d =====\n", noeud->cm.id);
        printf("\n==============================\n");
        printf("1) ID du pokemon commande\n");
        printf("2) Quantite\n");
        printf("3) Etat de la commande\n");
        printf("0) Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                do {
                    printf("Nouveau ID du Pokemon: ");
                    scanf("%d", &noeud->cm.idPokemon);
                    if (rechercherPokemon(listePokemons, noeud->cm.idPokemon) == NULL) {
                        printf("Pokemon inexistant - Reessayez\n");
                    }
                } while (rechercherPokemon(listePokemons, noeud->cm.idPokemon) == NULL);
                break;
            case 2:
                printf("Nouvelle quantite: ");
                scanf("%d", &noeud->cm.quantite);
                break;
            case 3:
                printf("Nouvel etat (0=En attente, 1=En cours, 2=Realisee): ");
                scanf("%d", &noeud->cm.etat);
                break;
            case 0:
                printf("Retour au menu precedent.\n");
                break;
            default:
                printf("Choix invalide\n");
        }
    } while (choix != 0);

    printf("Modification reussie.\n");
}

void supprimerCommande(ListeCommande** liste) {
    if (*liste == NULL) {
        printf("Aucune commande a supprimer\n");
        return;
    }

    int id;
    printf("ID de la commande a supprimer: ");
    scanf("%d", &id);

    ListeCommande* courant = *liste;
    ListeCommande* precedent = NULL;

    while (courant != NULL && courant->cm.id != id) {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Commande introuvable\n");
        return;
    }

    if (precedent == NULL) {
        *liste = courant->suivant;
    } else {
        precedent->suivant = courant->suivant;
    }

    free(courant);
    printf("Commande supprimee avec succes\n");
}

void libererListeCommande(ListeCommande** liste) {
    ListeCommande* courant = *liste;
    while (courant != NULL) {
        ListeCommande* temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    *liste = NULL;
}

int compterCommandes(ListeCommande* liste) {
    int count = 0;
    ListeCommande* courant = liste;
    while (courant != NULL) {
        count++;
        courant = courant->suivant;
    }
    return count;
}




void sauvegarderCommandes(ListeCommande* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListeCommande* courant = liste;
    while (courant != NULL) {
        fprintf(fichier, "%d;%d;%d;%d;%d;%s;%d\n",
                courant->cm.id,
                courant->cm.matriculeClient,
                courant->cm.idPokemon,
                courant->cm.quantite,
                courant->cm.quantiteProduite,
                courant->cm.dateHeure,
                courant->cm.etat);
        courant = courant->suivant;
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
            nouveau->cm = c;
            nouveau->suivant = liste;
            liste = nouveau;

            if (c.id > idAuto) {
                idAuto = c.id;
            }
        }
    }

    fclose(fichier);
    printf("Commandes chargees depuis %s\n", nomFichier);
    return liste;
}

