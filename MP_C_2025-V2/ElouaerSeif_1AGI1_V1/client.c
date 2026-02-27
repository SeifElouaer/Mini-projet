#include "headers.h"
#include "pokemon.h"

/****************Fonctions Développées**************************/


int genererMat(){
    static int matriculeAuto = 1;
    return matriculeAuto++;
}

client creerClient(){
    client c;
    c.matricule = genererMat();
    printf("Nom du client : ");
    scanf("%s", c.nom);
    c.nbrCommande = 0;
    return c;
}

void ajouterClient(client c[], int *n){
    if (*n >= MAX_TAILLE){
        printf("ERREUR : Le tableau des clients est plein.\n");
    }
    else{
        c[*n] = creerClient();
        (*n)++;
        printf("Client ajoute avec succes \n");
    }
}

void afficherClient(client c){
    int i;
    printf("- Matricule: %d | Nom: %s | Nb de commandes : %d\n", c.matricule, c.nom, c.nbrCommande);
    if (c.nbrCommande == 0){
        printf("Aucune commande commandee\n");
    }
    else{
        for(i=0;i<c.nbrCommande;i++){
            printf("  - Commande %d : ID= %d | Quantite= %d\n", i+1, c.liste[i].id, c.liste[i].quantite);
        }
    }
}

void afficherClients(client c[], int n){
    int i;
    if (n == 0) {
        printf("Aucun client a afficher.\n");
    }
    for (int i = 0; i < n; i++) {
        afficherClient(c[i]);
    }
}

int chercherClient(client c[], int n, int id){
    int i;
    for (i = 0; i < n; i++) {
        if (c[i].matricule == id) {
            return i;
        }
    }
    return -1;
}

void modifierClient(client c[], pokemon p[], int n, int nbPokemons){
    int mat, choix, op;
    if (n == 0){
        printf("Tableau de clients est vide\n");
    }
    else{
        printf("Matricule du client a modifier : ");
        scanf("%d", &mat);
        int x = chercherClient(c, n, mat);  // x est la position du client dans le tableau des clients
        if (x == -1){
            printf("Client introuvable\n");
        }
        else{
            do {
                printf(" Modifier Client %d \n",mat);
                printf("1. Nom\n");
                printf("2. Liste de commandes\n");
                printf("0. Retour au menu\n");
                printf("Choix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        printf("Nouveau nom: ");
                        scanf("%s", c[x].nom);
                        break;
                    case 2:
                        printf("1. Ajouter commande\n");
                        printf("2. Modifier commande\n");
                        printf("3. Supprimer commande\n");
                        printf("0. Retour\n");
                        printf("Choix : ");
                        scanf("%d", &op);
                        switch(op){
                            case 1:
                                ajouterCommande(c[x].liste, p, nbPokemons, &c[x].nbrCommande);
                                menuClient();
                                break;
                            case 2:
                                modifierCommande(c[x].liste, p, c[x].nbrCommande, nbPokemons);
                                menuClient();
                                break;
                            case 3:
                                supprimerCommande(c[x].liste, &c[x].nbrCommande);
                                menuClient();
                                break;
                            case 0:
                                printf("Retour au menu\n");
                                menuClient();
                                break;
                            default:
                                printf("Choix invalide.\n");
                                break;
                        break;
                        }
                        case 0:
                            printf("Retour au menu precedent.\n");
                            break;
                        default:
                            printf("Choix invalide.\n");
                }

                } while (choix < 0 || choix >2);
            printf("Client modifie\n");
        }
    }
}

void supprimerClient(client c[], int *n){
    int mat, i, x;
    if (*n == 0) {
        printf("Aucun client a supprimer.\n");
    }
    else{
        printf("Matricule du client a supprimer : ");
        scanf("%d", &mat);
        x = chercherClient(c, *n, mat);
        if (x == -1) {
            printf("Client est introuvable\n");
        }
        else{
            for(i=x;i<(*n);i++){
                c[i]=c[i+1];
            }
            (*n)--;
        }
        printf("Client est supprime avec succes\n");
    }
}
