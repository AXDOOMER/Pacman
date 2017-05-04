//Copyright (C) 2013-2017  Alexandre-Xavier Labonté-Lamoureux
//Pacman.h
//Code pour le Pac-Man

#ifndef PACMAN_H
#define PACMAN_H

#include "Personnage.h"

class Pacman : public Personnage
{
private:
	bool Miroir_;

public:
	Pacman(int X, int Y);
	bool Bouger(int Evenement, bool Miroir);
};

#endif


