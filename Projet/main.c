#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graph.h>
#include <unistd.h>
#define  CYCLE 1000000L
//#include <conio.h>

const int largeur = 60;
const int hauteur = 40;
int x, y, fruitx, fruity, score, echec = 0;
int taillex[100], tailley[100], taille;
enum Direction{ PAUSE = 0, Gauche, Droite, Haut, Bas};
enum Direction dir;

int Damier(){
	int i, j;
}

void Position(){
	echec = 0;
	dir = PAUSE;
	srand(time(NULL));
	x = largeur/2;
	y = hauteur/2;
	fruitx = rand() % largeur;
	fruity = rand() % hauteur;
	score = 0;
}

void Carte(){
	system("clear");
	for(int i = 0; i < largeur+2; i++){
		printf("#");
	}
	printf("\n");
	// EffacerEcran(CouleurParComposante(0,255,0));

	for (int i = 0; i < hauteur ; i++)
	{
		for (int j = 0; j < largeur; j++)
		{
			if ((i + j) %2)
			{
				ChoisirCouleurDessin(CouleurParComposante(0,100,0));
				RemplirRectangle(j*20,i*20,20,20);
			} else
			{
				ChoisirCouleurDessin(CouleurParComposante(0,110,0));
				RemplirRectangle(j*20,i*20,20,20);
			}
			if (j == 0)
			{
				printf("#");
			}
			if (i == y && j == x)
			{
				printf(">");
				ChoisirCouleurDessin(CouleurParComposante(0,0,255));
				RemplirRectangle(j*20,i*20,20,20);
			}
			else if (j == fruitx && i == fruity)
			{
				printf("*");
				int n = ChargerSprite("pommevert.jpg");
				AfficherSprite(n, j*20, i*20);
				LibererSprite(n);
				// ChoisirCouleurDessin(CouleurParComposante(255,0,0));
				// RemplirRectangle(j*20,i*20,20,20);
			}
			else
			{
				int queu = 0;
				for (int k = 0; k < taille; k++)
				{
					if (taillex[k] == j && tailley[k] == i)
					{
						printf("o");	
						ChoisirCouleurDessin(CouleurParComposante(0,0,0));
						DessinerRectangle(j*20,i*20,20,20);
						ChoisirCouleurDessin(CouleurParComposante(255,255,0));
						RemplirRectangle(j*20,i*20,18,18);
						queu = 1;
					}
				}
				if (!queu)
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

	for(int i = 0; i < largeur+2; i++){
		printf("#");
	}
	char s[50];
	printf("\n");
	printf("Score : %d\t", score);
	ChoisirCouleurDessin(CouleurParComposante(0,0,0));
	RemplirRectangle(0, 800, largeur*20,100);
	sprintf(s, "Score : %d", score);
	ChoisirCouleurDessin(CouleurParComposante(255,255,255));
	EcrireTexte(20,870,s,2);
	//while(1){
		
	//}
}
void Entree()
{
	int touche, t = 0;
	if (ToucheEnAttente())
	{
		touche = Touche();
		//switch(touche)
		//{
			//case XK_Left:
				if (touche == XK_Left)
				{
					dir = Gauche;
				}
				//break;
			//case XK_Right:
				if(touche == XK_Right)
				{
					dir = Droite;
				}
				//break;
			//case XK_Down:
				if(touche == XK_Up)
				{
					dir = Haut;
				}
				//break;
			//case XK_Up:
				if(touche == XK_Down)
				{
					dir = Bas;
				}
				if (touche == XK_space)
				{
					EcrireTexte(550, 870, "PAUSE...",2);
					while (Touche() != XK_space){}
				}
				//break;
			/*case XK_E:
				echec = 1;
				break;*/
		//}
	}
}

void SnakeAvance()
{
	int prevx = taillex[0];
	int prevy = tailley[0];
	int prev2x, prev2y;
	taillex[0] = x;
	tailley[0] = y;
	for (int i = 1; i < taille; i++)
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
			x--;
			break;
		case Droite:
			x++;
			break;
		case Haut:
			y--;
			break;
		case Bas:
			y++;
			break;
		default:
			break;
	}
	if (x > largeur || x < 0 || y > hauteur || y < 0)
	{
		echec = 1;
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
	for (int i = 0; i < taille; i++)
	{
		if (taillex[i] == x && tailley[i] == y)
		{
			echec = 1;
		}
	}
	if (x == fruitx && y == fruity)
	{
		score += 5;
		fruitx = rand() % largeur;
		fruity = rand() % hauteur;
		taille++;
	}
	if (echec)
	{
		EffacerEcran(CouleurParComposante(15,15,15));
		EcrireTexte(490,hauteur/2*20,"Vous avez perdu...!", 2);
		char perdu[100];
		sprintf(perdu,"Votre score est %d", score);
		EcrireTexte(490,(hauteur/2)*20+50,perdu,2);
	}
}

int main(int argc, char const *argv[])
{
	int secondes = 0, minutes = 0, testsecondes, q = secondes, nextheure;
	long int suivant = Microsecondes() + CYCLE;
	char temps[10];
	InitialiserGraphique();
	CreerFenetre(10,10,largeur*20, hauteur*20+100);
	Position();
	while (!echec){
		Carte();
		Entree();
		SnakeAvance();
		usleep(100000); //usleep(10)
		if (Microsecondes() > suivant)
		{
			ChoisirCouleurDessin(CouleurParComposante(255,255,255));
			sprintf(temps, "%02d:%02d", minutes, secondes);
			EcrireTexte(500,870,temps,2);
			secondes++;
			suivant = Microsecondes() + CYCLE;
		}
		testsecondes = secondes;
		if (secondes = 60)
		{
			secondes = 0;
			minutes++;
		}
		printf("Temps : %s\n", temps);
	}
	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;
}