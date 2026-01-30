#include "headers.h"

/****************Fonctions Développées**************************/

int genererIdCommande(){
    static int idAuto = 1;
    return idAuto++;
}

commande creerCommande(pokemon p[], int nbPokemons){
    commande c;
    c.id = genererIdCommande();
    printf("ID du client : ");
    scanf("%d",&c.matriculeClient);
    do{
        printf("ID de pokemon : ");
        scanf("%d",&c.idPokemon);
    }while (rechercherPokemon(p, nbPokemons, c.idPokemon) == -1);
    printf("Quantite : ");
    scanf("%d", &c.quantite);
    time_t t;
    time(&t); // obtient le timestamp actuel
    printf("date et heure d’emission de la commande: %s", ctime(&t));
    strcpy(c.dateHeure, ctime(&t));
    c.etat = 0; //en attente
    return c;
}

void ajouterCommande(commande c[], pokemon p[], int nbPokemons, int *n){
    if (*n >= MAX_TAILLE) {
        printf("ERREUR : tableau de commandes est plein.\n");
    }
    else{
        c[*n] = creerCommande(p, nbPokemons);
        (*n)++;
        printf("Commande ajoutee avec succes.\n");
    }
}

void afficherCommande(commande c){
    printf("- ID Commande: %d", c.id);
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
    }
}

void afficherCommandes(commande c[], int n){
    if (n == 0) {
        printf("Aucune commande.\n");
    }
    for (int i = 0; i < n; i++) {
        printf("#### Commande %d ####\n",i+1);
        afficherCommande(c[i]);
    }
}

int chercherCommande(commande c[], int n, int id){
    for (int i = 0; i < n; i++) {
        if (c[i].id == id) {
            return i;
        }
    }
    return -1;
}

void modifierCommande(commande c[], pokemon p[], int n, int nbPokemons){
    int id, choix;
    if (n == 0){
        printf("Tableau de commandes est vide\n");
    }
    else{
        printf("ID de commande a modifier : ");
        scanf("%d", &id);
        int x = chercherCommande(c, n, id);
        if (x == -1){
            printf("Commande introuvable\n");
        }
        else{
            do {
                printf(" Modifier Commande %d \n",id);
                printf("1. ID du pokemon commande\n");
                printf("2. quantite\n");
                printf("3. Etat de la commande\n");
                printf("0. Retour au menu\n");
                printf("Choix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        do{
                            printf("Nouveau ID  du Pokemon commande : ");
                            scanf("%d", &c[x].idPokemon);
                        }while(rechercherPokemon(p, nbPokemons,c[x].idPokemon)==-1);
                        break;
                    case 2:
                        printf("Nouvelle quantite: ");
                        scanf("%d", &c[x].quantite);
                        break;
                    case 3:
                        printf(" Nouvelle etat de commande :"); // 0=En attente, 1=En cours, 2=Realisee
                        scanf("%d", &c[x].etat);
                        break;
                    case 0:
                        printf("Retour au menu precedent.\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                }

            } while (choix < 0 || choix > 3);
        }
    }
}

void supprimerCommande(commande c[], int *n){
    int id, i, x;
    if (*n == 0) {
        printf("Aucune commande a supprimer.\n");
    }
    else{
        printf("ID de commande a supprimer : ");
        scanf("%d", &id);
        x = chercherCommande(c, *n, id);
        if (x == -1){
            printf(" Commande introuvable\n");
        }
        else{
            for (int i = x; i < (*n)-1 ; i++) {
                c[i] = c[i+1];
            }
            (*n)--;
            printf("Commande supprimee avec succes\n");
        }
    }
}
