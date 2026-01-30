#include "headers.h"

#define caisse 1000

int main(){

    pokemon Tab_Pokemon[MAX_TAILLE];
    machine Tab_Machine[MAX_TAILLE];
    client Tab_Client[MAX_TAILLE];
    commande Tab_Commande[MAX_TAILLE];

    int nbPokemons = 0;
    int nbMachines = 0;
    int nbClients = 0;
    int nbCommandes = 0;
    int choix;

/* ===== MENU PRINCIPAL ===== */
    do {
        printf("=================================\n");
        printf("========= USINE POKEMON =========\n");
        printf("=================================\n");
        printf("| 1. Gerer les Pokemon          |\n");
        printf("| 2. Gerer les machines         |\n");
        printf("| 3. Gerer les clients          |\n");
        printf("| 4. Gerer les commandes        |\n");
        printf("| 5. Afficher l'etat de l'usine |\n");
        printf("| 6. Quitter                    |\n");
        printf("================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                menuPokemon();
                break;
            case 2:
                menuMachine();
                break;
            case 3:
                menuClient();
                break;
            case 4:
                menuCommande();
                break;
            case 5:
                menuEtat_de_usine();
                break;
            case 6:
                printf("Au revoir !\n");
                exit(0);
                break;
            default:
                printf("Choix invalide !\n");
        }

    } while (choix<1 || choix>6);
}



