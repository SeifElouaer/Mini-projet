# LIVRAISON VERSION 2 - USINE POKÉMON

## Informations du Projet
- **Nom du projet** : Gestion d'une usine de figurines Pokémons
- **Version** : 2 (Dynamique avec fichiers)
- **Étudiant** : ElouaerSeif
- **Classe** : 1AGI1
- **Année** : 2025-2026

## Contenu de la Livraison

### Fichiers Sources (.c) - 7 fichiers
1. **main.c** - Programme principal avec gestion des fichiers
2. **pokemon.c** - Gestion des Pokémons (CRUD + fichiers)
3. **machine.c** - Gestion des machines (CRUD + fichiers)
4. **client.c** - Gestion des clients (CRUD + fichiers)
5. **commande.c** - Gestion des commandes (CRUD + fichiers)
6. **menu.c** - Menus interactifs
7. **production.c** - Fonctions de production et maintenance (NOUVEAU V2)

### Fichiers d'En-tête (.h) - 6 fichiers
1. **headers.h** - Définitions globales et structures
2. **pokemon.h** - Prototypes Pokémon
3. **machine.h** - Prototypes Machine
4. **client.h** - Prototypes Client
5. **commande.h** - Prototypes Commande
6. **menu.h** - Prototypes Menu

### Fichiers de Configuration
1. **ElouaerSeif_1AGI1_V2.cbp** - Projet Code::Blocks
2. **Makefile** - Script de compilation

### Documentation (.md) - 4 fichiers
1. **README.md** - Guide d'utilisation complet
2. **COMPARAISON_V1_V2.md** - Analyse des différences V1/V2
3. **GUIDE_TEST.md** - Scénarios de test détaillés
4. **LIVRAISON.md** - Ce fichier

## Nouveautés Version 2

### 1. Structures de Données Dynamiques
- ✅ Remplacement des tableaux par des listes chaînées
- ✅ Allocation dynamique avec `malloc()`
- ✅ Libération de la mémoire avec `free()`
- ✅ Capacité illimitée (limitée seulement par la RAM)

### 2. Gestion des Fichiers
- ✅ Sauvegarde automatique à la fermeture
- ✅ Chargement automatique au démarrage
- ✅ 5 fichiers de données :
  - `pokemons.txt`
  - `machines.txt`
  - `clients.txt`
  - `commandes.txt`
  - `caisse.txt`

### 3. Fonctions Supplémentaires

#### realiserCommande()
- Vérification de l'état de la machine
- Calcul du temps de production
- Mise à jour de la caisse (+argent)
- Changement d'état de la commande
- Gestion du compteur de production
- Passage automatique en maintenance

#### entretenirMachine()
- Vérification de la caisse
- Paiement du coût de maintenance (-argent)
- Réinitialisation du compteur
- Changement d'état (maintenance → libre)

#### afficherStatistiques()
- État de la caisse
- Nombre d'éléments par catégorie
- Répartition des commandes (attente/cours/réalisées)
- Répartition des machines (libre/occupée/maintenance)

### 4. Gestion du Temps
- ✅ Utilisation de `time.h`
- ✅ Date/heure automatique pour les commandes
- ✅ Stockage du timestamp

### 5. Gestion de la Caisse
- ✅ Variable globale modifiable
- ✅ Augmentation lors des ventes
- ✅ Diminution lors des maintenances
- ✅ Sauvegarde dans fichier
- ✅ Vérification avant dépense

## Compilation et Exécution

### Méthode 1 : Avec Makefile (Recommandé)
```bash
make                # Compiler
make run            # Compiler et exécuter
make clean          # Nettoyer
make rebuild        # Nettoyer et recompiler
```

### Méthode 2 : Avec GCC
```bash
gcc -Wall -Wextra -o usine_pokemon_v2 main.c pokemon.c machine.c client.c commande.c menu.c production.c
./usine_pokemon_v2
```

### Méthode 3 : Avec Code::Blocks
1. Ouvrir `ElouaerSeif_1AGI1_V2.cbp`
2. Build > Build (Ctrl+F9)
3. Build > Run (Ctrl+F10)

## Fonctionnalités Testées

### CRUD Complet
- ✅ Create (Ajouter)
- ✅ Read (Afficher)
- ✅ Update (Modifier)
- ✅ Delete (Supprimer)

### Opérations Avancées
- ✅ Production de commandes
- ✅ Maintenance des machines
- ✅ Gestion de la caisse
- ✅ Statistiques détaillées
- ✅ Validation des données
- ✅ Gestion des erreurs

### Persistance
- ✅ Sauvegarde dans fichiers
- ✅ Chargement depuis fichiers
- ✅ Conservation entre sessions

## Architecture du Code

### Modularité
- 1 fichier par entité (pokemon, machine, client, commande)
- Séparation des responsabilités
- Headers pour les interfaces
- Code source pour les implémentations

### Bonnes Pratiques
- ✅ Noms de variables explicites
- ✅ Commentaires pour les sections importantes
- ✅ Gestion des erreurs
- ✅ Validation des entrées
- ✅ Messages informatifs
- ✅ Indentation cohérente

## Points d'Amélioration Possibles (Bonus)

### Implémentés
- Production complète
- Maintenance des machines
- Statistiques détaillées

### Suggestions Futures
- Interface graphique (GTK, SDL)
- Base de données (SQLite)
- Statistiques avancées (graphiques)
- Gestion multi-utilisateurs
- Système de logs
- Export en PDF/Excel

## Scénario de Démonstration

### Étape 1 : Configuration Initiale
1. Créer 3 Pokémons (Pikachu, Bulbizarre, Salamèche)
2. Créer 2 Machines (M_Pikachu, M_Bulbizarre)
3. Créer 2 Clients (Jean, Marie)

### Étape 2 : Commandes
1. Jean commande 3 Pikachu
2. Marie commande 4 Pikachu

### Étape 3 : Production
1. Réaliser commande de Jean (Caisse +60)
2. Réaliser commande de Marie (Caisse +80, Machine → Maintenance)

### Étape 4 : Maintenance
1. Effectuer maintenance de M_Pikachu (Caisse -10)

### Étape 5 : Persistance
1. Quitter et sauvegarder
2. Relancer et vérifier que tout est conservé

## Critères d'Évaluation Remplis

### Version Statique (7 points) - Déjà validé en V1
- ✅ Structures de données
- ✅ Fonctions CRUD
- ✅ Menu interactif
- ✅ Modularité

### Version Dynamique (10 points)
- ✅ Listes chaînées
- ✅ Gestion des fichiers
- ✅ Fonction realiserCommande()
- ✅ Fonction entretenirMachine()
- ✅ Gestion du temps
- ✅ Statistiques

### Bonus (3 points)
- ✅ Statistiques avancées
- ✅ Gestion complète de la caisse
- ✅ Validation robuste des données
- ✅ Documentation complète
- ✅ Guide de test détaillé

## Vérification Avant Livraison

### Compilation
- [x] Compile sans erreurs
- [x] Compile sans warnings
- [x] Exécution sans crash

### Fonctionnalités
- [x] CRUD complet pour toutes les entités
- [x] Production fonctionnelle
- [x] Maintenance fonctionnelle
- [x] Sauvegarde/Chargement fonctionnels

### Documentation
- [x] README complet
- [x] Comparaison V1/V2
- [x] Guide de test
- [x] Commentaires dans le code

### Fichiers
- [x] Tous les .c présents
- [x] Tous les .h présents
- [x] Fichier .cbp présent
- [x] Makefile présent
- [x] Documentation présente

## Contact et Support

Pour toute question ou problème :
1. Consulter le README.md
2. Consulter le GUIDE_TEST.md
3. Vérifier la compilation
4. Contacter l'enseignant

## Conclusion

La **Version 2** est complète et fonctionnelle. Elle démontre :
- ✅ Maîtrise des structures de données dynamiques
- ✅ Compétence en gestion de fichiers
- ✅ Capacité à développer des fonctionnalités avancées
- ✅ Rigueur dans la documentation
- ✅ Attention aux détails

**Prêt pour la soutenance !**

---

Date de livraison : Février 2026
Version : 2.0
Statut : Terminé ✅
