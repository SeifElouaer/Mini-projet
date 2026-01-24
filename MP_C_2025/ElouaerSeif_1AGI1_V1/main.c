#include "headers.h"

int main()
{
    pokemon pokemons[];
    machine machines[];
    client clients[];
    commande commandes[];

    int nbPokemons = 0;
    int nbMachines = 0;
    int nbClients = 0;
    int nbCommandes = 0;

    while(1)
    {

        do{
            printf("\n=== USINE POKEMON ===\n");
            printf("1. Gerer les Pokemon\n");
            printf("2. Gerer les machines\n");
            printf("3. Gerer les clients\n");
            printf("4. Gerer les commandes\n");
            printf("5. Afficher l etat de l usine\n");
            printf("6. Quitter\n");

            printf("Donner votre choix: ");
            scanf("%d",&choix);
            fflush(stdin);
        }while(choix<0 || choix>6);

        switch (choix)
        {
            case 1:
            {
                printf("*** Saisir un ensemble d'etudiants ***\n");
                last_index=AjouterEtudiant(TabEtud,last_index, taille_tab_etu);
                break;
            }
            case 2:
            {
                printf("*** Afficher l'ensemble des etudiants ***\n");
                afficherTabEtudiant(TabEtud,last_index);
                break;
            }
            case 3:
            {
                printf("*** Chercher un etudiant par son Id***\n");
                position=rechercherId(TabEtud,last_index);
                if(position==-1)
                {
                    printf("L'etudiant n'existe pas!\n");
                }
                else
                {
                    printf("L'etudiant existe dans la position %d\n",position);
                    AfficherEtudiant(TabEtud[position]);
                }
                break;
            }
            case 4:
            {
                printf("*** Chercher un etudiant par son Nom***");
                printf("\nDonner le nom à rechercher :\n ");
                scanf("%s", nom);
                fflush(stdin);
                rechercherEtudiantNom(TabEtud,last_index,nom);
                break;
            }
            case 5:
            {
                printf("*** Modifier un etudiant ***\n");
                position=rechercherId(TabEtud,last_index);
                if (position==-1)
                {
                    printf("\n L'etudiant recherché n'existe pas\n");
                }
                else
                {
                    AfficherEtudiant(TabEtud[position]);
                    do{
                        printf("\n Vous etes sure de vouloir modifier cet etudiant: 1:Oui 0:Non\n");
                        scanf("%d",&rep);
                        fflush(stdin);
                    }while(rep!=0 && rep!=1);

                    if (rep==1)
                        modifier_etudiant(&TabEtud[position]);
                    else
                        printf ("Modification annulee\n");
                }
                break;
            }
            case 6:
            {
                printf("*** Supprimer un etudiant ***\n");
                position=rechercherId(TabEtud,last_index);
                if (position==-1)
                {
                    printf("\n L'etudiant recherche n'existe pas\n");
                }
                else
                {
                    AfficherEtudiant(TabEtud[position]);
                    do{
                        printf("\n Vous etes sure de vouloir supprimer cet etudiant: 1:Oui 0:Non\n");
                        scanf("%d",&rep);
                        fflush(stdin);
                    }while(rep!=0 && rep!=1);

                    if (rep==1)
                        supprimer_etudiant(TabEtud,&last_index,position);
                    else
                        printf ("Suppression annulee\n");
                }
                break;
            }
            case 0:
            {
                exit(0);
            }
            default: printf("Choix errone!\n");
        }

    }

    return 0;
}

