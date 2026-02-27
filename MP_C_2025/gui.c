#include "headers.h"
#ifdef GUI

// ============================================================
//  COULEURS PAR SECTION
// ============================================================
#define COL_MENU_PANEL     (Color){  0,   0,   0, 160}
#define COL_POKEMON_PANEL  (Color){ 34, 139,  34, 170}
#define COL_MACHINE_PANEL  (Color){ 30,  30,  60, 170}
#define COL_CLIENT_PANEL   (Color){ 70,   0, 130, 170}
#define COL_COMMANDE_PANEL (Color){ 10,  50, 120, 170}
#define COL_PROD_PANEL     (Color){120,  20,  20, 170}
#define COL_STATS_PANEL    (Color){ 20,  20,  20, 180}
#define COL_CLASS_PANEL    (Color){ 60,   0,  80, 170}

#define ACC_MENU       (Color){255, 203,   5, 255}
#define ACC_POKEMON    (Color){255, 140,   0, 255}
#define ACC_MACHINE    (Color){ 70, 180, 255, 255}
#define ACC_CLIENT     (Color){220, 130, 255, 255}
#define ACC_COMMANDE   (Color){  0, 220, 220, 255}
#define ACC_PROD       (Color){255, 200,  50, 255}
#define ACC_STATS      (Color){ 50, 220,  50, 255}
#define ACC_CLASSEMENT (Color){255, 215,   0, 255}

// ============================================================
//  TEXTURES
// ============================================================
static Texture2D texMenu;
static Texture2D texPokemon;
static Texture2D texMachine;
static Texture2D texClient;
static Texture2D texCommande;
static Texture2D texClassement;
static bool texturesLoaded = false;

Color accentCourant = {255, 203, 5, 255};

// ============================================================
//  HELPERS
// ============================================================
static void drawBackground(Texture2D tex)
{
    DrawTexturePro(tex,
        (Rectangle){0, 0, (float)tex.width, (float)tex.height},
        (Rectangle){0, 0, 1280, 720},
        (Vector2){0, 0}, 0.0f, WHITE);
}

static void drawPanel(Color c)
{
    DrawRectangle(0, 0, 1280, 720, c);
}

// ============================================================
//  BOUTON STYLISE
// ============================================================
bool bouton(Rectangle rect, const char* texte)
{
    Vector2 souris = GetMousePosition();
    bool hover  = CheckCollisionPointRec(souris, rect);
    bool clique = hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    Color fond    = hover ? (Color){accentCourant.r, accentCourant.g, accentCourant.b, 230}
                          : (Color){40, 40, 40, 210};
    Color coulTxt = hover ? BLACK : WHITE;
    Color bord    = hover ? WHITE
                          : (Color){accentCourant.r, accentCourant.g, accentCourant.b, 160};

    DrawRectangleRounded((Rectangle){rect.x+3, rect.y+3, rect.width, rect.height},
                         0.3f, 8, (Color){0,0,0,120});
    DrawRectangleRounded(rect, 0.3f, 8, fond);
    DrawRectangleRoundedLines(rect, 0.3f, 8, bord);

    int tw = MeasureText(texte, 20);
    DrawText(texte,
             (int)(rect.x + rect.width/2  - tw/2),
             (int)(rect.y + rect.height/2 - 10),
             20, coulTxt);
    return clique;
}

// ============================================================
//  SAUVEGARDE / LIBERATION
// ============================================================
void sauvegarderDonneesGUI()
{
    sauvegarderCaisse();
    sauvegarderPokemons(listePokemons,   FICHIER_POKEMONS);
    sauvegarderMachines(listeMachines,   FICHIER_MACHINES);
    sauvegarderClients(listeClients,     FICHIER_CLIENTS);
    sauvegarderCommandes(listeCommandes, FICHIER_COMMANDES);
}

void libererToutesLesListesGUI()
{
    libererListePokemon(&listePokemons);
    libererListeMachine(&listeMachines);
    libererListeClient(&listeClients);
    libererListeCommande(&listeCommandes);
}

// ============================================================
//  MACRO pratique pour dessiner fond + panel d'une section
// ============================================================
// SECTION_BG replaced by inline calls below

// ============================================================
//  BOUCLE PRINCIPALE
// ============================================================
Ecran ecranActuel = ECRAN_MENU;

void lancerInterface()
{
    InitWindow(1280, 720, "Usine Pokemon - Interface");
    SetTargetFPS(60);

    texMenu       = LoadTexture("bg_menu.png");
    texPokemon    = LoadTexture("bg_pokemon.png");
    texMachine    = LoadTexture("bg_machine.png");
    texClient     = LoadTexture("bg_client.png");
    texCommande   = LoadTexture("bg_commande.png");
    texClassement = LoadTexture("bg_classement.png");
    texturesLoaded = true;

    Rectangle boutonFermer = {490, 400, 300, 55};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        UI_BeginFrame();

        // ====================================================
        if (ecranActuel == ECRAN_MENU)
        {
            accentCourant = ACC_MENU;
            drawBackground(texMenu); drawPanel(COL_MENU_PANEL);

            const char* titre = "USINE POKEMON";
            int tw = MeasureText(titre, 48);
            DrawText(titre, 3+640-tw/2, 33, 48, BLACK);
            DrawText(titre,   640-tw/2, 30, 48, accentCourant);

            // Panneau boutons
            DrawRectangleRounded((Rectangle){433, 90, 414, 530}, 0.1f, 8, (Color){0,0,0,130});
            DrawRectangleRoundedLines((Rectangle){433, 90, 414, 530}, 0.1f, 8,
                (Color){accentCourant.r, accentCourant.g, accentCourant.b, 150});

            int bx=448, by=110, bw=384, bh=52, gap=61;
            if (bouton((Rectangle){bx,by+gap*0,bw,bh},"Gerer Pokemon"))       ecranActuel=ECRAN_POKEMON_MENU;
            if (bouton((Rectangle){bx,by+gap*1,bw,bh},"Gerer Machines"))      ecranActuel=ECRAN_MACHINE_MENU;
            if (bouton((Rectangle){bx,by+gap*2,bw,bh},"Gerer Clients"))       ecranActuel=ECRAN_CLIENT_MENU;
            if (bouton((Rectangle){bx,by+gap*3,bw,bh},"Gerer Commandes"))     ecranActuel=ECRAN_COMMANDE_MENU;
            if (bouton((Rectangle){bx,by+gap*4,bw,bh},"Production"))          ecranActuel=ECRAN_PROD_MENU;
            if (bouton((Rectangle){bx,by+gap*5,bw,bh},"Etat Usine"))          ecranActuel=ECRAN_ETAT;
            if (bouton((Rectangle){bx,by+gap*6,bw,bh},"Classement Pokemons")) ecranActuel=ECRAN_CLASSEMENT;
            if (bouton((Rectangle){bx,by+gap*7,bw,bh},"Quitter")) {
                sauvegarderDonneesGUI();
                libererToutesLesListesGUI();
                ecranActuel=ECRAN_FIN;
            }
        }
        // ====================================================
        //  POKEMON  (vert / orange)
        // ====================================================
        else if (ecranActuel==ECRAN_POKEMON_MENU)
        { accentCourant=ACC_POKEMON; drawBackground(texPokemon); drawPanel(COL_POKEMON_PANEL); menuPokemonGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_POKEMON_AJOUT)
        { accentCourant=ACC_POKEMON; drawBackground(texPokemon); drawPanel(COL_POKEMON_PANEL); pokemonAjoutGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_POKEMON_MODIF)
        { accentCourant=ACC_POKEMON; drawBackground(texPokemon); drawPanel(COL_POKEMON_PANEL); pokemonModifGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_POKEMON_SUPP)
        { accentCourant=ACC_POKEMON; drawBackground(texPokemon); drawPanel(COL_POKEMON_PANEL); pokemonSuppGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_POKEMON_AFF)
        { accentCourant=ACC_POKEMON; drawBackground(texPokemon); drawPanel(COL_POKEMON_PANEL); pokemonAffGUI(&ecranActuel); }

        // ====================================================
        //  MACHINE  (bleu acier / bleu clair)
        // ====================================================
        else if (ecranActuel==ECRAN_MACHINE_MENU)
        { accentCourant=ACC_MACHINE; drawBackground(texMachine); drawPanel(COL_MACHINE_PANEL); menuMachineGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_MACHINE_AJOUT)
        { accentCourant=ACC_MACHINE; drawBackground(texMachine); drawPanel(COL_MACHINE_PANEL); machineAjoutGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_MACHINE_MODIF)
        { accentCourant=ACC_MACHINE; drawBackground(texMachine); drawPanel(COL_MACHINE_PANEL); machineModifGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_MACHINE_SUPP)
        { accentCourant=ACC_MACHINE; drawBackground(texMachine); drawPanel(COL_MACHINE_PANEL); machineSuppGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_MACHINE_AFF)
        { accentCourant=ACC_MACHINE; drawBackground(texMachine); drawPanel(COL_MACHINE_PANEL); machineAffGUI(&ecranActuel); }

        // ====================================================
        //  CLIENT  (violet / rose)
        // ====================================================
        else if (ecranActuel==ECRAN_CLIENT_MENU)
        { accentCourant=ACC_CLIENT; drawBackground(texClient); drawPanel(COL_CLIENT_PANEL); menuClientGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_CLIENT_AJOUT)
        { accentCourant=ACC_CLIENT; drawBackground(texClient); drawPanel(COL_CLIENT_PANEL); clientAjoutGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_CLIENT_MODIF)
        { accentCourant=ACC_CLIENT; drawBackground(texClient); drawPanel(COL_CLIENT_PANEL); clientModifGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_CLIENT_SUPP)
        { accentCourant=ACC_CLIENT; drawBackground(texClient); drawPanel(COL_CLIENT_PANEL); clientSuppGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_CLIENT_AFF)
        { accentCourant=ACC_CLIENT; drawBackground(texClient); drawPanel(COL_CLIENT_PANEL); clientAffGUI(&ecranActuel); }

        // ====================================================
        //  COMMANDE  (bleu marine / cyan)
        // ====================================================
        else if (ecranActuel==ECRAN_COMMANDE_MENU)
        { accentCourant=ACC_COMMANDE; drawBackground(texCommande); drawPanel(COL_COMMANDE_PANEL); menuCommandeGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_COMMANDE_AJOUT)
        { accentCourant=ACC_COMMANDE; drawBackground(texCommande); drawPanel(COL_COMMANDE_PANEL); commandeAjoutGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_COMMANDE_MODIF)
        { accentCourant=ACC_COMMANDE; drawBackground(texCommande); drawPanel(COL_COMMANDE_PANEL); commandeModifGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_COMMANDE_SUPP)
        { accentCourant=ACC_COMMANDE; drawBackground(texCommande); drawPanel(COL_COMMANDE_PANEL); commandeSuppGUI(&ecranActuel); }

        // ====================================================
        //  PRODUCTION  (rouge brique / jaune chaud)
        // ====================================================
        else if (ecranActuel==ECRAN_PROD_MENU)
        { accentCourant=ACC_PROD; drawBackground(texMachine); drawPanel(COL_PROD_PANEL); menuProductionGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_PROD_REALISER)
        { accentCourant=ACC_PROD; drawBackground(texMachine); drawPanel(COL_PROD_PANEL); prodRealiserGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_PROD_ENTRETENIR)
        { accentCourant=ACC_PROD; drawBackground(texMachine); drawPanel(COL_PROD_PANEL); prodEntretenirGUI(&ecranActuel); }
        else if (ecranActuel==ECRAN_PROD_ETAT)
        { accentCourant=ACC_PROD; drawBackground(texMachine); drawPanel(COL_PROD_PANEL); prodEtatGUI(&ecranActuel); }

        // ====================================================
        //  ETAT USINE  (anthracite / vert)
        // ====================================================
        else if (ecranActuel==ECRAN_ETAT)
        { accentCourant=ACC_STATS; drawBackground(texMachine); drawPanel(COL_STATS_PANEL); menuEtatUsineGUI(&ecranActuel); }

        // ====================================================
        //  CLASSEMENT  (violet foncé / or)
        // ====================================================
        else if (ecranActuel==ECRAN_CLASSEMENT)
        { accentCourant=ACC_CLASSEMENT; drawBackground(texClassement); drawPanel(COL_CLASS_PANEL); menuClassementGUI(&ecranActuel); }

        // ====================================================
        //  FIN
        // ====================================================
        else if (ecranActuel==ECRAN_FIN)
        {
            accentCourant=ACC_MENU;
            drawBackground(texMenu); drawPanel((Color){0,0,0,160});

            const char* msg1 = "Merci d'avoir utilise l'Usine Pokemon!";
            const char* msg2 = "A bientot, Dresseur!";
            int tw1 = MeasureText(msg1,30);
            int tw2 = MeasureText(msg2,26);
            DrawText(msg1, 3+640-tw1/2, 283, 30, BLACK);
            DrawText(msg1,   640-tw1/2, 280, 30, accentCourant);
            DrawText(msg2, 3+640-tw2/2, 333, 26, BLACK);
            DrawText(msg2,   640-tw2/2, 330, 26, WHITE);

            if (bouton(boutonFermer,"Fermer")) {
                UnloadTexture(texMenu); UnloadTexture(texPokemon);
                UnloadTexture(texMachine); UnloadTexture(texClient);
                UnloadTexture(texCommande); UnloadTexture(texClassement);
                CloseWindow(); exit(0);
            }
        }

        UI_Draw();
        EndDrawing();
    }

    if (texturesLoaded) {
        UnloadTexture(texMenu); UnloadTexture(texPokemon);
        UnloadTexture(texMachine); UnloadTexture(texClient);
        UnloadTexture(texCommande); UnloadTexture(texClassement);
    }
}

#endif
