#include "headers.h"

static int compteurIdCommande = 0;

int genererIdCommande() {
    return ++compteurIdCommande;
}

commande creerCommande(ListePokemon* listePokemons) {
    commande c;
    c.id = genererIdCommande();

    printf("ID du client: ");
    scanf("%d", &c.matriculeClient);

    do {
        printf("ID du pokemon: ");
        scanf("%d", &c.idPokemon);
        if (rechercherPokemon(listePokemons, c.idPokemon) == NULL) {
            printf("Pokemon inexistant. Veuillez reessayer.\n");
        }
    } while (rechercherPokemon(listePokemons, c.idPokemon) == NULL);

    printf("Quantite: ");
    scanf("%d", &c.quantite);

    c.quantiteProduite = 0; // Initialiser à 0

    time_t t;
    time(&t);
    strcpy(c.dateHeure, ctime(&t));
    c.dateHeure[strlen(c.dateHeure) - 1] = '\0'; // Enlever le \n

    c.etat = 0; // En attente
    printf("Date et heure d'emission: %s\n", c.dateHeure);

    return c;
}

void ajouterCommande(ListeCommande** liste, ListePokemon* listePokemons) {
    ListeCommande* nouveau = (ListeCommande*)malloc(sizeof(ListeCommande));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }

    nouveau->data = creerCommande(listePokemons);
    nouveau->next = *liste;
    *liste = nouveau;
    printf("Commande ajoutee avec succes.\n");
}

void afficherCommande(commande c) {
    printf("- ID: %d | Client: %d | Pokemon: %d | Quantite: %d/%d\n",
           c.id, c.matriculeClient, c.idPokemon, c.quantiteProduite, c.quantite);
    printf("  Date/Heure: %s | Etat: ", c.dateHeure);
    switch (c.etat) {
        case 0: printf("En attente\n"); break;
        case 1: printf("En cours\n"); break;
        case 2: printf("Realisee\n"); break;
        default: printf("Inconnu\n");
    }
}

void afficherCommandes(ListeCommande* liste) {
    if (liste == NULL) {
        printf("Aucune commande.\n");
        return;
    }

    ListeCommande* current = liste;
    int count = 1;
    while (current != NULL) {
        printf("#### Commande %d ####\n", count++);
        afficherCommande(current->data);
        current = current->next;
    }
}

ListeCommande* rechercherCommande(ListeCommande* liste, int id) {
    ListeCommande* current = liste;
    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifierCommande(ListeCommande* liste, ListePokemon* listePokemons) {
    if (liste == NULL) {
        printf("Aucune commande.\n");
        return;
    }

    int id, choix;
    printf("ID de la commande a modifier: ");
    scanf("%d", &id);

    ListeCommande* node = rechercherCommande(liste, id);
    if (node == NULL) {
        printf("Commande introuvable.\n");
        return;
    }

    do {
        printf("\n===== Modifier Commande %d =====\n", node->data.id);
        printf("1. ID du pokemon commande\n");
        printf("2. Quantite\n");
        printf("3. Etat de la commande\n");
        printf("0. Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                do {
                    printf("Nouveau ID du Pokemon: ");
                    scanf("%d", &node->data.idPokemon);
                    if (rechercherPokemon(listePokemons, node->data.idPokemon) == NULL) {
                        printf("Pokemon inexistant. Reessayez.\n");
                    }
                } while (rechercherPokemon(listePokemons, node->data.idPokemon) == NULL);
                break;
            case 2:
                printf("Nouvelle quantite: ");
                scanf("%d", &node->data.quantite);
                break;
            case 3:
                printf("Nouvel etat (0=En attente, 1=En cours, 2=Realisee): ");
                scanf("%d", &node->data.etat);
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

void supprimerCommande(ListeCommande** liste) {
    if (*liste == NULL) {
        printf("Aucune commande a supprimer.\n");
        return;
    }

    int id;
    printf("ID de la commande a supprimer: ");
    scanf("%d", &id);

    ListeCommande* current = *liste;
    ListeCommande* prev = NULL;

    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Commande introuvable.\n");
        return;
    }

    printf("\n>>> Confirmation <<<\n");
    printf("Supprimer la commande ID:%d (Pokemon:%d, Quantite:%d, Etat:%s) ? (o/n): ",
           current->data.id, current->data.idPokemon, current->data.quantite,
           (current->data.etat==0)?"En attente":(current->data.etat==1)?"En cours":"Realisee");
    char rep[4];
    scanf("%s", rep);
    if (rep[0] != 'o' && rep[0] != 'O') {
        printf("Suppression annulee.\n");
        return;
    }

    if (prev == NULL) {
        *liste = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Commande supprimee avec succes.\n");
}

void libererListeCommande(ListeCommande** liste) {
    ListeCommande* current = *liste;
    while (current != NULL) {
        ListeCommande* temp = current;
        current = current->next;
        free(temp);
    }
    *liste = NULL;
}

int compterCommandes(ListeCommande* liste) {
    int count = 0;
    ListeCommande* current = liste;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Fonctions de gestion des fichiers
void sauvegarderCommandes(ListeCommande* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListeCommande* current = liste;
    while (current != NULL) {
        fprintf(fichier, "%d;%d;%d;%d;%d;%s;%d\n",
                current->data.id,
                current->data.matriculeClient,
                current->data.idPokemon,
                current->data.quantite,
                current->data.quantiteProduite,
                current->data.dateHeure,
                current->data.etat);
        current = current->next;
    }

    fclose(fichier);
    printf("Commandes sauvegardees dans %s\n", nomFichier);
}

ListeCommande* chargerCommandes(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier %s non trouve. Demarrage avec liste vide.\n", nomFichier);
        return NULL;
    }

    ListeCommande* liste = NULL;
    commande c;

    while (fscanf(fichier, "%d;%d;%d;%d;%d;%[^;];%d\n",
                  &c.id, &c.matriculeClient, &c.idPokemon,
                  &c.quantite, &c.quantiteProduite, c.dateHeure, &c.etat) == 7) {
        ListeCommande* nouveau = (ListeCommande*)malloc(sizeof(ListeCommande));
        if (nouveau != NULL) {
            nouveau->data = c;
            nouveau->next = liste;
            liste = nouveau;

            if (c.id > compteurIdCommande) {
                compteurIdCommande = c.id;
            }
        }
    }

    fclose(fichier);
    printf("Commandes chargees depuis %s\n", nomFichier);
    return liste;
}
#ifdef GUI

extern ListeCommande* listeCommandes;
extern ListePokemon*  listePokemons;
extern ListeClient*   listeClients;

// Ajout
static TextBox* tbCliId  = NULL;
static TextBox* tbPokId  = NULL;
static TextBox* tbQte    = NULL;
static ScrollableList* pokListAjout = NULL;
static ScrollableList* cliListAjout = NULL;
static bool cmdAjoutInit = false;
static char pokLabAjout[MAX_ITEMS][128];
static char cliLabAjout[MAX_ITEMS][128];

// Modifier
static TextBox* tbModId  = NULL;
static TextBox* tbModQte = NULL;
static ScrollableList* cmdListMod = NULL;
static bool cmdModifInit = false;
static char cmdLabMod[MAX_ITEMS][200];

// Supprimer
static TextBox* tbSuppId = NULL;
static ScrollableList* cmdListSupp = NULL;
static bool cmdSuppInit = false;
static char cmdLabSupp[MAX_ITEMS][200];

// Afficher
static ScrollableList* cmdListAff = NULL;
static char cmdLabAff[MAX_ITEMS][200];
static bool cmdAffInit = false;

static void fillCmdList(ScrollableList* list, char labels[][200])
{
    if (!list) return;
    UI_ListClear(list);
    ListeCommande* tmp = listeCommandes; int i = 0;
    while (tmp && i < MAX_ITEMS)
    {
        const char* et = (tmp->data.etat==0)?"Attente":(tmp->data.etat==1)?"En cours":"Realisee";
        sprintf(labels[i], "ID:%-3d | Cli:%-3d | Pok:%-3d | %d/%d | %s",
                tmp->data.id, tmp->data.matriculeClient, tmp->data.idPokemon,
                tmp->data.quantiteProduite, tmp->data.quantite, et);
        UI_ListAddItem(list, labels[i]);
        tmp = tmp->next; i++;
    }
}

static void fillPokAjout()
{
    if (!pokListAjout) return;
    UI_ListClear(pokListAjout);
    ListePokemon* tmp = listePokemons; int i = 0;
    while (tmp && i < MAX_ITEMS)
    {
        sprintf(pokLabAjout[i], "ID:%-4d %-12s %.2f", tmp->data.id, tmp->data.nom, tmp->data.prix);
        UI_ListAddItem(pokListAjout, pokLabAjout[i]);
        tmp = tmp->next; i++;
    }
}

static void fillCliAjout()
{
    if (!cliListAjout) return;
    UI_ListClear(cliListAjout);
    ListeClient* tmp = listeClients; int i = 0;
    while (tmp && i < MAX_ITEMS)
    {
        sprintf(cliLabAjout[i], "ID:%-3d %s", tmp->data.matricule, tmp->data.nom);
        UI_ListAddItem(cliListAjout, cliLabAjout[i]);
        tmp = tmp->next; i++;
    }
}

// ===== MENU PRINCIPAL =====
void menuCommandeGUI(Ecran *ecranActuel)
{
    DrawText("GESTION DES COMMANDES", 210, 50, 30, WHITE);
    if (bouton((Rectangle){300, 140, 280, 50}, "Ajouter Commande"))   *ecranActuel = ECRAN_COMMANDE_AJOUT;
    if (bouton((Rectangle){300, 210, 280, 50}, "Modifier Commande"))  *ecranActuel = ECRAN_COMMANDE_MODIF;
    if (bouton((Rectangle){300, 280, 280, 50}, "Supprimer Commande")) *ecranActuel = ECRAN_COMMANDE_SUPP;
    if (bouton((Rectangle){300, 350, 280, 50}, "Afficher Commandes")) *ecranActuel = ECRAN_COMMANDE_AFF;
    if (bouton((Rectangle){300, 450, 280, 50}, "Retour"))             *ecranActuel = ECRAN_MENU;
}

// ===== AJOUTER =====
// Colonne gauche x=10 w=165 : labels y=70/125/180, textboxes y=90/145/200
// Scrollable clients x=180 y=70 w=330 h=250
// Scrollable pokemons x=520 y=70 w=370 h=250
// Boutons y=310/370
void commandeAjoutGUI(Ecran *ecranActuel)
{
    if (!cmdAjoutInit)
    {
        UI_Clear();
        tbCliId = UI_CreateTextBox((Rectangle){10,  90, 165, 33}, 10);
        tbPokId = UI_CreateTextBox((Rectangle){10, 145, 165, 33}, 10);
        tbQte   = UI_CreateTextBox((Rectangle){10, 200, 165, 33}, 10);
        cliListAjout = UI_CreateList((Rectangle){180, 70, 330, 250});
        pokListAjout = UI_CreateList((Rectangle){520, 70, 370, 250});
        cmdAjoutInit = true;
        fillCliAjout();
        fillPokAjout();
    }
    UI_UpdateAndDraw();

    DrawText("AJOUTER COMMANDE", 275, 15, 28, WHITE);
    DrawText("ID Client :",  10, 70,  17, WHITE);
    DrawText("ID Pokemon :", 10, 125, 17, WHITE);
    DrawText("Quantite :",   10, 180, 17, WHITE);
    DrawText("Clients :",    180, 52, 17, WHITE);
    DrawText("Pokemons :",   520, 52, 17, WHITE);

    if (bouton((Rectangle){10, 250, 165, 40}, "Ajouter"))
    {
        int idCli = atoi(tbCliId->text);
        int idPok = atoi(tbPokId->text);
        int qte   = atoi(tbQte->text);
        if (idCli>0 && idPok>0 && qte>0
            && rechercherPokemon(listePokemons,idPok) != NULL
            && rechercherClient(listeClients,idCli)   != NULL)
        {
            ListeCommande* n = (ListeCommande*)malloc(sizeof(ListeCommande));
            if (n) {
                n->data.id = genererIdCommande();
                n->data.matriculeClient = idCli; n->data.idPokemon = idPok;
                n->data.quantite = qte; n->data.quantiteProduite = 0; n->data.etat = 0;
                time_t t; time(&t); strcpy(n->data.dateHeure, ctime(&t));
                n->data.dateHeure[strlen(n->data.dateHeure)-1] = '\0';
                n->next = listeCommandes; listeCommandes = n;
                tbCliId->text[0]='\0'; tbPokId->text[0]='\0'; tbQte->text[0]='\0';
                UI_Notif(TextFormat("Commande ajoutee avec succes (ID:%d).", n->data.id), NOTIF_SUCCES);
            }
        } else {
            if (idCli<=0 || !rechercherClient(listeClients,idCli))   UI_Notif("Client invalide. Verifiez l'ID client.", NOTIF_ERREUR);
            else if (idPok<=0 || !rechercherPokemon(listePokemons,idPok)) UI_Notif("Pokemon invalide. Verifiez l'ID pokemon.", NOTIF_ERREUR);
            else UI_Notif("Quantite invalide (doit etre > 0).", NOTIF_ERREUR);
        }
    }
    if (bouton((Rectangle){10, 305, 165, 40}, "Retour"))
    { UI_Clear(); cmdAjoutInit=false; *ecranActuel=ECRAN_COMMANDE_MENU; }
}

// ===== MODIFIER =====
// label y=70/125, textboxes y=90/145, scrollable x=190 y=70 w=700 h=430, boutons y=195/250
void commandeModifGUI(Ecran *ecranActuel)
{
    if (!cmdModifInit)
    {
        UI_Clear();
        tbModId  = UI_CreateTextBox((Rectangle){10,  90, 170, 33}, 10);
        tbModQte = UI_CreateTextBox((Rectangle){10, 145, 170, 33}, 10);
        cmdListMod = UI_CreateList((Rectangle){190, 70, 700, 430});
        cmdModifInit = true;
        fillCmdList(cmdListMod, cmdLabMod);
    }
    UI_UpdateAndDraw();

    DrawText("MODIFIER COMMANDE", 268, 15, 28, WHITE);
    DrawText("ID Commande :",  10, 70,  17, WHITE);
    DrawText("Nv Quantite :", 10, 125, 17, WHITE);
    DrawText("Commandes :", 190, 52, 17, WHITE);

    if (bouton((Rectangle){10, 198, 170, 40}, "Valider"))
    {
        int id  = atoi(tbModId->text);
        int qte = atoi(tbModQte->text);
        if (id>0 && qte>0) {
            ListeCommande* node = rechercherCommande(listeCommandes, id);
            if (node) {
                node->data.quantite = qte;
                UI_Notif(TextFormat("Commande %d modifiee avec succes.", id), NOTIF_SUCCES);
                tbModId->text[0]='\0'; tbModQte->text[0]='\0';
                fillCmdList(cmdListMod, cmdLabMod);
            } else UI_Notif("Commande introuvable. Verifiez l'ID.", NOTIF_ERREUR);
        }
    }
    if (bouton((Rectangle){10, 253, 170, 40}, "Retour"))
    { UI_Clear(); cmdModifInit=false; *ecranActuel=ECRAN_COMMANDE_MENU; }
}

// ===== SUPPRIMER =====
void commandeSuppGUI(Ecran *ecranActuel)
{
    if (!cmdSuppInit)
    {
        UI_Clear();
        tbSuppId    = UI_CreateTextBox((Rectangle){10, 150, 170, 35}, 10);
        cmdListSupp = UI_CreateList((Rectangle){190, 70, 700, 430});
        cmdSuppInit = true;
        fillCmdList(cmdListSupp, cmdLabSupp);
    }
    UI_UpdateAndDraw();

    DrawText("SUPPRIMER COMMANDE", 252, 15, 28, WHITE);
    DrawText("ID a supprimer :", 10, 130, 17, WHITE);
    DrawText("Commandes :", 190, 52, 17, WHITE);

    // Gestion popup confirmation
    static int cmdSuppPendingID = 0;
    int popupRes = UI_PopupDraw();
    if (popupRes == 1 && cmdSuppPendingID > 0)
    {
        ListeCommande* cur=listeCommandes; ListeCommande* prev=NULL;
        while (cur && cur->data.id!=cmdSuppPendingID) { prev=cur; cur=cur->next; }
        if (cur) {
            if (prev) prev->next=cur->next; else listeCommandes=cur->next;
            free(cur);
            UI_Notif(TextFormat("Commande %d supprimee.", cmdSuppPendingID), NOTIF_SUCCES);
            tbSuppId->text[0]='\0';
            fillCmdList(cmdListSupp, cmdLabSupp);
        }
        cmdSuppPendingID = 0;
    }
    else if (popupRes == -1) { cmdSuppPendingID = 0; UI_Notif("Suppression annulee.", NOTIF_INFO); }

    if (bouton((Rectangle){10, 205, 170, 40}, "Supprimer"))
    {
        int id = atoi(tbSuppId->text);
        if (id > 0) {
            ListeCommande* cur = listeCommandes;
            while (cur && cur->data.id != id) cur = cur->next;
            if (cur) {
                cmdSuppPendingID = id;
                const char* et = (cur->data.etat==0)?"En attente"
                               : (cur->data.etat==1)?"En cours":"Realisee";
                UI_PopupShow(TextFormat("Supprimer commande ID:%d (Pok:%d, Qte:%d, %s) ?",
                             id, cur->data.idPokemon, cur->data.quantite, et));
            } else UI_Notif("Commande introuvable. Verifiez l'ID.", NOTIF_ERREUR);
        } else UI_Notif("Entrez un ID valide.", NOTIF_ERREUR);
    }
    if (bouton((Rectangle){10, 260, 170, 40}, "Retour"))
    { UI_Clear(); cmdSuppInit=false; *ecranActuel=ECRAN_COMMANDE_MENU; }
}

// ===== AFFICHER COMMANDES =====
void commandeAffGUI(Ecran *ecranActuel)
{
    if (!cmdAffInit) {
        UI_Clear();
        cmdListAff = UI_CreateList((Rectangle){60, 90, 1140, 540});
        fillCmdList(cmdListAff, cmdLabAff);
        cmdAffInit = true;
    }
    UI_UpdateAndDraw();

    DrawText("LISTE DES COMMANDES", 480, 40, 30, WHITE);

    if (bouton((Rectangle){530, 650, 230, 45}, "Retour")) {
        UI_Clear(); cmdAffInit = false; *ecranActuel = ECRAN_COMMANDE_MENU;
    }
}

#endif
