#include "headers.h"

/****************Fonctions Développées**************************/

// Variables globales des listes
ListePokemon* listePokemons = NULL;
ListeMachine* listeMachines = NULL;
ListeClient* listeClients = NULL;
ListeCommande* listeCommandes = NULL;


/* ===== MENU PRINCIPAL ===== */
void menuPrincipal() {
    int choix;

    do {
        printf("\n======================================\n");
        printf("=========== USINE POKEMON ============\n");
        printf("======================================\n");
        printf("| 1. Gerer les Pokemon               |\n");
        printf("| 2. Gerer les machines              |\n");
        printf("| 3. Gerer les clients               |\n");
        printf("| 4. Gerer les commandes             |\n");
        printf("| 5. Production et maintenance       |\n");
        printf("| 6. Afficher l'etat de l'usine      |\n");
        printf("| 7. Classement des Pokemons vendus  |\n");
        printf("| 0. Quitter et sauvegarder          |\n");
        printf("======================================\n");
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
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

/* ===== SOUS-MENU POKEMON ===== */
void menuPokemon() {
    int choix;

    do {
        printf("=========================\n");
        printf("===== GERER POKEMON =====\n");
        printf("=========================\n");
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

/* ===== SOUS MENU MACHINE ===== */
void menuMachine() {
    int choix;

    do {
        printf("==========================\n");
        printf("===== GERER MACHINES =====\n");
        printf("==========================\n");
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

/* ===== SOUS-MENU CLIENT ===== */
void menuClient() {
    int choix;

    do {
        printf("=========================\n");
        printf("===== GERER CLIENTS =====\n");
        printf("=========================\n");
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

/* ===== SOUS-MENU COMMANDE ===== */
void menuCommande() {
    int choix;

    do {
        printf("===========================\n");
        printf("===== GERER COMMANDES =====\n");
        printf("===========================\n");
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
                ajouterCommande(&listeCommandes, listePokemons, listeClients);
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

/* ===== SOUS-MENU PRODUCTION ===== */
void menuProduction() {
    int choix;
    int idCommande, idMachine;

    do {
        printf("=====================================\n");
        printf("===== PRODUCTION ET MAINTENANCE =====\n");
        printf("=====================================\n");
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

void afficherClassementPokemons(ListeCommande* listeCommandes, ListePokemon* listePokemons) {
    if (listePokemons == NULL) {
        printf("\nAucun Pokemon disponible.\n");
        return;
    }

    // Compter le nombre de Pokémons
    int nbPokemons = compterPokemons(listePokemons);
    if (nbPokemons == 0) {
        printf("\nAucun Pokemon disponible.\n");
        return;
    }

    // Créer un tableau pour stocker les statistiques
    typedef struct {
        int idPokemon;
        char nomPokemon[20];
        int quantiteVendue;
        float revenuTotal;
        int nombreCommandes;
    } StatPokemon;

    StatPokemon* stats = (StatPokemon*)malloc(nbPokemons * sizeof(StatPokemon));
    if (stats == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }

    // Initialiser les statistiques pour chaque Pokémon
    int index = 0;
    ListePokemon* PokeCourant = listePokemons;
    while (PokeCourant != NULL && index < nbPokemons) {
        stats[index].idPokemon = PokeCourant->p.id;
        strcpy(stats[index].nomPokemon, PokeCourant->p.nom);
        stats[index].quantiteVendue = 0;
        stats[index].revenuTotal = 0.0;
        stats[index].nombreCommandes = 0;

        // Parcourir les commandes pour ce Pokémon
        ListeCommande* cmd = listeCommandes;
        while (cmd != NULL) {
            if (cmd->cm.idPokemon == PokeCourant->p.id && cmd->cm.etat == 2) {
                // Commande réalisée pour ce Pokémon
                stats[index].quantiteVendue += cmd->cm.quantiteProduite;
                stats[index].revenuTotal += cmd->cm.quantiteProduite * PokeCourant->p.prix;
                stats[index].nombreCommandes++;
            }
            cmd = cmd->suivant;
        }

        index++;
        PokeCourant = PokeCourant->suivant;
    }

    // Tri par quantité vendue
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (stats[j].quantiteVendue < stats[j + 1].quantiteVendue) {
                StatPokemon temp = stats[j];
                stats[j] = stats[j + 1];
                stats[j + 1] = temp;
            }
        }
    }

    // Affichage du classement
    printf("\n========================================\n");
    printf("=== CLASSEMENT DES POKEMONS VENDUS ====\n");
    printf("========================================\n\n");

    if (stats[0].quantiteVendue == 0) {
        printf("Aucune vente enregistree pour le moment.\n");
    } else {
        printf("%-5s %-15s %-12s %-15s %-12s\n",
               "Rang", "Pokemon", "Quantite", "Revenu Total", "Commandes");
        printf("--------------------------------------------------------------\n");

        int rang = 1;
        for (int i = 0; i < index; i++) {
            if (stats[i].quantiteVendue > 0) {
                // Afficher avec médailles pour le top 3
                if (rang == 1) {
                    printf("🥇 ");
                } else if (rang == 2) {
                    printf("🥈 ");
                } else if (rang == 3) {
                    printf("🥉 ");
                } else {
                    printf("%-3d", rang);
                }

                printf("%-15s %-12d %-15.2f %-12d\n",
                       stats[i].nomPokemon,
                       stats[i].quantiteVendue,
                       stats[i].revenuTotal,
                       stats[i].nombreCommandes);
                rang++;
            }
        }

        // Statistiques globales
        int totalVentes = 0;
        float totalRevenu = 0.0;
        for (int i = 0; i < index; i++) {
            totalVentes += stats[i].quantiteVendue;
            totalRevenu += stats[i].revenuTotal;
        }

        printf("\n--------------------------------------------------------------\n");
        printf("TOTAL : %d figurines vendues pour %.2f pieces de revenu\n",
               totalVentes, totalRevenu);

        // Pokémon le plus populaire
        if (stats[0].quantiteVendue > 0) {
            printf("\n⭐ POKEMON LE PLUS VENDU : %s (%d figurines)\n",
                   stats[0].nomPokemon, stats[0].quantiteVendue);
        }

        // Calcul du revenu moyen par figurine
        if (totalVentes > 0) {
            float moyenneRevenu = totalRevenu / totalVentes;
            printf("💰 REVENU MOYEN PAR FIGURINE : %.2f pieces\n", moyenneRevenu);
        }
    }

    printf("\n========================================\n");

    // Libérer la mémoire
    free(stats);
}

/* ===== SOUS-MENU ETAT_D'USINE ===== */
void menuEtatUsine() {
    afficherStatistiques(listePokemons, listeMachines, listeClients, listeCommandes);
}
