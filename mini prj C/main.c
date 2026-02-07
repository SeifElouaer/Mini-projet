#include "headers.h"

// Noms des fichiers de sauvegarde
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
    printf("\n========================================\n");
    printf("======= CHARGEMENT DES DONNEES ========\n");
    printf("========================================\n\n");
    
    // Charger la caisse
    chargerCaisse();
    
    // Charger les listes depuis les fichiers
    listePokemons = chargerPokemons(FICHIER_POKEMONS);
    listeMachines = chargerMachines(FICHIER_MACHINES);
    listeClients = chargerClients(FICHIER_CLIENTS);
    listeCommandes = chargerCommandes(FICHIER_COMMANDES);
    
    printf("\nChargement termine!\n");
    printf("========================================\n");
}

void sauvegarderDonnees() {
    printf("\n========================================\n");
    printf("====== SAUVEGARDE DES DONNEES =========\n");
    printf("========================================\n\n");
    
    // Sauvegarder la caisse
    sauvegarderCaisse();
    
    // Sauvegarder les listes dans les fichiers
    sauvegarderPokemons(listePokemons, FICHIER_POKEMONS);
    sauvegarderMachines(listeMachines, FICHIER_MACHINES);
    sauvegarderClients(listeClients, FICHIER_CLIENTS);
    sauvegarderCommandes(listeCommandes, FICHIER_COMMANDES);
    
    printf("\nSauvegarde terminee!\n");
    printf("========================================\n");
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
    printf("========================================\n");
    printf("====== USINE DE FIGURINES POKEMON =====\n");
    printf("=========== VERSION 2 (V2) ============\n");
    printf("========================================\n");
    printf("Projet realise par: ElouaerSeif_1AGI1\n");
    printf("========================================\n\n");
    
    // Charger les données au démarrage
    chargerDonnees();
    
    // Menu principal
    menuPrincipal();
    
    // Sauvegarder les données avant de quitter
    sauvegarderDonnees();
    
    // Libérer la mémoire
    libererToutesLesListes();
    
    printf("\n========================================\n");
    printf("Merci d'avoir utilise l'usine Pokemon!\n");
    printf("Au revoir!\n");
    printf("========================================\n");
    
    return 0;
}
