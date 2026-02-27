# Makefile pour le projet Usine Pokemon V2
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = usine_pokemon_v2
OBJECTS = main.o pokemon.o machine.o client.o commande.o menu.o production.o

# Règle par défaut
all: $(TARGET)

# Règle de compilation du programme principal
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Règles de compilation des fichiers objets
main.o: main.c headers.h pokemon.h machine.h client.h commande.h menu.h
	$(CC) $(CFLAGS) -c main.c

pokemon.o: pokemon.c headers.h pokemon.h
	$(CC) $(CFLAGS) -c pokemon.c

machine.o: machine.c headers.h machine.h pokemon.h commande.h
	$(CC) $(CFLAGS) -c machine.c

client.o: client.c headers.h client.h commande.h pokemon.h
	$(CC) $(CFLAGS) -c client.c

commande.o: commande.c headers.h commande.h pokemon.h client.h
	$(CC) $(CFLAGS) -c commande.c

menu.o: menu.c headers.h menu.h
	$(CC) $(CFLAGS) -c menu.c

production.o: production.c headers.h
	$(CC) $(CFLAGS) -c production.c

# Règle de nettoyage
clean:
	rm -f $(OBJECTS) $(TARGET)

# Règle pour nettoyer et recompiler
rebuild: clean all

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)
