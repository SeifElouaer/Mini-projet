#include "headers.h"

/****************Fonctions Développées**************************/

static int matriculeAuto = 1;
void ajouterClient(client c[], int *n){
    client cl;
    cl.matricule = matriculeAuto++;
    printf("Nom client : ");
    scanf("%s", cl.nom);
    c[*n] = cl;
    (*n)++;
    printf("Client ajouté\n");
}

void afficherClients(client c[], int n){
    int i;
    for (int i = 0; i < n; i++) {
        printf("Mat:%d | %s\n", c[i].matricule, c[i].nom);
    }
}

void modifierClient(client c[], int n){
    int mat;
    printf("Matricule : ");
    scanf("%d", &mat);

    for (int i = 0; i < n; i++) {
        if (c[i].matricule == mat) {
            printf("Nouveau nom : ");
            scanf("%s", c[i].nom);
        }
    }
    printf("Client introuvable.\n");

}
void supprimerClient(client c[], int *n){
    int mat;
    printf("Matricule : ");
    scanf("%d", &mat);
    for (int i = 0; i < *n; i++) {
        if (c[i].matricule == mat) {
            c[i] = c[*n - 1];
            (*n)--;
        }
    }
    printf("Client introuvable.\n");
}
