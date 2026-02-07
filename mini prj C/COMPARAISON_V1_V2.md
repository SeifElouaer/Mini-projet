# COMPARAISON VERSION 1 vs VERSION 2

## Vue d'ensemble

### Version 1 (Statique)
- Utilise des **tableaux statiques** de taille fixe
- Capacité limitée (MAX_POKEMONS, MAX_MACHINES, etc.)
- Données perdues à la fermeture du programme
- Pas de production réelle
- CRUD basique uniquement

### Version 2 (Dynamique)
- Utilise des **listes chaînées**
- Capacité illimitée (limitée uniquement par la RAM)
- Données **sauvegardées dans des fichiers**
- Production complète avec simulation
- Maintenance des machines
- Gestion de la caisse

## Différences Détaillées

### 1. Structures de Données

#### VERSION 1
```c
// Tableaux statiques
pokemon Tab_Pokemon[MAX_POKEMONS];    // Taille fixe : 50
machine Tab_Machine[MAX_MACHINES];    // Taille fixe : 20
client Tab_Client[MAX_CLIENTS];       // Taille fixe : 30
commande Tab_Commande[MAX_COMMANDES]; // Taille fixe : 100

int nbPokemons = 0;  // Compteur
```

**Limitations :**
- Taille maximale fixe
- Gaspillage de mémoire si peu d'éléments
- Erreur si dépassement de capacité

#### VERSION 2
```c
// Listes chaînées
typedef struct ListePokemon {
    pokemon data;
    struct ListePokemon* next;
} ListePokemon;

ListePokemon* listePokemons = NULL;  // Pointeur vers le premier élément
```

**Avantages :**
- Taille dynamique
- Utilisation optimale de la mémoire
- Pas de limite (sauf RAM disponible)

### 2. Gestion des Données

#### VERSION 1
- Données en **mémoire volatile** uniquement
- Perte totale à la fermeture
- Redémarrage à zéro à chaque exécution

#### VERSION 2
- **Sauvegarde automatique** dans des fichiers texte
- **Chargement automatique** au démarrage
- Persistance des données entre les sessions

**Fichiers créés :**
- `pokemons.txt`
- `machines.txt`
- `clients.txt`
- `commandes.txt`
- `caisse.txt`

### 3. Fonctions Principales

#### Ajout d'un Pokémon

**VERSION 1**
```c
void ajouterPokemon(pokemon p[], int *n) {
    if (*n >= MAX_POKEMONS) {
        printf("ERREUR : Le tableau est plein.\n");
    } else {
        p[*n] = creerPokemon();
        (*n)++;
    }
}
```

**VERSION 2**
```c
void ajouterPokemon(ListePokemon** liste) {
    ListePokemon* nouveau = (ListePokemon*)malloc(sizeof(ListePokemon));
    nouveau->data = creerPokemon();
    nouveau->next = *liste;
    *liste = nouveau;
}
```

#### Recherche d'un Pokémon

**VERSION 1**
```c
int rechercherPokemon(pokemon p[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (p[i].id == id)
            return i;  // Retourne l'index
    }
    return -1;
}
```

**VERSION 2**
```c
ListePokemon* rechercherPokemon(ListePokemon* liste, int id) {
    ListePokemon* current = liste;
    while (current != NULL) {
        if (current->data.id == id)
            return current;  // Retourne le pointeur
        current = current->next;
    }
    return NULL;
}
```

### 4. Fonctionnalités Supplémentaires

#### VERSION 1
- CRUD uniquement :
  - Create (Ajouter)
  - Read (Afficher)
  - Update (Modifier)
  - Delete (Supprimer)

#### VERSION 2
- CRUD complet
- **Production réelle** : `realiserCommande()`
  - Vérification de l'état de la machine
  - Calcul du temps de production
  - Mise à jour de la caisse
  - Changement d'état de la commande
  - Gestion du compteur de production

- **Maintenance** : `entretenirMachine()`
  - Vérification de la caisse
  - Paiement du coût de maintenance
  - Réinitialisation du compteur
  - Changement d'état de la machine

- **Statistiques** : `afficherStatistiques()`
  - État de la caisse
  - Nombre d'éléments par catégorie
  - Répartition des commandes par état
  - Répartition des machines par état

### 5. Gestion de la Mémoire

#### VERSION 1
- Allocation statique au démarrage
- Pas de gestion manuelle
- Mémoire libérée automatiquement à la fin

#### VERSION 2
- **Allocation dynamique** avec `malloc()`
- **Libération manuelle** avec `free()`
- Fonctions de libération :
  ```c
  void libererListePokemon(ListePokemon** liste);
  void libererListeMachine(ListeMachine** liste);
  void libererListeClient(ListeClient** liste);
  void libererListeCommande(ListeCommande** liste);
  ```

### 6. Structure du Client

#### VERSION 1
```c
typedef struct client {
    int matricule;
    char nom[20];
    int nbrCommande;
    commande liste[MAX_COMMANDES];  // Tableau statique
} client;
```

#### VERSION 2
```c
typedef struct client {
    int matricule;
    char nom[20];
    ListeCommande* commandes;  // Liste chaînée
} client;
```

### 7. Flux du Programme

#### VERSION 1
```
Démarrage
    ↓
Initialisation des tableaux vides
    ↓
Menu principal
    ↓
Opérations CRUD
    ↓
Fermeture (perte des données)
```

#### VERSION 2
```
Démarrage
    ↓
Chargement depuis les fichiers
    ↓
Initialisation des listes chaînées
    ↓
Menu principal
    ↓
Opérations CRUD + Production + Maintenance
    ↓
Sauvegarde dans les fichiers
    ↓
Libération de la mémoire
    ↓
Fermeture
```

### 8. Menu Principal

#### VERSION 1
```
1. Gérer les Pokémon
2. Gérer les machines
3. Gérer les clients
4. Gérer les commandes
5. Afficher l'état de l'usine
6. Quitter
```

#### VERSION 2
```
1. Gérer les Pokémon
2. Gérer les machines
3. Gérer les clients
4. Gérer les commandes
5. Production et maintenance        ← NOUVEAU
   - Réaliser une commande
   - Entretenir une machine
   - Afficher l'état des machines
6. Afficher l'état de l'usine
0. Quitter et sauvegarder           ← MODIFIÉ
```

### 9. Gestion de la Caisse

#### VERSION 1
```c
#define caisse 1000  // Constante, ne change jamais
```

#### VERSION 2
```c
float caisse = CAISSE_INITIALE;  // Variable globale modifiable

// Augmente lors des ventes
caisse += coutTotal;

// Diminue lors des maintenances
caisse -= machine->coutMaint;

// Sauvegardée dans caisse.txt
```

### 10. Complexité Algorithmique

#### Recherche
- **V1** : O(n) - parcours de tableau
- **V2** : O(n) - parcours de liste

#### Ajout
- **V1** : O(1) - ajout en fin de tableau
- **V2** : O(1) - ajout en tête de liste

#### Suppression
- **V1** : O(n) - décalage des éléments
- **V2** : O(n) - recherche puis suppression

### 11. Avantages et Inconvénients

#### VERSION 1

**Avantages :**
- Plus simple à comprendre
- Accès direct par index
- Pas de gestion de pointeurs

**Inconvénients :**
- Taille limitée
- Gaspillage de mémoire
- Pas de persistance
- Fonctionnalités limitées

#### VERSION 2

**Avantages :**
- Taille illimitée
- Mémoire optimisée
- Persistance des données
- Fonctionnalités complètes
- Plus proche du monde réel

**Inconvénients :**
- Plus complexe
- Gestion manuelle de la mémoire
- Risque de fuites mémoire si mal géré
- Accès séquentiel uniquement

## Migration V1 → V2

### Changements Nécessaires

1. **Remplacer les tableaux par des listes chaînées**
2. **Modifier toutes les fonctions CRUD**
3. **Ajouter les fonctions de fichiers**
4. **Créer les fonctions de production**
5. **Ajouter la gestion de la mémoire**
6. **Mettre à jour le menu principal**

### Nouveaux Fichiers

- `production.c` : Fonctions de production et maintenance
- `pokemons.txt`, `machines.txt`, etc. : Fichiers de données

### Fonctions Modifiées

Toutes les fonctions CRUD ont été adaptées pour :
- Accepter des pointeurs de listes au lieu de tableaux
- Utiliser `malloc()` pour l'allocation
- Parcourir les listes avec des boucles `while`
- Retourner des pointeurs au lieu d'indices

## Conclusion

La **Version 2** est une amélioration majeure qui :
- Rend le programme plus **professionnel**
- Permet une **utilisation réelle** avec sauvegarde
- Ajoute des **fonctionnalités essentielles**
- Prépare à des développements futurs

Elle démontre la maîtrise de concepts avancés :
- Allocation dynamique
- Gestion de fichiers
- Structures de données complexes
- Programmation modulaire
