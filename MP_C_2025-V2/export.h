#ifndef EXPORT_H_INCLUDED
#define EXPORT_H_INCLUDED

// Export CSV - version console ET interface
void exporterCSV(ListePokemon* listePokemons, ListeMachine* listeMachines,
                 ListeClient* listeClients, ListeCommande* listeCommandes,
                 float caisse);

#ifndef GUI
void menuExportGUI(Ecran *ecranActuel);
#endif

#endif // EXPORT_H_INCLUDED
