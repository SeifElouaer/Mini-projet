#include "headers.h"

/****************Fonctions Développées**************************/

int genererIdP(){
    static int idAuto = 1;
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

void ajouterPokemon(pokemon p[], int *n){
    if (*n >= MAX_TAILLE) {
        printf("Le tableau est plein.\n");
    }
    else{
        p[*n] = creerPokemon();
        (*n)++;
        printf("Pokemon ajoute avec succes\n");
    }
}

void afficherpokemon(pokemon p){
    printf("- ID: %d", p.id);
    printf(" | Nom: %s", p.nom);
    printf(" | Cout unitaire: %.2f", p.prix);
    printf(" | Type: %s \n", p.type);
}

void afficherPokemons(pokemon p[], int n){
    if (n == 0) {
        printf("Aucun Pokemon trouve\n");
    }
    else{
        for (int i = 0; i < n; i++) {
           afficherpokemon(p[i]);
        }
    }
}

int rechercherPokemon(pokemon p[], int n, int id) {
    int i;
    for ( i = 0; i < n; i++) {
        if (p[i].id == id)
            return i;
    }
    return -1;
}

void modifierPokemon(pokemon p[], int n){
    int id, choix, index;
    if (n == 0) {
        printf("Aucun Pokemon trouve\n");
    }
    else{
        printf("ID du pokemon a modifier : ");
        scanf("%d", &id);
        index = rechercherPokemon(p, n, id);
        if (index == -1){
            printf("Pokemon introuvable\n");
        }
        else{
            do{
                printf(" Modifier Pokemon %d \n",p[index].id);
                printf("1. Nom du pokemon\n");
                printf("2. Cout du pokemon\n");
                printf("3. Type du pokemon \n");
                printf("0. Retour au menu\n");
                printf("Choix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        printf("Nouveau nom : ");
                        scanf(" %s", p[index].nom);
                        break;
                    case 2:
                        printf("Nouveau cout : ");
                        scanf("%f", &p[index].prix);
                        break;
                    case 3:
                        printf("Nouveau type : ");
                        scanf("%s", p[index].type);
                        break;
                    case 0:
                        printf("Retour au menu precedent.\n");
                        break;
                    default:
                        printf("Choix invalide\n");
                }
            } while (choix < 0 || choix > 3);
        printf("Modification reussie\n");
        }
    }
}

void supprimerPokemon(pokemon p[], int *n){
    int id, index, i;
    if (*n == 0) {
        printf("Aucun pokemon a supprimer.\n");
    }
    else{
    printf("ID du pokemon a supprimer: ");
    scanf("%d", &id);
    index = rechercherPokemon(p,*n,id);
    if (index == -1) {
        printf("Pokemon %d est introuvable.\n",id);
    }
    else{
        for (i = index; i<(*n)-1; i++){
            p[i] = p[i+1];
        }
        (*n)--;
        printf("Pokemon supprime avec succes.\n");
    }
}
}
