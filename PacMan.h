//PacMan game made as an end of session project at college
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


// PacMan.h
//Alexandre-Xavier L-Lamoureux
//4-12 Décembre 2013
//Initialisation des fonctions, des constantes, etc.

#ifndef _FONCTIONS_CPP
#define _FONCTIONS_CPP

//Déclarations de constantes requises pour le jeu
const int Largeur = 19;
const int Hauteur = 21;
const int NbPixelsParCase = 16;
//Ajoutez vos propres constantes ici...
const int VitesseFantome = 10; // Bougent à tous les 10 tours
const int MurMince = 4;

//Énumération pour représenter une case du labyrinthe
//V=Vide, M=Mur, P=Point
enum Objet {V, M, P, W};

//Ajoutez vos propres enum, structures et prototypes de fonctions ici...

struct Personnage
{
	int x;
	int y;
	int Ax;	//Ancien X
	int Ay;	//Ancien Y
};

//BougerFantomRandom
//Intrant: Tableau et Random (reste en référence)
//Extrant: Bouger
//Mouvement de Pokey et Bashful
bool BougerFantomRandom(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY, Objet Tableau[Hauteur][Largeur], int Random);

//BougerFantomSuivre
//Intrant: Tableau, Random, PacManX et PacManY (reste en référence)
//Extrant: Bouger
//Mouvement de Shadow et Speedy
bool BougerFantomSuivre(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY, int PacManX, int PacManY, Objet Tableau[Hauteur][Largeur], int Random);

//BougerFantomFuite
//Intrant: Tableau, Random, PacManX et PacManY (reste en référence)
//Extrant: Bouger
//Quand le fantomes prennent la fuite, on utilise ce code
bool BougerFantomFuite(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY, int PacManX, int PacManY, Objet Tableau[Hauteur][Largeur], int Random);

//BougerFantomCommum
//Intrant: Tableau, Random et Bouger (reste en référence)
//Extrant: Bouger
//Code commun qui est utilisé par tout les sortes de fantomes
bool BougerFantomCommun(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY, Objet Tableau[Hauteur][Largeur], int Random, bool Bouger);

//BougerPacMan
//Intrant: Tableau, Evenement et Miroir (le reste est en référence)
//Extrant: Miroir
//Code pour bouger PacMan
bool BougerPacMan(int &PositionX, int &PositionY, Objet Tableau[Hauteur][Largeur], int Evenement, bool Miroir);

//Bouger[Direction], étant soit haut, bas, gauche ou droite.
//Intrant: Prennent leur position X et Y et leurs anciennes positions X et Y en référence
//Extrant: Bouger (1)
//Utilisé pour bouger les fantomes dans certaines directions
bool BougerHaut(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY);
bool BougerBas(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY);
bool BougerDroite(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY);
bool BougerGauche(int &PositionX, int &PositionY, int &PositionAX, int &PositionAY);

#endif
