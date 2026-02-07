#include "headers.h"

// Variables globales des listes
ListePokemon* listePokemons = NULL;
ListeMachine* listeMachines = NULL;
ListeClient* listeClients = NULL;
ListeCommande* listeCommandes = NULL;

void menuPrincipal() {
    int choix;

    do {
        printf("\n========================================\n");
        printf("=========== USINE POKEMON ==========\n");
        printf("========================================\n");
        printf("| 1. Gerer les Pokemon               |\n");
        printf("| 2. Gerer les machines              |\n");
        printf("| 3. Gerer les clients               |\n");
        printf("| 4. Gerer les commandes             |\n");
        printf("| 5. Production et maintenance       |\n");
        printf("| 6. Afficher l'etat de l'usine      |\n");
        printf("| 7. Classement des Pokemons vendus  |\n");
        printf("| 0. Quitter et sauvegarder          |\n");
        printf("========================================\n");
        printf("Votre choix: ");
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
                menuProduction();
                break;
            case 6:
                menuEtatUsine();
                break;
            case 7:
                afficherClassementPokemons(listeCommandes, listePokemons);
                break;
            case 0:
                printf("\nSauvegarde et fermeture...\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

void menuPokemon() {
    int choix;

    do {
        printf("\n===== GERER POKEMON =====\n");
        printf("1. Ajouter un Pokemon\n");
        printf("2. Afficher les Pokemons\n");
        printf("3. Modifier un Pokemon\n");
        printf("4. Supprimer un Pokemon\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Ajouter un Pokemon <<<\n");
                ajouterPokemon(&listePokemons);
                break;
            case 2:
                printf("\n>>> Liste des Pokemons <<<\n");
                afficherPokemons(listePokemons);
                break;
            case 3:
                printf("\n>>> Modifier un Pokemon <<<\n");
                modifierPokemon(listePokemons);
                break;
            case 4:
                printf("\n>>> Supprimer un Pokemon <<<\n");
                supprimerPokemon(&listePokemons);
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

void menuMachine() {
    int choix;

    do {
        printf("\n===== GERER MACHINES =====\n");
        printf("1. Ajouter une machine\n");
        printf("2. Afficher les machines\n");
        printf("3. Modifier une machine\n");
        printf("4. Supprimer une machine\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Ajouter une Machine <<<\n");
                ajouterMachine(&listeMachines, listePokemons);
                break;
            case 2:
                printf("\n>>> Liste des Machines <<<\n");
                afficherMachines(listeMachines, listeCommandes);
                break;
            case 3:
                printf("\n>>> Modifier une Machine <<<\n");
                modifierMachine(listeMachines, listePokemons, listeCommandes);
                break;
            case 4:
                printf("\n>>> Supprimer une Machine <<<\n");
                supprimerMachine(&listeMachines);
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

void menuClient() {
    int choix;

    do {
        printf("\n===== GERER CLIENTS =====\n");
        printf("1. Ajouter un client\n");
        printf("2. Afficher les clients\n");
        printf("3. Modifier un client\n");
        printf("4. Supprimer un client\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Ajouter un Client <<<\n");
                ajouterClient(&listeClients);
                break;
            case 2:
                printf("\n>>> Liste des Clients <<<\n");
                afficherClients(listeClients);
                break;
            case 3:
                printf("\n>>> Modifier un Client <<<\n");
                modifierClient(listeClients, listePokemons);
                break;
            case 4:
                printf("\n>>> Supprimer un Client <<<\n");
                supprimerClient(&listeClients);
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

void menuCommande() {
    int choix;

    do {
        printf("\n===== GERER COMMANDES =====\n");
        printf("1. Ajouter une commande\n");
        printf("2. Afficher les commandes\n");
        printf("3. Modifier une commande\n");
        printf("4. Supprimer une commande\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Ajouter une Commande <<<\n");
                ajouterCommande(&listeCommandes, listePokemons);
                break;
            case 2:
                printf("\n>>> Liste des Commandes <<<\n");
                afficherCommandes(listeCommandes);
                break;
            case 3:
                printf("\n>>> Modifier une Commande <<<\n");
                modifierCommande(listeCommandes, listePokemons);
                break;
            case 4:
                printf("\n>>> Supprimer une Commande <<<\n");
                supprimerCommande(&listeCommandes);
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

void menuProduction() {
    int choix;
    int idCommande, idMachine;

    do {
        printf("\n===== PRODUCTION ET MAINTENANCE =====\n");
        printf("1. Realiser une commande\n");
        printf("2. Entretenir une machine\n");
        printf("3. Afficher l'etat des machines\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n>>> Realiser une Commande <<<\n");
                printf("ID de la commande a realiser: ");
                scanf("%d", &idCommande);
                realiserCommande(&listeCommandes, &listeMachines, listePokemons, idCommande);
                break;
            case 2:
                printf("\n>>> Entretenir une Machine <<<\n");
                printf("ID de la machine a entretenir: ");
                scanf("%d", &idMachine);
                entretenirMachine(&listeMachines, idMachine);
                break;
            case 3:
                printf("\n>>> Etat des Machines <<<\n");
                afficherMachines(listeMachines, listeCommandes);
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

void menuEtatUsine() {
    afficherStatistiques(listePokemons, listeMachines, listeClients, listeCommandes);
}
