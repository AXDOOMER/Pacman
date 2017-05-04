#include "sdlclg.h"
#include "Constantes.h"
#include "Personnage.h"
#include "Pacman.h"

Pacman::Pacman(int X, int Y) : Personnage(X, Y)
{
	X_ = X;
	Y_ = Y;
	Miroir_ = false;
}

bool Pacman::Bouger(int Evenement, bool Miroir)
{
	Xold_ = X_;
	Yold_ = Y_;

	if (Evenement == EVHaut && Y_ > 0 && Tableau[(Y_-1)][X_] != M)
	{
		Y_ -= 1;
	}
	else if (Evenement == EVBas && Y_ < (Hauteur-1) && Tableau[(Y_+1)][X_] != M)
	{
		if (X_ != 9 || Y_ != 7)
		{
			Y_ += 1;
		}
	}
	else if (Evenement == EVGauche && X_ > 0)
	{
		if (Tableau[Y_][(X_-1)] != M)
		{
			X_ -= 1;
		}
		Miroir = true;
	}
	else if (Evenement == EVDroite && X_ < Largeur-1)
	{
		if (Tableau[Y_][X_+1] != M)
		{
			X_ += 1;
		}
		Miroir = false;
	}

	//Teleporteur
	if (Y_ == 9 && X_ == 0)
	{
		X_ = 17;
	}
	else if (Y_ == 9 && X_ == 18)
	{
		X_ = 1;
    }

	return Miroir;
}



