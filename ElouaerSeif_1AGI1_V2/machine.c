#include "headers.h"

/****************Fonctions Développées**************************/

static int idAuto = 1;

int genererId(){
    return idAuto++;
}

machine creerMachine(ListePokemon* listePokemons){
    machine m;
    m.id = genererId();
    printf("Nom de la machine : \n");
    scanf("%s", m.nom);
    do{
        printf("ID du Pokemon produit : \n");
        scanf("%d", &m.idPokemon);
        if (rechercherPokemon(listePokemons, m.idPokemon) == NULL) {
            printf("Pokemon inexistant. Veuillez reessayer.\n");
        }
    }while (rechercherPokemon(listePokemons, m.idPokemon) == NULL);

    printf("Temps de production d'une figurine (en minutes): \n");
    scanf("%d", &m.tempsProd);

    printf("Nombre maximum de figurines avant maintenance : \n");
    scanf("%d", &m.nbMax);

    m.compteur = 0;

    printf("Cout de maintenance : \n");
    scanf("%f", &m.coutMaint);

    m.etat = 0;                // machine libre
    m.idCommande = 0;          // aucune commande
    m.dateDisponibilite = 0;   // machine disponible

    return m;
}

void ajouterMachine(ListeMachine** liste, ListePokemon* listePokemons){
    ListeMachine* nv = (ListeMachine*) malloc(sizeof(ListeMachine));
    if (nv == NULL){
        printf("ERREUR\n");
        return;
    }

    nv -> m = creerMachine(listePokemons);
    nv -> suivant = *liste;
    *liste = nv;
    printf("Machine ajoutee avec succes.\n");
}

void afficherMachine(machine m, ListeCommande* listeCommandes){
    printf("-ID: %d", m.id);
    printf(" | Nom: %s", m.nom);
    printf(" | Pokemon produit: %d",m.idPokemon);
    printf(" | Temps de production: %d", m.tempsProd);
    printf(" | Nb max de figurines: %d", m.nbMax);
    printf(" | Compteur actuel: %d", m.compteur);
    printf(" | Cout de maintenance: %.2f", m.coutMaint);
    printf(" | Etat : ");
    switch (m.etat) {
        case 0:
            printf(" Libre\n");
            break;
        case 1:
            printf("Occupee");
            if (m.dateDisponibilite > 0) {
                time_t maintenant = time(NULL);
                double secondesRestantes = difftime(m.dateDisponibilite, maintenant);
                if (secondesRestantes > 0) {
                    int minutesRestantes = (int)(secondesRestantes / 60);
                    printf(" (disponible dans %d minutes)\n", minutesRestantes);
                }
                else {
                    printf(" (production terminee)\n");
                }
            }
            break;
        case 2:
            printf(" En attente de maintenance\n");
            break;
        default:
            printf("Inconnu\n");
    }

    if (m.idCommande == 0) {
        printf("Aucune commande en cours\n");
    }
    else{
        ListeCommande* cmd = rechercherCommande(listeCommandes, m.idCommande);
        if (cmd != NULL) {
            printf("  Commande en cours: ID=%d, Quantite=%d\n", cmd->cm.id, cmd->cm.quantite);
        }
    }
}

void afficherMachines(ListeMachine* liste, ListeCommande* listeCommandes){
    if (liste == NULL) {
        printf("Aucune machine.\n");
        return;
    }

    ListeMachine* courant = liste;
    int nb = 1;
    while (courant != NULL) {
        printf("#### Machine %d ####\n", nb++);
        afficherMachine(courant->m, listeCommandes);
        courant = courant->suivant;
    }
}

ListeMachine* rechercherMachine(ListeMachine* liste, int id) {
    ListeMachine* courant = liste;
    while (courant != NULL) {
        if (courant->m.id == id) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

ListeMachine* rechercherMachineParPokemon(ListeMachine* liste, int idPokemon) {
    ListeMachine* courant = liste;
    while (courant != NULL) {
        if (courant->m.idPokemon == idPokemon) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

void modifierMachine(ListeMachine* liste, ListePokemon* listePokemons, ListeCommande* listeCommandes){
    if (liste == NULL) {
        printf("Aucune machine.\n");
        return;
    }

    int id, choix;
    printf("ID de la machine a modifier: ");
    scanf("%d", &id);

    ListeMachine* noeud = rechercherMachine(liste, id);
    if (noeud == NULL) {
        printf("Machine introuvable.\n");
        return;
    }

    do {
        printf("===============================\n");
        printf("===== Modifier Machine %d =====\n", noeud->m.id);
        printf("===============================\n");
        printf("1. Nom de la machine\n");
        printf("2. Pokemon produit\n");
        printf("3. Temps de production\n");
        printf("4. Nombre maximum de figurines\n");
        printf("5. Cout de maintenance\n");
        printf("6. Etat de la machine\n");
        printf("7. Commande en cours\n");
        printf("0. Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nouveau nom: ");
                scanf("%s", noeud->m.nom);
                break;
            case 2:
                do {
                    printf("Nouveau Pokemon produit: ");
                    scanf("%d", &noeud->m.idPokemon);
                    if (rechercherPokemon(listePokemons, noeud->m.idPokemon) == NULL) {
                        printf("Reessayez! (Pokemon inexistant)\n");
                    }
                } while (rechercherPokemon(listePokemons, noeud->m.idPokemon) == NULL);
                break;
            case 3:
                printf("Nouveau temps de production: ");
                scanf("%d", &noeud->m.tempsProd);
                break;
            case 4:
                printf("Nouveau nombre max: ");
                scanf("%d", &noeud->m.nbMax);
                break;
            case 5:
                printf("Nouveau cout de maintenance: ");
                scanf("%f", &noeud->m.coutMaint);
                break;
            case 6:
                printf("Nouvel etat (0=Libre, 1=Occupee, 2=Maintenance): ");
                scanf("%d", &noeud->m.etat);
                break;
            case 7:
                do {
                    printf("Nouvelle commande en cours (0 pour aucune): ");
                    scanf("%d", &noeud->m.idCommande);
                    if (noeud->m.idCommande != 0 && rechercherCommande(listeCommandes, noeud->m.idCommande) == NULL) {
                        printf("Reessayez! (Commande inexistante)\n");
                    }
                } while (noeud->m.idCommande != 0 && rechercherCommande(listeCommandes, noeud->m.idCommande) == NULL);
                break;
            case 0:
                printf("Retour au menu precedent.\n");
                break;
            default:
                printf("Choix invalide\n");
        }
    } while (choix != 0);

    printf("Modification reussie.\n");
}

void supprimerMachine(ListeMachine** liste) {
    if (*liste == NULL) {
        printf("Aucune machine a supprimer.\n");
        return;
    }

    int id;
    printf("ID de la machine a supprimer: ");
    scanf("%d", &id);

    ListeMachine* courant = *liste;
    ListeMachine* pre = NULL;

    while (courant != NULL && courant->m.id != id) {
        pre = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Machine introuvable\n");
        return;
    }

    if (pre == NULL) {
        *liste = courant->suivant;
    }
    else {
        pre->suivant = courant->suivant;
    }

    free(courant);
    printf("Machine supprimee avec succes.\n");
}

void libererListeMachine(ListeMachine** liste) {
    ListeMachine* courant = *liste;
    while (courant != NULL) {
        ListeMachine* temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    *liste = NULL;
}

int compterMachines(ListeMachine* liste) {
    int count = 0;
    ListeMachine* courant = liste;
    while (courant != NULL) {
        count++;
        courant = courant->suivant;
    }
    return count;
}





void sauvegarderMachines(ListeMachine* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListeMachine* courant = liste;
    while (courant != NULL) {
        fprintf(fichier, "%d;%s;%d;%d;%d;%d;%.2f;%d;%d;%ld\n",
                courant->m.id,
                courant->m.nom,
                courant->m.idPokemon,
                courant->m.tempsProd,
                courant->m.nbMax,
                courant->m.compteur,
                courant->m.coutMaint,
                courant->m.etat,
                courant->m.idCommande,
                (long)courant->m.dateDisponibilite);
        courant = courant->suivant;
    }

    fclose(fichier);
    printf("Machines sauvegardees dans %s\n", nomFichier);
}

ListeMachine* chargerMachines(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier %s non trouve. Demarrage avec liste vide.\n", nomFichier);
        return NULL;
    }

    ListeMachine* liste = NULL;
    machine m;
    long dateDisp;

    while (fscanf(fichier, "%d;%[^;];%d;%d;%d;%d;%f;%d;%d;%ld\n",
                  &m.id, m.nom, &m.idPokemon, &m.tempsProd,
                  &m.nbMax, &m.compteur, &m.coutMaint,
                  &m.etat, &m.idCommande, &dateDisp) == 10) {
        m.dateDisponibilite = (time_t)dateDisp;
        ListeMachine* nouveau = (ListeMachine*)malloc(sizeof(ListeMachine));
        if (nouveau != NULL) {
            nouveau->m = m;
            nouveau->suivant = liste;
            liste = nouveau;

            if (m.id > idAuto) {
                idAuto = m.id;
            }
        }
    }

    fclose(fichier);
    printf("Machines chargees depuis %s\n", nomFichier);
    return liste;
}

