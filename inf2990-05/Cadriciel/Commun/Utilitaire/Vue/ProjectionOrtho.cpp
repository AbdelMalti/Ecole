////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionOrtho.h"
#include <glm/gtc/matrix_transform.inl>
#include<iostream>


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int largeurCloture, int hauteurCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double largeurFenetre, double hauteurFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] largeurCloture   : dimension en @a X de la clôture.
	/// @param[in] hauteurCloture   : dimension en @a Y de la clôture.
	/// @param[in] zAvant			: distance du plan avant (en @a z).
	/// @param[in] zArriere			: distance du plan arrière (en @a z).
	/// @param[in] zoomInMax		: facteur de zoom in maximal.
	/// @param[in] zoomOutMax		: facteur de zoom out maximal.
	/// @param[in] incrementZoom	: distance du plan arrière (en @a z).
	/// @param[in] largeurFenetre	: dimension en @a X de la fenêtre
	///								  virtuelle.
	/// @param[in] hauteurFenetre	: dimension en @a Y de la fenêtre
	///								  virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrtho::ProjectionOrtho(int largeurCloture, int hauteurCloture,
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
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		/*std::cout << "********************************************" << std::endl;
		std::cout << "largeurFenetre_ : " << largeurFenetre_ << std::endl;
		std::cout << "hauteurFenetre_ : " << hauteurFenetre_ << std::endl;
		std::cout << "zoomInMax_      : " << zoomInMax_ << std::endl;
		std::cout << "********************************************" << std::endl;*/
		// À IMPLANTER.
		//Vérifie la taille du zoom
		if (largeurFenetre_ < 258 || hauteurFenetre_ < 140 )//&& largeurFenetre_ * hauteurFenetre_ < 10)		//zoomInMax_
		{
			return; //zoom max atteint, donc on ne fait pas de zoom
		}

		//Ajuster pour agrandir l'objet
		else {
			largeurFenetre_ -= largeurFenetre_ * (incrementZoom_ - 1);
			hauteurFenetre_ -= hauteurFenetre_ * (incrementZoom_ - 1);

			//Appliquer le zoom
			obtenirMatrice();
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{

		//Vérifie la taille du zoom
		/*std::cout << "********************************************" << std::endl;
		std::cout << "largeurFenetre_ : " << largeurFenetre_ << std::endl;
		std::cout << "hauteurFenetre_ : " << hauteurFenetre_ << std::endl;
		std::cout << "zoomInMax_      : " << zoomInMax_ << std::endl;
		std::cout << "********************************************" << std::endl;*/
		if (largeurFenetre_ > zoomOutMax_ && hauteurFenetre_ > zoomOutMax_)
		{
			/*std::cout << "Dans limite Zone " << std::endl;*/
			return; //zoom max atteint, donc on ne fait pas de zoom
		}
		//Ajuster pour réduire l'objet
		largeurFenetre_ += largeurFenetre_ * (incrementZoom_ - 1);
		hauteurFenetre_ += hauteurFenetre_ * (incrementZoom_ - 1);

		//Appliquer le zoom
		obtenirMatrice();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( double largeur, double hauteur )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// L'agrandissement de la fenêtre virtuelle est proportionnel à
	/// l'agrandissement de la clotûre afin que les objets gardent la même
	/// grandeur apparente lorsque la fenêtre est redimensionnée.
	///
	/// @param[in]  largeur : largeur de la nouvelle clôture
	/// @param[in]  hauteur : hauteur de la nouvelle clôture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(int largeur, int hauteur)
	{

		// À IMPLANTER.
		/*double rapportFenetreCLotureLargeur = largeurFenetre_ / largeurCloture_;
		double rapportFenetreClotureHauteur = hauteurFenetre_ / hauteurCloture_;

		largeurFenetre_ = largeurCloture_ * rapportFenetreCLotureLargeur;
		hauteurFenetre_ = hauteurCloture_ * rapportFenetreClotureHauteur;

		largeurCloture_ = largeur;
		hauteurCloture_ = hauteur;

		ajusterRapportAspect();
		obtenirMatrice();*/

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
	/// @fn glm::mat4 ProjectionOrtho::obtenirMatrice() const
	///
	/// Cette fonction permet de retourner la fenêtre virtuelle en appelant les
	/// fonctions de glm selon le type de projection et les propriétés de la
	/// fenêtre.
	///
	/// @return Matrice de projection.
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4 ProjectionOrtho::obtenirMatrice() const
	{
		return glm::ortho(-largeurFenetre_ / 2, largeurFenetre_ / 2, 
			-hauteurFenetre_ / 2, hauteurFenetre_ / 2,	
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// de la clôture de façon à ce que le rapport d'aspect soit respecté.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{

		// À IMPLANTER.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0 , largeurCloture_, hauteurCloture_);
		glMatrixMode(GL_MODELVIEW);
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
