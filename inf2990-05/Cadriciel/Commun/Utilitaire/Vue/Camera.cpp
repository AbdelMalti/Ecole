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
	/// Constructeur de la caméra à partir des coordonnées cartésiennes.
	///
	/// @param[in]  position            : position de la caméra.
	/// @param[in]  pointVise           : point visé.
	/// @param[in]  directionHautCamera : direction du haut de la caméra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   caméra.
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
	/// Déplace la caméra dans le plan perpendiculaire à la direction visée
	///
	/// @param[in]  deplacementX : Déplacement sur l'axe horizontal du plan de
	///                            la caméra.
	/// @param[in]  deplacementY : Déplacement sur l'axe vertical du plan de la
	///                            caméra.
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
	/// Déplace la caméra dans l'axe de la direction visée.
	///
	/// @param[in]  deplacement    : Déplacement sur l'axe de la direction visée
	/// @param[in]  bougePointVise : Si vrai, le point de visé est également
	///                              déplacé.
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
	/// Rotation de la caméra autour de sa position (et donc déplacement du
	/// point visé en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point visé par rapport à la position.
	/// @param[in] rotationY        : Modification de l'angle d'élévation du
	///                               point visé par rapport à la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectuée
	///                               si elle amènerait une inversion de la
	///                               caméra.
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
	/// Rotation de la caméra autour de son point de visé (et donc déplacement
	/// de la position en gardant le point de visé fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de visé.
	/// @param[in]  rotationY        : Modification de l'angle d'élévation de la
	///                                position par rapport au point de visé.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectué
	///                                si elle amènerait une inversion de la
	///                                caméra.
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
	/// Cette fonction permet d'obtenir la distance de la caméra par rapport au centre.
	///
	/// @return La distance de la caméra.
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
	/// Cette fonction permet d'assigner la distance de la caméra par rapport au centre.
	///
	/// @param[in] dist : distance par rapport au centre de la caméra.
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
	/// @return La mode de vue de la caméra.
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
	/// Calcule la matrice aidant à positionner la caméra dans la scène.
	///
	/// @return Matrice de la caméra.
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
