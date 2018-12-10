CC=gcc
OBJ=obj/main.o obj/affichage.o obj/setup.o obj/grille.o obj/liste.o obj/save.o
EXE=demineur
OPT=-Wall -std=c99 -g

all : $(OBJ)
	$(CC) $(OPT) -o $(EXE) $(OBJ)

obj/%.o : src/%.c
	$(CC) $(OPT) -o $@ -c $<

clean :
	rm *~ obj/*.o $(EXE) $(OBJ)
