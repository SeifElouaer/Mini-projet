#include "headers.h"

/****************Fonctions Développées**************************/


void afficherPokemons(pokemon tab[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("ID: %d | %s | %.2f | %s \n",
               tab[i].id, tab[i].nom, tab[i].prix, tab[i].type);
    }
}

static int idAuto = 1;
void ajouterPokemon(pokemon tab[], int *n){
    pokemon p;
    p.id = idAuto++;
    printf("Nom du pokemon: ");
    scanf("%s",p.nom);
    printf("Prix unitaire: ");
    scanf("%f",&p.prix);
    printf("Type : ");
    scanf("%s", p.type);
    tab[*n] = p;
    (*n)++;
    printf("Pokemon ajoute avec succès\n");
}

void modifierPokemon(pokemon tab[], int n){
    int id;
    printf("ID du pokemon a modifier : ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) {
        if (tab[i].id == id) {
            printf("Nouveau prix : ");
            scanf("%f", &tab[i].prix);
            printf("Nouveau type : ");
            scanf("%s", tab[i].type);
            printf("Modification reussie\n");
        }
    }
    printf("Pokemon introuvable\n");
}

void supprimerPokemon(pokemon tab[], int *n){
    int id;
    printf("ID du pokemon à supprimer: ");
    scanf("%d", &id);
    for (int i = 0; i < *n; i++) {
        if (tab[i].id == id) {
            tab[i] = tab[*n - 1];
            (*n)--;
            printf("Suppression terminée\n");
        }
    }
    printf("Pokemon introuvable\n");
}
