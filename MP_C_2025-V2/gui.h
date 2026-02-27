#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED
#ifndef GUI
#include "raylib.h"
typedef enum {
    ECRAN_MENU,
    ECRAN_POKEMON,
    ECRAN_CLIENT,
    ECRAN_COMMANDE,
    ECRAN_PRODUCTION,
    ECRAN_ETAT,
    ECRAN_FIN,
    ECRAN_MACHINE_MENU,
    ECRAN_MACHINE_AJOUT,
    ECRAN_MACHINE_MODIF,
    ECRAN_MACHINE_SUPP,
    ECRAN_MACHINE_AFF,
    ECRAN_POKEMON_MENU,
    ECRAN_POKEMON_AJOUT,
    ECRAN_POKEMON_MODIF,
    ECRAN_POKEMON_SUPP,
    ECRAN_POKEMON_AFF,
    ECRAN_CLASSEMENT,
    ECRAN_COMMANDE_MENU,
    ECRAN_COMMANDE_AJOUT,
    ECRAN_COMMANDE_MODIF,
    ECRAN_COMMANDE_SUPP,
    ECRAN_COMMANDE_AFF,
    ECRAN_PROD_MENU,
    ECRAN_PROD_REALISER,
    ECRAN_PROD_ENTRETENIR,
    ECRAN_PROD_ETAT,
    ECRAN_CLIENT_MENU,
    ECRAN_CLIENT_AJOUT,
    ECRAN_CLIENT_MODIF,
    ECRAN_CLIENT_SUPP,
    ECRAN_CLIENT_AFF,
    ECRAN_EXPORT
} Ecran;


// Couleur d'accent courante (change selon la section active)
extern Color accentCourant;

// ============================================================
//  SYSTEME DE NOTIFICATIONS (messages in-game)
// ============================================================
typedef enum {
    NOTIF_SUCCES,   // vert
    NOTIF_ERREUR,   // rouge
    NOTIF_INFO      // bleu/cyan
} TypeNotif;

void UI_Notif(const char* message, TypeNotif type);
void UI_NotifDraw(void);   // a appeler dans la boucle, apres UI_Draw()

// ============================================================
//  POPUP DE CONFIRMATION
// ============================================================
// Affiche un popup "Confirmer ?" avec Oui/Non
// Retourne 1 si Oui clique, -1 si Non clique, 0 si en attente
// Appeler UI_PopupShow() pour ouvrir, UI_PopupDraw() chaque frame
void UI_PopupShow(const char* message);
int  UI_PopupDraw(void);   // 1=confirme, -1=annule, 0=en attente

bool bouton(Rectangle rect, const char* texte);

void lancerInterface();

#endif // GUI_H_INCLUDED
#endif
