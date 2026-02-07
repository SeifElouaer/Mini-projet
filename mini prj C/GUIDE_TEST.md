# GUIDE DE TEST - VERSION 2

## Objectif
Ce guide vous permet de tester toutes les fonctionnalités de la Version 2.

## Préparation

### 1. Compilation
```bash
make clean
make
```

Ou avec GCC directement :
```bash
gcc -Wall -Wextra -o usine_pokemon_v2 main.c pokemon.c machine.c client.c commande.c menu.c production.c
```

### 2. Vérification
```bash
ls -la
```
Vous devriez voir : `usine_pokemon_v2` (ou `usine_pokemon_v2.exe` sur Windows)

## Scénario de Test Complet

### TEST 1 : Premier Démarrage (Liste Vide)

#### Étape 1 : Lancer le programme
```bash
./usine_pokemon_v2
```

**Résultat attendu :**
```
========================================
====== CHARGEMENT DES DONNEES ========
========================================

INFO: Fichier caisse.txt non trouve. Utilisation de la caisse initiale.
Caisse chargee: 1000.00 pieces
INFO: Fichier pokemons.txt non trouve. Demarrage avec liste vide.
INFO: Fichier machines.txt non trouve. Demarrage avec liste vide.
INFO: Fichier clients.txt non trouve. Demarrage avec liste vide.
INFO: Fichier commandes.txt non trouve. Demarrage avec liste vide.

Chargement termine!
========================================
```

### TEST 2 : Créer des Pokémons

#### Actions
1. Choisir `1` (Gérer les Pokémon)
2. Choisir `1` (Ajouter un Pokémon)
3. Entrer les données :
   - Nom : `Pikachu`
   - Coût : `20`
   - Type : `Electrique`
4. Répéter pour créer :
   - Bulbizarre, 25, Plante
   - Salamèche, 30, Feu
5. Choisir `2` (Afficher les Pokémons)
6. Choisir `0` (Retour)

**Résultat attendu :**
```
#### Pokemon 1 ####
- ID: 1 | Nom: Pikachu | Cout: 20.00 | Type: Electrique
#### Pokemon 2 ####
- ID: 2 | Nom: Bulbizarre | Cout: 25.00 | Type: Plante
#### Pokemon 3 ####
- ID: 3 | Nom: Salameche | Cout: 30.00 | Type: Feu
```

### TEST 3 : Créer des Machines

#### Actions
1. Choisir `2` (Gérer les machines)
2. Choisir `1` (Ajouter une machine)
3. Entrer les données :
   - Nom : `M_Pikachu`
   - ID Pokemon : `1`
   - Temps prod : `2`
   - Nb max : `5`
   - Coût maint : `10`
4. Répéter pour :
   - M_Bulbizarre, Pokemon 2, Temps 3, Max 4, Coût 15
5. Choisir `2` (Afficher les machines)
6. Choisir `0` (Retour)

**Résultat attendu :**
```
#### Machine 1 ####
- ID: 1 | Nom: M_Pikachu | Pokemon: 1
  Temps prod: 2 min | Max: 5 | Compteur: 0
  Cout maint: 10.00 | Etat: Libre
  Aucune commande en cours
```

### TEST 4 : Créer des Clients

#### Actions
1. Choisir `3` (Gérer les clients)
2. Choisir `1` (Ajouter un client)
3. Entrer : Nom = `Jean`
4. Ajouter un autre : Nom = `Marie`
5. Choisir `2` (Afficher)
6. Choisir `0` (Retour)

**Résultat attendu :**
```
#### Client 1 ####
- Matricule: 1 | Nom: Jean
  Nombre de commandes: 0
#### Client 2 ####
- Matricule: 2 | Nom: Marie
  Nombre de commandes: 0
```

### TEST 5 : Créer des Commandes

#### Actions
1. Choisir `4` (Gérer les commandes)
2. Choisir `1` (Ajouter une commande)
3. Entrer :
   - ID client : `1`
   - ID Pokemon : `1`
   - Quantité : `3`
4. Ajouter une autre :
   - ID client : `2`
   - ID Pokemon : `1`
   - Quantité : `4`
5. Choisir `2` (Afficher)
6. Choisir `0` (Retour)

**Résultat attendu :**
```
#### Commande 1 ####
- ID: 1 | Client: 1 | Pokemon: 1 | Quantite: 3
  Date/Heure: Thu Feb 06 10:30:25 2026 | Etat: En attente
#### Commande 2 ####
- ID: 2 | Client: 2 | Pokemon: 1 | Quantite: 4
  Date/Heure: Thu Feb 06 10:31:15 2026 | Etat: En attente
```

### TEST 6 : Afficher l'État de l'Usine

#### Actions
1. Choisir `6` (Afficher l'état de l'usine)

**Résultat attendu :**
```
========================================
===== STATISTIQUES DE L'USINE ======
========================================

Caisse de l'usine: 1000.00 pieces

Nombre de Pokemons: 3
Nombre de machines: 2
Nombre de clients: 2
Nombre de commandes: 2

Commandes en attente: 2
Commandes en cours: 0
Commandes realisees: 0

Machines libres: 2
Machines occupees: 0
Machines en attente de maintenance: 0

========================================
```

### TEST 7 : Réaliser une Commande

#### Actions
1. Choisir `5` (Production et maintenance)
2. Choisir `1` (Réaliser une commande)
3. Entrer ID commande : `1`
4. Lire les informations affichées
5. Appuyer sur Entrée pour terminer la production

**Résultat attendu :**
```
=== REALISATION DE LA COMMANDE 1 ===
Client: 1
Pokemon: Pikachu (ID: 1)
Quantite: 3
Machine: M_Pikachu (ID: 1)

Machine disponible. Debut de la production...
Temps de production: 6 minutes (3 x 2)
Cout de production: 60.00 pieces (20.00 x 3)

Production lancee!
Appuyez sur Entree pour terminer la production...

=== PRODUCTION TERMINEE ===
Paiement recu: 60.00 pieces
Nouvelle caisse: 1060.00 pieces

Machine libre. Figurines produites: 3/5

Commande 1 realisee avec succes!
```

### TEST 8 : Vérifier la Caisse

#### Actions
1. Retour au menu principal
2. Choisir `6` (Afficher l'état)

**Résultat attendu :**
```
Caisse de l'usine: 1060.00 pieces
```

### TEST 9 : Réaliser Deuxième Commande

#### Actions
1. Choisir `5` (Production et maintenance)
2. Choisir `1` (Réaliser une commande)
3. Entrer ID : `2`
4. Appuyer sur Entrée

**Résultat attendu :**
```
=== PRODUCTION TERMINEE ===
Paiement recu: 80.00 pieces
Nouvelle caisse: 1140.00 pieces

ATTENTION: La machine a produit 7/5 figurines.
La machine passe en attente de maintenance.

Commande 2 realisee avec succes!
```

### TEST 10 : Tenter une Production (Machine en Maintenance)

#### Actions
1. Créer une nouvelle commande (Menu 4 > 1)
   - Client : 1
   - Pokemon : 1
   - Quantité : 2
2. Essayer de la réaliser (Menu 5 > 1)
3. Entrer l'ID de la nouvelle commande

**Résultat attendu :**
```
ERREUR: La machine est en attente de maintenance.
Veuillez d'abord effectuer la maintenance (cout: 10.00 pieces).
```

### TEST 11 : Effectuer la Maintenance

#### Actions
1. Choisir `2` (Entretenir une machine)
2. Entrer ID machine : `1`

**Résultat attendu :**
```
=== MAINTENANCE DE LA MACHINE 1 ===
Cout de la maintenance: 10.00 pieces
Maintenance effectuee avec succes!
Nouvelle caisse: 1130.00 pieces
Machine 1 est maintenant libre.
```

### TEST 12 : Modifier un Pokémon

#### Actions
1. Menu principal > 1 (Gérer les Pokémon)
2. Choisir `3` (Modifier)
3. Entrer ID : `1`
4. Choisir `2` (Cout)
5. Entrer nouveau coût : `22`
6. Choisir `0` (Retour)
7. Afficher les Pokémons

**Résultat attendu :**
```
- ID: 1 | Nom: Pikachu | Cout: 22.00 | Type: Electrique
```

### TEST 13 : Supprimer une Commande

#### Actions
1. Menu 4 (Gérer les commandes)
2. Choisir `4` (Supprimer)
3. Entrer ID : `1`
4. Afficher les commandes

**Résultat attendu :**
```
Commande supprimee avec succes.
```
La commande 1 ne doit plus apparaître.

### TEST 14 : Sauvegarder et Quitter

#### Actions
1. Retour au menu principal
2. Choisir `0` (Quitter et sauvegarder)

**Résultat attendu :**
```
========================================
====== SAUVEGARDE DES DONNEES =========
========================================

Caisse sauvegardee: 1130.00 pieces
Pokemons sauvegardes dans pokemons.txt
Machines sauvegardees dans machines.txt
Clients sauvegardes dans clients.txt
Commandes sauvegardees dans commandes.txt

Sauvegarde terminee!
========================================

Liberation de la memoire...
Memoire liberee avec succes.

========================================
Merci d'avoir utilise l'usine Pokemon!
Au revoir!
========================================
```

### TEST 15 : Vérifier les Fichiers Créés

#### Actions
```bash
ls -la *.txt
cat caisse.txt
cat pokemons.txt
```

**Résultat attendu :**
Vous devriez voir 5 fichiers .txt avec les données sauvegardées.

### TEST 16 : Deuxième Démarrage (Avec Données)

#### Actions
```bash
./usine_pokemon_v2
```

**Résultat attendu :**
```
========================================
====== CHARGEMENT DES DONNEES ========
========================================

Caisse chargee: 1130.00 pieces
Pokemons charges depuis pokemons.txt
Machines chargees depuis machines.txt
Clients charges depuis clients.txt
Commandes chargees depuis commandes.txt

Chargement termine!
========================================
```

Vérifier que toutes les données sont bien présentes !

## Tests d'Erreur

### Test E1 : Ajouter une Machine avec Pokémon Inexistant
1. Menu 2 > 1
2. Entrer ID Pokemon : `999`

**Résultat attendu :** Message d'erreur et redemande de l'ID

### Test E2 : Réaliser une Commande Inexistante
1. Menu 5 > 1
2. Entrer ID : `999`

**Résultat attendu :** "Commande 999 introuvable."

### Test E3 : Maintenance sans Argent
1. Modifier la caisse pour qu'elle soit insuffisante
2. Essayer une maintenance

**Résultat attendu :** "ERREUR: Caisse insuffisante"

### Test E4 : Suppression d'un Élément Inexistant
1. Menu 1 > 4 (Supprimer Pokemon)
2. Entrer ID : `999`

**Résultat attendu :** "Pokemon introuvable."

## Checklist de Validation

- [ ] Compilation sans erreurs ni warnings
- [ ] Création de Pokémons
- [ ] Création de Machines
- [ ] Création de Clients
- [ ] Création de Commandes
- [ ] Affichage de tous les éléments
- [ ] Modification d'éléments
- [ ] Suppression d'éléments
- [ ] Réalisation de commande
- [ ] Mise à jour de la caisse
- [ ] Passage en maintenance automatique
- [ ] Entretien de machine
- [ ] Affichage des statistiques
- [ ] Sauvegarde dans les fichiers
- [ ] Chargement depuis les fichiers
- [ ] Gestion des erreurs
- [ ] Libération de la mémoire

## Outils de Debug

### Vérifier les fuites mémoire (Linux)
```bash
valgrind --leak-check=full ./usine_pokemon_v2
```

### Afficher les allocations
```bash
valgrind --track-origins=yes ./usine_pokemon_v2
```

## Conclusion

Si tous les tests passent, la Version 2 est **fonctionnelle et complète** !

En cas d'erreur, vérifier :
1. Les messages de compilation
2. Les fichiers .h sont bien inclus
3. Les fonctions sont bien déclarées
4. La mémoire est bien libérée
