#ifndef PERSONNAGE_H
#define PERSONNAGE_H

class Personnage
{
protected:
	int X_;
	int Y_;
	int Xold_;	//Ancien X
	int Yold_;	//Ancien Y

public:
	Personnage(int X, int Y);
	bool BougerHaut();
	bool BougerBas();
	bool BougerDroite();
	bool BougerGauche();

	int GetX();
	int GetY();
	int GetOldX();
	int GetOldY();

	void SetX(int X);
	void SetY(int Y);
};

#endif


