#include "headers.h"

static int compteurIdMachine = 0;

int genererIdMachine() {
    return ++compteurIdMachine;
}

machine creerMachine(ListePokemon* listePokemons) {
    machine m;
    m.id = genererIdMachine();

    printf("Nom de la machine: ");
    scanf("%s", m.nom);

    do {
        printf("ID du Pokemon produit: ");
        scanf("%d", &m.idPokemon);
        if (rechercherPokemon(listePokemons, m.idPokemon) == NULL) {
            printf("Pokemon inexistant. Veuillez reessayer.\n");
        }
    } while (rechercherPokemon(listePokemons, m.idPokemon) == NULL);

    printf("Temps de production d'une figurine (en minutes): ");
    scanf("%d", &m.tempsProd);

    printf("Nombre maximum de figurines avant maintenance: ");
    scanf("%d", &m.nbMax);

    m.compteur = 0;

    printf("Cout de maintenance: ");
    scanf("%f", &m.coutMaint);

    m.etat = 0; // Libre
    m.idCommande = 0; // Aucune commande
    m.dateDisponibilite = 0; // Disponible immédiatement

    return m;
}

void ajouterMachine(ListeMachine** liste, ListePokemon* listePokemons) {
    ListeMachine* nouveau = (ListeMachine*)malloc(sizeof(ListeMachine));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }

    nouveau->data = creerMachine(listePokemons);
    nouveau->next = *liste;
    *liste = nouveau;
    printf("Machine ajoutee avec succes.\n");
}

void afficherMachine(machine m, ListeCommande* listeCommandes) {
    printf("- ID: %d | Nom: %s | Pokemon: %d\n", m.id, m.nom, m.idPokemon);
    printf("  Temps prod: %d min | Max: %d | Compteur: %d\n",
           m.tempsProd, m.nbMax, m.compteur);
    printf("  Cout maint: %.2f | Etat: ", m.coutMaint);

    switch (m.etat) {
        case 0:
            printf("Libre\n");
            break;
        case 1:
            printf("Occupee");
            if (m.dateDisponibilite > 0) {
                time_t maintenant = time(NULL);
                double secondesRestantes = difftime(m.dateDisponibilite, maintenant);
                if (secondesRestantes > 0) {
                    int minutesRestantes = (int)(secondesRestantes / 60);
                    printf(" (disponible dans %d minutes)", minutesRestantes);
                } else {
                    printf(" (production terminee)");
                }
            }
            printf("\n");
            break;
        case 2:
            printf("En attente de maintenance\n");
            break;
        default:
            printf("Inconnu\n");
    }

    if (m.idCommande == 0) {
        printf("  Aucune commande en cours\n");
    } else {
        ListeCommande* cmd = rechercherCommande(listeCommandes, m.idCommande);
        if (cmd != NULL) {
            printf("  Commande en cours: ID=%d, Quantite=%d\n",
                   cmd->data.id, cmd->data.quantite);
        }
    }
}

void afficherMachines(ListeMachine* liste, ListeCommande* listeCommandes) {
    if (liste == NULL) {
        printf("Aucune machine.\n");
        return;
    }

    ListeMachine* current = liste;
    int count = 1;
    while (current != NULL) {
        printf("#### Machine %d ####\n", count++);
        afficherMachine(current->data, listeCommandes);
        current = current->next;
    }
}

ListeMachine* rechercherMachine(ListeMachine* liste, int id) {
    ListeMachine* current = liste;
    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

ListeMachine* rechercherMachineParPokemon(ListeMachine* liste, int idPokemon) {
    ListeMachine* current = liste;
    while (current != NULL) {
        if (current->data.idPokemon == idPokemon) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifierMachine(ListeMachine* liste, ListePokemon* listePokemons, ListeCommande* listeCommandes) {
    if (liste == NULL) {
        printf("Aucune machine.\n");
        return;
    }

    int id, choix;
    printf("ID de la machine a modifier: ");
    scanf("%d", &id);

    ListeMachine* node = rechercherMachine(liste, id);
    if (node == NULL) {
        printf("Machine introuvable.\n");
        return;
    }

    do {
        printf("\n===== Modifier Machine %d =====\n", node->data.id);
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
                scanf("%s", node->data.nom);
                break;
            case 2:
                do {
                    printf("Nouveau Pokemon produit: ");
                    scanf("%d", &node->data.idPokemon);
                    if (rechercherPokemon(listePokemons, node->data.idPokemon) == NULL) {
                        printf("Pokemon inexistant. Reessayez.\n");
                    }
                } while (rechercherPokemon(listePokemons, node->data.idPokemon) == NULL);
                break;
            case 3:
                printf("Nouveau temps de production: ");
                scanf("%d", &node->data.tempsProd);
                break;
            case 4:
                printf("Nouveau nombre max: ");
                scanf("%d", &node->data.nbMax);
                break;
            case 5:
                printf("Nouveau cout de maintenance: ");
                scanf("%f", &node->data.coutMaint);
                break;
            case 6:
                printf("Nouvel etat (0=Libre, 1=Occupee, 2=Maintenance): ");
                scanf("%d", &node->data.etat);
                break;
            case 7:
                do {
                    printf("Nouvelle commande en cours (0 pour aucune): ");
                    scanf("%d", &node->data.idCommande);
                    if (node->data.idCommande != 0 &&
                        rechercherCommande(listeCommandes, node->data.idCommande) == NULL) {
                        printf("Commande inexistante. Reessayez.\n");
                    }
                } while (node->data.idCommande != 0 &&
                         rechercherCommande(listeCommandes, node->data.idCommande) == NULL);
                break;
            case 0:
                printf("Retour au menu precedent.\n");
                break;
            default:
                printf("Choix invalide.\n");
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

    ListeMachine* current = *liste;
    ListeMachine* prev = NULL;

    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Machine introuvable.\n");
        return;
    }

    if (prev == NULL) {
        *liste = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Machine supprimee avec succes.\n");
}

void libererListeMachine(ListeMachine** liste) {
    ListeMachine* current = *liste;
    while (current != NULL) {
        ListeMachine* temp = current;
        current = current->next;
        free(temp);
    }
    *liste = NULL;
}

int compterMachines(ListeMachine* liste) {
    int count = 0;
    ListeMachine* current = liste;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Fonctions de gestion des fichiers
void sauvegarderMachines(ListeMachine* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListeMachine* current = liste;
    while (current != NULL) {
        fprintf(fichier, "%d;%s;%d;%d;%d;%d;%.2f;%d;%d;%ld\n",
                current->data.id,
                current->data.nom,
                current->data.idPokemon,
                current->data.tempsProd,
                current->data.nbMax,
                current->data.compteur,
                current->data.coutMaint,
                current->data.etat,
                current->data.idCommande,
                (long)current->data.dateDisponibilite);
        current = current->next;
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
            nouveau->data = m;
            nouveau->next = liste;
            liste = nouveau;

            if (m.id > compteurIdMachine) {
                compteurIdMachine = m.id;
            }
        }
    }

    fclose(fichier);
    printf("Machines chargees depuis %s\n", nomFichier);
    return liste;
}
#ifdef GUI

extern ListeMachine* listeMachines;
extern ListeCommande* listeCommandes;
extern ListePokemon* listePokemons;

// Ajout
static bool ajoutInit = false;
static TextBox *tbNom   = NULL;
static TextBox *tbCapacite = NULL;
static TextBox *tbTemps = NULL;
static TextBox *tbCout  = NULL;

// Modifier
static bool modifInit = false;
static TextBox *tbModifID   = NULL;
static TextBox *tbModifNom  = NULL;
static TextBox *tbModifCap  = NULL;
static TextBox *tbModifTps  = NULL;
static TextBox *tbModifCout = NULL;
static ScrollableList *machListModif = NULL;
static char machLabModif[MAX_ITEMS][200];

// Supprimer
static bool suppInit = false;
static TextBox *tbSuppID = NULL;
static ScrollableList *machListSupp = NULL;
static char machLabSupp[MAX_ITEMS][200];

// Afficher
static bool affInit = false;
static ScrollableList *machineListAff = NULL;
static char machineLabelsAff[MAX_ITEMS][200];

static void fillMachList(ScrollableList* list, char labels[][200])
{
    if (!list) return;
    UI_ListClear(list);
    ListeMachine* tmp = listeMachines; int i = 0;
    while (tmp && i < MAX_ITEMS)
    {
        const char* et = (tmp->data.etat==0)?"Libre":(tmp->data.etat==1)?"Occupee":"Maintenance";
        sprintf(labels[i], "ID:%-3d | %-10s | Cap:%d | Tps:%d | Cout:%.2f | %s | Cmd:%d",
                tmp->data.id, tmp->data.nom, tmp->data.nbMax,
                tmp->data.tempsProd, tmp->data.coutMaint, et, tmp->data.idCommande);
        UI_ListAddItem(list, labels[i]);
        tmp = tmp->next; i++;
    }
}

void RefreshMachineListAff() { fillMachList(machineListAff, machineLabelsAff); fillMachList(machListModif, machLabModif); fillMachList(machListSupp, machLabSupp); }
void RefreshMachineList() {}
void initMachineUI() {}

// ===== MENU PRINCIPAL =====
void menuMachineGUI(Ecran *ecranActuel)
{
    DrawText("GESTION MACHINES", 280, 50, 30, WHITE);
    if (bouton((Rectangle){300, 140, 280, 50}, "Ajouter Machine"))   *ecranActuel = ECRAN_MACHINE_AJOUT;
    if (bouton((Rectangle){300, 210, 280, 50}, "Modifier Machine"))  *ecranActuel = ECRAN_MACHINE_MODIF;
    if (bouton((Rectangle){300, 280, 280, 50}, "Supprimer Machine")) *ecranActuel = ECRAN_MACHINE_SUPP;
    if (bouton((Rectangle){300, 350, 280, 50}, "Afficher Machines")) *ecranActuel = ECRAN_MACHINE_AFF;
    if (bouton((Rectangle){300, 440, 280, 50}, "Retour"))            *ecranActuel = ECRAN_MENU;
}

// ===== AJOUTER =====
// Titre y=50, labels y=105/160/215/270, textboxes y=125/180/235/290, boutons y=345/410
void machineAjoutGUI(Ecran *ecranActuel)
{
    if (!ajoutInit)
    {
        UI_Clear();
        tbNom      = UI_CreateTextBox((Rectangle){320, 125, 250, 38}, 20);
        tbCapacite = UI_CreateTextBox((Rectangle){320, 180, 250, 38}, 10);
        tbTemps    = UI_CreateTextBox((Rectangle){320, 235, 250, 38}, 10);
        tbCout     = UI_CreateTextBox((Rectangle){320, 290, 250, 38}, 10);
        ajoutInit  = true;
    }
    UI_UpdateAndDraw();
    DrawText("AJOUTER MACHINE", 295, 50, 30, WHITE);
    DrawText("Nom :",        215, 105, 20, WHITE);
    DrawText("Capacite :",   215, 160, 20, WHITE);
    DrawText("Temps prod :", 215, 215, 20, WHITE);
    DrawText("Cout maint :", 215, 270, 20, WHITE);
    DrawText("(ID genere automatiquement)", 215, 340, 15, (Color){180,180,180,255});

    if (bouton((Rectangle){320, 360, 250, 45}, "Valider"))
    {
        if (strlen(tbNom->text) > 0)
        {
            ListeMachine* m = (ListeMachine*)malloc(sizeof(ListeMachine));
            if (m) {
                m->data.id = genererIdMachine();
                strcpy(m->data.nom, tbNom->text);
                m->data.nbMax = atoi(tbCapacite->text);
                m->data.tempsProd = atoi(tbTemps->text);
                m->data.coutMaint = atof(tbCout->text);
                m->data.compteur=0; m->data.etat=0;
                m->data.idCommande=0; m->data.idPokemon=0;
                m->data.dateDisponibilite=0;
                m->next = listeMachines; listeMachines = m;
                printf("Machine ajoutee : %s (ID:%d)\n", m->data.nom, m->data.id);
                tbNom->text[0]='\0'; tbCapacite->text[0]='\0';
                tbTemps->text[0]='\0'; tbCout->text[0]='\0';
            }
        } else printf("Nom obligatoire.\n");
    }
    if (bouton((Rectangle){320, 420, 250, 45}, "Retour"))
    { UI_Clear(); ajoutInit=false; *ecranActuel=ECRAN_MACHINE_MENU; }
}

// ===== MODIFIER (avec scrollable) =====
// Colonne gauche x=10 w=170, labels y=70/125/180/235/290, textboxes y=90/145/200/255/310
// Scrollable x=190 y=70 w=700 h=430
void machineModifGUI(Ecran *ecranActuel)
{
    if (!modifInit)
    {
        UI_Clear();
        tbModifID   = UI_CreateTextBox((Rectangle){10,  90, 170, 33}, 10);
        tbModifNom  = UI_CreateTextBox((Rectangle){10, 145, 170, 33}, 20);
        tbModifCap  = UI_CreateTextBox((Rectangle){10, 200, 170, 33}, 10);
        tbModifTps  = UI_CreateTextBox((Rectangle){10, 255, 170, 33}, 10);
        tbModifCout = UI_CreateTextBox((Rectangle){10, 310, 170, 33}, 10);
        machListModif = UI_CreateList((Rectangle){190, 70, 700, 430});
        modifInit = true;
        fillMachList(machListModif, machLabModif);
    }
    UI_UpdateAndDraw();

    DrawText("MODIFIER MACHINE", 285, 15, 28, WHITE);
    DrawText("ID :",        10, 70,  17, WHITE);
    DrawText("Nom :",       10, 125, 17, WHITE);
    DrawText("Capacite :",  10, 180, 17, WHITE);
    DrawText("Temps :",     10, 235, 17, WHITE);
    DrawText("Cout :",      10, 290, 17, WHITE);
    DrawText("vide=inchange", 10, 350, 13, (Color){180,180,180,255});
    DrawText("Machines :", 190, 52, 17, WHITE);

    if (bouton((Rectangle){10, 370, 170, 40}, "Valider"))
    {
        int id = atoi(tbModifID->text);
        if (id > 0) {
            ListeMachine* node = rechercherMachine(listeMachines, id);
            if (node) {
                if (strlen(tbModifNom->text)  > 0) strcpy(node->data.nom, tbModifNom->text);
                if (strlen(tbModifCap->text)  > 0) node->data.nbMax = atoi(tbModifCap->text);
                if (strlen(tbModifTps->text)  > 0) node->data.tempsProd = atoi(tbModifTps->text);
                if (strlen(tbModifCout->text) > 0) node->data.coutMaint = atof(tbModifCout->text);
                printf("Machine %d modifiee.\n", id);
                tbModifID->text[0]='\0'; tbModifNom->text[0]='\0';
                tbModifCap->text[0]='\0'; tbModifTps->text[0]='\0'; tbModifCout->text[0]='\0';
                fillMachList(machListModif, machLabModif);
            } else printf("Machine introuvable.\n");
        }
    }
    if (bouton((Rectangle){10, 425, 170, 40}, "Retour"))
    { UI_Clear(); modifInit=false; *ecranActuel=ECRAN_MACHINE_MENU; }
}

// ===== SUPPRIMER (avec scrollable) =====
void machineSuppGUI(Ecran *ecranActuel)
{
    if (!suppInit)
    {
        UI_Clear();
        tbSuppID     = UI_CreateTextBox((Rectangle){10, 150, 170, 35}, 10);
        machListSupp = UI_CreateList((Rectangle){190, 70, 700, 430});
        suppInit = true;
        fillMachList(machListSupp, machLabSupp);
    }
    UI_UpdateAndDraw();

    DrawText("SUPPRIMER MACHINE", 270, 15, 28, WHITE);
    DrawText("ID a supprimer :", 10, 130, 17, WHITE);
    DrawText("Machines :", 190, 52, 17, WHITE);

    if (bouton((Rectangle){10, 205, 170, 40}, "Supprimer"))
    {
        int id = atoi(tbSuppID->text);
        if (id > 0) {
            ListeMachine* cur=listeMachines; ListeMachine* prev=NULL;
            while (cur && cur->data.id!=id) { prev=cur; cur=cur->next; }
            if (cur) {
                if (prev) prev->next=cur->next; else listeMachines=cur->next;
                free(cur);
                printf("Machine %d supprimee.\n", id);
                tbSuppID->text[0]='\0';
                fillMachList(machListSupp, machLabSupp);
            } else printf("Machine introuvable.\n");
        }
    }
    if (bouton((Rectangle){10, 260, 170, 40}, "Retour"))
    { UI_Clear(); suppInit=false; *ecranActuel=ECRAN_MACHINE_MENU; }
}

// ===== AFFICHER =====
void machineAffGUI(Ecran *ecranActuel)
{
    if (!affInit)
    {
        UI_Clear();
        machineListAff = UI_CreateList((Rectangle){60, 80, 770, 410});
        fillMachList(machineListAff, machineLabelsAff);
        affInit = true;
    }
    UI_UpdateAndDraw();
    DrawText("LISTE DES MACHINES", 270, 30, 30, WHITE);
    if (bouton((Rectangle){330, 510, 230, 45}, "Retour"))
    { UI_Clear(); affInit=false; *ecranActuel=ECRAN_MACHINE_MENU; }
}

void modifierMachineGUI() {}
void supprimerMachineGUI() {}
void afficherMachinesListeGUI() {}

#endif
