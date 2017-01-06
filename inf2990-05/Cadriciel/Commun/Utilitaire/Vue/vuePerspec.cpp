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
	/// Constructeur d'une vue perspective.  Ne fait que créer les objets
	/// Projection et Camera correspondant.
	///
	/// @param[in] camera        : Caméra à utiliser au départ pour cette vue.
	/// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arrière (en @a z).
	/// @param[in] xMinFenetre   : coordonnée minimale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonnée maximale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonnée minimale en @a y de la fenêtre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonnée maximale en @a y de la fenêtre
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
	/// Retourne la projection perspective associée à cette vue.
	///
	/// @return La projection perspective associée à cette vue.
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
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// @param[in]  hauteur : Dimension en X de la nouvelle clôture.
	/// @param[in]  largeur : Dimension en Y de la nouvelle clôture.
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
	/// Permet de faire un zoom in selon l'incrément de zoom.
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
	/// Permet de faire un zoom out selon l'incrément de zoom.
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
	/// @param[in]  deplacementX : Déplacement en pourcentage de la largeur.
	/// @param[in]  deplacementY : Déplacement en pourcentage de la hauteur.
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
	/// Permet de faire un "pan" équivalent à la distance du déplacement
	/// spécifié en coordonnées de clôture.
	///
	/// @param[in]  deplacement : Déplacement en coordonnées de clôture
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
	/// Ne fait rien, car se déplacer dans l'axe de la profondeur n'a pas
	/// vraiment de signification avec une vue orthogonale.
	///
	/// @param[in]  deplacement : Déplacement selon l'axe Z.
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
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Une rotation de 100% correspondant à 360 degrés en X (angle de
	/// rotation) ou 180 degrés en Y (angle d'élévation).
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
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Un déplacement de la taille de la fenêtre correspond à 100%.
	///
	/// @param[in]  rotation : Rotation en coordonnées de clotûre (pixels).
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
	/// correspondrait à un rouli et n'est pas souhaitable pour cette vue.
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
