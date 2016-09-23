//Copyright (C) 2013-2014  Alexandre-Xavier Labonté-Lamoureux
//This file is part of Pacman.
//
//Pacman is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 2 of the License, or
//(at your option) any later version.
//
//Pacman is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Pacman. If not, see <http://www.gnu.org/licenses/>.


// main.cpp
//Alexandre-Xavier L-Lamoureux
//4-12 Décembre 2013
//Affaires principales du jeu

#include "sdlclg.h"	//Intéressant: habilité de screenshot et message d'erreur
#include "PacMan.h"
#include <ctime>
#include <stdlib.h>
#ifdef _WIN32
#include <SDL_mixer.h>
#include <Windows.h>
#else
#include <SDL/SDL_mixer.h>
#endif
using namespace std;

int main(int argc, char *argv[])
{
	Objet Tableau[Hauteur][Largeur]  =
	{
		{ M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
		{ M, P, P, P, P, P, P, P, P, M, P, P, P, P, P, P, P, P, M},
		{ M, W, M, M, P, M, M, M, P, M, P, M, M, M, P, M, M, W, M},
		{ M, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, M},
		{ M, P, M, M, P, M, P, M, M, M, M, M, P, M, P, M, M, P, M},
		{ M, P, P, P, P, M, P, P, P, M, P, P, P, M, P, P, P, P, M},
		{ M, M, M, M, P, M, M, M, V, M, V, M, M, M, P, M, M, M, M},
		{ V, V, V, M, P, M, V, V, V, V, V, V, V, M, P, M, V, V, V},
		{ M, M, M, M, P, M, V, M, M, V, M, M, V, M, P, M, M, M, M},
		{ V, V, V, V, P, V, V, M, V, V, V, M, V, V, P, V, V, V, V},
		{ M, M, M, M, P, M, V, M, M, M, M, M, V, M, P, M, M, M, M},
		{ V, V, V, M, P, M, V, V, V, V, V, V, V, M, P, M, V, V, V},
		{ M, M, M, M, P, M, V, M, M, M, M, M, V, M, P, M, M, M, M},
		{ M, P, P, P, P, P, P, P, P, M, P, P, P, P, P, P, P, P, M},
		{ M, P, M, M, P, M, M, M, P, M, P, M, M, M, P, M, M, P, M},
		{ M, W, P, M, P, P, P, P, P, P, P, P, P, P, P, M, P, W, M},
		{ M, M, P, M, P, M, P, M, M, M, M, M, P, M, P, M, P, M, M},
		{ M, P, P, P, P, M, P, P, P, M, P, P, P, M, P, P, P, P, M},
		{ M, P, M, M, M, M, M, M, P, M, P, M, M, M, M, M, M, P, M},
		{ M, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, M},
		{ M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
	};

	//Initialisation du générateur de nombres aléatoires
	srand(static_cast<unsigned int>(time(0)));

	//Créer une fenêtre graphique de la bonne taille
	InitialiserAffichage("PacMan by Alexandre-Xavier", Largeur*NbPixelsParCase, Hauteur*NbPixelsParCase);

	//Initialiser SDL_mixer
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);
	//Pour que la musique soit jouée, il faut la loader.
	Mix_Music *musique = Mix_LoadMUS("level.mid");;

	//Message d'erreur si on la trouve pas
	if(!musique) {
		printf("Mix_LoadMUS(\"level.mid\"): %s\n", Mix_GetError());
	}	//Si la musique joue pas, ben on la joue!
	else if( Mix_PlayingMusic() == 0 )
	{
		//Jouer la musque!
		Mix_PlayMusic(musique, -1);
	}

	//Identification des images
	int ImagePac;
	string pacman = "pacman.bmp";
	int ImagePacM;
	string pacmanm = "pacman2.bmp";		//Image miroir de PacMan
	int ImageBash;
	string bashful = "bashful.bmp";
	int ImagePok;
	string pokey = "pokey.bmp";
	int ImageShadow;
	string shadow = "shadow.bmp";
	int ImageSpeedy;
	string speedy = "speedy.bmp";
	int ImageMur;
	string mur = "mur.bmp";
	int ImagePoint;
	string point = "point.bmp";
	int ImagePower;
	string power = "power.bmp";
	int ImagePeur;
	string peur = "peur.bmp";
	int ImageGagne;
	string gagne = "gagne.bmp";
	int ImagePerdu;
	string perdu = "perdu.bmp";

	//Charger les images
	ImagePac = ChargerImage(pacman);
	ImagePacM = ChargerImage(pacmanm);
	ImageBash = ChargerImage(bashful);
	ImagePok = ChargerImage(pokey);
	ImageShadow = ChargerImage(shadow);
	ImageSpeedy = ChargerImage(speedy);
	ImageMur = ChargerImage(mur);
	ImagePoint = ChargerImage(point);
	ImagePower = ChargerImage(power);
	ImagePeur = ChargerImage(peur);
	ImageGagne = ChargerImage(gagne);
	ImagePerdu = ChargerImage(perdu);

	//Initialiser Pac Man et les fantômes
	Personnage PacMan;
	Personnage Bashful;
	Personnage Pokey;
	Personnage Shadow;
	Personnage Speedy;
	PacMan.x = 9; PacMan.y = 15;
	Shadow.x = 9; Shadow.y = 8;
	Bashful.x = 8; Bashful.y = 9;
	Speedy.x = 9; Speedy.y = 9;
	Pokey.x = 10; Pokey.y = 9;

	//Les variables
	bool Bouger = 0;
	int CompteurFantome = 0;
	int e = EVAucun;  //Faut l'initialiser à rien
	int Fuite = 0;
	bool Miroir = 0;
	bool Mort = 0;
	int NbPoints = 1;
	bool Quitter = 0;
	int Random;

	//Boucle principale: jouer tant qu'il reste des points, que Pac Man est en vie et que l'usager n'a pas demandé de quitter
	while(e != EVQuitter && NbPoints != 0 && Mort == 0)
	{
		//Remplir la fenêtre de noir
		RemplirFenetre(0, 0, 0);

		//Dessiner les murs blancs (petites barrières ou genre de téléporteur)
		DessinerRectangle(0, NbPixelsParCase*9, MurMince, NbPixelsParCase, 255, 255, 255);
		DessinerRectangle(NbPixelsParCase*Largeur-MurMince, NbPixelsParCase*9, MurMince, NbPixelsParCase, 255, 255, 255);
		DessinerRectangle(NbPixelsParCase*9, NbPixelsParCase*8+MurMince, NbPixelsParCase, MurMince, 255, 255, 255);

		//Afficher le labyrinthe (murs et points)
		NbPoints = 0;
		for (int i=0; i < Largeur; i++)
		{
			for (int j=0; j < Hauteur; j++)
			{
				if (Tableau[j][i] == M)  //Tableau[y][x]
				{
					AfficherImage(ImageMur, i*NbPixelsParCase, j*NbPixelsParCase);
				}
				else if (Tableau[j][i] == P)
				{
					AfficherImage(ImagePoint, i*NbPixelsParCase, j*NbPixelsParCase);
					NbPoints++;
				}
				else if (Tableau[j][i] == W)
				{
					AfficherImage(ImagePower, i*NbPixelsParCase, j*NbPixelsParCase);
				}
				//Sinon il y a juste rien là et alors on affiche rien
			}
		}

		//Afficher Pac Man. Deux directions seulement, car il a l'oeil est tout le temps en haut.
		if (Miroir == 0)
		{
			AfficherImage(ImagePac, PacMan.x*NbPixelsParCase, PacMan.y*NbPixelsParCase);
		}
		else
		{
			AfficherImage(ImagePacM, PacMan.x*NbPixelsParCase, PacMan.y*NbPixelsParCase);
		}

		//Afficher les fantômes
		if (Fuite == 0 || Fuite == 4 || Fuite == 5 || Fuite == 8 || Fuite == 9 || Fuite == 12 || Fuite == 13 || Fuite == 16 || Fuite == 17)
		{   //On les fait flacher avant de redevenir normal (pour pas avoir de surprise, c'est chien)
			AfficherImage(ImageBash, Bashful.x*NbPixelsParCase, Bashful.y*NbPixelsParCase);
			AfficherImage(ImagePok, Pokey.x*NbPixelsParCase, Pokey.y*NbPixelsParCase);
			AfficherImage(ImageShadow, Shadow.x*NbPixelsParCase, Shadow.y*NbPixelsParCase);
			AfficherImage(ImageSpeedy, Speedy.x*NbPixelsParCase, Speedy.y*NbPixelsParCase);
		}
		else
		{
			AfficherImage(ImagePeur, Bashful.x*NbPixelsParCase, Bashful.y*NbPixelsParCase);
			AfficherImage(ImagePeur, Pokey.x*NbPixelsParCase, Pokey.y*NbPixelsParCase);
			AfficherImage(ImagePeur, Shadow.x*NbPixelsParCase, Shadow.y*NbPixelsParCase);
			AfficherImage(ImagePeur, Speedy.x*NbPixelsParCase, Speedy.y*NbPixelsParCase);
		}

		//Bouger Pac Man selon la touche appuyée
		e = LireEvenement();

		if(e == EVQuitter)
		{
			Quitter = 1;
		}
		else if (e == EVHaut || e == EVBas || e == EVGauche || e == EVDroite)
		{
			Miroir = BougerPacMan(PacMan.x, PacMan.y, Tableau, e, Miroir);
		}
		else
		{
			e = EVAucun;
		}

		//Manger des points si on est dessus
		if (Tableau[PacMan.y][PacMan.x] == P)
		{
			Tableau[PacMan.y][PacMan.x] = V;
			NbPoints--;
		}

		//Mettre les fantomes en mode fuite
		if (Tableau[PacMan.y][PacMan.x] == W)
		{
			Tableau[PacMan.y][PacMan.x] = V;
			Fuite = 150;
		}
		//Dure 150 tours de boucle
		if (Fuite > 0)
		{
			Fuite--;
		}

		//Bouger les fantômes un tour sur 10 (à l'aide d'un compteur qui est remis à 0 une fois que les fantômes ont bougé)
		CompteurFantome++;		//Ajuster ce délais augmente la difficulté
		if (CompteurFantome >= VitesseFantome)
		{
			CompteurFantome = 0;
		}

		if (CompteurFantome == 0)
		{
			Bouger = 0;
			while (Bouger == 0)
			{
				Random = rand() % 4;
				if (Fuite == 0)
				{
					Bouger =  BougerFantomRandom(Pokey.x, Pokey.y, Pokey.Ax, Pokey.Ay, Tableau, Random);
				}
				else
				{
					Bouger = BougerFantomFuite(Pokey.x, Pokey.y, Pokey.Ax, Pokey.Ay, PacMan.x, PacMan.y, Tableau, Random);
				}
			}

			Bouger=0;
			while (Bouger == 0)
			{
				Random = rand() % 4;
				if (Fuite == 0)
				{
					Bouger =  BougerFantomRandom(Bashful.x, Bashful.y, Bashful.Ax, Bashful.Ay, Tableau, Random);
				}
				else
				{
					Bouger = BougerFantomFuite(Bashful.x, Bashful.y, Bashful.Ax, Bashful.Ay, PacMan.x, PacMan.y, Tableau, Random);
				}
			}

			Bouger=0;
			while (Bouger == 0)
			{
				Random = rand() % 4;
				if (Fuite == 0)
				{
					Bouger =  BougerFantomSuivre(Shadow.x, Shadow.y, Shadow.Ax, Shadow.Ay, PacMan.x, PacMan.y, Tableau, Random);
				}
				else
				{
					Bouger = BougerFantomFuite(Shadow.x, Shadow.y, Shadow.Ax, Shadow.Ay, PacMan.x, PacMan.y, Tableau, Random);
				}
			}

			Bouger=0;
			while (Bouger == 0)
			{
				Random = rand() % 4;
				if (Fuite == 0)
				{
					Bouger = BougerFantomSuivre(Speedy.x, Speedy.y, Speedy.Ax, Speedy.Ay, PacMan.x, PacMan.y, Tableau, Random);
				}
				else
				{
					Bouger = BougerFantomFuite(Speedy.x, Speedy.y, Speedy.Ax, Speedy.Ay, PacMan.x, PacMan.y, Tableau, Random);
				}
			}
		}

		//Vérifier si Pac Man a été mangé
		if (Fuite == 0)
		{
			if (PacMan.x == Pokey.x && PacMan.y == Pokey.y)
			{
				Mort = 1;
			}
			else if (PacMan.x == Bashful.x && PacMan.y == Bashful.y)
			{
				Mort = 1;
			}
			else if (PacMan.x == Shadow.x && PacMan.y == Shadow.y)
			{
				Mort = 1;
			}
			else if (PacMan.x == Speedy.x && PacMan.y == Speedy.y)
			{
				Mort = 1;
			}
		}
		else
		{
			if (PacMan.x == Pokey.x && PacMan.y == Pokey.y)
			{
				Pokey.x = 9; Pokey.y = 9;
			}
			if (PacMan.x == Bashful.x && PacMan.y == Bashful.y)
			{
				Bashful.x = 9; Bashful.y = 9;
			}
			if (PacMan.x == Shadow.x && PacMan.y == Shadow.y)
			{
				Shadow.x = 9; Shadow.y = 9;
			}
			if (PacMan.x == Speedy.x && PacMan.y == Speedy.y)
			{
				Speedy.x = 9; Speedy.y = 9;
			}
		}
		//Rafraichir la fenêtre
		RafraichirFenetre();
		//Attendre 30 ms pour ralentir le jeu
		SDL_Delay(30);
	}

	//Afficher le bon message de fin de partie
	if (Quitter == 0)
	{
		if (NbPoints == 0)
		{
			AfficherImage(ImageGagne, 30, 140);
		}
		else
		{
			AfficherImage(ImagePerdu, 90, 140);
		}
		//Attendre un peu
		RafraichirFenetre();
		SDL_Delay(2500);
	}

	//Fermer la fenêtre
	Mix_FreeMusic(musique);
	QuitterAffichage();
	return 0;
}

