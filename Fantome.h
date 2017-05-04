#include "Pacman.h"
#include "Personnage.h"

#ifndef FANTOME_H
#define FANTOME_H

class Fantome : public Personnage
{
private:
	bool Bouger_;
	Pacman* Pacman_;
public:
	Fantome(int X, int Y, Pacman* Pac);
    //Fantome(int X, int Y);
	bool BougerRandom(int Random);
	bool BougerSuivre(int Random);
	bool BougerCommun(int Random, bool Bouge);
	bool BougerFuite(int Random);
};

#endif // FANTOME_H


