#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graph.h>
#include <unistd.h>
#include "main.h"
#include "menu.h"

void Position(int* x, int* y, int fruitx[], int fruity[], int* echec, int* score){
	int i;
	*echec = 0;
	dir = PAUSE;
	srand(time(NULL));
	*x = largeur/2;/*Position du serpent au commencement*/
	*y = hauteur/2;
	for (i = 0; i < 5; ++i)
	{
		fruitx[i] = rand() % largeur;/*Position des fruits au commencement*/
		fruity[i] = rand() % hauteur;
	}
	*score = 0;
}

void Carte(int* x, int* y, int fruitx[], int fruity[], int* score, int taillex[], int tailley[], int* taille){
	int i, j, k, n, m;
	char s[50];
	system("clear");
	for( i = 0; i < largeur+2; i++){/*Bordure haut du terrain*/
		printf("#");
	}
	printf("\n");
	for (i = 0; i < hauteur ; i++)
	{
		for (j = 0; j < largeur; j++)
		{
			if ((i + j) %2)
			{
				ChoisirCouleurDessin(CouleurParComposante(255,255,255));/*Changement de couleur en fonction de la position*/
				RemplirRectangle(j*20,i*20,20,20);						
			} else
			{
				ChoisirCouleurDessin(CouleurParComposante(248,248,255 ));
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
			else
			{
				int queue = 0;
				for (k = 0; k < *taille; k++)
				{
					if (taillex[k] == j && tailley[k] == i)
					{
						printf("o");/*Affichage de la queue du serpent au fur et à mesure qu'il évolu*/
						ChoisirCouleurDessin(CouleurParComposante(0,0,0));
						RemplirRectangle(j*20,i*20,20,20);
						ChoisirCouleurDessin(CouleurParComposante(255,255,0));
						RemplirRectangle(j*20,i*20,17,17);
						queue = 1;
					}
				}
				if (!queue)
					{
						printf(" ");
					}
			}
			for (m = 0; m < 5; m++)
			{
				if (j == fruitx[m] && i == fruity[m])
				{
					printf("*");/*Affichage des fruits au début du jeu*/
					n = ChargerSprite("Images/po.jpg");
					AfficherSprite(n, j*20, i*20);
					LibererSprite(n);
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

void SnakeAvance(int* x, int* y, int fruitx[], int fruity[], int* echec, int* score, int taillex[], int tailley[], int* taille)
{
	char perdu[100];
	int i, j;
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
		for (j = 0; j < 5; j++)
		{
			if (taillex[i] == fruitx[j] && tailley[i] == fruity[j])
			{
				fruitx[j] = rand() % largeur;
				fruity[j] = rand() % hauteur;
			}
		}
		
	}
	for ( i = 0; i < 5; i++)
	{
		if (*x == fruitx[i] && *y == fruity[i])
		{
			*score += 5;
			fruitx[i] = rand() % largeur;
			fruity[i] = rand() % hauteur;
			(*taille) += 2;
		}
	}
	
	if(*echec)
	{
		EffacerEcran(CouleurParComposante(15,15,15));
		EcrireTexte(480,hauteur/2*20-50,"Vous avez perdu...!", 2);
		sprintf(perdu,"Votre score est: %d", *score);
		EcrireTexte(20,(hauteur/2)*20+50,perdu,2);
		EcrireTexte(480,870,"Appuyer sur Echap.",2);
	}
}

int main(void)
{
	int secondes = 0, minutes = 0, testsecondes;
	unsigned long int suivant = Microsecondes() + CYCLE;
	char temps[50];
	int choix;
	int x, y, fruitx[5], fruity[5], score, echec = 0, vitesse = 100000;
 	int taillex[2060], tailley[2060], taille;
	InitialiserGraphique();
	CreerFenetre(50,10,largeur*20, hauteur*20+100);
	ChoisirTitreFenetre("Jeu Snake");
	ChoisirCurseur(2);
	choix = menu();
	if (choix == 1)
	{
		Position(&x, &y, fruitx, fruity, &echec, &score);
		while (!echec)
		{				EcrireTexte(1000,870,temps,2);/*Affichage de temps*/

			Carte(&x, &y, fruitx, fruity, &score, taillex, tailley, &taille);
			Entree(); 
			SnakeAvance(&x, &y, fruitx, fruity, &echec, &score, taillex, tailley, &taille);
			usleep(vitesse); /*usleep(10)*/
			if (score >= 50)
			{
				vitesse = 99999;
			}
			if (score >= 100)
			{
				vitesse = 50000;
			}
			if (score >= 150)
			{
				vitesse = 25000;
			}
			if (score >= 200)
			{
				vitesse = 15000;
			}
			if (score >= 250)
			{
				vitesse = 7000;
			}
			if (score >= 500)
			{
				vitesse = 5000;
			}
			if (score >= 1000)
			{
				vitesse = 1000;
			}
			if (Microsecondes() > suivant)
			{
				suivant = Microsecondes() + CYCLE;
				secondes++;
				ChoisirCouleurDessin(CouleurParComposante(255,255,255));
				sprintf(temps, "%02d:%02d", minutes, secondes);
				EcrireTexte(1000,870,temps,2);/*Affichage de temps*/
			}
			testsecondes = secondes;
			if (secondes == 60)
			{
				secondes = 0;
				minutes++;
			}
			printf("Temps : %s\n", temps);
		}
		EcrireTexte(900,(hauteur/2)*20+50,"Duree de Jeu: ",2);
		EcrireTexte(1100,(hauteur/2)*20+50,temps,2);
		ChoisirCouleurDessin(CouleurParComposante(15,15,15));
		RemplirRectangle(910,830,80,40);
	}
	if (choix == 2)
	{
		ChargerImageFond("Images/FondRegles.jpg");
		if ((_X >= 940) && (_X <= 1160) && (_Y >= 801) && (_Y <= 870))
        {
            choix = menu();
        }
	}
	if (choix == 3)
	{
		exit(1);
	}
	
	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;
}