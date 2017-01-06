#include "VisiteurDuplication.h"
#include "NoeudComposite.h"
#include "NoeudAbstrait.h"
#include "NoeudBonus.h"
#include "NoeudMaillet.h"
#include "NoeudMailletOrdi.h"
#include "NoeudPortail.h"
#include "NoeudMuret.h"
#include "NoeudRondelle.h"
#include "NoeudTable.h"
#include "FacadeModele.h"

#include <iostream>

VisiteurDuplication::VisiteurDuplication():VisiteurAbstrait()
{

}

VisiteurDuplication::~VisiteurDuplication()
{

}

void VisiteurDuplication::visiter(NoeudComposite* noeudComposite)
{
	for (int i = 0; i < noeudComposite->obtenirNombreEnfants(); i++)
	{
		if (noeudComposite->chercher(i)->estSelectionne())
		{
			noeudComposite->chercher(i)->accepter(this);
		}
	}
}

void VisiteurDuplication::visiter(NoeudBonus* noeudBonus)
{
	NoeudBonus* nouveauNoeudBonus = new NoeudBonus(noeudBonus->obtenirType()); //  A verifier
	noeudBonus->obtenirParent()->ajouter(nouveauNoeudBonus);
	noeudEtampe_.push_back(nouveauNoeudBonus);
}

void VisiteurDuplication::visiter(NoeudMaillet* noeudMaillet)
{
	NoeudMaillet* nouveauNoeudMaillet = new NoeudMaillet(noeudMaillet->obtenirType());
	noeudMaillet->obtenirParent()->ajouter(nouveauNoeudMaillet);
	noeudEtampe_.push_back(nouveauNoeudMaillet);
}


void VisiteurDuplication::visiter(NoeudMailletOrdi* noeudMailletOrdi)
{
	NoeudMailletOrdi* nouveauNoeudMaillet = new NoeudMailletOrdi(noeudMailletOrdi->obtenirType());
	noeudMailletOrdi->obtenirParent()->ajouter(nouveauNoeudMaillet);
	noeudEtampe_.push_back(nouveauNoeudMaillet);
}



void VisiteurDuplication::visiter(NoeudPortail* noeudPortail)
{
	NoeudPortail* nouveauNoeudPortail = new NoeudPortail(noeudPortail->obtenirType());
	noeudPortail->obtenirParent()->ajouter(nouveauNoeudPortail);
	noeudEtampe_.push_back(nouveauNoeudPortail);
}

void VisiteurDuplication::visiter(NoeudMuret* noeudMuret)
{
	NoeudMuret* nouveauNoeudMuret = new NoeudMuret(noeudMuret->obtenirType());
	noeudMuret->obtenirParent()->ajouter(nouveauNoeudMuret);
	noeudEtampe_.push_back(nouveauNoeudMuret);
}

void VisiteurDuplication::visiter(NoeudRondelle* noeudRondelle)
{
	NoeudRondelle* nouveauNoeudRondelle = new NoeudRondelle(noeudRondelle->obtenirType());
	noeudRondelle->obtenirParent()->ajouter(nouveauNoeudRondelle);
	noeudEtampe_.push_back(nouveauNoeudRondelle);
}

void VisiteurDuplication::visiter(NoeudTable* noeudTable)
{
	/*for (int i = 0; i < noeudTable.obtenirNombreEnfants(); i++)
	{
		if (noeudTable.chercher(i)->estSelectionne())
		{
			noeudTable.chercher(i)->accepter(*this);
		}
	}*/
}

void VisiteurDuplication::visiter(NoeudBut * noeudBut)
{

}

void VisiteurDuplication::deplacementDeEtampe(double x, double y)
{
	glm::vec3 pos;

	for (int i = 0; i < noeudEtampe_.size(); i++)
	{
		pos = noeudEtampe_[i]->obtenirPositionRelative();
		pos[0] += x - centre_[0];
		pos[1] += y - centre_[1];
		noeudEtampe_[i]->assignerPositionRelative(pos);
	}

	centre_[0] = x;
	centre_[1] = y;
}

void VisiteurDuplication::effacerEtampe()
{
	/*for (int i = 0; i < noeudEtampe_.size(); i++)
	{
		noeudComposite_->effacer(noeudEtampe_[i]);
	}*/
	noeudEtampe_.clear();
}

bool VisiteurDuplication::estPossibleDeDupliquer(double x, double y)
{
	//glm::vec3 posInit;
	//glm::vec3 pos;

	//for (int i = 0; i < noeudEtampe_.size(); i++)
	//{
	//	pos = noeudEtampe_[i]->obtenirPositionRelative();
	//	posInit = pos;
	//	pos[0] += x - centre_[0];
	//	pos[1] += y - centre_[1];
	//	noeudEtampe_[i]->assignerPositionRelative(pos);
	//	//bool estdansJeu = FacadeModele::estDansZoneDeJeu(noeudEtampe_[i]->obtenirPositionRelative());
	//	if (noeudEtampe_[i]->estDansZoneDeJeu())
	//	{
	//		noeudEtampe_[i]->assignerPositionRelative(posInit);
	//	}
	//	else
	//	{
	//		noeudEtampe_[i]->assignerPositionRelative(posInit);
	//		return false;
	//	}
	//}

	return true;

}

void VisiteurDuplication::initialisation(double centre_X, double centre_Y) //, NoeudComposite* noeudComposite
{
	centre_[0] = centre_X;
	centre_[1] = centre_Y;
	//noeudComposite_ = noeudComposite;
	noeudEtampe_.clear();
	//noeudComposite_->accepter(this);

}