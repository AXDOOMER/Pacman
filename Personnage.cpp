#include "Personnage.h"


Personnage::Personnage(int X, int Y)
{
	X_ = X;
	Y_ = Y;
}

bool Personnage::BougerHaut()
{
	Xold_ = X_;
	Yold_ = Y_;
	Y_ -= 1;
	return true;
}

bool Personnage::BougerBas()
{
	Xold_ = X_;
	Yold_ = Y_;
	Y_ += 1;
	return true;
}

bool Personnage::BougerDroite()
{
	Xold_ = X_;
	Yold_ = Y_;
	X_ += 1;
	return true;
}

bool Personnage::BougerGauche()
{
	Xold_ = X_;
	Yold_ = Y_;
	X_ -= 1;
	return true;
}

int Personnage::GetX()
{
	return X_;
}

int Personnage::GetY()
{
	return Y_;
}

int Personnage::GetOldX()
{
	return Xold_;
}

int Personnage::GetOldY()
{
	return Yold_;
}

void Personnage::SetX(int X)
{
    X_ = X;
}

void Personnage::SetY(int Y)
{
    Y_ = Y;
}

