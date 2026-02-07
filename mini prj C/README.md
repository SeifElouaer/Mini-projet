# USINE DE FIGURINES POKÉMON - VERSION 2 (V2)

## Auteur
ElouaerSeif_1AGI1

## Description
Version 2 du projet de gestion d'une usine de figurines Pokémon avec :
- Structures de données dynamiques (listes chaînées)
- Sauvegarde et chargement depuis des fichiers
- Gestion complète de la production
- Maintenance des machines
- Gestion de la caisse

## Améliorations par rapport à la Version 1
1. **Listes chaînées** : Remplacement des tableaux statiques par des listes dynamiques
2. **Persistance des données** : Sauvegarde automatique dans des fichiers texte
3. **Production réelle** : Fonction `realiserCommande()` complète
4. **Maintenance** : Fonction `entretenirMachine()` avec gestion de la caisse
5. **Statistiques** : Affichage détaillé de l'état de l'usine

## Structure du Projet

### Fichiers sources (.c)
- `main.c` : Point d'entrée du programme avec gestion des fichiers
- `pokemon.c` : Gestion des Pokémons
- `machine.c` : Gestion des machines
- `client.c` : Gestion des clients
- `commande.c` : Gestion des commandes
- `menu.c` : Menus interactifs
- `production.c` : Fonctions de production et maintenance

### Fichiers d'en-tête (.h)
- `headers.h` : Définitions des structures et includes globaux
- `pokemon.h` : Prototypes des fonctions Pokémon
- `machine.h` : Prototypes des fonctions Machine
- `client.h` : Prototypes des fonctions Client
- `commande.h` : Prototypes des fonctions Commande
- `menu.h` : Prototypes des menus

### Fichiers de données (générés automatiquement)
- `pokemons.txt` : Liste des Pokémons
- `machines.txt` : Liste des machines
- `clients.txt` : Liste des clients
- `commandes.txt` : Liste des commandes
- `caisse.txt` : État de la caisse

## Compilation

### Avec Makefile (recommandé)
```bash
make
```

### Compilation manuelle avec GCC
```bash
gcc -Wall -Wextra -o usine_pokemon_v2 main.c pokemon.c machine.c client.c commande.c menu.c production.c
```

### Avec Code::Blocks
1. Créer un nouveau projet Console Application
2. Ajouter tous les fichiers .c et .h
3. Compiler et exécuter

## Exécution
```bash
./usine_pokemon_v2
```

Ou avec Make :
```bash
make run
```

## Utilisation

### Premier démarrage
Au premier lancement, le programme :
1. Cherche les fichiers de données
2. Si absents, démarre avec des listes vides
3. Affiche un message d'information

### Menu principal
1. **Gérer les Pokémon** : CRUD sur les types de figurines
2. **Gérer les machines** : CRUD sur les machines de production
3. **Gérer les clients** : CRUD sur les clients
4. **Gérer les commandes** : CRUD sur les commandes
5. **Production et maintenance** : 
   - Réaliser une commande
   - Entretenir une machine
   - Afficher l'état des machines
6. **Afficher l'état de l'usine** : Statistiques complètes
7. **Quitter et sauvegarder** : Sauvegarde automatique

### Workflow typique

#### 1. Créer des Pokémons
```
Menu > 1. Gérer les Pokémon > 1. Ajouter
- Nom : Pikachu
- Coût : 20
- Type : Electrique
```

#### 2. Créer des Machines
```
Menu > 2. Gérer les machines > 1. Ajouter
- Nom : Machine_Pikachu
- ID Pokemon : 1
- Temps production : 2 minutes
- Max figurines : 5
- Coût maintenance : 10
```

#### 3. Créer des Clients
```
Menu > 3. Gérer les clients > 1. Ajouter
- Nom : Jean
```

#### 4. Créer des Commandes
```
Menu > 4. Gérer les commandes > 1. Ajouter
- ID Client : 1
- ID Pokemon : 1
- Quantité : 3
```

#### 5. Réaliser la Production
```
Menu > 5. Production et maintenance > 1. Réaliser une commande
- ID Commande : 1
[Le programme affiche les détails et simule la production]
```

#### 6. Entretenir une Machine
```
Menu > 5. Production et maintenance > 2. Entretenir une machine
- ID Machine : 1
[La machine repasse à l'état libre après paiement]
```

## Format des Fichiers de Données

### pokemons.txt
Format : `id;nom;prix;type`
```
1;Pikachu;20.00;Electrique
2;Bulbizarre;25.00;Plante
```

### machines.txt
Format : `id;nom;idPokemon;tempsProd;nbMax;compteur;coutMaint;etat;idCommande`
```
1;Machine_Pikachu;1;2;5;0;10.00;0;0
```

### commandes.txt
Format : `id;matriculeClient;idPokemon;quantite;dateHeure;etat`
```
1;1;1;3;Thu Feb 06 10:30:25 2026;0
```

### clients.txt
Format : `matricule;nom;nbCommandes;id1;id2;...`
```
1;Jean;2;1;2
```

### caisse.txt
Format : `montant`
```
1000.00
```

## États

### États des Machines
- 0 : Libre
- 1 : Occupée
- 2 : En attente de maintenance

### États des Commandes
- 0 : En attente
- 1 : En cours
- 2 : Réalisée

## Fonctionnalités Avancées

### Gestion de la Caisse
- Caisse initiale : 1000 pièces
- Augmente lors des ventes
- Diminue lors des maintenances
- Vérification avant chaque dépense

### Maintenance Automatique
- Compteur de production par machine
- Passage automatique en maintenance après nbMax figurines
- Impossible de produire tant que la maintenance n'est pas faite

### Validation des Données
- Vérification de l'existence des Pokémons
- Vérification de l'état des machines
- Vérification de la disponibilité
- Messages d'erreur détaillés

## Nettoyage

Pour supprimer les fichiers compilés :
```bash
make clean
```

Pour tout nettoyer et recompiler :
```bash
make rebuild
```

## Conseils d'Utilisation

1. **Toujours créer les Pokémons en premier**
2. **Créer les machines associées aux Pokémons**
3. **Créer les clients**
4. **Créer les commandes**
5. **Réaliser les productions**
6. **Surveiller l'état des machines**
7. **Effectuer les maintenances nécessaires**

## Gestion de la Mémoire

Le programme :
- Alloue dynamiquement la mémoire pour chaque élément
- Libère toute la mémoire à la fermeture
- Affiche un message de confirmation

## Debugging

Pour compiler avec les symboles de debug :
```bash
gcc -g -Wall -Wextra -o usine_pokemon_v2 main.c pokemon.c machine.c client.c commande.c menu.c production.c
```

Puis utiliser gdb :
```bash
gdb ./usine_pokemon_v2
```

## Limitations Connues

1. Les dates/heures sont générées automatiquement (pas de modification manuelle)
2. Les IDs sont auto-incrémentés (pas de réinitialisation)
3. Un Pokémon ne peut être supprimé s'il est utilisé par une machine
4. Une machine ne peut être supprimée si elle a une commande en cours

## Auteur et Contact

Projet réalisé dans le cadre du cours de Programmation C
Classe : 1AGI1
Année : 2025-2026
