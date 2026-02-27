#include "headers.h"

/****************Fonctions Développées**************************/

pokemon Tab_Pokemon[MAX_TAILLE];
machine Tab_Machine[MAX_TAILLE];
client Tab_Client[MAX_TAILLE];
commande Tab_Commande[MAX_TAILLE];

int nbPokemons = 0;
int nbMachines = 0;
int nbClients = 0;
int nbCommandes = 0;

 /* ===== MENU PRINCIPAL ===== */
void menuPrincipal() {
    int choix;

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

    } while (choix<0 || choix>6);
}

/* ===== SOUS-MENU POKEMON ===== */
void menuPokemon() {
    int choix;
    do {
        printf("\n===== GERER POKEMON =====\n");
        printf("1. Ajouter un Pokemon\n");
        printf("2. Afficher les Pokemons\n");
        printf("3. Modifier un Pokemon\n");
        printf("4. Supprimer un Pokemon\n");
        printf("5. Revenir au menu precedent\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Ajouter un Pokemon <<<\n");
                ajouterPokemon(Tab_Pokemon, &nbPokemons);
                menuPokemon();
                break;
            case 2:
                printf("\n>>> Afficher les Pokemons <<<\n");
                afficherPokemons(Tab_Pokemon, nbPokemons);
                menuPokemon();
                break;
            case 3:
                printf("\n>>> Modifier un Pokemon <<<\n");
                modifierPokemon(Tab_Pokemon, nbPokemons);
                menuPokemon();
                break;
            case 4:
                printf("\n>>> Supprimer un Pokemon <<<\n");
                supprimerPokemon(Tab_Pokemon, &nbPokemons);
                menuPokemon();
                break;
            case 5:
                printf("\n>>> Revenir au menu precedent <<<\n");
                menuPrincipal();
                break;
            default:
                printf("Choix invalide !\n");
        }
    } while (choix <1 || choix >5);
}

/* ===== SOUS MENU MACHINE ===== */
void menuMachine() {
    int choix;
    do {
        printf("\n===== GERER MACHINE =====\n");
        printf("1. Ajouter un machine\n");
        printf("2. Afficher les machines\n");
        printf("3. Modifier un machine\n");
        printf("4. Supprimer un machine\n");
        printf("5. Revenir au menu precedent\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Ajouter une Machine <<<\n");
                ajouterMachine(Tab_Machine,Tab_Pokemon , nbPokemons, &nbMachines);
                menuMachine();
                break;
            case 2:
                printf("\n>>> Afficher une Machine <<<\n");
                afficherMachines(Tab_Machine, Tab_Commande, nbMachines);
                menuMachine();
                break;
            case 3:
                printf("\n>>> Modifier une Machine <<<\n");
                modifierMachine(Tab_Machine, Tab_Pokemon, Tab_Commande, nbMachines, nbPokemons, nbCommandes);
                menuMachine();
                break;
            case 4:
                printf("\n>>> Supprimer une Machine <<<\n");
                supprimerMachine(Tab_Machine, &nbMachines);
                menuMachine();
                break;
            case 5:
                printf("\n>>> Revenir au menu precedent <<<\n");
                menuPrincipal();
                break;
            default:
                printf("Choix invalide !\n");
        }
    } while (choix < 1 || choix > 5);
}
/* ===== SOUS-MENU COMMANDE ===== */
void menuCommande() {
    int choix;
    do {
        printf("\n===== GERER COMMANDE =====\n");
        printf("1. Ajouter une commande\n");
        printf("2. Afficher les commandes\n");
        printf("3. Modifier une commande\n");
        printf("4. Supprimer une commande \n");
        printf("5. Revenir au menu precedent\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Ajouter un commande <<<\n");
                ajouterCommande(Tab_Commande, Tab_Pokemon, nbPokemons, &nbCommandes);
                menuCommande();
                break;
            case 2:
                printf("\n>>> Afficher les commandes <<<\n");
                afficherCommandes(Tab_Commande ,nbCommandes);
                menuCommande();
                break;
            case 3:
                printf("\n>>> Modifier une commande <<<\n");
                modifierCommande(Tab_Commande, Tab_Pokemon, nbCommandes, nbPokemons);
                menuCommande();
                break;
            case 4:
                printf("\n>>> Supprimer une commande <<<\n");
                supprimerCommande(Tab_Commande ,&nbCommandes);
                menuCommande();
                break;
            case 5:
                printf("\n>>> Revenir au menu precedent <<<\n");
                menuPrincipal();
                break;
            default:
                printf("Choix invalide !\n");
        }

    } while ( choix < 1 || choix > 5);
}

/* ===== SOUS-MENU CLIENT ===== */
void menuClient() {
    int choix;
    do {
        printf("\n===== GERER CLIENT =====\n");
        printf("1. Ajouter un Client\n");
        printf("2. Afficher les Clients\n");
        printf("3. Modifier un Client\n");
        printf("4. Supprimer un Client\n");
        printf("5. Revenir au menu precedent\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Ajouter un client <<<\n");
                ajouterClient(Tab_Client ,&nbClients);
                menuClient();
                break;
            case 2:
                printf("\n>>> Afficher les clients <<<\n");
                afficherClients(Tab_Client, nbClients);
                menuClient();
                break;
            case 3:
                printf("\n>>> Modifier un client <<<\n");
                modifierClient(Tab_Client,Tab_Pokemon, nbClients, nbPokemons);
                menuClient();
                break;
            case 4:
                printf("\n>>> Supprimer un client <<<\n");
                supprimerClient(Tab_Client, &nbClients);
                menuClient();
                break;
            case 5:
                printf("\n>>> Revenir au menu precedent <<<\n");
                menuPrincipal();
                break;
            default:
                printf("Choix invalide !\n");
        }
    } while (choix < 0 || choix > 6);
}

/* ===== SOUS-MENU ETAT_D'USINE ===== */
void menuEtat_de_usine(){
    printf("\n======= ETAT DE L'USINE =======\n");
    printf("Caisse de l'usine  : %d pieces\n",caisse);
    printf("--------------------------------\n");
    printf("Nombre de Pokemons : %d\n",nbPokemons);
    printf("Nombre de machines : %d\n",nbMachines);
    printf("Nombre de clients  : %d\n",nbClients);
    printf("Nombre de commandes: %d\n",nbCommandes);
    printf("================================\n\n");
    menuPrincipal();
}

