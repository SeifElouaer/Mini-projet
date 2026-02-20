#include "headers.h"

// fichiers
#define FICHIER_POKEMONS "pokemons.txt"
#define FICHIER_MACHINES "machines.txt"
#define FICHIER_CLIENTS "clients.txt"
#define FICHIER_COMMANDES "commandes.txt"
#define FICHIER_CAISSE "caisse.txt"

void chargerCaisse() {
    FILE* fichier = fopen(FICHIER_CAISSE, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier caisse non trouve. Utilisation de la caisse initiale.\n");
        caisse = CAISSE_INITIALE;
        return;
    }

    if (fscanf(fichier, "%f", &caisse) != 1) {
        printf("ERREUR: Lecture de la caisse echouee. Utilisation de la caisse initiale.\n");
        caisse = CAISSE_INITIALE;
    } else {
        printf("Caisse chargee: %.2f pieces\n", caisse);
    }

    fclose(fichier);
}

void sauvegarderCaisse() {
    FILE* fichier = fopen(FICHIER_CAISSE, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible de sauvegarder la caisse.\n");
        return;
    }

    fprintf(fichier, "%.2f", caisse);
    fclose(fichier);
    printf("Caisse sauvegardee: %.2f pieces\n", caisse);
}

void chargerDonnees() {
    printf("\n=======================================\n");
    printf("======= CHARGEMENT DES DONNEES ========\n");
    printf("=======================================\n\n");

    chargerCaisse();

    listePokemons = chargerPokemons(FICHIER_POKEMONS);
    listeMachines = chargerMachines(FICHIER_MACHINES);
    listeClients = chargerClients(FICHIER_CLIENTS);
    listeCommandes = chargerCommandes(FICHIER_COMMANDES);

    printf("\nChargement termine!\n");
    printf("=========================================\n");
    printf("=========================================\n");
}

void sauvegarderDonnees() {
    printf("\n========================================\n");
    printf("====== SAUVEGARDE DES DONNEES =========\n");
    printf("========================================\n\n");

    sauvegarderCaisse();

    sauvegarderPokemons(listePokemons, FICHIER_POKEMONS);
    sauvegarderMachines(listeMachines, FICHIER_MACHINES);
    sauvegarderClients(listeClients, FICHIER_CLIENTS);
    sauvegarderCommandes(listeCommandes, FICHIER_COMMANDES);

    printf("\nSauvegarde terminee!\n");
    printf("=========================================\n");
    printf("=========================================\n");
}

void libererToutesLesListes() {
    printf("\nLiberation de la memoire...\n");

    libererListePokemon(&listePokemons);
    libererListeMachine(&listeMachines);
    libererListeClient(&listeClients);
    libererListeCommande(&listeCommandes);

    printf("Memoire liberee avec succes.\n");
}

int main() {
    printf("==========================================\n");
    printf("======= USINE DE FIGURINES POKEMON =======\n");
    printf("============== VERSION 2 (V2) ============\n");
    printf("==========================================\n");
    printf("| Projet realise par: Khemakhem Farah    |\n");
    printf("|                     Ben Othman Youssef |\n");
    printf("|                     Elouaer Seif       |\n");
    printf("==========================================\n\n");

    chargerDonnees();

    menuPrincipal();

    sauvegarderDonnees();

    libererToutesLesListes();

    printf("\n========================================\n");
    printf("Merci d'avoir utiliser l'usine Pokemon!\n");
    printf("Au revoir!\n");
    printf("=========================================\n");

    return 0;
}
