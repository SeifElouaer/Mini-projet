#include "headers.h"

/****************Fonctions Développées**************************/

static int idAuto = 1;

int genererIdP(){
    return idAuto++;
}

pokemon creerPokemon(){
    pokemon p;
    p.id = genererIdP();
    printf("Nom du pokemon: ");
    scanf("%s",p.nom);
    printf("Cout unitaire: ");
    scanf("%f",&p.prix);
    printf("Type : ");
    scanf("%s", p.type);
    return p;
}

void ajouterPokemon(ListePokemon** liste){
    ListePokemon* nouveau = (ListePokemon*) malloc(sizeof(ListePokemon));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation de memoire est echouee.\n");
        return;
    }

    nouveau->p = creerPokemon();
    nouveau->suivant = *liste;
    *liste = nouveau;
    printf("Pokemon ajoute avec succes.\n");
}

void afficherpokemon(pokemon p){
    printf("- ID: %d", p.id);
    printf(" | Nom: %s", p.nom);
    printf(" | Cout unitaire: %.2f", p.prix);
    printf(" | Type: %s \n", p.type);
}

void afficherPokemons(ListePokemon* liste){
    if (liste == NULL) {
        printf("Aucun Pokemon trouve.\n");
        return;
    }

    ListePokemon* courant = liste;
    while (courant != NULL) {
        afficherpokemon(courant->p);
        courant = courant->suivant;
    }
}

ListePokemon* rechercherPokemon(ListePokemon* liste, int id) {
    ListePokemon* courant = liste;
    while (courant != NULL) {
        if (courant->p.id == id) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

void modifierPokemon(ListePokemon* liste) {
    int id, choix;
    if (liste == NULL) {
        printf("Aucun Pokemon trouve.\n");
        return;
    }

    printf("ID du pokemon a modifier: ");
    scanf("%d", &id);

    ListePokemon* noeud = rechercherPokemon(liste, id);
    if (noeud == NULL) {
        printf("Pokemon introuvable.\n");
        return;
    }

    do {
        printf("===============================\n");
        printf("===== Modifier Pokemon %d =====\n", noeud->p.id);
        printf("===============================\n");
        printf("1) Nom du pokemon\n");
        printf("2) Cout du pokemon\n");
        printf("3) Type du pokemon\n");
        printf("0) Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nouveau nom: ");
                scanf("%s", noeud->p.nom);
                break;
            case 2:
                printf("Nouveau cout: ");
                scanf("%f", &noeud->p.prix);
                break;
            case 3:
                printf("Nouveau type: ");
                scanf("%s", noeud->p.type);
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

    ListePokemon* courant = *liste;
    ListePokemon* pre = NULL;

    while (courant != NULL && courant->p.id != id) {
        pre = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Pokemon introuvable.\n");
        return;
    }

    if (pre == NULL) { // pos 1
        *liste = courant->suivant;
    }
    else {
        pre->suivant = courant->suivant;
    }

    free(courant);
    printf("Pokemon supprime avec succes.\n");
}

void libererListePokemon(ListePokemon** liste) {
    ListePokemon* courant = *liste;
    while (courant != NULL) {
        ListePokemon* temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    *liste = NULL;
}

int compterPokemons(ListePokemon* liste) {
    int nb = 0;
    ListePokemon* courant = liste;
    while (courant != NULL) {
        nb++;
        courant = courant->suivant;
    }
    return nb;
}



void sauvegarderPokemons(ListePokemon* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListePokemon* courant = liste;
    while (courant != NULL) {
        fprintf(fichier, "%d;%s;%.2f;%s\n",
                courant->p.id,
                courant->p.nom,
                courant->p.prix,
                courant->p.type);
        courant = courant->suivant;
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
            nouveau->p = p;
            nouveau->suivant = liste;
            liste = nouveau;

            // Mettre à jour le compteur d'ID
            if (p.id > idAuto) {
                idAuto = p.id;
            }
        }
    }

    fclose(fichier);
    printf("Pokemons charges depuis %s\n", nomFichier);
    return liste;
}
