#include<stdlib.h>
#include<stdio.h>
#include<graph.h>
#include <unistd.h>
#include "menu.h"

 
int menu()
{
    int CHOIX;
    InitialiserGraphique();
    CreerFenetre(0,0,1200,900);
    ChargerImageFond("Images/Menu.jpg");/*Affiche le fond d'écran*/
    ChoisirCouleurDessin(CouleurParComposante(255,255,255));
    ChoisirCouleurDessin(CouleurParComposante(0,0,0));
    RemplirRectangle(0,0,20,900);
    RemplirRectangle(1180,0,20,900);
    RemplirRectangle(0,0,1200,20);
    ChoisirCurseur(2);
    while(1)
    {
    	while(!SourisCliquee())
    	{
    		if((_X >= 408) && (_X <= 830) && (_Y >= 289) && (_Y <= 435))/*Zone Cliquable pour jouer*/
            {
                CHOIX = 1;
    			/*printf("Jouer\n");*/
    			return CHOIX;
    		}
            if ((_X >= 408) && (_X <= 825) && (_Y >= 535) && (_Y <= 670))/*Zone Cliquable pour l'aide*/
            {
                CHOIX = 2;
                if ((_X >= 940) && (_X <= 1160) && (_Y >= 801) && (_Y <= 870))
                {
                    CHOIX = 5;
                }
                /*printf("Aide\n");*/
                return CHOIX;
            }
    		if((_X >= 424) && (_X <= 804) && (_Y >= 750) && (_Y <= 880))/*Zone Cliquable pour quitter*/
            {
    			/*printf("Quitter\n");
    			ChoisirCurseur(50);
    			EffacerEcran(CouleurParComposante(255,255,255));
    			ChoisirCouleurDessin(CouleurParComposante(0,0,0));
    			EcrireTexte(525,450,"Au revoir...",2);
    			sleep(2);*/
                exit(1);

    	   }

           if ((_X >= 940) && (_X <= 1160) && (_Y >= 801) && (_Y <= 870))
           {
               CHOIX = 4;
           }
	   }
    }
    /* Touche();
     FermerGraphique();*/
    return CHOIX;
}