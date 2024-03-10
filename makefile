CC = gcc
CFLAGS = -ansi -Wall -pedantic
LDFLAGS =-lm -lrt
MLV= -lMLV
OBJ = obj/main.o obj/Collision.o obj/Gardien.o obj/Gestion_terrain.o obj/Joueur.o obj/Moteur_de_jeu.o obj/Moteur_graphique.o obj/Relique.o obj/Deplacement.o obj/Menu.o obj/Score.o
DIR_SRC = src
DIR_OBJ = obj
DIR_HEADER = include
DIR_BIN = bin
TARGET = exe

all: $(DIR_BIN)/$(TARGET)

$(DIR_BIN)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@  $^ $(LDFLAGS) $(MLV)

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.c $(DIR_HEADER)/Menu.h $(DIR_HEADER)/Moteur_graphique.h $(DIR_HEADER)/Score.h
	$(CC) -c $< -o $(DIR_OBJ)/main.o $(CFLAGS)

$(DIR_OBJ)/Deplacement.o: $(DIR_SRC)/Deplacement.c $(DIR_HEADER)/Deplacement.h
	$(CC) -c $< -o $(DIR_OBJ)/Deplacement.o $(CFLAGS)

$(DIR_OBJ)/Relique.o: $(DIR_SRC)/Relique.c $(DIR_HEADER)/Relique.h
	$(CC) -c $< -o $(DIR_OBJ)/Relique.o $(CFLAGS)

$(DIR_OBJ)/Gardien.o: $(DIR_SRC)/Gardien.c $(DIR_HEADER)/Gardien.h $(DIR_HEADER)/Deplacement.h
	$(CC) -c $< -o $(DIR_OBJ)/Gardien.o $(CFLAGS)

$(DIR_OBJ)/Joueur.o: $(DIR_SRC)/Joueur.c $(DIR_HEADER)/Joueur.h $(DIR_HEADER)/Deplacement.h
	$(CC) -c $< -o $(DIR_OBJ)/Joueur.o $(CFLAGS)

$(DIR_OBJ)/Moteur_graphique.o: $(DIR_SRC)/Moteur_graphique.c $(DIR_HEADER)/Moteur_graphique.h $(DIR_HEADER)/Gestion_terrain.h
	$(CC) -c $< -o $(DIR_OBJ)/Moteur_graphique.o $(CFLAGS) $(MLV)

$(DIR_OBJ)/Moteur_de_jeu.o: $(DIR_SRC)/Moteur_de_jeu.c $(DIR_HEADER)/Moteur_de_jeu.h $(DIR_HEADER)/Relique.h $(DIR_HEADER)/Gardien.h $(DIR_HEADER)/Joueur.h
	$(CC) -c $< -o $(DIR_OBJ)/Moteur_de_jeu.o $(CFLAGS)

$(DIR_OBJ)/Collision.o: $(DIR_SRC)/Collision.c $(DIR_HEADER)/Collision.h $(DIR_HEADER)/Moteur_de_jeu.h
	$(CC) -c $< -o $(DIR_OBJ)/Collision.o $(CFLAGS)

$(DIR_OBJ)/Gestion_terrain.o: $(DIR_SRC)/Gestion_terrain.c $(DIR_HEADER)/Gestion_terrain.h $(DIR_HEADER)/Collision.h
	$(CC) -c $< -o $(DIR_OBJ)/Gestion_terrain.o $(CFLAGS)

$(DIR_OBJ)/Menu.o: $(DIR_SRC)/Menu.c $(DIR_HEADER)/Menu.h $(DIR_HEADER)/Moteur_graphique.h
	$(CC) -c $< -o $(DIR_OBJ)/Menu.o $(CFLAGS)
	
$(DIR_OBJ)/Score.o: $(DIR_SRC)/Score.c $(DIR_HEADER)/Score.h
	$(CC) -c $< -o $(DIR_OBJ)/Score.o $(CFLAGS)


#Au cas ou on ajouterrai d'autre module
#$(DIR_OBJ)/arboresence.o: $(DIR_SRC)/.c $(DIR_HEADER)/.h
#	$(CC) -c $< -o $(DIR_OBJ)/.o $(CFLAGS)

clean:
	rm -f $(OBJ) $(DIR_BIN)/$(TARGET)
