#include "headers.h"
#include <time.h>

// ============================================================
//  EXPORT CSV COMPLET
//  Génère 5 fichiers CSV dans le dossier courant
// ============================================================

static void ecrireEntete(FILE* f, const char* titre)
{
    // BOM UTF-8 pour Excel
    fprintf(f, "\xEF\xBB\xBF");
    fprintf(f, "# %s\n", titre);

    time_t t = time(NULL);
    char buf[64];
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", localtime(&t));
    fprintf(f, "# Genere le: %s\n", buf);
    fprintf(f, "\n");
}

void exporterCSV(ListePokemon* listePokemons, ListeMachine* listeMachines,
                 ListeClient* listeClients, ListeCommande* listeCommandes,
                 float caisse)
{
    int ok = 0;

    // ---- 1. POKEMONS ----
    {
        FILE* f = fopen("export_pokemons.csv", "w");
        if (f) {
            ecrireEntete(f, "Pokemons");
            fprintf(f, "ID;Nom;Type;Prix unitaire\n");
            ListePokemon* p = listePokemons;
            while (p) {
                fprintf(f, "%d;%s;%s;%.2f\n",
                        p->data.id, p->data.nom,
                        p->data.type, p->data.prix);
                p = p->next;
            }
            fclose(f);
            printf("  -> export_pokemons.csv\n");
            ok++;
        }
    }

    // ---- 2. MACHINES ----
    {
        FILE* f = fopen("export_machines.csv", "w");
        if (f) {
            ecrireEntete(f, "Machines");
            fprintf(f, "ID;Nom;Pokemon ID;Temps prod (min);Capacite max;Compteur;Cout maint;Etat;Commande en cours\n");
            ListeMachine* m = listeMachines;
            while (m) {
                const char* et = (m->data.etat==0)?"Libre"
                               : (m->data.etat==1)?"Occupee":"Maintenance";
                fprintf(f, "%d;%s;%d;%d;%d;%d;%.2f;%s;%d\n",
                        m->data.id, m->data.nom, m->data.idPokemon,
                        m->data.tempsProd, m->data.nbMax, m->data.compteur,
                        m->data.coutMaint, et, m->data.idCommande);
                m = m->next;
            }
            fclose(f);
            printf("  -> export_machines.csv\n");
            ok++;
        }
    }

    // ---- 3. CLIENTS ----
    {
        FILE* f = fopen("export_clients.csv", "w");
        if (f) {
            ecrireEntete(f, "Clients");
            fprintf(f, "Matricule;Nom;Nb commandes\n");
            ListeClient* c = listeClients;
            while (c) {
                fprintf(f, "%d;%s;%d\n",
                        c->data.matricule, c->data.nom,
                        compterCommandes(c->data.commandes));
                c = c->next;
            }
            fclose(f);
            printf("  -> export_clients.csv\n");
            ok++;
        }
    }

    // ---- 4. COMMANDES ----
    {
        FILE* f = fopen("export_commandes.csv", "w");
        if (f) {
            ecrireEntete(f, "Commandes");
            fprintf(f, "ID;Client;Pokemon;Quantite commandee;Quantite produite;Date;Etat;Revenu genere\n");
            ListeCommande* c = listeCommandes;
            while (c) {
                const char* et = (c->data.etat==0)?"En attente"
                               : (c->data.etat==1)?"En cours":"Realisee";
                float revenu = 0.0f;
                if (c->data.etat == 2) {
                    ListePokemon* pNode = rechercherPokemon(listePokemons, c->data.idPokemon);
                    if (pNode) revenu = c->data.quantiteProduite * pNode->data.prix;
                }
                fprintf(f, "%d;%d;%d;%d;%d;%s;%s;%.2f\n",
                        c->data.id, c->data.matriculeClient, c->data.idPokemon,
                        c->data.quantite, c->data.quantiteProduite,
                        c->data.dateHeure, et, revenu);
                c = c->next;
            }
            fclose(f);
            printf("  -> export_commandes.csv\n");
            ok++;
        }
    }

    // ---- 5. RAPPORT GLOBAL ----
    {
        FILE* f = fopen("export_rapport_global.csv", "w");
        if (f) {
            ecrireEntete(f, "Rapport Global - Usine Pokemon");
            fprintf(f, "Indicateur;Valeur\n");
            fprintf(f, "Caisse actuelle;%.2f\n", caisse);
            fprintf(f, "Nombre de Pokemons;%d\n",  compterPokemons(listePokemons));
            fprintf(f, "Nombre de Machines;%d\n",  compterMachines(listeMachines));
            fprintf(f, "Nombre de Clients;%d\n",   compterClients(listeClients));
            fprintf(f, "Nombre de Commandes;%d\n", compterCommandes(listeCommandes));

            int ea=0, ec=0, er=0;
            ListeCommande* cmd = listeCommandes;
            while (cmd) {
                if      (cmd->data.etat==0) ea++;
                else if (cmd->data.etat==1) ec++;
                else                        er++;
                cmd = cmd->next;
            }
            fprintf(f, "Commandes en attente;%d\n", ea);
            fprintf(f, "Commandes en cours;%d\n",   ec);
            fprintf(f, "Commandes realisees;%d\n",  er);

            // Revenu total
            float revenuTotal = 0.0f;
            cmd = listeCommandes;
            while (cmd) {
                if (cmd->data.etat == 2) {
                    ListePokemon* pNode = rechercherPokemon(listePokemons, cmd->data.idPokemon);
                    if (pNode) revenuTotal += cmd->data.quantiteProduite * pNode->data.prix;
                }
                cmd = cmd->next;
            }
            fprintf(f, "Revenu total genere;%.2f\n", revenuTotal);

            fclose(f);
            printf("  -> export_rapport_global.csv\n");
            ok++;
        }
    }

    printf("\n=== Export CSV termine : %d fichier(s) cree(s) ===\n", ok);
}

#ifndef GUI

// ============================================================
//  ECRAN GUI EXPORT
// ============================================================
static bool exportDone = false;


void menuExportGUI(Ecran *ecranActuel)
{
    DrawText("EXPORT CSV", 540, 40, 34, WHITE);
    DrawText("Exporte les donnees en fichiers .csv", 400, 90, 20, LIGHTGRAY);
    DrawText("(dans le meme dossier que l'executable)", 390, 115, 18, LIGHTGRAY);

    DrawText("Fichiers qui seront crees :", 200, 170, 20, WHITE);
    DrawText("  export_pokemons.csv",        200, 200, 18, (Color){100,220,100,255});
    DrawText("  export_machines.csv",        200, 225, 18, (Color){100,220,100,255});
    DrawText("  export_clients.csv",         200, 250, 18, (Color){100,220,100,255});
    DrawText("  export_commandes.csv",       200, 275, 18, (Color){100,220,100,255});
    DrawText("  export_rapport_global.csv",  200, 300, 18, (Color){100,220,100,255});
    DrawText("Ouvrez-les avec Excel ou LibreOffice.", 200, 340, 18, LIGHTGRAY);

    // Bouton export
    if (bouton((Rectangle){430, 400, 300, 55}, "Lancer l'export CSV"))
    {
        exporterCSV(listePokemons, listeMachines, listeClients, listeCommandes, caisse);
        exportDone = true;
        UI_Notif("Export CSV termine ! 5 fichiers crees.", NOTIF_SUCCES);
    }

    if (exportDone)
    {
        DrawText("Export effectue avec succes !", 430, 475, 20, (Color){80,255,120,255});
        DrawText("Verifiez le dossier de l'executable.", 400, 500, 18, LIGHTGRAY);
    }

    if (bouton((Rectangle){490, 570, 200, 48}, "Retour"))
    {
        exportDone = false;
        *ecranActuel = ECRAN_MENU;
    }
}

#endif
