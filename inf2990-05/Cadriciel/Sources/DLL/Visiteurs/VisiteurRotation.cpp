//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.cpp
/// @author groupe5
/// @date 2016-09-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "VisiteurRotation.h"
#include "../Arbre/Noeuds/NoeudAbstrait.h"
#include "../Arbre/Noeuds/NoeudComposite.h"
#include "../Arbre/Noeuds/NoeudMaillet.h"
#include "../Arbre/Noeuds/NoeudMailletOrdi.h"
#include "../Arbre/Noeuds/NoeudMuret.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include "../Arbre/Noeuds/NoeudRondelle.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "../Arbre/Noeuds/NoeudBut.h"
#include "../Arbre/Noeuds/NoeudBonus.h"
#include "../Arbre/ArbreRenduINF2990.h"

#include <tuple>

#define X 0
#define Y 1
#define Z 2

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation(double deltaY)
///
/// constructeur du visiteur de rotation
///
/// @param[in] deltaY : variation de la souris en Y indiquant la vitesse et le sens de la rotation
/// @param[in] centreX : coordonnée en X du centre de rotation
/// @param[in] centreY : coordonnée en Y du centre de rotation
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation(double deltaY, double centreX, double centreY)
{
	centreX_ = centreX;
	centreY_ = centreY;
	deltaY_ = deltaY;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudComposite& noeud)
///
/// Fonction de rotation des noeuds composites
///
/// @param[in] noeud : noeud sur lequel on applique la sélection
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudComposite* noeud)
{
	double maxX = 0.0;
	double minX = 0.0;
	double maxY = 0.0;
	double minY = 0.0;

	std::vector<glm::dvec3> positionInit;
	glm::dvec3 pos;
	glm::dvec3 centreDeRotation;
	NoeudAbstrait* enfantDeNoeudAbstrait;

	for (size_t i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfantDeNoeudAbstrait = noeud->getEnfants()[i];
		pos = enfantDeNoeudAbstrait->obtenirPositionRelative();
		positionInit.push_back(enfantDeNoeudAbstrait->obtenirPositionRelative());

		if (pos[0] > maxX)
		{
			maxX = pos[0];
		}

		if (pos[0] < minX)
		{
			minX = pos[0];
		}

		if (pos[1] > maxY)
		{
			maxY = pos[1];
		}

		if (pos[1] < minY)
		{
			minY = pos[1];
		}
	}

	for (size_t i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfantDeNoeudAbstrait = noeud->getEnfants()[i];
		centreDeRotation[0] = ((maxX + minX) / 2) - positionInit[i][0];
		centreDeRotation[1] = ((maxY - minY) / 2) - positionInit[i][1];
		enfantDeNoeudAbstrait->setCentreDeRotation(centreDeRotation);
		enfantDeNoeudAbstrait->accepter(this);
		enfantDeNoeudAbstrait->assignerPositionRelative(positionInit[i]);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudTable& noeud)
///
/// Fonction de rotation des noeuds table
///
/// @param[in] noeud : noeud sur lequel on applique la sélection
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudTable* noeud)
{
	double maxX = 0.0;
	double minX = 0.0;
	double maxY = 0.0;
	double minY = 0.0;

	std::vector<glm::dvec3> positionInit;
	glm::dvec3 pos;
	glm::dvec3 centreDeRotation;
	NoeudAbstrait* enfantDeNoeudAbstrait;

	for (size_t i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfantDeNoeudAbstrait = noeud->getEnfants()[i];
		pos = enfantDeNoeudAbstrait->obtenirPositionRelative();
		positionInit.push_back(enfantDeNoeudAbstrait->obtenirPositionRelative());

		if (pos[0] > maxX)
		{
			maxX = pos[0];
		}

		if (pos[0] < minX)
		{
			minX = pos[0];
		}

		if (pos[1] > maxY)
		{
			maxY = pos[1];
		}

		if (pos[1] < minY)
		{
			minY = pos[1];
		}
	}

	for (size_t i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfantDeNoeudAbstrait = noeud->getEnfants()[i];
		centreDeRotation[0] = ((maxX + minX) / 2) - positionInit[i][0];
		centreDeRotation[1] = ((maxY - minY) / 2) - positionInit[i][1];
		enfantDeNoeudAbstrait->setCentreDeRotation(centreDeRotation);
		enfantDeNoeudAbstrait->accepter(this);
		enfantDeNoeudAbstrait->assignerPositionRelative(positionInit[i]);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudMaillet& noeud)
///
/// Fonction de rotation des noeuds maillets
///
/// @param[in] noeud : noeud sur lequel on applique la sélection
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudMaillet* noeud)
{
	double angle = noeud->getAngleRotation();
	angle += deltaY_;
	if (angle >= 360.0f)
	{
		angle -= 360.0f;
	}
	else if (angle < -360.0f)
	{
		angle += 360.0f;
	}
	noeud->setAngleRotation(angle);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudMailletOrdi& noeud)
///
/// Fonction de rotation des noeuds maillets
///
/// @param[in] noeud : noeud sur lequel on applique la sélection
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudMailletOrdi* noeud)
{
	double angle = noeud->getAngleRotation();
	angle += deltaY_;
	if (angle >= 360.0f)
	{
		angle -= 360.0f;
	}
	else if (angle < -360.0f)
	{
		angle += 360.0f;
	}
	noeud->setAngleRotation(angle);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotater::visiter(NoeudRondelle& noeud)
///
/// Fonction de rotation des noeuds rondelles
///
/// @param[in] noeud : noeud sur lequel on applique la sélection
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudRondelle* noeud)
{
	double angle = noeud->getAngleRotation();
	angle += deltaY_;
	if (angle >= 360.0f)
	{
		angle -= 360.0f;
	}
	else if (angle < -360.0f)
	{
		angle += 360.0f;
	}
	noeud->setAngleRotation(angle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudMuret& noeud)
///
/// Fonction de rotation des noeuds murets
///
/// @param[in] noeud : noeud sur lequel on applique la sélection
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudMuret* noeud)
{
	double angle = noeud->getAngleRotation();
	angle += deltaY_;
	if (angle >= 360.0f)
	{
		angle -= 360.0f;
	}
	else if (angle < -360.0f)
	{
		angle += 360.0f;
	}
	noeud->setAngleRotation(angle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudPortail& noeud)
///
/// Fonction de rotation des noeuds portails
///
/// @param[in] noeud : noeud sur lequel on applique la sélection
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudPortail* noeud)
{
	double angle = noeud->getAngleRotation();
	angle += deltaY_;
	if (angle >= 360.0f)
	{
		angle -= 360.0f;
	}
	else if (angle < -360.0f)
	{
		angle += 360.0f;
	}
	noeud->setAngleRotation(angle);
}

void VisiteurRotation::visiter(NoeudBut* noeud)
{

}

double VisiteurRotation::getCentreX()
{
	return centreX_;
}

double VisiteurRotation::getCentreY()
{
	return centreY_;
}

void VisiteurRotation::setCentre(double centreX, double centreY)
{
	centreX_ = centreX;
	centreY_ = centreY;
}

double VisiteurRotation::getDelta()
{
	return deltaY_;
}

void VisiteurRotation::setDelta(double delta)
{
	deltaY_ = delta;
}

void VisiteurRotation::visiter(NoeudBonus* noeud)
{
	double angle = noeud->getAngleRotation();
	angle += deltaY_;
	if (angle >= 360.0f)
	{
		angle -= 360.0f;
	}
	else if (angle < -360.0f)
	{
		angle += 360.0f;
	}
	noeud->setAngleRotation(angle);
}