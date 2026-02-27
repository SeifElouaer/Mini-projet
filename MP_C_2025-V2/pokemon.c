#include "headers.h"

static int compteurIdPokemon = 0;

int genererIdP() {
    return ++compteurIdPokemon;
}

pokemon creerPokemon() {
    pokemon p;
    p.id = genererIdP();
    printf("Nom du pokemon: ");
    scanf("%s", p.nom);
    printf("Type: ");
    scanf("%s", p.type);
    printf("Cout unitaire: ");
    scanf("%f", &p.prix);
    return p;
}

void ajouterPokemon(ListePokemon** liste) {
    ListePokemon* nouveau = (ListePokemon*)malloc(sizeof(ListePokemon));
    if (nouveau == NULL) {
        printf("ERREUR: Allocation memoire echouee.\n");
        return;
    }

    nouveau->data = creerPokemon();
    nouveau->next = *liste;
    *liste = nouveau;
    printf("Pokemon ajoute avec succes.\n");
}

void afficherPokemon(pokemon p) {
    printf("- ID: %d | Nom: %s | Cout: %.2f | Type: %s\n",
           p.id, p.nom, p.prix, p.type);
}

void afficherPokemons(ListePokemon* liste) {
    if (liste == NULL) {
        printf("Aucun Pokemon trouve.\n");
        return;
    }

    ListePokemon* current = liste;
    int count = 1;
    while (current != NULL) {
        printf("#### Pokemon %d ####\n", count++);
        afficherPokemon(current->data);
        current = current->next;
    }
}

ListePokemon* rechercherPokemon(ListePokemon* liste, int id) {
    ListePokemon* current = liste;
    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifierPokemon(ListePokemon* liste) {
    if (liste == NULL) {
        printf("Aucun Pokemon trouve.\n");
        return;
    }

    int id, choix;
    printf("ID du pokemon a modifier: ");
    scanf("%d", &id);

    ListePokemon* node = rechercherPokemon(liste, id);
    if (node == NULL) {
        printf("Pokemon introuvable.\n");
        return;
    }

    do {
        printf("\n===== Modifier Pokemon %d =====\n", node->data.id);
        printf("1. Nom du pokemon\n");
        printf("2. Cout du pokemon\n");
        printf("3. Type du pokemon\n");
        printf("0. Retour au menu\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nouveau nom: ");
                scanf("%s", node->data.nom);
                break;
            case 2:
                printf("Nouveau cout: ");
                scanf("%f", &node->data.prix);
                break;
            case 3:
                printf("Nouveau type: ");
                scanf("%s", node->data.type);
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

void supprimerPokemon(ListePokemon** liste) {
    if (*liste == NULL) {
        printf("Aucun Pokemon a supprimer.\n");
        return;
    }

    int id;
    printf("ID du pokemon a supprimer: ");
    scanf("%d", &id);

    ListePokemon* current = *liste;
    ListePokemon* prev = NULL;

    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Pokemon introuvable.\n");
        return;
    }

    printf("\n>>> Confirmation <<<\n");
    printf("Supprimer le Pokemon '%s' (ID:%d, Prix:%.2f) ? (o/n): ",
           current->data.nom, current->data.id, current->data.prix);
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
    printf("Pokemon supprime avec succes.\n");
}

void libererListePokemon(ListePokemon** liste) {
    ListePokemon* current = *liste;
    while (current != NULL) {
        ListePokemon* temp = current;
        current = current->next;
        free(temp);
    }
    *liste = NULL;
}

int compterPokemons(ListePokemon* liste) {
    int count = 0;
    ListePokemon* current = liste;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


// Fonctions de gestion des fichiers
void sauvegarderPokemons(ListePokemon* liste, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    ListePokemon* current = liste;
    while (current != NULL) {
        fprintf(fichier, "%d;%s;%.2f;%s\n",
                current->data.id,
                current->data.nom,
                current->data.prix,
                current->data.type);
        current = current->next;
    }

    fclose(fichier);
    printf("Pokemons sauvegardes dans %s\n", nomFichier);
}

ListePokemon* chargerPokemons(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("INFO: Fichier %s non trouve. Demarrage avec liste vide.\n", nomFichier);
        return NULL;
    }

    ListePokemon* liste = NULL;
    pokemon p;

    while (fscanf(fichier, "%d;%[^;];%f;%[^\n]\n",
                  &p.id, p.nom, &p.prix, p.type) == 4) {
        ListePokemon* nouveau = (ListePokemon*)malloc(sizeof(ListePokemon));
        if (nouveau != NULL) {
            nouveau->data = p;
            nouveau->next = liste;
            liste = nouveau;

            // Mettre à jour le compteur d'ID
            if (p.id > compteurIdPokemon) {
                compteurIdPokemon = p.id;
            }
        }
    }

    fclose(fichier);
    printf("Pokemons charges depuis %s\n", nomFichier);
    return liste;
}
#ifndef GUI

extern ListePokemon* listePokemons;

static ScrollableList* pokemonListView = NULL;
static bool pokemonListInit = false;
static char pokemonLabels[MAX_ITEMS][200];

static TextBox* tbPokNom   = NULL;
static TextBox* tbPokPrix  = NULL;
static TextBox* tbPokType  = NULL;
static bool pokAjoutInit   = false;

static TextBox* tbPokID    = NULL;
static TextBox* tbPokNom2  = NULL;
static TextBox* tbPokPrix2 = NULL;
static TextBox* tbPokType2 = NULL;
static ScrollableList* pokListModif = NULL;
static char pokLabelsModif[MAX_ITEMS][200];
static bool pokModifInit   = false;

static TextBox* tbPokIDSupp     = NULL;
static ScrollableList* pokListSupp = NULL;
static char pokLabelsSupp[MAX_ITEMS][200];
static bool pokSuppInit = false;

void RefreshPokemonList()
{
    ScrollableList* lists[] = {pokemonListView, pokListModif, pokListSupp};
    char (*labels[])[200]   = {pokemonLabels,   pokLabelsModif, pokLabelsSupp};
    for (int l = 0; l < 3; l++)
    {
        if (!lists[l]) continue;
        UI_ListClear(lists[l]);
        ListePokemon* tmp = listePokemons; int i = 0;
        while (tmp && i < MAX_ITEMS)
        {
            sprintf(labels[l][i], "ID:%-5d | %-12s | Prix:%.2f | Type:%s",
                    tmp->data.id, tmp->data.nom, tmp->data.prix, tmp->data.type);
            UI_ListAddItem(lists[l], labels[l][i]);
            tmp = tmp->next; i++;
        }
    }
}

// ===== MENU PRINCIPAL =====
void menuPokemonGUI(Ecran *ecran)
{
    DrawText("GESTION DES POKEMONS", 240, 50, 30, WHITE);
    if (bouton((Rectangle){300, 140, 280, 50}, "Ajouter Pokemon"))   *ecran = ECRAN_POKEMON_AJOUT;
    if (bouton((Rectangle){300, 210, 280, 50}, "Modifier Pokemon"))  *ecran = ECRAN_POKEMON_MODIF;
    if (bouton((Rectangle){300, 280, 280, 50}, "Supprimer Pokemon")) *ecran = ECRAN_POKEMON_SUPP;
    if (bouton((Rectangle){300, 350, 280, 50}, "Afficher Pokemons")) *ecran = ECRAN_POKEMON_AFF;
    if (bouton((Rectangle){300, 440, 280, 50}, "Retour"))            *ecran = ECRAN_MENU;
}

// ===== AJOUTER =====
// Layout: titre y=15, labels y=110/170/230, textboxes y=132/192/252, boutons y=310/375
void pokemonAjoutGUI(Ecran *ecran)
{
    if (!pokAjoutInit)
    {
        UI_Clear();
        tbPokNom  = UI_CreateTextBox((Rectangle){320, 110, 260, 38}, 20);
        tbPokPrix = UI_CreateTextBox((Rectangle){320, 170, 260, 38}, 10);
        tbPokType = UI_CreateTextBox((Rectangle){320, 230, 260, 38}, 20);
        pokAjoutInit = true;
    }
    UI_UpdateAndDraw();

    DrawText("AJOUTER POKEMON", 295, 50, 30, WHITE);
    DrawText("Nom :",  220, 110, 20, WHITE);
    DrawText("Prix :", 220, 170, 20, WHITE);
    DrawText("Type :", 220, 230, 20, WHITE);

    if (bouton((Rectangle){320, 310, 260, 45}, "Valider"))
    {
        if (strlen(tbPokNom->text)>0 && strlen(tbPokPrix->text)>0 && strlen(tbPokType->text)>0)
        {
            ListePokemon* n = (ListePokemon*)malloc(sizeof(ListePokemon));
            if (n) {
                n->data.id = genererIdP();
                strcpy(n->data.nom,  tbPokNom->text);
                n->data.prix = atof(tbPokPrix->text);
                strcpy(n->data.type, tbPokType->text);
                n->next = listePokemons; listePokemons = n;
                UI_Notif(TextFormat("Pokemon ajoute : %s (ID:%d)", n->data.nom, n->data.id), NOTIF_SUCCES);
                tbPokNom->text[0]='\0'; tbPokPrix->text[0]='\0'; tbPokType->text[0]='\0';
            }
        } else UI_Notif("Remplissez tous les champs.", NOTIF_ERREUR);
    }
    if (bouton((Rectangle){320, 375, 260, 45}, "Retour"))
    { UI_Clear(); pokAjoutInit=false; *ecran=ECRAN_POKEMON_MENU; }
}

// ===== MODIFIER (avec scrollable) =====
// Layout: titre y=15, colonne gauche x=10 w=170, scrollable x=190 y=70 w=700 h=430
// Labels: y=72/132/192/252  TextBox: y=92/152/212/272
void pokemonModifGUI(Ecran *ecran)
{
    if (!pokModifInit)
    {
        UI_Clear();
        tbPokID    = UI_CreateTextBox((Rectangle){10,  92, 170, 33}, 10);
        tbPokNom2  = UI_CreateTextBox((Rectangle){10, 152, 170, 33}, 20);
        tbPokPrix2 = UI_CreateTextBox((Rectangle){10, 212, 170, 33}, 10);
        tbPokType2 = UI_CreateTextBox((Rectangle){10, 272, 170, 33}, 20);
        pokListModif = UI_CreateList((Rectangle){190, 70, 700, 430});
        pokModifInit = true;
        RefreshPokemonList();
    }
    UI_UpdateAndDraw();

    DrawText("MODIFIER POKEMON", 280, 15, 28, WHITE);
    DrawText("ID :",   10, 72,  17, WHITE);
    DrawText("Nom :",  10, 132, 17, WHITE);
    DrawText("Prix :", 10, 192, 17, WHITE);
    DrawText("Type :", 10, 252, 17, WHITE);
    DrawText("Pokemons :", 190, 52, 17, WHITE);

    if (bouton((Rectangle){10, 335, 170, 40}, "Valider"))
    {
        int id = atoi(tbPokID->text);
        if (id > 0) {
            ListePokemon* node = rechercherPokemon(listePokemons, id);
            if (node) {
                if (strlen(tbPokNom2->text)  > 0) strcpy(node->data.nom,  tbPokNom2->text);
                if (strlen(tbPokPrix2->text) > 0) node->data.prix = atof(tbPokPrix2->text);
                if (strlen(tbPokType2->text) > 0) strcpy(node->data.type, tbPokType2->text);
                UI_Notif(TextFormat("Pokemon %d modifie avec succes.", id), NOTIF_SUCCES);
                tbPokID->text[0]='\0'; tbPokNom2->text[0]='\0';
                tbPokPrix2->text[0]='\0'; tbPokType2->text[0]='\0';
                RefreshPokemonList();
            } else UI_Notif("Pokemon introuvable. Verifiez l'ID.", NOTIF_ERREUR);
        }
    }
    if (bouton((Rectangle){10, 390, 170, 40}, "Retour"))
    { UI_Clear(); pokModifInit=false; *ecran=ECRAN_POKEMON_MENU; }
}

// ===== SUPPRIMER (avec scrollable) =====
// Layout: titre y=15, label y=130, textbox y=150, scrollable x=190 y=70
void pokemonSuppGUI(Ecran *ecran)
{
    if (!pokSuppInit)
    {
        UI_Clear();
        tbPokIDSupp = UI_CreateTextBox((Rectangle){10, 150, 170, 35}, 10);
        pokListSupp = UI_CreateList((Rectangle){190, 70, 700, 430});
        pokSuppInit = true;
        RefreshPokemonList();
    }
    UI_UpdateAndDraw();

    DrawText("SUPPRIMER POKEMON", 265, 15, 28, WHITE);
    DrawText("ID a supprimer :", 10, 130, 17, WHITE);
    DrawText("Pokemons :", 190, 52, 17, WHITE);

    // Gestion popup confirmation
    static int pokSuppPendingID = 0;
    int popupRes = UI_PopupDraw();
    if (popupRes == 1 && pokSuppPendingID > 0)
    {
        ListePokemon* cur = listePokemons; ListePokemon* prev = NULL;
        while (cur && cur->data.id != pokSuppPendingID) { prev=cur; cur=cur->next; }
        if (cur) {
            if (prev) prev->next=cur->next; else listePokemons=cur->next;
            free(cur);
            UI_Notif(TextFormat("Pokemon %d supprime.", pokSuppPendingID), NOTIF_SUCCES);
            tbPokIDSupp->text[0]='\0';
            RefreshPokemonList();
        }
        pokSuppPendingID = 0;
    }
    else if (popupRes == -1) { pokSuppPendingID = 0; UI_Notif("Suppression annulee.", NOTIF_INFO); }

    if (bouton((Rectangle){10, 205, 170, 40}, "Supprimer"))
    {
        int id = atoi(tbPokIDSupp->text);
        if (id > 0) {
            ListePokemon* cur = listePokemons;
            while (cur && cur->data.id != id) cur = cur->next;
            if (cur) {
                pokSuppPendingID = id;
                UI_PopupShow(TextFormat("Supprimer Pokemon '%s' (ID:%d) ?", cur->data.nom, id));
            } else UI_Notif("Pokemon introuvable. Verifiez l'ID.", NOTIF_ERREUR);
        } else UI_Notif("Entrez un ID valide.", NOTIF_ERREUR);
    }
    if (bouton((Rectangle){10, 260, 170, 40}, "Retour"))
    { UI_Clear(); pokSuppInit=false; *ecran=ECRAN_POKEMON_MENU; }
}

// ===== AFFICHER =====
void pokemonAffGUI(Ecran *ecran)
{
    if (!pokemonListInit)
    {
        UI_Clear();
        pokemonListView = UI_CreateList((Rectangle){60, 80, 770, 410});
        RefreshPokemonList();
        pokemonListInit = true;
    }
    UI_UpdateAndDraw();
    DrawText("LISTE DES POKEMONS", 270, 30, 30, WHITE);
    if (bouton((Rectangle){330, 510, 230, 45}, "Retour"))
    { UI_Clear(); pokemonListInit=false; *ecran=ECRAN_POKEMON_MENU; }
}

void InitPokemonUI() {}
void AjouterPokemonGUI() {}
void SupprimerPokemonGUI() {}
void ModifierPokemonGUI() {}

#endif
