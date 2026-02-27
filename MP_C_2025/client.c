#include "headers.h"

static int compteurMatricule = 0;

int genererMatricule() {
    return ++compteurMatricule;
}

client creerClient() {
    client c;
    c.matricule = genererMatricule();
    printf("Nom du client: ");
    scanf("%s", c.nom);
    c.commandes = NULL;
    return c;
}

void ajouterClient(ListeClient** liste) {
    ListeClient* nouveau = (ListeClient*)malloc(sizeof(ListeClient));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }

    nouveau->data = creerClient();
    nouveau->next = *liste;
    *liste = nouveau;
    printf("Client ajoute avec succes.\n");
}

void afficherClient(client c) {
    printf("- Matricule: %d | Nom: %s\n", c.matricule, c.nom);

    int nbCommandes = compterCommandes(c.commandes);
    printf("  Nombre de commandes: %d\n", nbCommandes);

    if (c.commandes != NULL) {
        printf("  Commandes du client:\n");
        ListeCommande* current = c.commandes;
        while (current != NULL) {
            printf("    - ID=%d, Pokemon=%d, Quantite=%d\n",
                   current->data.id, current->data.idPokemon, current->data.quantite);
            current = current->next;
        }
    }
}

void afficherClients(ListeClient* liste) {
    if (liste == NULL) {
        printf("Aucun client.\n");
        return;
    }

    ListeClient* current = liste;
    int count = 1;
    while (current != NULL) {
        printf("#### Client %d ####\n", count++);
        afficherClient(current->data);
        current = current->next;
    }
}

ListeClient* rechercherClient(ListeClient* liste, int matricule) {
    ListeClient* current = liste;
    while (current != NULL) {
        if (current->data.matricule == matricule) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifierClient(ListeClient* liste, ListePokemon* listePokemons) {
    if (liste == NULL) {
        printf("Aucun client.\n");
        return;
    }

    int mat, choix, op;
    printf("Matricule du client a modifier: ");
    scanf("%d", &mat);

    ListeClient* node = rechercherClient(liste, mat);
    if (node == NULL) {
        printf("Client introuvable.\n");
        return;
    }

    do {
        printf("\n===== Modifier Client %d =====\n", node->data.matricule);
        printf("1. Nom\n");
        printf("2. Liste de commandes\n");
        printf("0. Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nouveau nom: ");
                scanf("%s", node->data.nom);
                break;
            case 2:
                printf("\n=== Gestion des commandes du client ===\n");
                printf("1. Ajouter commande\n");
                printf("2. Modifier commande\n");
                printf("3. Supprimer commande\n");
                printf("0. Retour\n");
                printf("Choix: ");
                scanf("%d", &op);

                switch (op) {
                    case 1:
                        ajouterCommande(&(node->data.commandes), listePokemons);
                        break;
                    case 2:
                        modifierCommande(node->data.commandes, listePokemons);
                        break;
                    case 3:
                        supprimerCommande(&(node->data.commandes));
                        break;
                    case 0:
                        printf("Retour.\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
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

void supprimerClient(ListeClient** liste) {
    if (*liste == NULL) {
        printf("Aucun client a supprimer.\n");
        return;
    }

    int mat;
    printf("Matricule du client a supprimer: ");
    scanf("%d", &mat);

    ListeClient* current = *liste;
    ListeClient* prev = NULL;

    while (current != NULL && current->data.matricule != mat) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Client introuvable.\n");
        return;
    }

    // Libérer les commandes du client
    libererListeCommande(&(current->data.commandes));

    if (prev == NULL) {
        *liste = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Client supprime avec succes.\n");
}

// Lie les commandes aux clients apres chargement des deux listes
void lierCommandesClients(ListeClient* listeClients, ListeCommande* listeCommandes) {
    ListeClient* cl = listeClients;
    while (cl != NULL) {
        cl->data.commandes = NULL; // reset
        ListeCommande* cmd = listeCommandes;
        while (cmd != NULL) {
            if (cmd->data.matriculeClient == cl->data.matricule) {
                // Ajouter cette commande au client
                ListeCommande* copie = (ListeCommande*)malloc(sizeof(ListeCommande));
                if (copie) {
                    copie->data = cmd->data;
                    copie->next = cl->data.commandes;
                    cl->data.commandes = copie;
                }
            }
            cmd = cmd->next;
        }
        cl = cl->next;
    }
}

void libererListeClient(ListeClient** liste) {
    ListeClient* current = *liste;
    while (current != NULL) {
        ListeClient* temp = current;
        current = current->next;
        libererListeCommande(&(temp->data.commandes));
        free(temp);
    }
    *liste = NULL;
}

int compterClients(ListeClient* liste) {
    int count = 0;
    ListeClient* current = liste;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Fonctions de gestion des fichiers
void sauvegarderClients(ListeClient* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListeClient* current = liste;
    while (current != NULL) {
        // Sauvegarder les infos du client
        fprintf(fichier, "%d;%s;", current->data.matricule, current->data.nom);

        // Compter et sauvegarder le nombre de commandes
        int nbCommandes = compterCommandes(current->data.commandes);
        fprintf(fichier, "%d", nbCommandes);

        // Sauvegarder les IDs des commandes
        ListeCommande* cmd = current->data.commandes;
        while (cmd != NULL) {
            fprintf(fichier, ";%d", cmd->data.id);
            cmd = cmd->next;
        }
        fprintf(fichier, "\n");

        current = current->next;
    }

    fclose(fichier);
    printf("Clients sauvegardes dans %s\n", nomFichier);
}

ListeClient* chargerClients(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier %s non trouve. Demarrage avec liste vide.\n", nomFichier);
        return NULL;
    }

    ListeClient* liste = NULL;
    char ligne[1000];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        client c;
        c.commandes = NULL;

        char* token = strtok(ligne, ";");
        if (token == NULL) continue;
        c.matricule = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strcpy(c.nom, token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;

        // Les IDs des commandes seront chargés plus tard si nécessaire
        // Pour l'instant on les ignore

        ListeClient* nouveau = (ListeClient*)malloc(sizeof(ListeClient));
        if (nouveau != NULL) {
            nouveau->data = c;
            nouveau->next = liste;
            liste = nouveau;

            if (c.matricule > compteurMatricule) {
                compteurMatricule = c.matricule;
            }
        }
    }

    fclose(fichier);
    printf("Clients charges depuis %s\n", nomFichier);
    return liste;
}
#ifdef GUI

extern ListeClient* listeClients;
extern ListePokemon* listePokemons;

// ===== Variables =====
// Ajout
static TextBox* tbCliNomAjout = NULL;
static bool cliAjoutInit = false;

// Modifier
static TextBox* tbCliModifMat = NULL;
static TextBox* tbCliModifNom = NULL;
static ScrollableList* cliListModif = NULL;
static char cliLabModif[MAX_ITEMS][128];
static bool cliModifInit = false;

// Supprimer
static TextBox* tbCliSuppMat = NULL;
static ScrollableList* cliListSupp = NULL;
static char cliLabSupp[MAX_ITEMS][128];
static bool cliSuppInit = false;

// Afficher
static ScrollableList* cliListAff = NULL;
static char cliLabAff[MAX_ITEMS][128];
static bool cliAffInit = false;

// ===== Refresh =====
static void fillCliList(ScrollableList* list, char labels[][128])
{
    if (!list) return;
    UI_ListClear(list);
    ListeClient* tmp = listeClients;
    int i = 0;
    while (tmp && i < MAX_ITEMS)
    {
        sprintf(labels[i], "Matricule:%-4d | Nom: %s | Commandes: %d",
                tmp->data.matricule, tmp->data.nom,
                compterCommandes(tmp->data.commandes));
        UI_ListAddItem(list, labels[i]);
        tmp = tmp->next;
        i++;
    }
}

// ===== MENU PRINCIPAL CLIENT =====
void menuClientGUI(Ecran *ecranActuel)
{
    DrawText("GESTION DES CLIENTS", 255, 50, 30, WHITE);
    if (bouton((Rectangle){300, 140, 280, 50}, "Ajouter Client"))   *ecranActuel = ECRAN_CLIENT_AJOUT;
    if (bouton((Rectangle){300, 210, 280, 50}, "Modifier Client"))  *ecranActuel = ECRAN_CLIENT_MODIF;
    if (bouton((Rectangle){300, 280, 280, 50}, "Supprimer Client")) *ecranActuel = ECRAN_CLIENT_SUPP;
    if (bouton((Rectangle){300, 350, 280, 50}, "Afficher Clients")) *ecranActuel = ECRAN_CLIENT_AFF;
    if (bouton((Rectangle){300, 440, 280, 50}, "Retour"))           *ecranActuel = ECRAN_MENU;
}

// ===== AJOUTER CLIENT =====
void clientAjoutGUI(Ecran *ecranActuel)
{
    if (!cliAjoutInit)
    {
        UI_Clear();
        tbCliNomAjout = UI_CreateTextBox((Rectangle){320, 280, 260, 38}, 20);
        cliAjoutInit  = true;
    }
    UI_UpdateAndDraw();

    DrawText("AJOUTER CLIENT", 300, 80, 30, WHITE);
    DrawText("L'ID (matricule) sera genere automatiquement.", 170, 160, 18, WHITE);
    DrawText("Entrez le nom du client :", 230, 255, 20, WHITE);

    if (bouton((Rectangle){320, 340, 260, 45}, "Valider"))
    {
        if (strlen(tbCliNomAjout->text) > 0)
        {
            ListeClient* n = (ListeClient*)malloc(sizeof(ListeClient));
            if (n)
            {
                n->data.matricule = genererMatricule();
                strcpy(n->data.nom, tbCliNomAjout->text);
                n->data.commandes = NULL;
                n->next = listeClients;
                listeClients = n;
                printf("Client ajoute : %s (ID:%d)\n", n->data.nom, n->data.matricule);
                tbCliNomAjout->text[0] = '\0';
            }
        }
        else printf("Nom obligatoire.\n");
    }
    if (bouton((Rectangle){320, 400, 260, 45}, "Retour"))
    {
        UI_Clear();
        cliAjoutInit = false;
        *ecranActuel = ECRAN_CLIENT_MENU;
    }
}

// ===== MODIFIER CLIENT (scrollable gauche) =====
void clientModifGUI(Ecran *ecranActuel)
{
    if (!cliModifInit)
    {
        UI_Clear();
        // Labels a y=75 et y=140, TextBox a y=95 et y=160 → pas de chevauchement
        tbCliModifMat = UI_CreateTextBox((Rectangle){10,  95, 165, 35}, 10);
        tbCliModifNom = UI_CreateTextBox((Rectangle){10, 160, 165, 35}, 20);
        // Scrollable commence a y=70 (sous le titre a y=15)
        cliListModif  = UI_CreateList((Rectangle){190, 70, 695, 420});
        cliModifInit  = true;
        fillCliList(cliListModif, cliLabModif);
    }
    UI_UpdateAndDraw();

    DrawText("MODIFIER CLIENT", 290, 15, 28, WHITE);
    // Labels AU-DESSUS des TextBox
    DrawText("Matricule :", 10, 75,  18, WHITE);
    DrawText("Nouveau Nom :", 10, 140, 18, WHITE);
    DrawText("(vide=inchange)", 10, 200, 13, (Color){180,180,180,255});
    DrawText("Clients :", 190, 50, 18, WHITE);

    if (bouton((Rectangle){10, 220, 165, 40}, "Valider"))
    {
        int mat = atoi(tbCliModifMat->text);
        if (mat > 0 && strlen(tbCliModifNom->text) > 0)
        {
            ListeClient* node = rechercherClient(listeClients, mat);
            if (node)
            {
                strcpy(node->data.nom, tbCliModifNom->text);
                tbCliModifMat->text[0] = '\0';
                tbCliModifNom->text[0] = '\0';
                fillCliList(cliListModif, cliLabModif);
                printf("Client modifie.\n");
            }
            else printf("Client introuvable.\n");
        }
    }
    if (bouton((Rectangle){10, 275, 165, 40}, "Retour"))
    {
        UI_Clear();
        cliModifInit = false;
        *ecranActuel = ECRAN_CLIENT_MENU;
    }
}

// ===== SUPPRIMER CLIENT (scrollable) =====
void clientSuppGUI(Ecran *ecranActuel)
{
    if (!cliSuppInit)
    {
        UI_Clear();
        tbCliSuppMat = UI_CreateTextBox((Rectangle){10, 155, 165, 35}, 10);
        cliListSupp  = UI_CreateList((Rectangle){190, 70, 695, 420});
        cliSuppInit  = true;
        fillCliList(cliListSupp, cliLabSupp);
    }
    UI_UpdateAndDraw();

    DrawText("SUPPRIMER CLIENT", 285, 15, 28, WHITE);
    DrawText("Matricule :", 10, 135, 18, WHITE);
    DrawText("Clients :", 190, 50, 18, WHITE);

    if (bouton((Rectangle){10, 210, 165, 40}, "Supprimer"))
    {
        int mat = atoi(tbCliSuppMat->text);
        if (mat > 0)
        {
            ListeClient* cur = listeClients;
            ListeClient* prev = NULL;
            while (cur && cur->data.matricule != mat) { prev = cur; cur = cur->next; }
            if (cur)
            {
                libererListeCommande(&(cur->data.commandes));
                if (prev) prev->next = cur->next;
                else listeClients = cur->next;
                free(cur);
                tbCliSuppMat->text[0] = '\0';
                fillCliList(cliListSupp, cliLabSupp);
                printf("Client supprime.\n");
            }
            else printf("Client introuvable.\n");
        }
    }
    if (bouton((Rectangle){10, 265, 165, 40}, "Retour"))
    {
        UI_Clear();
        cliSuppInit = false;
        *ecranActuel = ECRAN_CLIENT_MENU;
    }
}

// ===== AFFICHER CLIENTS =====
void clientAffGUI(Ecran *ecranActuel)
{
    if (!cliAffInit)
    {
        UI_Clear();
        cliListAff = UI_CreateList((Rectangle){60, 80, 770, 410});
        fillCliList(cliListAff, cliLabAff);
        cliAffInit = true;
    }
    UI_UpdateAndDraw();

    DrawText("LISTE DES CLIENTS", 285, 30, 30, WHITE);

    if (bouton((Rectangle){330, 510, 230, 45}, "Retour"))
    {
        UI_Clear();
        cliAffInit = false;
        *ecranActuel = ECRAN_CLIENT_MENU;
    }
}

#endif
