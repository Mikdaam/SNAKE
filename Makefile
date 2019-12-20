#############################################
#				VARIABLES                   #
#############################################

CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -lgraph
EXEC = snake
OFILES = menu.o main.o
all: $(EXEC)


#############################################
#			REGLES ESSENTIELLES             #
#############################################
run: all
	./snake

snake: $(OFILES)
	$(CC) -o snake menu.o main.o -lgraph

menu.o: menu.c menu.h
	$(CC) -o menu.o -c menu.c $(CFLAGS) 

main.o: main.c main.h menu.h
	$(CC) -o main.o -c main.c $(CFLAGS) 

.PHONY: clean mrproper run all

clean:
	rm -rf *.o

mrproper: clean all 

#############################################
#					FIN                     #
#############################################