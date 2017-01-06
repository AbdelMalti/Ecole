//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author groupe5
/// @date 2016-09-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef __VISITEUR_ROTATION_H__
#define __VISITEUR_ROTATION_H__

#include "VisiteurAbstrait.h"

class VisiteurRotation : public VisiteurAbstrait
{
public:
	// Constructeur de la classe
	VisiteurRotation(double deltaY = 0.0, double centreX = 0.0, double centreY = 0.0);

	// Destructeur Virtuel
	~VisiteurRotation() {};

	// fonctions de visiste
	void visiter(NoeudComposite* noeud);
	void visiter(NoeudMaillet* noeud);
	void visiter(NoeudMailletOrdi* noeud);
	void visiter(NoeudTable* noeud);
	void visiter(NoeudMuret* noeud);
	void visiter(NoeudPortail* noeud);
	void visiter(NoeudRondelle* noeud);
	void visiter(NoeudBonus* noeud);
	void visiter(NoeudBut* noeud);

	double getCentreX();
	double getCentreY();
	void setCentre(double centreX, double centreY);
	double getDelta();
	void setDelta(double delta);

private:
	// variation de la souris en Y indiquant la vitesse et le sens de la rotation
	double deltaY_;

	// centre de la rotation
	double centreX_;
	double centreY_;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
#endif
