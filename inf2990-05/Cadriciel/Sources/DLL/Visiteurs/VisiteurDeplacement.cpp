#include "VisiteurDeplacement.h"
#include "NoeudComposite.h"
#include "NoeudAbstrait.h"
#include "NoeudBonus.h"
#include "NoeudMaillet.h"
#include "NoeudMailletOrdi.h"
#include "NoeudPortail.h"
#include "NoeudMuret.h"
#include "NoeudRondelle.h"
#include "NoeudTable.h"

VisiteurDeplacement::VisiteurDeplacement()
{
	X_ = 0;
	Y_ = 0;
	Z_ = 0;
}


VisiteurDeplacement::~VisiteurDeplacement()
{

}


void VisiteurDeplacement::setX(double X)
{
	X_ = X;
}

void VisiteurDeplacement::setY(double Y)
{
	Y_ = Y;
}

void VisiteurDeplacement::setZ(double Z)
{
	Z_ = Z;
}

double VisiteurDeplacement::getX() const
{
	return X_;
}

double VisiteurDeplacement::getY() const
{
	return Y_;
}

double VisiteurDeplacement::getZ() const
{
	return Z_;
}

void VisiteurDeplacement::visiter(NoeudComposite* noeudComposite)
{
	/*for (int i = 0; i < noeudComposite->obtenirNombreEnfants(); i++)
	{
		if (noeudComposite-> chercher(i)->estSelectionne())
		{
			noeudComposite->chercher(i)->accepter(this);
		}
	}*/
}

void VisiteurDeplacement::visiter(NoeudBonus *noeudBonus)
{
	//if (noeudBonus->estSelectionne())
	//{
		glm::dvec3 pos;
		pos = noeudBonus->obtenirPositionRelative();
		X_ += pos[0];
		Y_ += pos[1];
		Z_ += pos[2];

		pos[0] = X_;
		pos[1] = Y_;
		pos[2] = Z_;

		noeudBonus->assignerPositionRelative(pos);
	//}
}

void VisiteurDeplacement::visiter(NoeudMaillet* noeudMaillet)
{
	//if (noeudMaillet->estSelectionne())
	//{
		glm::vec3 pos;
		pos = noeudMaillet->obtenirPositionRelative();
		X_ += pos[0];
		Y_ += pos[1];
		Z_ += pos[2];

		pos[0] = X_;
		pos[1] = Y_;
		pos[2] = Z_;

		noeudMaillet->assignerPositionRelative(pos);
	//}
}

void VisiteurDeplacement::visiter(NoeudMailletOrdi* noeudMailletOrdi)
{
	//if (noeudMailletOrdi->estSelectionne())
	//{
	glm::vec3 pos;
	pos = noeudMailletOrdi->obtenirPositionRelative();
	X_ += pos[0];
	Y_ += pos[1];
	Z_ += pos[2];

	pos[0] = X_;
	pos[1] = Y_;
	pos[2] = Z_;

	noeudMailletOrdi->assignerPositionRelative(pos);
	//}
}


void VisiteurDeplacement::visiter(NoeudPortail* noeudPortail)
{
	//if (noeudPortail->estSelectionne())
	//{
		glm::vec3 pos;
		pos = noeudPortail->obtenirPositionRelative();
		X_ += pos[0];
		Y_ += pos[1];
		Z_ += pos[2];

		pos[0] = X_;
		pos[1] = Y_;
		pos[2] = Z_;

		noeudPortail->assignerPositionRelative(pos);
	//}
}

void VisiteurDeplacement::visiter(NoeudMuret* noeudMuret)
{
	//if (noeudMuret->estSelectionne())
	//{
		glm::vec3 pos;
		pos = noeudMuret->obtenirPositionRelative();
		X_ += pos[0];
		Y_ += pos[1];
		Z_ += pos[2];

		pos[0] = X_;
		pos[1] = Y_;
		pos[2] = Z_;

		noeudMuret->assignerPositionRelative(pos);
	//}
}

void VisiteurDeplacement::visiter(NoeudRondelle* noeudRondelle)
{
	//if (noeudRondelle->estSelectionne())
	//{
		glm::vec3 pos;
		pos = noeudRondelle->obtenirPositionRelative();
		X_ += pos[0];
		Y_ += pos[1];
		Z_ += pos[2];

		pos[0] = X_;
		pos[1] = Y_;
		pos[2] = Z_;

		noeudRondelle->assignerPositionRelative(pos);
	//}
}

void VisiteurDeplacement::visiter(NoeudTable* noeudTable)
{
	/*for (int i = 0; i < noeudTable->obtenirNombreEnfants(); i++)
	{
		if (noeudTable->chercher(i)->estSelectionne())
		{
			noeudTable->chercher(i)->accepter(this);
		}
	}*/
}

void VisiteurDeplacement::visiter(NoeudBut * noeudBut)
{

}

