////////////////////////////////////////////////////////////////////////////////////
/// @file VueOrtho.cpp
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "vuePerspec.h"
#include <iostream>


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VuePerspec::VuePerspec(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une vue perspective.  Ne fait que cr�er les objets
	/// Projection et Camera correspondant.
	///
	/// @param[in] camera        : Cam�ra � utiliser au d�part pour cette vue.
	/// @param[in] xMinCloture   : coordonn�e minimale en @a x de la cl�ture.
	/// @param[in] xMaxCloture   : coordonn�e maximale en @a x de la cl�ture.
	/// @param[in] yMinCloture   : coordonn�e minimale en @a y de la cl�ture.
	/// @param[in] yMaxCloture   : coordonn�e maximale en @a y de la cl�ture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arri�re (en @a z).
	/// @param[in] xMinFenetre   : coordonn�e minimale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonn�e maximale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonn�e minimale en @a y de la fen�tre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonn�e maximale en @a y de la fen�tre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	VuePerspec::VuePerspec(Camera const& camera, ProjectionPerspec const& projection) :
		Vue{ camera },
		projection_{ projection }
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn const ProjectionPerspec& VuePerspec::obtenirProjection() const
	///
	/// Retourne la projection perspective associ�e � cette vue.
	///
	/// @return La projection perspective associ�e � cette vue.
	///
	////////////////////////////////////////////////////////////////////////
	const ProjectionPerspec& VuePerspec::obtenirProjection() const
	{
		return projection_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::redimensionnerFenetre( int largeur, int hauteur )
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// @param[in]  hauteur : Dimension en X de la nouvelle cl�ture.
	/// @param[in]  largeur : Dimension en Y de la nouvelle cl�ture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::redimensionnerFenetre(int largeur, int hauteur)
	{
		projection_.redimensionnerFenetre(largeur, hauteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::zoomerIn()
	{
		
		/*std::cout << "distance : " << camera_.getDist() << std::endl;*/
		if (camera_.getDist() < 210)
			return;
		else
		{
			if (camera_.getDist() < 204)
				camera_.setDist(210);
			else
				camera_.setDist(camera_.getDist() - 6);
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::zoomerOut()
	{
		//camera_.setDist(camera_.getDist() + 6);
		/*std::cout << "distance : " << camera_.getDist() << std::endl;*/
		if (camera_.getDist() > 540)
			return;
		else
		{
			if (camera_.getDist() > 546)
				camera_.setDist(540);
			else
				camera_.setDist(camera_.getDist() + 6);
		}
	}

	void VuePerspec::zoomerInElastique(const glm::ivec2 & coin1, const glm::ivec2 & coin2)
	{
	}

	void VuePerspec::zoomerOutElastique(const glm::ivec2 & coin1, const glm::ivec2 & coin2)
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::deplacerXY(double deplacementX, double deplacementY)
	///
	/// @param[in]  deplacementX : D�placement en pourcentage de la largeur.
	/// @param[in]  deplacementY : D�placement en pourcentage de la hauteur.
	///
	/// Permet de faire un "pan" d'un certain pourcentage.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::deplacerXY(double deplacementX, double deplacementY)
	{
		camera_.deplacerXY(deplacementX * projection_.obtenirDimensionCloture()[0],
			deplacementY * projection_.obtenirDimensionCloture()[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::deplacerXY(const glm::ivec2& deplacement)
	///
	/// Permet de faire un "pan" �quivalent � la distance du d�placement
	/// sp�cifi� en coordonn�es de cl�ture.
	///
	/// @param[in]  deplacement : D�placement en coordonn�es de cl�ture
	///                           (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::deplacerXY(const glm::ivec2& deplacement)
	{
		camera_.deplacerXY(deplacement[0], deplacement[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::deplacerZ(double deplacement)
	///
	/// Ne fait rien, car se d�placer dans l'axe de la profondeur n'a pas
	/// vraiment de signification avec une vue orthogonale.
	///
	/// @param[in]  deplacement : D�placement selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::deplacerZ(double deplacement)
	{
		camera_.deplacerZ(deplacement, false);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::rotaterXY(double rotationX, double rotationY)
	///
	/// Permet de faire une rotation de la cam�ra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'�l�vation.
	///
	/// Une rotation de 100% correspondant � 360 degr�s en X (angle de
	/// rotation) ou 180 degr�s en Y (angle d'�l�vation).
	///
	/// @param[in]  rotationX : Rotation en pourcentage de la largeur.
	/// @param[in]  rotationY : Rotation en pourcentage de la hauteur.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::rotaterXY(double rotationX, double rotationY)
	{
		camera_.orbiterXY(rotationX * 360, rotationY * 180);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::rotaterXY(const glm::ivec2& rotation)
	///
	/// Permet de faire une rotation de la cam�ra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'�l�vation.
	///
	/// Un d�placement de la taille de la fen�tre correspond � 100%.
	///
	/// @param[in]  rotation : Rotation en coordonn�es de clot�re (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::rotaterXY(const glm::ivec2& rotation)
	{
		const glm::ivec2 dimensions{ projection_.obtenirDimensionCloture() };
		rotaterXY(rotation[0] / (double)dimensions[0],
			rotation[1] / (double)dimensions[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspec::rotaterZ(double rotation)
	///
	/// Ne fait rien, car tourner autour de l'axe de la profondeur
	/// correspondrait � un rouli et n'est pas souhaitable pour cette vue.
	///
	/// @param[in]  rotation : Rotation selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspec::rotaterZ(double rotation)
	{
	}


}; // Fin du namespace vue.


   ///////////////////////////////////////////////////////////////////////////
   /// @}
   ///////////////////////////////////////////////////////////////////////////
