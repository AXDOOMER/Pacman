#include "Personnage.h"

#ifndef PACMAN_H
#define PACMAN_H

class Pacman : public Personnage
{
private:
	bool Miroir_;

public:
	Pacman(int X, int Y);
	bool Bouger(int Evenement, bool Miroir);
};

#endif


