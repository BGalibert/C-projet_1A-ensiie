CC = gcc -g -Wall -Wextra -Iinclude
SRC = src
INC = include
OBJ = build

all: exec

$(OBJ)/stack.o: $(INC)/stack.h
$(OBJ)/image.o: $(INC)/image.h
$(OBJ)/bloc.o: $(INC)/bloc.h $(INC)/image.h $(INC)/couleur.h $(INC)/interpreteur.h
$(OBJ)/couleur.o: $(INC)/couleur.h $(INC)/image.h
$(OBJ)/interpreteur.o: $(INC)/interpreteur.h
$(OBJ)/actions.o: $(INC)/actions.h $(INC)/interpreteur.h
$(OBJ)/step.o: $(INC)/step.h $(INC)/bloc.h $(INC)/interpreteur.h $(INC)/image.h $(INC)/couleur.h $(INC)/actions.h $(INC)/print.h
$(OBJ)/print.o: $(INC)/print.h $(INC)/image.h $(INC)/couleur.h

exec: $(SRC)/main.c $(OBJ)/image.o $(OBJ)/couleur.o $(OBJ)/stack.o $(OBJ)/bloc.o $(OBJ)/interpreteur.o $(OBJ)/actions.o $(OBJ)/step.o $(OBJ)/print.o
	@mkdir -p $(OBJ)
	$(CC) -o $@ $^ -ljpeg

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJ) exec
