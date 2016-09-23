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


// Fonctions.cpp
//Alexandre-Xavier L-Lamoureux
//4-12 Décembre 2013
//Définit les fonctions

#include "PacMan.h"
#include "sdlclg.h"

bool Bouger = 0;

bool BougerFantomRandom(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY, Objet Tableau[Hauteur][Largeur], int Random)
{
	Bouger = 0;

	//Pour le bas de la cage fermé - Ne pas aller se promener dedans
	if (PositionY == 9 && PositionX == 9 && Bouger == 0)
	{
		PositionY -= 1;
		PositionAX = 9;
		PositionAY = 9;
		Bouger = 1;
	}

	if (Tableau[PositionY-1][PositionX] != M && Random == 0)
	{
		if (PositionY-1 != PositionAY && Bouger == 0)
		{
			Bouger = BougerHaut(PositionX, PositionY, PositionAX, PositionAY);
		}
	}
	else if (Tableau[PositionY+1][PositionX] != M && Random == 1)
	{
		if(PositionY+1 != PositionAY && Bouger == 0)
		{
			Bouger = BougerBas(PositionX, PositionY, PositionAX, PositionAY);
		}
	}
	else if (Tableau[PositionY][PositionX-1] != M && Random == 2)
	{
		if (PositionX-1 != PositionAX && Bouger == 0)
		{
			Bouger = BougerGauche(PositionX, PositionY, PositionAX, PositionAY);
		}
	}
	else if (Tableau[PositionY][PositionX+1] != M && Random == 3)
	{
		if(PositionX+1 != PositionAX && Bouger == 0)
		{
			Bouger = BougerDroite(PositionX, PositionY, PositionAX, PositionAY);
		}
	}

	Bouger = BougerFantomCommun(PositionX, PositionY, PositionAX, PositionAY, Tableau, Random, Bouger);

	return Bouger;
}

bool BougerFantomSuivre(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY, int PacManX, int PacManY, Objet Tableau[Hauteur][Largeur], int Random)
{
	Bouger = 0;

	//Pour le bas de la cage fermé - Ne pas aller se promener dedans
	if (PositionY == 9 && PositionX == 9 && Bouger == 0)
	{
		PositionY -= 1;
		PositionAX = 9;
		PositionAY = 9;
		Bouger = 1;
	}

	if (Tableau[PositionY-1][PositionX] != M && PositionY > PacManY && PositionY-1 != PositionAY && Bouger == 0)
	{
		Bouger = BougerHaut(PositionX, PositionY, PositionAX, PositionAY);
		Bouger = BougerFantomCommun(PositionX, PositionY, PositionAX, PositionAY, Tableau, Random, Bouger);
	}
	else if (Tableau[PositionY+1][PositionX] != M && PositionY < PacManY && PositionY+1 != PositionAY && Bouger == 0)
	{
		if(PositionY == 7 && PositionX == 9)
		{
			if (PositionX+1 == PositionAX)
			{
				Bouger = BougerGauche(PositionX, PositionY, PositionAX, PositionAY);
			}
			else
			{
				Bouger = BougerDroite(PositionX, PositionY, PositionAX, PositionAY);
			}
		}
		else
		{
			Bouger = BougerBas(PositionX, PositionY, PositionAX, PositionAY);
		}
		Bouger = BougerFantomCommun(PositionX, PositionY, PositionAX, PositionAY, Tableau, Random, Bouger);
	}
	else if (Tableau[PositionY][PositionX-1] != M && PositionX > PacManX && PositionX-1 != PositionAX && Bouger == 0)
	{     //Si on est plus à gauche de PacMan, il faut aller à droite
		Bouger = BougerGauche(PositionX, PositionY, PositionAX, PositionAY);
		Bouger = BougerFantomCommun(PositionX, PositionY, PositionAX, PositionAY, Tableau, Random, Bouger);
	}
	else if (Tableau[PositionY][PositionX+1] != M && PositionX < PacManX && PositionX+1 != PositionAX && Bouger == 0)
	{     //Si on est plus à droite de PacMan, il faut aller plus à gauche
		Bouger = BougerDroite(PositionX, PositionY, PositionAX, PositionAY);
		Bouger = BougerFantomCommun(PositionX, PositionY, PositionAX, PositionAY, Tableau, Random, Bouger);
	}
	//Ça pass encore marché, alors en s'en remet au random et on bouge si possible
	else if (Bouger == 0)
	{
		Bouger = BougerFantomRandom(PositionX, PositionY, PositionAX, PositionAY, Tableau, Random);
	}

	return Bouger;
}

bool BougerFantomCommun(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY, Objet Tableau[Hauteur][Largeur], int Random, bool Bouger)
{
	//Ne pas réentrer dans la cage
	if (PositionY == 8 && PositionX == 9 && PositionAY != 9 && Bouger == 1)
	{
		PositionY -= 1;
		Bouger = 0;
	}

	//Passer par les tunnels pour warper l'autre bord
	if (PositionY == 9 && PositionX == 0)
	{
		PositionX = 17;
		PositionAX = 18;
		PositionAY = 9;
		Bouger = 1;
	}
	else if (PositionY == 9 && PositionX == 18)
	{
		PositionX = 1;
		PositionAX = 0;
		PositionAY = 9;
		Bouger = 1;
	}

	//Code du cul de sac droit
	if (Tableau[PositionY][PositionX+1] == M && Tableau[PositionY+1][PositionX] == M &&
		Tableau[PositionY-1][PositionX] == M && Bouger == 0)
	{
		PositionX -= 1;
		Bouger = 1;
	}
	//Code du cul de sac gauche
	else if (Tableau[PositionY][PositionX-1] == M && Tableau[PositionY+1][PositionX] == M &&
		Tableau[PositionY-1][PositionX] == M && Bouger == 0)
	{
		PositionX += 1;
		Bouger = 1;
	}

	return Bouger;
}

bool BougerPacMan(int &PositionX, int &PositionY, Objet Tableau[Hauteur][Largeur], int Evenement, bool Miroir)
{
	if (Evenement == EVHaut && PositionY > 0 && Tableau[PositionY-1][PositionX] != M)
	{
		PositionY -= 1;
	}
	else if (Evenement == EVBas && PositionY < Hauteur-1 && Tableau[PositionY+1][PositionX] != M)
	{
		if (PositionX != 9 || PositionY != 7)
		{
			PositionY += 1;
		}
	}
	else if (Evenement == EVGauche && PositionX > 0)
	{
		if (Tableau[PositionY][PositionX-1] != M)
		{
			PositionX -= 1;
		}
		Miroir = 1;
	}
	else if (Evenement == EVDroite && PositionX < Largeur-1)
	{
		if (Tableau[PositionY][PositionX+1] != M)
		{
			PositionX += 1;
		}
		Miroir = 0;
	}

	//Teleporteur
	if (PositionY == 9 && PositionX == 0)
	{
		PositionX = 17;
	}
	else if (PositionY == 9 && PositionX == 18)
	{
		PositionX = 1;
	}

	return Miroir;
}

bool BougerFantomFuite(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY, int PacManX, int PacManY, Objet Tableau[Hauteur][Largeur], int Random)
{
	Bouger = 0;

	//Pour le bas de la cage fermé - Ne pas aller se promener dedans
	if (PositionY == 9 && PositionX == 9 && Bouger == 0)
	{
		PositionY -= 1;
		PositionAX = 9;
		PositionAY = 9;
		Bouger = 1;
	}

	if (Tableau[PositionY-1][PositionX] != M && PositionY < PacManY && PositionY-1 != PositionAY && Bouger == 0)
	{
		Bouger = BougerHaut(PositionX, PositionY, PositionAX, PositionAY);
	}
	else if (Tableau[PositionY+1][PositionX] != M && PositionY > PacManY && PositionY+1 != PositionAY && Bouger == 0)
	{
		if(PositionY == 7 && PositionX == 9)
		{
			if (PositionX+1 == PositionAX)
			{
				Bouger = BougerGauche(PositionX, PositionY, PositionAX, PositionAY);
			}
			else
			{
				Bouger = BougerDroite(PositionX, PositionY, PositionAX, PositionAY);
			}
		}
		else
		{
			Bouger = BougerBas(PositionX, PositionY, PositionAX, PositionAY);
		}
	}
	else if (Tableau[PositionY][PositionX-1] != M && PositionX < PacManX && PositionX-1 != PositionAX && Bouger == 0)
	{     //Si on est plus à gauche de PacMan, il faut aller à droite
		Bouger = BougerGauche(PositionX, PositionY, PositionAX, PositionAY);
	}
	else if (Tableau[PositionY][PositionX+1] != M && PositionX > PacManX && PositionX+1 != PositionAX && Bouger == 0)
	{     //Si on est plus à droite de PacMan, il faut aller plus à gauche
		Bouger = BougerDroite(PositionX, PositionY, PositionAX, PositionAY);
	}
	//Ça pass encore marché, alors en s'en remet au random
	else if (Tableau[PositionY-1][PositionX] != M && Random == 0 && PositionY-1 != PositionAY && Bouger == 0)
	{     //Si c'est pas possible, on bouge random
		Bouger = BougerHaut(PositionX, PositionY, PositionAX, PositionAY);
	}
	else if (Tableau[PositionY+1][PositionX] != M && Random == 1 && PositionY+1 != PositionAY && Bouger == 0)
	{     //Si c'est pas possible, on bouge random
		Bouger = BougerBas(PositionX, PositionY, PositionAX, PositionAY);
	}
	else if (Tableau[PositionY][PositionX-1] != M && Random == 2 && PositionX-1 != PositionAX && Bouger == 0)
	{
		Bouger = BougerGauche(PositionX, PositionY, PositionAX, PositionAY);
	}
	else if (Tableau[PositionY][PositionX+1] != M && Random == 3 && PositionX+1 != PositionAX && Bouger == 0)
	{
		Bouger = BougerDroite(PositionX, PositionY, PositionAX, PositionAY);
	}

	Bouger = BougerFantomCommun(PositionX, PositionY, PositionAX, PositionAY, Tableau, Random, Bouger);

	return Bouger;
}

bool BougerHaut(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY)
{
	PositionAX = PositionX;
	PositionAY = PositionY;
	PositionY -= 1;
	return 1;
}

bool BougerBas(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY)
{
	PositionAX = PositionX;
	PositionAY = PositionY;
	PositionY += 1;
	return 1;
}

bool BougerDroite(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY)
{
	PositionAX = PositionX;
	PositionAY = PositionY;
	PositionX += 1;
	return 1;
}

bool BougerGauche(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY)
{
	PositionAX = PositionX;
	PositionAY = PositionY;
	PositionX -= 1;
	return 1;
}

