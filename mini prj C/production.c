#include "headers.h"

// Variable globale pour la caisse
float caisse = CAISSE_INITIALE;

// Fonction pour finaliser une production terminée
void finaliserProduction(ListeCommande** listeCommandes, ListeMachine** listeMachines, int idCommande) {
    ListeCommande* commandeNode = rechercherCommande(*listeCommandes, idCommande);
    if (commandeNode == NULL) {
        return; // Commande introuvable
    }

    commande* cmd = &(commandeNode->data);

    // Rechercher la machine
    ListeMachine* machineNode = rechercherMachineParPokemon(*listeMachines, cmd->idPokemon);
    if (machineNode == NULL) {
        return;
    }

    machine* mach = &(machineNode->data);

    // Rechercher le pokemon pour le prix
    ListePokemon* pokemonNode = NULL;
    extern ListePokemon* listePokemons;
    pokemonNode = rechercherPokemon(listePokemons, cmd->idPokemon);
    if (pokemonNode == NULL) {
        return;
    }

    pokemon* poke = &(pokemonNode->data);

    // Calculer ce qui a été produit
    int quantiteRestante = cmd->quantite - cmd->quantiteProduite;
    int capaciteRestante = mach->nbMax - mach->compteur;
    int quantitePossible = (quantiteRestante <= capaciteRestante) ? quantiteRestante : capaciteRestante;

    float coutTotal = quantitePossible * poke->prix;

    printf("\n=== PRODUCTION TERMINEE ===\n");
    printf("Commande %d : Finalisation automatique\n", idCommande);

    // Mettre à jour le compteur de la machine
    mach->compteur += quantitePossible;

    // Mettre à jour la quantité produite de la commande
    cmd->quantiteProduite += quantitePossible;

    // Mettre à jour la caisse
    caisse += coutTotal;
    printf("Paiement recu: %.2f pieces\n", coutTotal);
    printf("Nouvelle caisse: %.2f pieces\n", caisse);
    printf("Total produit pour la commande: %d/%d figurines\n", cmd->quantiteProduite, cmd->quantite);

    // Vérifier si la commande est complète ou partielle
    if (cmd->quantiteProduite < cmd->quantite) {
        // Production partielle
        printf("\n>>> PRODUCTION PARTIELLE <<<\n");
        printf("La machine a atteint sa limite: %d/%d figurines produites.\n",
               mach->compteur, mach->nbMax);
        printf("Il reste %d figurines a produire pour cette commande.\n",
               cmd->quantite - cmd->quantiteProduite);

        // La commande reste en cours
        cmd->etat = 1; // En cours

        // Passer la machine en maintenance
        printf("La machine passe en attente de maintenance.\n");
        printf("Effectuez la maintenance puis relancez la commande %d pour terminer.\n", idCommande);
        mach->etat = 2; // En attente de maintenance
        mach->idCommande = 0;
        mach->dateDisponibilite = 0;
    } else {
        // Production complète
        cmd->etat = 2; // Réalisée

        // Vérifier si la machine doit passer en maintenance
        if (mach->compteur >= mach->nbMax) {
            printf("\nATTENTION: La machine a produit %d/%d figurines.\n",
                   mach->compteur, mach->nbMax);
            printf("La machine passe en attente de maintenance.\n");
            mach->etat = 2; // En attente de maintenance
            mach->idCommande = 0;
            mach->dateDisponibilite = 0;
        } else {
            printf("\nMachine libre. Figurines produites: %d/%d\n",
                   mach->compteur, mach->nbMax);
            mach->etat = 0; // Libre
            mach->idCommande = 0;
            mach->dateDisponibilite = 0;
        }

        printf("\nCommande %d realisee avec succes!\n", idCommande);
    }
}

void afficherTempsRestant(machine m) {
    if (m.etat == 1 && m.idCommande != 0) {
        printf("Temps restant estime: En cours de production\n");
    } else if (m.etat == 0) {
        printf("Machine libre, disponible immediatement\n");
    } else if (m.etat == 2) {
        printf("Machine en attente de maintenance\n");
    }
}

void entretenirMachine(ListeMachine** listeMachines, int idMachine) {
    if (*listeMachines == NULL) {
        printf("Aucune machine disponible.\n");
        return;
    }

    ListeMachine* machine = rechercherMachine(*listeMachines, idMachine);
    if (machine == NULL) {
        printf("Machine %d introuvable.\n", idMachine);
        return;
    }

    if (machine->data.etat != 2) {
        printf("La machine %d n'est pas en attente de maintenance.\n", idMachine);
        printf("Etat actuel: ");
        switch (machine->data.etat) {
            case 0: printf("Libre\n"); break;
            case 1: printf("Occupee\n"); break;
        }
        return;
    }

    // Vérifier si la caisse a assez d'argent
    if (caisse < machine->data.coutMaint) {
        printf("ERREUR: Caisse insuffisante pour la maintenance.\n");
        printf("Caisse actuelle: %.2f pieces\n", caisse);
        printf("Cout de maintenance: %.2f pieces\n", machine->data.coutMaint);
        return;
    }

    // Effectuer la maintenance
    printf("\n=== MAINTENANCE DE LA MACHINE %d ===\n", idMachine);
    printf("Cout de la maintenance: %.2f pieces\n", machine->data.coutMaint);

    caisse -= machine->data.coutMaint;
    machine->data.compteur = 0;
    machine->data.etat = 0; // Libre
    machine->data.dateDisponibilite = 0; // Réinitialiser

    printf("Maintenance effectuee avec succes!\n");
    printf("Nouvelle caisse: %.2f pieces\n", caisse);
    printf("Machine %d est maintenant libre.\n", idMachine);
    printf("Compteur reinitialise a 0/%d\n", machine->data.nbMax);
}

void realiserCommande(ListeCommande** listeCommandes, ListeMachine** listeMachines,
                      ListePokemon* listePokemons, int idCommande) {

    if (*listeCommandes == NULL) {
        printf("Aucune commande disponible.\n");
        return;
    }

    // Rechercher la commande
    ListeCommande* commandeNode = rechercherCommande(*listeCommandes, idCommande);
    if (commandeNode == NULL) {
        printf("Commande %d introuvable.\n", idCommande);
        return;
    }

    commande* cmd = &(commandeNode->data);

    // Vérifier l'état de la commande
    if (cmd->etat == 2) {
        printf("La commande %d est deja realisee.\n", idCommande);
        return;
    }

    // Rechercher le Pokémon commandé
    ListePokemon* pokemonNode = rechercherPokemon(listePokemons, cmd->idPokemon);
    if (pokemonNode == NULL) {
        printf("ERREUR: Pokemon %d introuvable.\n", cmd->idPokemon);
        return;
    }

    // Rechercher la machine qui produit ce Pokémon
    ListeMachine* machineNode = rechercherMachineParPokemon(*listeMachines, cmd->idPokemon);
    if (machineNode == NULL) {
        printf("ERREUR: Aucune machine ne produit le Pokemon %d.\n", cmd->idPokemon);
        return;
    }

    machine* mach = &(machineNode->data);
    pokemon* poke = &(pokemonNode->data);

    printf("\n=== REALISATION DE LA COMMANDE %d ===\n", idCommande);
    printf("Client: %d\n", cmd->matriculeClient);
    printf("Pokemon: %s (ID: %d)\n", poke->nom, poke->id);
    printf("Quantite totale: %d | Deja produite: %d | Reste: %d\n",
           cmd->quantite, cmd->quantiteProduite, cmd->quantite - cmd->quantiteProduite);
    printf("Machine: %s (ID: %d)\n", mach->nom, mach->id);

    // Vérifier l'état de la machine
    if (mach->etat == 2) {
        printf("\nERREUR: La machine est en attente de maintenance.\n");
        printf("Veuillez d'abord effectuer la maintenance (cout: %.2f pieces).\n",
               mach->coutMaint);
        return;
    }

    if (mach->etat == 1) {
        // Vérifier si la production est terminée
        time_t maintenant = time(NULL);
        if (mach->dateDisponibilite > maintenant) {
            double secondesRestantes = difftime(mach->dateDisponibilite, maintenant);
            int minutesRestantes = (int)(secondesRestantes / 60);
            int secondesAffichees = (int)secondesRestantes % 60;
            printf("\nERREUR: La machine est occupee.\n");
            printf("Commande en cours: %d\n", mach->idCommande);
            if (minutesRestantes > 0) {
                printf("Temps restant: %d min %d sec\n", minutesRestantes, secondesAffichees);
            } else {
                printf("Temps restant: %d secondes\n", secondesAffichees);
            }
            printf("Veuillez attendre qu'elle soit libre.\n");
            return;
        } else {
            // La production précédente est terminée, finaliser automatiquement
            printf("\nProduction precedente terminee. Finalisation...\n");
            finaliserProduction(listeCommandes, listeMachines, mach->idCommande);
        }
    }

    // La machine est libre, on peut produire
    printf("\nMachine disponible. Debut de la production...\n");
    printf("Compteur actuel de la machine: %d/%d\n", mach->compteur, mach->nbMax);

    // Calculer la quantité restante à produire
    int quantiteRestante = cmd->quantite - cmd->quantiteProduite;
    int capaciteRestante = mach->nbMax - mach->compteur;

    if (capaciteRestante <= 0) {
        printf("\nERREUR: La machine a deja atteint sa limite de production!\n");
        printf("Veuillez effectuer la maintenance avant de continuer.\n");
        return;
    }

    // Calculer combien on peut produire avant maintenance
    int quantitePossible = (quantiteRestante <= capaciteRestante) ? quantiteRestante : capaciteRestante;

    if (quantitePossible < quantiteRestante) {
        printf("\nATTENTION: La machine ne peut produire que %d figurines avant maintenance.\n", quantitePossible);
        printf("La commande complete necessite %d figurines.\n", quantiteRestante);
        printf("Production partielle de %d figurines...\n", quantitePossible);
    }

    // Calculer le temps et le cout pour la quantité produite
    int tempsTotal = quantitePossible * mach->tempsProd;
    float coutTotal = quantitePossible * poke->prix;

    printf("Temps de production: %d minutes (%d x %d)\n",
           tempsTotal, quantitePossible, mach->tempsProd);
    printf("Cout de production: %.2f pieces (%.2f x %d)\n",
           coutTotal, poke->prix, quantitePossible);

    // Calculer la date de disponibilité (en secondes pour la simulation)
    time_t maintenant = time(NULL);
    mach->dateDisponibilite = maintenant + (tempsTotal * 60); // Convertir minutes en secondes

    // Mettre à jour la machine
    mach->etat = 1; // Occupée
    mach->idCommande = idCommande;
    cmd->etat = 1; // En cours

    printf("\n=== PRODUCTION LANCEE ===\n");
    printf("La machine sera disponible dans %d minutes.\n", tempsTotal);

    // Afficher l'heure de disponibilité
    struct tm* tm_info = localtime(&mach->dateDisponibilite);
    char buffer[26];
    strftime(buffer, 26, "%H:%M:%S", tm_info);
    printf("Heure de disponibilite prevue: %s\n", buffer);

    printf("\nLa production est en cours...\n");
    printf("Vous pouvez consulter l'etat de la machine pour voir la progression.\n");
    printf("La machine finalisera automatiquement la production quand le temps sera ecoule.\n");
}

void afficherStatistiques(ListePokemon* listePokemons, ListeMachine* listeMachines,
                         ListeClient* listeClients, ListeCommande* listeCommandes) {
    printf("\n========================================\n");
    printf("===== STATISTIQUES DE L'USINE ======\n");
    printf("========================================\n\n");

    printf("Caisse de l'usine: %.2f pieces\n\n", caisse);

    printf("Nombre de Pokemons: %d\n", compterPokemons(listePokemons));
    printf("Nombre de machines: %d\n", compterMachines(listeMachines));
    printf("Nombre de clients: %d\n", compterClients(listeClients));
    printf("Nombre de commandes: %d\n\n", compterCommandes(listeCommandes));

    // Statistiques sur les commandes
    int enAttente = 0, enCours = 0, realisees = 0;
    ListeCommande* cmd = listeCommandes;
    while (cmd != NULL) {
        switch (cmd->data.etat) {
            case 0: enAttente++; break;
            case 1: enCours++; break;
            case 2: realisees++; break;
        }
        cmd = cmd->next;
    }

    printf("Commandes en attente: %d\n", enAttente);
    printf("Commandes en cours: %d\n", enCours);
    printf("Commandes realisees: %d\n\n", realisees);

    // Statistiques sur les machines
    int libres = 0, occupees = 0, maintenance = 0;
    ListeMachine* mach = listeMachines;
    while (mach != NULL) {
        switch (mach->data.etat) {
            case 0: libres++; break;
            case 1: occupees++; break;
            case 2: maintenance++; break;
        }
        mach = mach->next;
    }

    printf("Machines libres: %d\n", libres);
    printf("Machines occupees: %d\n", occupees);
    printf("Machines en attente de maintenance: %d\n", maintenance);

    printf("\n========================================\n");
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
    ListePokemon* currentPoke = listePokemons;
    while (currentPoke != NULL && index < nbPokemons) {
        stats[index].idPokemon = currentPoke->data.id;
        strcpy(stats[index].nomPokemon, currentPoke->data.nom);
        stats[index].quantiteVendue = 0;
        stats[index].revenuTotal = 0.0;
        stats[index].nombreCommandes = 0;

        // Parcourir les commandes pour ce Pokémon
        ListeCommande* cmd = listeCommandes;
        while (cmd != NULL) {
            if (cmd->data.idPokemon == currentPoke->data.id && cmd->data.etat == 2) {
                // Commande réalisée pour ce Pokémon
                stats[index].quantiteVendue += cmd->data.quantiteProduite;
                stats[index].revenuTotal += cmd->data.quantiteProduite * currentPoke->data.prix;
                stats[index].nombreCommandes++;
            }
            cmd = cmd->next;
        }

        index++;
        currentPoke = currentPoke->next;
    }

    // Tri par quantité vendue (tri à bulles)
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
