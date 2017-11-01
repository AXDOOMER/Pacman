//Copyright (C) 2013-2017  Alexandre-Xavier Labonté-Lamoureux
//main.cpp
//Affaires principales du jeu

#include "sdlclg.h"	//Intéressant: habilité de screenshot et message d'erreur
#include "Constantes.h"
#include "Personnage.h"
#include "Pacman.h"
#include "Fantome.h"
#include <ctime>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
	//Initialisation du générateur de nombres aléatoires
	srand(static_cast<unsigned int>(time(0)));

	//Créer une fenêtre graphique de la bonne taille
	InitialiserAffichage("PacMan par Alexandre-Xavier L-L", Largeur*NbPixelsParCase, Hauteur*NbPixelsParCase);

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

	//Initialiser Pac-Man et les fantômes
	Pacman PacMan = Pacman(9, 15);
	Fantome Bashful = Fantome(8, 9, &PacMan);
	Fantome Pokey = Fantome(10, 9, &PacMan);
	Fantome Shadow = Fantome(9, 8, &PacMan);
	Fantome Speedy = Fantome (9, 9, &PacMan);

	//Les variables
	bool Bouger = false;
	int CompteurFantome = 0;
	int e = EVAucun;  //Faut l'initialiser à rien
	int Fuite = 0;
	bool Miroir = false;
	bool Mort = false;
	int NbPoints = 1;
	bool Quitter = false;
	int Random;

	//Boucle principale: jouer tant que l'usager n'a pas demandé de quitter
	while(!Quitter)
	{
        //Boucle secondaire: jouer tant qu'il reste des points et que Pac Man est en vie
        while (NbPoints != 0 && !Mort && !Quitter)
        {
            //Bouger Pac Man selon la touche appuyée
            e = LireEvenement();

            if(e == EVQuitter)
            {
                Quitter = true;
            }
            else if (e == EVHaut || e == EVBas || e == EVGauche || e == EVDroite)
            {
                Miroir = PacMan.Bouger(e, Miroir);
            }
            else
            {
                e = EVAucun;
            }

            //Manger des points si on est dessus
            if (Tableau[PacMan.GetY()][PacMan.GetX()] == P)
            {
                Tableau[PacMan.GetY()][PacMan.GetX()] = V;
            }

            //Mettre les fantomes en mode fuite
            if (Tableau[PacMan.GetY()][PacMan.GetX()] == W)
            {
                Tableau[PacMan.GetY()][PacMan.GetX()] = V;
                Fuite = TEMPS_FUITE;
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
                        Bouger =  Pokey.BougerRandom(Random);
                    }
                    else
                    {
                        Bouger = Pokey.BougerFuite(Random);
                    }
                }

                Bouger=0;
                while (Bouger == 0)
                {
                    Random = rand() % 4;
                    if (Fuite == 0)
                    {
                        Bouger =  Bashful.BougerRandom(Random);
                    }
                    else
                    {
                        Bouger = Bashful.BougerFuite(Random);
                    }
                }

                Bouger=0;
                while (Bouger == 0)
                {
                    Random = rand() % 4;
                    if (Fuite == 0)
                    {
                        Bouger =  Shadow.BougerSuivre(Random);
                    }
                    else
                    {
                        Bouger = Shadow.BougerFuite(Random);
                    }
                }

                Bouger=0;
                while (Bouger == 0)
                {
                    Random = rand() % 4;
                    if (Fuite == 0)
                    {
                        Bouger = Speedy.BougerSuivre(Random);
                    }
                    else
                    {
                        Bouger = Speedy.BougerFuite(Random);
                    }
                }
            }

            //Vérifier si Pac Man a été mangé
            if (!Fuite)
            {
                if (PacMan.GetX() == Pokey.GetX() && PacMan.GetY() == Pokey.GetY())
                {
                    Mort = true;
                }
                else if (PacMan.GetX() == Bashful.GetX() && PacMan.GetY() == Bashful.GetY())
                {
                    Mort = true;
                }
                else if (PacMan.GetX() == Shadow.GetX() && PacMan.GetY() == Shadow.GetY())
                {
                    Mort = true;
                }
                else if (PacMan.GetX() == Speedy.GetX() && PacMan.GetY() == Speedy.GetY())
                {
                    Mort = true;
                }
            }
            else
            {
                if (PacMan.GetX() == Pokey.GetX() && PacMan.GetY() == Pokey.GetY())
                {
                    Pokey.SetX(9);
                    Pokey.SetY(9);
                }
                if (PacMan.GetX() == Bashful.GetX() && PacMan.GetY() == Bashful.GetY())
                {
                    Bashful.SetX(9);
                    Bashful.SetY(9);
                }
                if (PacMan.GetX() == Shadow.GetX() && PacMan.GetY() == Shadow.GetY())
                {
                    Shadow.SetX(9);
                    Shadow.SetY(9);
                }
                if (PacMan.GetX() == Speedy.GetX() && PacMan.GetY() == Speedy.GetY())
                {
                    Speedy.SetX(9);
                    Speedy.SetY(9);
                }
            }

            //Remplir la fenêtre de noir
            RemplirFenetre(0, 0, 0);

            //Dessiner les murs blancs (petites barrières ou genre de téléporteur)
            DessinerRectangle(0, NbPixelsParCase*9, MurMince, NbPixelsParCase, 255, 255, 255);
            DessinerRectangle(NbPixelsParCase*Largeur-MurMince, NbPixelsParCase*9, MurMince, NbPixelsParCase, 255, 255, 255);
            DessinerRectangle(NbPixelsParCase*9, NbPixelsParCase*8+MurMince, NbPixelsParCase, MurMince, 255, 255, 255);

            //Afficher le labyrinthe (murs et points)
            NbPoints = 0;
            for (int i = 0; i < Largeur; i++)
            {
                for (int j = 0; j < Hauteur; j++)
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
            if (!Miroir)
            {
                AfficherImage(ImagePac, PacMan.GetX()*NbPixelsParCase, PacMan.GetY()*NbPixelsParCase);
            }
            else
            {
                AfficherImage(ImagePacM, PacMan.GetX()*NbPixelsParCase, PacMan.GetY()*NbPixelsParCase);
            }

            //Afficher les fantômes
            if (Fuite == 0 || Fuite == 4 || Fuite == 5 || Fuite == 8 || Fuite == 9 || Fuite == 12 || Fuite == 13 || Fuite == 16 || Fuite == 17)
            {   //On les fait flacher avant de redevenir normal (pour pas avoir de surprise, c'est chien)
                AfficherImage(ImageBash, Bashful.GetX()*NbPixelsParCase, Bashful.GetY()*NbPixelsParCase);
                AfficherImage(ImagePok, Pokey.GetX()*NbPixelsParCase, Pokey.GetY()*NbPixelsParCase);
                AfficherImage(ImageShadow, Shadow.GetX()*NbPixelsParCase, Shadow.GetY()*NbPixelsParCase);
                AfficherImage(ImageSpeedy, Speedy.GetX()*NbPixelsParCase, Speedy.GetY()*NbPixelsParCase);
            }
            else
            {
                AfficherImage(ImagePeur, Bashful.GetX()*NbPixelsParCase, Bashful.GetY()*NbPixelsParCase);
                AfficherImage(ImagePeur, Pokey.GetX()*NbPixelsParCase, Pokey.GetY()*NbPixelsParCase);
                AfficherImage(ImagePeur, Shadow.GetX()*NbPixelsParCase, Shadow.GetY()*NbPixelsParCase);
                AfficherImage(ImagePeur, Speedy.GetX()*NbPixelsParCase, Speedy.GetY()*NbPixelsParCase);
            }

            //Rafraichir la fenêtre
            RafraichirFenetre();
            //Attendre 30 ms pour ralentir le jeu
            SDL_Delay(30);
        }

        //Afficher le bon message de fin de partie
        if (!Quitter)
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

            for (int i = 0; i < Largeur; i++)
            {
                for (int j = 0; j < Hauteur; j++)
                {
                    Tableau[j][i] = TableauCopie[j][i];
                }
            }

            //Réinitialiser Pac-Man et les fantômes
            PacMan.SetX(9);     PacMan.SetY(15);
            Bashful.SetX(8);    Bashful.SetY(9);
            Pokey.SetX(10);     Pokey.SetY(9);
            Shadow.SetX(9);     Shadow.SetY(8);
            Speedy.SetX(9);     Speedy.SetY(9);

            Mort = Miroir = false;
            NbPoints = 1;
            Fuite = 0;

            // Flusher les événements qui peuvent s'avoir cumulés durant SDL_Delay
            for (int i = 0; i < 100; i++)
            {
                e = LireEvenement();
            }
            e = EVAucun;
        }
	}

	//Fermer la fenêtre
	QuitterAffichage();
	return 0;
}

