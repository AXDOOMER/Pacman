#ifndef _SDLCLG_H
#define _SDLCLG_H
///////////////////////////////////////////////////////////////////////////////
// sdlclg.h
// Interface de programmation graphique pour le cours de KA0 utilisation la
// la libraire SDL 1.2.14-VC8
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
#include <SDL2/SDL.h>
#include <string>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Type de données utilisé pour conserver les numéros d'images
///////////////////////////////////////////////////////////////////////////////
typedef int ImageId;

///////////////////////////////////////////////////////////////////////////////
// Liste des événements associés au clavier
///////////////////////////////////////////////////////////////////////////////
enum Evenement
{
	EVAucun, EVQuitter, EVBas, EVHaut, EVGauche, EVDroite
};
///////////////////////////////////////////////////////////////////////////////
// Attendre
// Permet de placer le programme en attente pendant un certain temps
// Intrant: Temps: Nombre de millisecondes
// Extrant: Aucun
///////////////////////////////////////////////////////////////////////////////
void Attendre(int Temps);
///////////////////////////////////////////////////////////////////////////////
// InitialiserAffichage
// Fait apparaître une fenêtre graphique
// IMPORTANT: InitialiserAffichage doit être appelé avant même de charger des images
//   sinon tout l'affichage sera noir.
// Intrant: Titre: Titre de la fenêtre
//			Largeur: Largeur de la fenêtre en pixels
//		    Hauteur: Hauteur de la fenêtre en pixels
// Extrant: Aucun
///////////////////////////////////////////////////////////////////////////////
void InitialiserAffichage(string Titre, int Largeur, int Hauteur);
///////////////////////////////////////////////////////////////////////////////
// RemplirFenetre
// Colore toute la fenêtre d'une certaine couleur
// Intrant: Rouge: Composante rouge de la couleur (0-255)
//          Vert : Composante verte de la couleur (0-255)
//          Bleu : Composante bleue de la couleur (0-255)
// Extrant: Aucun
///////////////////////////////////////////////////////////////////////////////
void RemplirFenetre(int Rouge, int Vert, int Bleu);
///////////////////////////////////////////////////////////////////////////////
// DessinerRectangle
// Permet de dessiner un rectangle d'une certaine couleur dans la fenêtre
// Intrant: PosX: Position horizontale du rectangle. 
//          PosY: Position verticale du rectangle. 
//          Le point (0,0) est en haut à gauche
//			Largeur: Largeur du rectangle en pixels
//			Hauteur: Hauteur du rectangle en pixels
//          Rouge: Composante rouge de la couleur (0-255)
//          Vert : Composante verte de la couleur (0-255)
//          Bleu : Composante bleue de la couleur (0-255)
// Extrant: Aucun
///////////////////////////////////////////////////////////////////////////////
void DessinerRectangle(int PosX, int PosY, int Largeur, int Hauteur, int Rouge, int Vert, int Bleu);
///////////////////////////////////////////////////////////////////////////////
// ChargerImage
// Permet de charger une image du disque dur vers la mémoire
// Le seul type d'image supporté est le bitmap (BMP)
// Intrant: NomFichier: Nom du fichier image. Le fichier doit être dans le 
//                      même répertoire que le projet
// Extrant: un numéro identifiant uniquement l'image
///////////////////////////////////////////////////////////////////////////////
ImageId ChargerImage(string NomFichier);
///////////////////////////////////////////////////////////////////////////////
// AfficherImage
// Permet d'afficher une image à un certain endroit dans le fenêtre graphique
// Intrant: Image: Numéro de l'image
//			PosX: Position horizontale de l'image
//          PosY: Position verticale de l'image
//          Le point (0,0) est en haut à gauche
// Extrant: Aucun
///////////////////////////////////////////////////////////////////////////////
void AfficherImage(ImageId Image, int PosX, int PosY);
///////////////////////////////////////////////////////////////////////////////
// RafraichirFenetre
// Mettre à jour la fenêtre d'affichage pour que les dernières modifications
// soient visibles
// Intrant: Aucun
// Extrant: Aucun
///////////////////////////////////////////////////////////////////////////////
void RafraichirFenetre();
///////////////////////////////////////////////////////////////////////////////
// QuitterAffichage
// Ferme la fenêtre graphique
///////////////////////////////////////////////////////////////////////////////
void QuitterAffichage();
///////////////////////////////////////////////////////////////////////////////
// AttendreEvenement
// Attend que l'usager appuie sur une touche du clavier
// Intrant: Aucun
// Extrant: L'événement correspondant à la touche du clavier:
//   EVHaut: Flèche vers le haut
//   EVBas:  Flèche vers le bas
//   EVDroite: Flèche vers la droite
//   EVGauche: Flèche vers la gauche
//   EVQuitter: Esc
///////////////////////////////////////////////////////////////////////////////
Evenement AttendreEvenement();
///////////////////////////////////////////////////////////////////////////////
// LireEvenement
// Vérifie si l'usager a appuyé sur une touche du clavier
// Cette fonction n'est pas bloquante!!
// Intrant: Aucun
// Extrant: L'événement correspondant à la touche du clavier:
//   EVHaut: Flèche vers le haut
//   EVBas:  Flèche vers le bas
//   EVDroite: Flèche vers la droite
//   EVGauche: Flèche vers la gauche
//   EVQuitter: Esc
///////////////////////////////////////////////////////////////////////////////
Evenement LireEvenement();

#endif //_SDLCLG_H
