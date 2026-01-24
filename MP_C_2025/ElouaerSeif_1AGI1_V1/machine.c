#include "headers.h"

/****************Fonctions Développées**************************/

static int idAuto = 1;
void ajouterMachine(machine m[], int *n){
    machine mc;
    mc.id = idAuto++;
    printf("Nom machine : ");
    scanf("%s", mc.nom);
    printf("ID Pokemon produit : ");
    scanf("%d", &mc.idPokemon);
    printf("Temps production (en min) : ");
    scanf("%d", &mc.tempsProd);
    printf("Max production avant maintenance : ");
    scanf("%d", &mc.nbMax);
    printf("Cout maintenance : ");
    scanf("%f", &mc.coutMaint);
    mc.compteur = 0;
    mc.etat ='libre';
    m[*n] = mc;
    (*n)++;
    printf("Machine ajoutée\n");
}

void afficherMachines(machine m[], int n){
    int i;
    for (int i = 0; i < n; i++) {
        printf("ID:%d | nom:%s | Pokemon:%d | temps:%d | Max prod:%f | Cout maintenance:%f | Etat:%d\n",
               m[i].id, m[i].nom, m[i].idPokemon,
                m[i].tempsProd,m[i].nbMax,
                m[i].coutMaint, m[i].etat);
    }
}

void modifierMachine(machine m[], int n){
    int id;
    printf("ID machine : ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (m[i].id == id) {
            printf("Nouveau cout maintenance : ");
            scanf("%f", &m[i].coutMaint);
            printf("Machine modifiée\n");
        }
    }
    printf("Machine introuvable\n");
}
void supprimerMachine(machine m[], int *n){
    int id, i;
    printf("ID machine : ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if (m[i].id == id) {
            m[i] = m[*n - 1];
            (*n)--;
            printf("Machine supprimée\n");
        }
    }
    printf("Machine introuvable\n");
}
