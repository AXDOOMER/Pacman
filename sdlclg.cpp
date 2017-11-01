///////////////////////////////////////////////////////////////////////////////
// sdlclg.cpp
// Interface de programmation graphique pour le cours de KA0 utilisation la
// la libraire SDL 2.0.4-VC
// Joan-Sébastien Morales, Stéphane Chassé et Etienne Forest
// Version 1.0 Création 25 octobre 2009
// Version 1.1 Modification 27 octobre 2009
//   -- Ajout de messages d'erreurs
//   -- Ajout de la fonction RafraichirFenetre
// Version 1.2 Modification 17 novembre 2009
//   -- Ajout du type ImageId
//   -- Ajout de l'énumération Evenement
//   -- Ajout de la fonction AttendreEvenement
// Version 1.21 Modification 24 novembre 2009
//   -- Correction d'un bug avec la fonction AttendreEvenement
// Version 1.3 Modification 23 septembre 2016
//   -- Conversion à SDL 2.0.4 pour Visual Studio 2015
// Version 1.31 Modification 31 octobre 2016
//   -- Correction d'un problème de création de textures à l'affichage
//      qui remplissait la RAM inutilement
///////////////////////////////////////////////////////////////////////////////

// Finalement débarrassés de windows.h!
#include <vector> // Pour stocker les images
#include <iostream>
#include "sdlclg.h"

SDL_Window *fenetre = 0;  // On peut maintenant créer plusieurs fenêtres
						  // On doit donc en créer une avant de faire quoi que ce soit.
SDL_Renderer *renderer = 0; // On doit créer un renderer pour afficher des textures dans la fenêtre
vector<SDL_Surface*> Images;  // Vecteur d'images, inchangé en SDL2
vector<SDL_Texture*> Textures; // Vecteur de textures, nouveauté.  On affiche des textures construites à partir des images
	// Mais on doit conserver les images aussi pour accéder à leurs propriétés.

inline void VerifierErreur(bool Test, string Msg)
{
	if (Test)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur!", Msg.c_str(), NULL); // NULL : No parent window
		// MessageBox de SDL, plus besoin de windows.h
		exit(1);
	}
}

void Attendre(int Temps)
{
	VerifierErreur(Temps <= 0, "Attendre: Temps invalide");
	SDL_Delay(Temps); // Maintenant inclus dans SDL, plus besoin de windows.h!
}

void InitialiserAffichage(string Titre, int Largeur, int Hauteur)
{
	VerifierErreur(Largeur <= 0, "InitialiserAffichage: Largeur invalide");
	VerifierErreur(Hauteur <= 0, "InitialiserAffichage: Hauteur invalide");

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(Largeur, // La fonction a changé un peu en SDL2 à cause de la fenêtre et du renderer
			Hauteur,
			SDL_WINDOW_RESIZABLE,
			&fenetre,
			&renderer);
	VerifierErreur(!fenetre, "InitialiserAffichage: Impossible de charger le mode vidéo");
	VerifierErreur(!renderer, "InitialiserAffichage: Impossible de créer le rendu");
	SDL_SetWindowTitle(fenetre, Titre.c_str()); // Changé en SDL2
}

void RemplirFenetre(int Rouge, int Vert, int Bleu)
{
	VerifierErreur(Rouge<0 || Rouge>255, "RemplirFenetre: Couleur rouge invalide");
	VerifierErreur(Vert<0 || Vert>255, "RemplirFenetre: Couleur verte invalide");
	VerifierErreur(Bleu<0 || Bleu>255, "RemplirFenetre: Couleur bleue invalide");

	SDL_SetRenderDrawColor(renderer, Rouge, Vert, Bleu, 255); // Alpha 255: opaque	
	SDL_RenderClear(renderer); // RenderClear "vide" le renderer avec la couleur choisie
}

void DessinerRectangle(int PosX, int PosY, int Largeur, int Hauteur,
	int Rouge, int Vert, int Bleu)
{
	VerifierErreur(PosX<0, "DessinerRectangle: PosX invalide");
	VerifierErreur(PosY<0, "DessinerRectangle: PosY invalide");
	VerifierErreur(Largeur<0, "DessinerRectangle: Largeur invalide");
	VerifierErreur(Hauteur<0, "DessinerRectangle: Hauteur invalide");
	VerifierErreur(Rouge<0 || Rouge>255, "DessinerRectangle: Couleur rouge invalide");
	VerifierErreur(Vert<0 || Vert>255, "DessinerRectangle: Couleur verte invalide");
	VerifierErreur(Bleu<0 || Bleu>255, "DessinerRectangle: Couleur bleue invalide");

	SDL_Surface *rectangle = 0;
	SDL_Texture* rectTexture = 0; 
	SDL_Rect destR;

	// Créer la surface
	rectangle = SDL_CreateRGBSurface(0, Largeur, Hauteur, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff); // masques RGBA
	// Remplir avec la couleur
	SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, Rouge, Vert, Bleu));
	// Créer la texture à partir de la surface (nouveau de SDL2)
	rectTexture = SDL_CreateTextureFromSurface(renderer, rectangle);
	SDL_FreeSurface(rectangle); // Libération de la surface

	// Destination dans la fenêtre
	destR.x = PosX;
	destR.y = PosY;
	destR.h = Hauteur;
	destR.w = Largeur;

	// Copier la texture rectangle dans le renderer
	SDL_RenderCopy(renderer, rectTexture, NULL, &destR); // NULL: Copier la texture au complet 
}

ImageId ChargerImage(string NomFichier)
{
	SDL_Surface* Image = SDL_LoadBMP(NomFichier.c_str());
	
	VerifierErreur(!Image, string("ChargerImage: Impossible de charger l'image ") + NomFichier);

	Images.push_back(Image);

	// Le color key doit être set ici, dans l'image.  Problème si on le fait plusieurs fois (à l'affichage)
	SDL_SetColorKey(Images[Images.size()-1], SDL_TRUE, // enable color key (transparency)
		SDL_MapRGB(Images[Images.size()-1]->format, 0, 0, 0));

	// Créer une texture à partir de la surface (image)
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, Images[Images.size()-1]);
	Textures.push_back(Texture);

	return Images.size() - 1;
}

void AfficherImage(ImageId Image, int PosX, int PosY)
{
	VerifierErreur(Image<0 || (unsigned int)(Image)>Images.size() - 1, "Numéro d'image invalide");
	VerifierErreur(PosX<0, "AfficherImage: PosX invalide");
	VerifierErreur(PosY<0, "AfficherImage: PosY invalide");

	// Rectangle représentant la position et la dimension de l'image dans la fenêtre
	SDL_Rect position;
	position.x = PosX;
	position.y = PosY;
	position.h = Images[Image]->h; // SDL2
	position.w = Images[Image]->w; // SDL2

	// Copier la texture dans le renderer
	SDL_RenderCopy(renderer, Textures[Image], NULL, &position); // NULL: Copier la texture au complet 
}

void RafraichirFenetre()
{
	SDL_RenderPresent(renderer);  // SDL2
}

void QuitterAffichage()
{
	// Libérer les surfaces (images)
	for (unsigned int i = 0; i<Images.size(); i++)
	{
		SDL_FreeSurface(Images[i]);
	}
	// Détruire le renderer
	SDL_DestroyRenderer(renderer);
	// Détruire la fenêtre
	SDL_DestroyWindow(fenetre);
	// Quitter
	SDL_Quit();
}

Evenement AttendreEvenement()
{
	// Rien n'a changé ici avec SDL2
	Evenement e = EVAucun;
	SDL_Event event;
	bool Valide = false;
	while (!Valide)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			e = EVQuitter;
			Valide = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP: // Flèche haut
				e = EVHaut;
				Valide = true;
				break;
			case SDLK_DOWN: // Flèche bas
				e = EVBas;
				Valide = true;
				break;
			case SDLK_RIGHT: // Flèche droite
				e = EVDroite;
				Valide = true;
				break;
			case SDLK_LEFT: // Flèche gauche
				e = EVGauche;
				Valide = true;
				break;
			case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
				e = EVQuitter;
				Valide = true;
				break;
			}
			break;
		}
	}
	return e;
}

Evenement LireEvenement()
{
	Evenement e = EVAucun;
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
        switch(event.type)
        {
        case SDL_QUIT:
            e = EVQuitter;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_UP: // Flèche haut
                e = EVHaut;
                break;
            case SDLK_DOWN: // Flèche bas
                e = EVBas;
                break;
            case SDLK_RIGHT: // Flèche droite
                e = EVDroite;
                break;
            case SDLK_LEFT: // Flèche gauche
                e =  EVGauche;
                break;
            case SDLK_ESCAPE: // Appui sur la touche Echap, on arrête le programme
                e = EVQuitter;
                break;
            default:    // Shut up compiler warnings
                break;
            }
            break;
        }
	}
	return e;
}
