#include "headers.h"

/****************Fonctions Développées**************************/


 /* ===== MENU PRINCIPAL ===== */
void menuPrincipal() {
    int choix;

    do {
        printf("\n===== USINE POKEMON =====\n");
        printf("1. Gerer les Pokemon\n");
        printf("2. Gerer les machines\n");
        printf("3. Gerer les clients\n");
        printf("4. Gerer les commandes\n");
        printf("5. Afficher l'etat de l'usine\n");
        printf("6. Quitter\n");
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
                menucommande();
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
                printf(">> Ajouter un Pokemon\n");
                ajouterPokemon(pokemons , nbPokemons);
                menuPrincipal;
                break;
            case 2:
                printf(">> Afficher les Pokemons\n");
                afficherPokemons(pokemons , nbPokemons);
                menuPrincipal;
                break;
            case 3:
                printf(">> Modifier un Pokemon\n");
                modifierPokemon(pokemons , nbPokemons);
                menuPrincipal;
                break;
            case 4:
                printf(">> Supprimer un Pokemon\n");
                supprimerPokemon(pokemons , nbPokemons);
                menuPrincipal;
                break;
            case 5:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide !\n");
        }

    } while (choix <0 || choix >6);
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
                printf(">> Ajouter une Machine \n");
                ajouterMachine(machines,nbMachines);
                menuPrincipal;
                break;
            case 2:
                printf(">> Afficher une Machine \n");
                afficherMachines(machines,nbMachines);
                menuPrincipal;
                break;
            case 3:
                printf(">> Modifier une Machine \n");
                modifierMachine(machines,nbMachines);
                menuPrincipal;
                break;
            case 4:
                printf(">> Supprimer une Machine\n");
                supprimerMachine(machines,nbMachines);
                menuPrincipal;
                break;
            case 5:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide !\n");
        }

    } while choix <0 || choix >6);
}
/* ===== SOUS-MENU Commande ===== */
void menuCommande() {
    int choix;

    do {
        printf("\n===== GERER commande =====\n");
        printf("1. Ajouter une commande\n");
        printf("2. Afficher les commandes\n");
        printf("3. Modifier une commande\n");
        printf("4. Supprimer une commande \n");
        printf("5. Revenir au menu precedent\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf(">> Ajouter un commande\n");
                ajouterCommande(commandes,nbCommandes);
                menuPrincipal;
                break;
            case 2:
                printf(">> Afficher les commandes\n");
                afficherCommandes(commandes,nbCommandes);
                menuPrincipal;
                break;
            case 3:
                printf(">> Modifier une commande\n");
                modifierCommande(commandes,nbCommandes);
                menuPrincipal;
                break;
            case 4:
                printf(">> Supprimer une commande \n");
                supprimerCommande(commandes,nbCommandes);
                menuPrincipal;
                break;
            case 5:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide !\n");
        }

    } while choix <0 || choix >6);
}
void menuClient() {
    int choix;

    do {
        printf("\n===== GERER Clients =====\n");
        printf("1. Ajouter un Client\n");
        printf("2. Afficher les Clients\n");
        printf("3. Modifier un Client\n");
        printf("4. Supprimer un Client\n");
        printf("5. Revenir au menu precedent\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf(">> Ajouter un client\n");
                ajouterClient(clients,nbClients);
                menuPrincipal;
                break;
            case 2:
                printf(">> Afficher les clients\n");
                afficherClients(clients,nbClients);
                menuPrincipal;
                break;
            case 3:
                printf(">> Modifier un client\n");
                modifierClient(clients,nbClients);
                menuPrincipal;
                break;
            case 4:
                printf(">> Supprimer un client\n");
                supprimerClient(clients,nbClients);
                menuPrincipal;
                break;
            case 5:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide !\n");
        }

    } while choix <0 || choix >6);
}


