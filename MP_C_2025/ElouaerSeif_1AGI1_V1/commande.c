#include "headers.h"

/****************Fonctions Développées**************************/

static int idCommandeAuto = 1;
void ajouterCommande(commande c[], int *n){
    commande cm;
    cm.id = idCommandeAuto++;
    printf("Matricule client : ");
    scanf("%d", &cm.matriculeClient);
    printf("ID Pokemon : ");
    scanf("%d", &cm.idPokemon);
    printf("Quantité : ");
    scanf("%d", &cm.quantite);
    cm.date = time(NULL);
    cm.etat='en attente';
    c[*n] = cm;
    (*n)++;
}

void afficherCommandes(commande c[], int n){
    if (n == 0) {
        printf("Aucune commande.\n");
    }

    for (int i = 0; i < n; i++) {
        printf("ID:%d | Client:%d | Pokemon:%d | Qte:%d | Etat:%d\n",
               c[i].id, c[i].matriculeClient,
               c[i].idPokemon, c[i].quantite, c[i].etat);
    }
}

void modifierCommande(commande c[], int n){
    int id;
    printf("ID commande : ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (c[i].id == id) {
            printf("Nouvelle quantité : ");
            scanf("%d", &c[i].quantite);

            printf("Nouvel etat: ");
            scanf("%s", c[i].etat);
            return;
        }
    }
    printf("Commande introuvable.\n");
}
void supprimerCommande(commande c[], int *n){
    int id,i;
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
