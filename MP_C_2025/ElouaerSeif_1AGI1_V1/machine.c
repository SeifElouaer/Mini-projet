#include "headers.h"

/****************Fonctions Développées**************************/

int genererId(){
    static int idAuto = 1;
    return idAuto++;
}

machine creerMachine(pokemon p[], int nbPokemons){
    machine m;
    m.id = genererId();
    printf("Nom de la machine : \n");
    scanf("%s", m.nom);
    do{
        printf("ID du Pokemon : \n");
        scanf("%d", &m.idPokemon);
    }while (rechercherPokemon(p, nbPokemons, m.idPokemon) == -1);
    printf("Temps de production d'une figurine : \n");
    scanf("%d", &m.tempsProd);
    printf("Nombre maximum de figurines avant maintenance : \n");
    scanf("%d", &m.nbMax);
    m.compteur = 0;
    printf("Cout de maintenance : \n");
    scanf("%f", &m.coutMaint);
    m.etat = 0;
    m.idCommande = 0;
    return m;
}

void ajouterMachine(machine m[],pokemon p[], int nbPokemons, int *n){
    if (*n >= MAX_TAILLE) {
        printf("ERREUR : Le tableau de machines est plein.\n");
    }
    else{
        m[*n] = creerMachine(p, nbPokemons);
        (*n)++;
        printf("Machine ajoutee\n");
    }
}

void afficherMachine(machine m ,commande Tab_Commande[], int n){
    int index;
    printf("-ID: %d", m.id);
    printf(" | Nom: %s", m.nom);
    printf(" | Pokemon produit: %d",m.idPokemon);
    printf(" | Temps de production: %d", m.tempsProd);
    printf(" | Nb max de figurines: %d", m.nbMax);
    printf(" | Compteur actuel: %d", m.compteur);
    printf(" | Cout de maintenance: %.2f", m.coutMaint);
    printf(" | Etat de la machine: ");
    switch (m.etat) {
        case 0:
            printf(" Libre\n");
            break;
        case 1:
            printf(" Occupee\n");
            break;
        case 2:
            printf(" En attente de maintenance\n");
            break;
    }
    if (m.idCommande == 0) {
        printf("Aucune commande en cours\n");
    }
    else{
        index = chercherCommande(Tab_Commande, n, m.idCommande);
        if (index == -1){
            printf("commande n'existe pas");
        }
        else{
            printf("##Commande en cours :\n -ID: %d\n -Quantite: %d\n",m.idCommande,Tab_Commande[index].quantite);
        }
    }
}
void afficherMachines(machine m[], commande Tab_Commande[], int n){
    int i;
    if (n == 0) {
        printf("Aucune machine a afficher.\n");
    }
    for (int i = 0; i < n; i++) {
        printf("#### Machine %d ####\n",i+1);
        afficherMachine(m[i] ,Tab_Commande, n);
    }
}

int chercherMachine(machine m[],int *n,int id){
    int i;
    for(i=0;i<n;i++){
        if (m[i].id == id) {
            return i;
        }
    }
    return -1;
}

void modifierMachine(machine m[], pokemon p[], commande c[], int n, int nbPokemons, int nbCommandes){
    int id, choix, index;
    if (n == 0) {
        printf("Aucune machine trouvee\n");
    }
    else{
        printf("ID de machine a modifier : ");
        scanf("%d", &id);
        index = chercherMachine(m, &n, id);
        if (index == -1){
            printf("Machine introuvable\n");
        }
        else{
            do{
                printf(" Modifier Machine %d \n",m[index].id);
                printf("1. Nom de machine\n");
                printf("2. Pokemon produit\n");
                printf("3. Temps de production d’une figurine \n");
                printf("4. Nombre maximum de figurines\n");
                printf("5. Cout de maintenance\n");
                printf("6. Etat de la machine\n");
                printf("7. Commande en cours\n");
                printf("0. Retour au menu\n");
                printf("Choix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        printf("Nouveau nom : ");
                        scanf(" %s", m[index].nom);
                        break;
                    case 2:
                        do{
                            printf("Nouveau Pokemon produit : ");
                            scanf("%d", &m[index].idPokemon);
                        }while(rechercherPokemon(p, nbPokemons,m[index].idPokemon) == -1);
                        break;
                    case 3:
                        printf("Nouveau Temps de production : ");
                        scanf("%d", &m[index].tempsProd);
                        break;
                    case 4:
                        printf("Nouveau nb max de figurines : ");
                        scanf("%d", &m[index].nbMax);
                        break;
                    case 5:
                        printf("Nouveau Cout de maintenance : ");
                        scanf("%f", &m[index].coutMaint);
                        break;
                    case 6:
                        printf("Nouveau Etat de la machine : ");  //(0=LIBRE, 1=OCCUPEE, 2=EN ATTENTE DE MAINTENANCE)
                        scanf("%d", &m[index].etat);
                        break;
                    case 7:
                        do{
                            printf("Nouvelle commande en cours");
                            scanf("%d",&m[index].idCommande);
                        }while(chercherCommande(c, nbCommandes, m[index].idCommande)==-1);
                        break;
                    case 0:
                        printf("Retour au menu precedent.\n");
                        break;
                    default:
                        printf("Choix invalide\n");
                }
            } while (choix < 0 || choix > 7);
        }
        printf("Modification reussie\n");
    }
}
void supprimerMachine(machine m[], int *n){
    int id, i, pos;
    printf("ID de machine a supprimer : ");
    scanf("%d", &id);
    if (*n == 0) {
        printf("Aucune machine a supprimer.\n");
    }
    else{
        pos = chercherMachine(m, n, id);
        if (pos == -1){
            printf("Machine introuvable\n");
        }
        else{
            for(i=pos;i<(*n);i++){
                m[i] = m[i+1];
            }
            (*n)--;
            printf("Machine supprimée\n");
        }
    }
}
