//Copyright (C) 2013-2017  Alexandre-Xavier Labonté-Lamoureux
//Fantomes.cpp
//Code pour les fantomes

#include "sdlclg.h"
#include "Constantes.h"
#include "Pacman.h"
#include "Personnage.h"
#include "Fantome.h"

Fantome::Fantome(int X, int Y, Pacman* Pac) : Personnage(X, Y)
{
	X_ = X;
	Y_ = Y;
	Pacman_ = Pac;
}

bool Fantome::BougerRandom(int Random)
{
	Bouger_ = false;

	//Pour le bas de la cage fermé - Ne pas aller se promener dedans
	if (Y_ == 9 && X_ == 9 && !Bouger_)
	{
		Y_ -= 1;
		Xold_ = 9;
		Yold_ = 9;
		Bouger_ = true;
	}

	if (Tableau[Y_-1][X_] != M && Random == 0)
	{
		if (Y_-1 != Yold_ && !Bouger_)
		{
			Bouger_ = BougerHaut();
		}
	}
	else if (Tableau[Y_+1][X_] != M && Random == 1)
	{
		if(Y_+1 != Yold_ && !Bouger_)
		{
			Bouger_ = BougerBas();
		}
	}
	else if (Tableau[Y_][X_-1] != M && Random == 2)
	{
		if (X_-1 != Xold_ && !Bouger_)
		{
			Bouger_ = BougerGauche();
		}
	}
	else if (Tableau[Y_][X_+1] != M && Random == 3)
	{
		if(X_+1 != Xold_ && !Bouger_)
		{
			Bouger_ = BougerDroite();
		}
	}

	Bouger_ = BougerCommun(Random, Bouger_);

	return Bouger_;
}

bool Fantome::BougerSuivre(int Random)
{
	Bouger_ = false;

	//Pour le bas de la cage fermé - Ne pas aller se promener dedans
	if (Y_ == 9 && X_ == 9 && Bouger_ == 0)
	{
		Y_ -= 1;
		Xold_ = 9;
		Yold_ = 9;
		Bouger_ = true;
	}

	if (Tableau[Y_-1][X_] != M && Y_ > Pacman_->GetY() && Y_-1 != Yold_ && !Bouger_)
	{
		Bouger_ = BougerHaut();
		Bouger_ = BougerCommun(Random, Bouger_);
	}
	else if (Tableau[Y_+1][X_] != M && Y_ < Pacman_->GetY() && Y_+1 != Yold_ && !Bouger_)
	{
		if(Y_ == 7 && X_ == 9)
		{
			if (X_+1 == Xold_)
			{
				Bouger_ = BougerGauche();
			}
			else
			{
				Bouger_ = BougerDroite();
			}
		}
		else
		{
			Bouger_ = BougerBas();
		}
		Bouger_ = BougerCommun(Random, Bouger_);
	}
	else if (Tableau[Y_][X_-1] != M && X_ > Pacman_->GetX() && X_-1 != Xold_ && !Bouger_)
	{     //Si on est plus à gauche de PacMan, il faut aller à droite
		Bouger_ = BougerGauche();
		Bouger_ = BougerCommun(Random, Bouger_);
	}
	else if (Tableau[Y_][X_+1] != M && X_ < Pacman_->GetX() && X_+1 != Xold_ && !Bouger_)
	{     //Si on est plus à droite de PacMan, il faut aller plus à gauche
		Bouger_ = BougerDroite();
		Bouger_ = BougerCommun(Random, Bouger_);
	}
	//Ça pass encore marché, alors en s'en remet au random et on bouge si possible
	else if (!Bouger_)
	{
		Bouger_ = BougerRandom(Random);
	}

	return Bouger_;
}

bool Fantome::BougerCommun(int Random, bool Bouger)
{
	//Ne pas réentrer dans la cage
	if (Y_ == 8 && X_ == 9 && Yold_ != 9 && Bouger)
	{
		Y_ -= 1;
		Bouger = false;
	}

	//Passer par les tunnels pour warper l'autre bord
	if (Y_ == 9 && X_ == 0)
	{
		X_ = 17;
		Xold_ = 18;
		Yold_ = 9;
		Bouger = true;
	}
	else if (Y_ == 9 && X_ == 18)
	{
		X_ = 1;
		Xold_ = 0;
		Yold_ = 9;
		Bouger = true;
	}

	//Code du cul de sac droit
	if (Tableau[Y_][X_+1] == M && Tableau[Y_+1][X_] == M &&
		Tableau[Y_-1][X_] == M && Bouger_)
	{
		X_ -= 1;
		Bouger = true;
	}
	//Code du cul de sac gauche
	else if (Tableau[Y_][X_-1] == M && Tableau[Y_+1][X_] == M &&
		Tableau[Y_-1][X_] == M && !Bouger_)
	{
		X_ += 1;
		Bouger = true;
	}

	return Bouger;
}

bool Fantome::BougerFuite(int Random)
{
	Bouger_ = false;

	//Pour le bas de la cage fermé - Ne pas aller se promener dedans
	if (Y_ == 9 && X_ == 9 && !Bouger_)
	{
		Y_ -= 1;
		Xold_ = 9;
		Yold_ = 9;
		Bouger_ = true;
	}

	if (Tableau[Y_-1][X_] != M && Y_ < Pacman_->GetY() && Y_-1 != Yold_ && !Bouger_)
	{
		Bouger_ = BougerHaut();
	}
	else if (Tableau[Y_+1][X_] != M && Y_ > Pacman_->GetY() && Y_+1 != Yold_ && !Bouger_)
	{
		if(Y_ == 7 && X_ == 9)
		{
			if (X_+1 == Xold_)
			{
				Bouger_ = BougerGauche();
			}
			else
			{
				Bouger_ = BougerDroite();
			}
		}
		else
		{
			Bouger_ = BougerBas();
		}
	}
	else if (Tableau[Y_][X_-1] != M && X_ < Pacman_->GetX() && X_-1 != Xold_ && !Bouger_)
	{     //Si on est plus à gauche de PacMan, il faut aller à droite
		Bouger_ = BougerGauche();
	}
	else if (Tableau[Y_][X_+1] != M && X_ > Pacman_->GetX() && X_+1 != Xold_ && !Bouger_)
	{     //Si on est plus à droite de PacMan, il faut aller plus à gauche
		Bouger_ = BougerDroite();
	}
	//Ça pass encore marché, alors en s'en remet au random
	else if (Tableau[Y_-1][X_] != M && Random == 0 && Y_-1 != Yold_ && !Bouger_)
	{     //Si c'est pas possible, on bouge random
		Bouger_ = BougerHaut();
	}
	else if (Tableau[Y_+1][X_] != M && Random == 1 && Y_+1 != Yold_ && !Bouger_)
	{     //Si c'est pas possible, on bouge random
		Bouger_ = BougerBas();
	}
	else if (Tableau[Y_][X_-1] != M && Random == 2 && X_-1 != Xold_ && !Bouger_)
	{
		Bouger_ = BougerGauche();
	}
	else if (Tableau[Y_][X_+1] != M && Random == 3 && X_+1 != Xold_ && !Bouger_)
	{
		Bouger_ = BougerDroite();
	}

	Bouger_ = BougerCommun(Random, Bouger_);

	return Bouger_;
}

