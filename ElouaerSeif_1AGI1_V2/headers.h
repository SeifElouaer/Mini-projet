#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#define CAISSE_INITIALE 1000

extern float caisse;

typedef struct pokemon pokemon;
typedef struct machine machine;
typedef struct client client;
typedef struct commande commande;

typedef struct ListePokemon ListePokemon;
typedef struct ListeMachine ListeMachine;
typedef struct ListeClient ListeClient;
typedef struct ListeCommande ListeCommande;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pokemon.h"
#include "machine.h"
#include "client.h"
#include "commande.h"
#include "menu.h"
#include "production.h"


#endif // HEADERS_H_INCLUDED
