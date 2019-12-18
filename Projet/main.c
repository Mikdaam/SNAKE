#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graph.h>
#include <unistd.h>
#include "main.h"
#include "menu.h"

/*#include <conio.h>*

// const int largeur = 60;
// const int hauteur = 40;
 int x, y, fruitx, fruity, score, echec = 0;
 int taillex[100], tailley[100], taille;
// enum Direction{ PAUSE = 0, Gauche, Droite, Haut, Bas};
// enum Direction dir;

int Damier(){
	int i, j;
}
*/
void Position(int* x, int* y, int* fruitx, int* fruity, int* echec, int* score){
	*echec = 0;
	dir = PAUSE;
	srand(time(NULL));
	*x = largeur/2;/*Position du serpent au commencement*/
	*y = hauteur/2;
	*fruitx = rand() % largeur;/*Position des fruits au commencement*/
	*fruity = rand() % hauteur;
	*score = 0;
}

void Carte(int* x, int* y, int* fruitx, int* fruity, int* score, int taillex[], int tailley[], int* taille){
	int i, j, k, n;
	char s[50];
	system("clear");
	for( i = 0; i < largeur+2; i++){/*Bordure haut du terrain*/
		printf("#");
	}
	printf("\n");
	/*EffacerEcran(CouleurParComposante(0,255,0));*/

	for (i = 0; i < hauteur ; i++)
	{
		for (j = 0; j < largeur; j++)
		{
			if ((i + j) %2)
			{
				ChoisirCouleurDessin(CouleurParComposante(0,100,0));/*Changement de couleur en fonction de la position*/
				RemplirRectangle(j*20,i*20,20,20);						
			} else
			{
				ChoisirCouleurDessin(CouleurParComposante(0,110,0));
				RemplirRectangle(j*20,i*20,20,20);
			}
			if (j == 0)
			{
				printf("#");/*Bordure Gauche du terrain*/
			}
			if (i == *y && j == *x)
			{
				printf(">");/*Affichage du serpent au début du jeu*/
				ChoisirCouleurDessin(CouleurParComposante(0,0,255));
				RemplirRectangle(j*20,i*20,20,20);
			}
			else if (j == *fruitx && i == *fruity)
			{
				printf("*");/*Affichage des fruits au début du jeu*/
				n = ChargerSprite("Images/pommevert.jpg");
				AfficherSprite(n, j*20, i*20);
				LibererSprite(n);
				/*ChoisirCouleurDessin(CouleurParComposante(255,0,0));
				RemplirRectangle(j*20,i*20,20,20);*/
			}
			else
			{
				int queue = 0;
				for (k = 0; k < *taille; k++)
				{
					if (taillex[k] == j && tailley[k] == i)
					{
						printf("o");/*Affichage de la queue du serpent au fur et à mesure qu'il évolu*/
						ChoisirCouleurDessin(CouleurParComposante(0,0,0));
						DessinerRectangle(j*20,i*20,20,20);
						ChoisirCouleurDessin(CouleurParComposante(255,255,0));
						RemplirRectangle(j*20,i*20,18,18);
						queue = 1;
					}
				}
				if (!queue)
					{
						printf(" ");
					}
			}
			if (j == largeur -1 )
			{
				printf("#");
			}

			

		}
		printf("\n");
	}

	for(i = 0; i < largeur+2; i++){
		printf("#");
	}
	printf("\n");
	printf("Score : %d\n", *score);/*Affichage du score à chaque fois que le serpent mange un fruit*/
	ChoisirCouleurDessin(CouleurParComposante(0,0,0));
	RemplirRectangle(0, 800, largeur*20,100);
	sprintf(s, "Score : %d", *score);
	ChoisirCouleurDessin(CouleurParComposante(255,255,255));
	EcrireTexte(20,870,s,2);
}
void Entree()
{
	int touche;
	if (ToucheEnAttente())
	{
		touche = Touche();/*Appui des touches pour diriger le snake*/
		switch(touche)
		{
			case XK_Left:
				dir = Gauche;
				break;
			case XK_Right:
				dir = Droite;
				break;
			case XK_Up:
				dir = Haut;
				break;
			case XK_Down:
				dir = Bas;
				break;
			case XK_space:
				EcrireTexte(550, 870, "PAUSE...",2);
				while (Touche() != XK_space){}
				break;
			case XK_Escape:
				exit(1);
				break;
		}
	}
}

void SnakeAvance(int* x, int* y, int* fruitx, int* fruity, int* echec, int* score, int taillex[500], int tailley[500], int* taille)
{
	char perdu[100];
	int i;
	int prevx = taillex[0];
	int prevy = tailley[0];
	int prev2x, prev2y;
	taillex[0] = *x;
	tailley[0] = *y;
	for (i = 1; i < *taille; i++)
	{
		prev2x = taillex[i];
		prev2y = tailley[i];
		taillex[i] = prevx;
		tailley[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	switch(dir)
	{
		case Gauche:
			(*x)--;
			break;
		case Droite:
			(*x)++;
			break;
		case Haut:
			(*y)--;
			break;
		case Bas:
			(*y)++;
			break;
		default:
			break;
	}
	if (*x > largeur || *x < 0 || *y > hauteur || *y < 0)
	{
		*echec = 1;
	}
	/*if (x >= largeur)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = largeur - 1;
	}
	if (y >= hauteur)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = hauteur - 1;
	}*/
	for (i = 0; i < *taille; i++)
	{
		if (taillex[i] == *x && tailley[i] == *y)
		{
			*echec = 1;
		}
	}
	if (*x == *fruitx && *y == *fruity)
	{
		*score += 5;
		*fruitx = rand() % largeur;
		*fruity = rand() % hauteur;
		(*taille)++;
	}
	if(*echec)
	{
		EffacerEcran(CouleurParComposante(15,15,15));
		EcrireTexte(490,hauteur/2*20,"Vous avez perdu...!", 2);
		sprintf(perdu,"Votre score est %d", *score);
		EcrireTexte(490,(hauteur/2)*20+50,perdu,2);
		EcrireTexte(480,870,"Appuyer sur Echappe.",2);
	}
}

int main(void)
{
	int x, y, fruitx, fruity, score, echec = 0;
 	int taillex[100], tailley[100], taille;
	/*int echec = 0;
	int secondes = 0, minutes = 0, testsecondes, q = secondes, nextheure;
	long unsigned int suivant = Microsecondes() + CYCLE;
	char temps[10];*/
	InitialiserGraphique();
	CreerFenetre(10,10,largeur*20, hauteur*20+100);
	/*menu();*/
	Position(&x, &y, &fruitx, &fruity, &echec, &score);
	while (!echec){
		Carte(&x, &y, &fruitx, &fruity, &score, taillex, tailley, &taille);
		Entree(); 
		SnakeAvance(&x, &y, &fruitx, &fruity, &echec, &score, taillex, tailley, &taille);
		usleep(100000); /*usleep(10)*/
		/*if (Microsecondes() > suivant)
		{
			ChoisirCouleurDessin(CouleurParComposante(255,255,255));
			sprintf(temps, "%02d:%02d", minutes, secondes);
			EcrireTexte(500,870,temps,2);
			secondes++;
			if (secondes == 60)
			{
				secondes = 0;
				minutes++;
			}
			suivant = Microsecondes() + CYCLE;
		}
		testsecondes = secondes;
		
		printf("Temps : %s\n", temps);
		}*/
	}
	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;
}