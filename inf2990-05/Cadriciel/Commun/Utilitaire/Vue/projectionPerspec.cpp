////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionPerspec.cpp
/// @author Equipe 05
/// @date 2016-11-23
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionPerspec.h"
#include <glm/gtc/matrix_transform.inl>


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionPerspec::ProjectionPerspec(int largeurCloture, int hauteurCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double largeurFenetre, double hauteurFenetre)
	///
	/// Constructeur d'une projection perspective. Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] largeurCloture   : dimension en @a X de la cl�ture.
	/// @param[in] hauteurCloture   : dimension en @a Y de la cl�ture.
	/// @param[in] zAvant			: distance du plan avant (en @a z).
	/// @param[in] zArriere			: distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax		: facteur de zoom in maximal.
	/// @param[in] zoomOutMax		: facteur de zoom out maximal.
	/// @param[in] incrementZoom	: distance du plan arri�re (en @a z).
	/// @param[in] largeurFenetre	: dimension en @a X de la fen�tre
	///								  virtuelle.
	/// @param[in] hauteurFenetre	: dimension en @a Y de la fen�tre
	///								  virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionPerspec::ProjectionPerspec(int largeurCloture, int hauteurCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double largeurFenetre, double hauteurFenetre) :
		Projection{ largeurCloture, hauteurCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
		largeurFenetre_{ largeurFenetre },
		hauteurFenetre_{ hauteurFenetre }
	{
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspec::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspec::zoomerIn()
	{
		////V�rifie la taille du zoom
		//if (largeurFenetre_ < zoomInMax_ && hauteurFenetre_ < zoomInMax_)//(largeurFenetre_ * hauteurFenetre_ < 10)		//zoomInMax_
		//	return; //zoom max atteint, donc on ne fait pas de zoom

		////Ajuster pour agrandir l'objet
		//largeurFenetre_ -= largeurFenetre_ * (incrementZoom_ - 1);
		//hauteurFenetre_ -= hauteurFenetre_ * (incrementZoom_ - 1);

		////Appliquer le zoom
		//obtenirMatrice();

		

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspec::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionPerspec::zoomerOut()
	{
		////V�rifie la taille du zoom
		//if (largeurFenetre_ > zoomOutMax_ && hauteurFenetre_ > zoomOutMax_)
		//	return; //zoom max atteint, donc on ne fait pas de zoom

		//			//Ajuster pour r�duire l'objet
		//largeurFenetre_ += largeurFenetre_ * (incrementZoom_ - 1);
		//hauteurFenetre_ += hauteurFenetre_ * (incrementZoom_ - 1);

		////Appliquer le zoom
		//obtenirMatrice();


	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspec::redimensionnerFenetre( double largeur, double hauteur )
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// L'agrandissement de la fen�tre virtuelle est proportionnel �
	/// l'agrandissement de la clot�re afin que les objets gardent la m�me
	/// grandeur apparente lorsque la fen�tre est redimensionn�e.
	///
	/// @param[in]  largeur : largeur de la nouvelle cl�ture
	/// @param[in]  hauteur : hauteur de la nouvelle cl�ture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspec::redimensionnerFenetre(int largeur, int hauteur)
	{
		largeurFenetre_ += (largeurFenetre_ / largeurCloture_) * largeur - largeurFenetre_;
		hauteurFenetre_ += (hauteurFenetre_ / hauteurCloture_) * hauteur - hauteurFenetre_;

		largeurCloture_ = largeur;
		hauteurCloture_ = hauteur;


		obtenirMatrice();
		ajusterRapportAspect();

		glViewport(0, 0, largeur, hauteur);


	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4 ProjectionPerspec::obtenirMatrice() const
	///
	/// Cette fonction permet de retourner la fen�tre virtuelle en appelant les
	/// fonctions de glm selon le type de projection et les propri�t�s de la
	/// fen�tre.
	///
	/// @return Matrice de projection.
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4 ProjectionPerspec::obtenirMatrice() const
	{
		/*return glm::frustum(-largeurFenetre_ / 400, largeurFenetre_ / 400,
			-hauteurFenetre_ / 400, hauteurFenetre_ / 400,
			zAvant_, zArriere_);*/
		return glm::perspective(glm::radians(45.0), largeurFenetre_ / hauteurFenetre_, zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspec::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspec::ajusterRapportAspect()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, largeurCloture_, hauteurCloture_);
		glMatrixMode(GL_MODELVIEW);
	}

}; // Fin du namespace vue.


   ///////////////////////////////////////////////////////////////////////////
   /// @}
   ///////////////////////////////////////////////////////////////////////////
