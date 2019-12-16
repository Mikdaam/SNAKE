#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED 
	#define largeur 60
	#define hauteur 40
	#define  CYCLE 1000000L
enum Direction{ PAUSE = 0, Gauche, Droite, Haut, Bas};
enum Direction dir;

#endif

int x, y, fruitx, fruity, score, echec = 0;
int taillex[100], tailley[100], taille;
