#include "headers.h"

static int compteurIdPokemon = 0;

int genererIdP() {
    return ++compteurIdPokemon;
}

pokemon creerPokemon() {
    pokemon p;
    p.id = genererIdP();
    printf("Nom du pokemon: ");
    scanf("%s", p.nom);
    printf("Cout unitaire: ");
    scanf("%f", &p.prix);
    printf("Type: ");
    scanf("%s", p.type);
    return p;
}

void ajouterPokemon(ListePokemon** liste) {
    ListePokemon* nouveau = (ListePokemon*)malloc(sizeof(ListePokemon));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }

    nouveau->data = creerPokemon();
    nouveau->next = *liste;
    *liste = nouveau;
    printf("Pokemon ajoute avec succes.\n");
}

void afficherPokemon(pokemon p) {
    printf("- ID: %d | Nom: %s | Cout: %.2f | Type: %s\n",
           p.id, p.nom, p.prix, p.type);
}

void afficherPokemons(ListePokemon* liste) {
    if (liste == NULL) {
        printf("Aucun Pokemon trouve.\n");
        return;
    }

    ListePokemon* current = liste;
    int count = 1;
    while (current != NULL) {
        printf("#### Pokemon %d ####\n", count++);
        afficherPokemon(current->data);
        current = current->next;
    }
}

ListePokemon* rechercherPokemon(ListePokemon* liste, int id) {
    ListePokemon* current = liste;
    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifierPokemon(ListePokemon* liste) {
    if (liste == NULL) {
        printf("Aucun Pokemon trouve.\n");
        return;
    }

    int id, choix;
    printf("ID du pokemon a modifier: ");
    scanf("%d", &id);

    ListePokemon* node = rechercherPokemon(liste, id);
    if (node == NULL) {
        printf("Pokemon introuvable.\n");
        return;
    }

    do {
        printf("\n===== Modifier Pokemon %d =====\n", node->data.id);
        printf("1. Nom du pokemon\n");
        printf("2. Cout du pokemon\n");
        printf("3. Type du pokemon\n");
        printf("0. Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nouveau nom: ");
                scanf("%s", node->data.nom);
                break;
            case 2:
                printf("Nouveau cout: ");
                scanf("%f", &node->data.prix);
                break;
            case 3:
                printf("Nouveau type: ");
                scanf("%s", node->data.type);
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

void supprimerPokemon(ListePokemon** liste) {
    if (*liste == NULL) {
        printf("Aucun Pokemon a supprimer.\n");
        return;
    }

    int id;
    printf("ID du pokemon a supprimer: ");
    scanf("%d", &id);

    ListePokemon* current = *liste;
    ListePokemon* prev = NULL;

    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Pokemon introuvable.\n");
        return;
    }

    if (prev == NULL) {
        *liste = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Pokemon supprime avec succes.\n");
}

void libererListePokemon(ListePokemon** liste) {
    ListePokemon* current = *liste;
    while (current != NULL) {
        ListePokemon* temp = current;
        current = current->next;
        free(temp);
    }
    *liste = NULL;
}

int compterPokemons(ListePokemon* liste) {
    int count = 0;
    ListePokemon* current = liste;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


// Fonctions de gestion des fichiers
void sauvegarderPokemons(ListePokemon* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListePokemon* current = liste;
    while (current != NULL) {
        fprintf(fichier, "%d;%s;%.2f;%s\n",
                current->data.id,
                current->data.nom,
                current->data.prix,
                current->data.type);
        current = current->next;
    }

    fclose(fichier);
    printf("Pokemons sauvegardes dans %s\n", nomFichier);
}

ListePokemon* chargerPokemons(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier %s non trouve. Demarrage avec liste vide.\n", nomFichier);
        return NULL;
    }

    ListePokemon* liste = NULL;
    pokemon p;

    while (fscanf(fichier, "%d;%[^;];%f;%[^\n]\n",
                  &p.id, p.nom, &p.prix, p.type) == 4) {
        ListePokemon* nouveau = (ListePokemon*)malloc(sizeof(ListePokemon));
        if (nouveau != NULL) {
            nouveau->data = p;
            nouveau->next = liste;
            liste = nouveau;

            // Mettre à jour le compteur d'ID
            if (p.id > compteurIdPokemon) {
                compteurIdPokemon = p.id;
            }
        }
    }

    fclose(fichier);
    printf("Pokemons charges depuis %s\n", nomFichier);
    return liste;
}
