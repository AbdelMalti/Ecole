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
#include "VueOrtho.h"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VueOrtho::VueOrtho(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une vue orthogonale.  Ne fait que cr�er les objets
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
	VueOrtho::VueOrtho(Camera const& camera, ProjectionOrtho const& projection) :
		Vue{ camera },
		projection_{projection}
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn const ProjectionOrtho& VueOrtho::obtenirProjection() const
	///
	/// Retourne la projection orthogonale associ�e � cette vue.
	///
	/// @return La projection orthogonale associ�e � cette vue.
	///
	////////////////////////////////////////////////////////////////////////
	const ProjectionOrtho& VueOrtho::obtenirProjection() const
	{
		return projection_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::redimensionnerFenetre( int largeur, int hauteur )
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
	void VueOrtho::redimensionnerFenetre(int largeur, int hauteur)
	{
		projection_.redimensionnerFenetre(largeur, hauteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::zoomerIn()
	{
		projection_.zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::zoomerOut()
	{
		projection_.zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in �lastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonn�es du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonn�es du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::zoomerInElastique(const glm::ivec2& coin1,
		const glm::ivec2& coin2)
	{
		/// � Faire: Redimensionner la projection et d�placer la cam�ra
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out �lastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonn�es du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonn�es du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::zoomerOutElastique(const glm::ivec2& coin1,
		const glm::ivec2& coin2)
	{
		/// � Faire: Redimensionner la projection et d�placer la cam�ra
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::deplacerXY(double deplacementX, double deplacementY)
	///
	/// @param[in]  deplacementX : D�placement en pourcentage de la largeur.
	/// @param[in]  deplacementY : D�placement en pourcentage de la hauteur.
	///
	/// Permet de faire un "pan" d'un certain pourcentage.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::deplacerXY(double deplacementX, double deplacementY)
	{
		camera_.deplacerXY(deplacementX * projection_.obtenirDimensionCloture()[0], 
			deplacementY * projection_.obtenirDimensionCloture()[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::deplacerXY(const glm::ivec2& deplacement)
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
	void VueOrtho::deplacerXY(const glm::ivec2& deplacement)
	{
		camera_.deplacerXY(deplacement[0], deplacement[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::deplacerZ(double deplacement)
	///
	/// Ne fait rien, car se d�placer dans l'axe de la profondeur n'a pas
	/// vraiment de signification avec une vue orthogonale.
	///
	/// @param[in]  deplacement : D�placement selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::deplacerZ(double deplacement)
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::rotaterXY(double rotationX, double rotationY)
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
	void VueOrtho::rotaterXY(double rotationX, double rotationY)
	{
		camera_.orbiterXY(rotationX * 360, rotationY * 180);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::rotaterXY(const glm::ivec2& rotation)
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
	void VueOrtho::rotaterXY(const glm::ivec2& rotation)
	{
		const glm::ivec2 dimensions{ projection_.obtenirDimensionCloture() };
		rotaterXY(rotation[0] / (double) dimensions[0],
			rotation[1] / (double) dimensions[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::rotaterZ(double rotation)
	///
	/// Ne fait rien, car tourner autour de l'axe de la profondeur
	/// correspondrait � un rouli et n'est pas souhaitable pour cette vue.
	///
	/// @param[in]  rotation : Rotation selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::rotaterZ(double rotation)
	{
	}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
