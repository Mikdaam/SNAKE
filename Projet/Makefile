#############################################
				VARIABLES
#############################################

CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -lgraph
EXEC = run
OFILES = menu.o main.o
all: $(EXEC)


#############################################
			REGLES ESSENTIELLES
#############################################

run: $(OFILES)
		$(CC) -o run menu.o main.o -lgraph

menu.o: menu.c menu.h
		$(CC) -o menu.o -c menu.c $(CFLAGS) 

main.o: main.c main.h menu.h
		$(CC) -o main.o -c main.c $(CFLAGS) 

.PHONY: clean mrproper

clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)

#############################################
					FIN
#############################################