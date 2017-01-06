///////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "Utilitaire.h"
#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>

double limiteZoom = 0.0;

namespace vue {


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn Camera::Camera(const glm::dvec3& position, const glm::dvec3& pointVise, const glm::dvec3& directionHautCamera, const glm::dvec3& directionHautMonde)
	///
	/// Constructeur de la cam�ra � partir des coordonn�es cart�siennes.
	///
	/// @param[in]  position            : position de la cam�ra.
	/// @param[in]  pointVise           : point vis�.
	/// @param[in]  directionHautCamera : direction du haut de la cam�ra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   cam�ra.
	///
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////////
	Camera::Camera(const glm::dvec3& position,
		const glm::dvec3& pointVise,
		const glm::dvec3& directionHautCamera,
		const glm::dvec3& directionHautMonde
	)
		: position_{ position },
		pointVise_{ pointVise },
		directionHaut_{ directionHautCamera },
		directionHautMonde_{ directionHautMonde }
		//
	{
		dist_ = sqrt(pow(position[0], 2.0) + pow(position[1], 2.0) + pow(position[2], 2.0));
		/*angleTetha_ = abs(atan2(position[1], position[0])) * 180;
		anglePhi_ = acos(position[2] / dist_)* 30;*/
		angleTetha_ = 270.503;
		anglePhi_ = 46.3319;
		estOrbite_ = false ;
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerXY( double deplacementX, double deplacementY )
	///
	/// D�place la cam�ra dans le plan perpendiculaire � la direction vis�e
	///
	/// @param[in]  deplacementX : D�placement sur l'axe horizontal du plan de
	///                            la cam�ra.
	/// @param[in]  deplacementY : D�placement sur l'axe vertical du plan de la
	///                            cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerXY(double deplacementX, double deplacementY)
	{
		position_[0] += deplacementX;
		position_[1] += deplacementY;
		pointVise_[0] += deplacementX;
		pointVise_[1] += deplacementY;
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerZ( double deplacement, bool bougePointVise )
	///
	/// D�place la cam�ra dans l'axe de la direction vis�e.
	///
	/// @param[in]  deplacement    : D�placement sur l'axe de la direction vis�e
	/// @param[in]  bougePointVise : Si vrai, le point de vis� est �galement
	///                              d�plac�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerZ(double deplacement, bool bougePointVise)
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::tournerXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de sa position (et donc d�placement du
	/// point vis� en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point vis� par rapport � la position.
	/// @param[in] rotationY        : Modification de l'angle d'�l�vation du
	///                               point vis� par rapport � la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectu�e
	///                               si elle am�nerait une inversion de la
	///                               cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::tournerXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::orbiterXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de son point de vis� (et donc d�placement
	/// de la position en gardant le point de vis� fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  rotationY        : Modification de l'angle d'�l�vation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectu�
	///                                si elle am�nerait une inversion de la
	///                                cam�ra.
	///
	///  @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::orbiterXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
		angleTetha_ += rotationX / 360;
		anglePhi_ += rotationY / 180;

		if (angleTetha_ > 360.0)
			angleTetha_ -= 360.0;
		else if (angleTetha_ < 0.0)
			angleTetha_ += 360.0;

		if (anglePhi_ > 90.0)
			anglePhi_ = 90.0;
		else if (anglePhi_ < 0.1)
			anglePhi_ = 0.01;

		position_[0] = dist_ * cos(glm::radians(angleTetha_))*sin(glm::radians(anglePhi_));
		position_[1] = dist_ * sin(glm::radians(angleTetha_))*sin(glm::radians(anglePhi_));
		position_[2] = dist_ * cos(glm::radians(anglePhi_));

		//Calculer le nouveau directionHaut de la camera
		glm::dvec3 distPlan = { -position_[0], -position_[1], 0.0 };
		glm::dvec3 vectoriel = glm::cross(distPlan, glm::dvec3(0, 0, 1));

		directionHaut_ = glm::cross(vectoriel, -position_);
	}

	/////////////////////////////////////////////////////////////////////////////////////
	///
	/// @fn double Camera::getDist() const
	///
	/// Cette fonction permet d'obtenir la distance de la cam�ra par rapport au centre.
	///
	/// @return La distance de la cam�ra.
	///
	/////////////////////////////////////////////////////////////////////////////////////
	double Camera::getDist() const
	{
		return dist_;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::setDist(double dist)
	///
	/// Cette fonction permet d'assigner la distance de la cam�ra par rapport au centre.
	///
	/// @param[in] dist : distance par rapport au centre de la cam�ra.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////////////////////
	void Camera::setDist(double dist)
	{
		dist_ = dist;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool Camera::getEstOrbite() const
	///
	/// Cette fonction permet d'obtenir le mode de vue
	///
	/// @return La mode de vue de la cam�ra.
	///
	/////////////////////////////////////////////////////////////////////////////////////
	bool Camera::getEstOrbite() const
	{
		return estOrbite_;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::setEstOrbite(bool estOrbite)
	///
	/// Cette fonction permet de modifier le mode de vue
	///
	/// @param[in] estOrbite : mode de vue
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////////////////////
	void Camera::setEstOrbite(bool estOrbite)
	{
		estOrbite_ = estOrbite;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4 Camera::obtenirMatrice() const
	///
	/// Calcule la matrice aidant � positionner la cam�ra dans la sc�ne.
	///
	/// @return Matrice de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4 Camera::obtenirMatrice() const
	{
		if (estOrbite_)
		{
			return glm::lookAt(glm::dvec3(dist_ * cos(glm::radians(angleTetha_))*sin(glm::radians(anglePhi_)),
				dist_ * sin(glm::radians(angleTetha_))*sin(glm::radians(anglePhi_)),
				dist_ * cos(glm::radians(anglePhi_))), pointVise_, directionHaut_);
		}
		else
			return glm::lookAt(position_,pointVise_, directionHaut_);
	}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
