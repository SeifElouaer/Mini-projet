#include "headers.h"

/****************Fonctions Développées**************************/

static int idCommandeAuto = 1;
void ajouterCommande(commande c[], int *n){
    commande c;
    c.id = idCommandeAuto++;
    printf("Matricule client : ");
    scanf("%d", &c.matriculeClient);
    printf("ID Pokemon : ");
    scanf("%d", &c.idPokemon);
    printf("Quantité : ");
    scanf("%d", &c.quantité);
    c.date = time(NULL);
    c.etat = 0;
    tab[*n] = c;
    (*n)++;
}

void afficherCommandes(commande c[], int n){
    if (n == 0) {
        printf("Aucune commande.\n");
    }

    for (int i = 0; i < n; i++) {
        printf("ID:%d | Client:%d | Pokemon:%d | Qte:%d | Etat:%d\n",
               c[i].id, c[i].matriculeClient,
               c[i].idPokemon, c[i].quantité, c[i].etat);
    }
}

void modifierCommande(commande c[], int n){
    int id;
    printf("ID commande : ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (tab[i].id == id) {
            printf("Nouvelle quantité : ");
            scanf("%d", &c[i].quantité);

            printf("Nouvel etat: ");
            scanf("%s", c[i].etat);
            return;
        }
    }
    printf("Commande introuvable.\n");
}
void supprimerCommande(commande c[], int *n){
    int id, int i;
    printf("ID commande : ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if (c[i].id == id) {
            c[i] = c[*n - 1];
            (*n)--;
        }
    }
    printf("Commande introuvable.\n");
}
