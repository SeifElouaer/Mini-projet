#include "headers.h"

// Variable globale
float caisse = CAISSE_INITIALE;

// Fonction pour finaliser une production terminée
void finaliserProduction(ListeCommande** listeCommandes, ListeMachine** listeMachines, int idCommande) {
    ListeCommande* commandeNoeud = rechercherCommande(*listeCommandes, idCommande);
    if (commandeNoeud == NULL) {
        return; // Commande introuvable
    }

    commande* cmd = &(commandeNoeud->cm);

    // Rechercher la machine
    ListeMachine* machineNoeud = rechercherMachineParPokemon(*listeMachines, cmd->idPokemon);
    if (machineNoeud == NULL) {
        return;
    }

    machine* mach = &(machineNoeud->m);

    // Rechercher le pokemon pour le prix
    ListePokemon* pokemonNoeud = NULL;
    extern ListePokemon* listePokemons;
    pokemonNoeud = rechercherPokemon(listePokemons, cmd->idPokemon);
    if (pokemonNoeud == NULL) {
        return;
    }

    pokemon* poke = &(pokemonNoeud->p);

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

    if (machine->m.etat != 2) {
        printf("La machine %d n'est pas en attente de maintenance.\n", idMachine);
        printf("Etat actuel: ");
        switch (machine->m.etat) {
            case 0: printf("Libre\n"); break;
            case 1: printf("Occupee\n"); break;
        }
        return;
    }

    // Vérifier si la caisse a assez d'argent
    if (caisse < machine->m.coutMaint) {
        printf("ERREUR: Caisse insuffisante pour la maintenance.\n");
        printf("Caisse actuelle: %.2f pieces\n", caisse);
        printf("Cout de maintenance: %.2f pieces\n", machine->m.coutMaint);
        return;
    }

    // Effectuer la maintenance
    printf("\n=== MAINTENANCE DE LA MACHINE %d ===\n", idMachine);
    printf("Cout de la maintenance: %.2f pieces\n", machine->m.coutMaint);

    caisse -= machine->m.coutMaint;
    machine->m.compteur = 0;
    machine->m.etat = 0; // Libre
    machine->m.dateDisponibilite = 0; // Réinitialiser

    printf("Maintenance effectuee avec succes!\n");
    printf("Nouvelle caisse: %.2f pieces\n", caisse);
    printf("Machine %d est maintenant libre.\n", idMachine);
    printf("Compteur reinitialise a 0/%d\n", machine->m.nbMax);
}

void realiserCommande(ListeCommande** listeCommandes, ListeMachine** listeMachines,
                      ListePokemon* listePokemons, int idCommande) {

    if (*listeCommandes == NULL) {
        printf("Aucune commande disponible.\n");
        return;
    }

    // Rechercher la commande
    ListeCommande* commandeNoeud = rechercherCommande(*listeCommandes, idCommande);
    if (commandeNoeud == NULL) {
        printf("Commande %d introuvable.\n", idCommande);
        return;
    }

    commande* cmd = &(commandeNoeud->cm);

    // Vérifier l'état de la commande
    if (cmd->etat == 2) {
        printf("La commande %d est deja realisee.\n", idCommande);
        return;
    }

    // Rechercher le Pokémon commandé
    ListePokemon* pokemonNoeud = rechercherPokemon(listePokemons, cmd->idPokemon);
    if (pokemonNoeud == NULL) {
        printf("ERREUR: Pokemon %d introuvable.\n", cmd->idPokemon);
        return;
    }

    // Rechercher la machine qui produit ce Pokémon
    ListeMachine* machineNoeud = rechercherMachineParPokemon(*listeMachines, cmd->idPokemon);
    if (machineNoeud == NULL) {
        printf("ERREUR: Aucune machine ne produit le Pokemon %d.\n", cmd->idPokemon);
        return;
    }

    machine* mach = &(machineNoeud->m);
    pokemon* poke = &(pokemonNoeud->p);

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
    printf("======= STATISTIQUES DE L'USINE ========\n");
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
        switch (cmd->cm.etat) {
            case 0:
                enAttente++;
                break;
            case 1:
                enCours++;
                break;
            case 2:
                realisees++;
                break;
        }
        cmd = cmd->suivant;
    }

    printf("Commandes en attente: %d\n", enAttente);
    printf("Commandes en cours: %d\n", enCours);
    printf("Commandes realisees: %d\n\n", realisees);

    // Statistiques sur les machines
    int libres = 0, occupees = 0, maintenance = 0;
    ListeMachine* mach = listeMachines;
    while (mach != NULL) {
        switch (mach->m.etat) {
            case 0: libres++; break;
            case 1: occupees++; break;
            case 2: maintenance++; break;
        }
        mach = mach->suivant;
    }

    printf("Machines libres: %d\n", libres);
    printf("Machines occupees: %d\n", occupees);
    printf("Machines en attente de maintenance: %d\n", maintenance);

    printf("\n========================================\n");
}

