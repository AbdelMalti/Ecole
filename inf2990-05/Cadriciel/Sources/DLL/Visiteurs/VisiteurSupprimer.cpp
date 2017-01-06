#include "VisiteurSupprimer.h"
#include "NoeudComposite.h"
#include "NoeudAbstrait.h"
#include "NoeudBonus.h"
#include "NoeudMaillet.h"
#include "NoeudMailletOrdi.h"
#include "NoeudPortail.h"
#include "NoeudMuret.h"
#include "NoeudRondelle.h"
#include "NoeudTable.h"


void VisiteurSupprimer::visiter(NoeudComposite* noeudComposite)
{
	/*if (noeudComposite->estSelectionne())
	{
		noeudComposite->effacerSelection();
	}*/
}

void VisiteurSupprimer::visiter(NoeudAbstrait* noeudAbstrait)
{
	/*if (noeudAbstrait->estSelectionne())
	{
		noeudAbstrait->obtenirParent()->effacerSelection();
	}*/
}

void VisiteurSupprimer::visiter(NoeudBonus* noeudBonus)
{
	//if (noeudBonus->estSelectionne())
	//{
		noeudBonus->obtenirParent()->effacerSelection();
	//}
}

void VisiteurSupprimer::visiter(NoeudMaillet* noeudMaillet)
{
	//if (noeudMaillet->estSelectionne())
	//{
		noeudMaillet->obtenirParent()->effacerSelection();
	//}
}


void VisiteurSupprimer::visiter(NoeudMailletOrdi* noeudMailletOrdi)
{
	//if (noeudMailletOrdi->estSelectionne())
	//{
	noeudMailletOrdi->obtenirParent()->effacerSelection();
	//}
}




void VisiteurSupprimer::visiter(NoeudPortail* noeudPortail)
{
	//if (noeudPortail->estSelectionne())
	//{
		noeudPortail->obtenirParent()->effacerSelection();
	//}
}

void VisiteurSupprimer::visiter(NoeudMuret* noeudMuret)
{
	//if (noeudMuret->estSelectionne())
	//{
		noeudMuret->obtenirParent()->effacerSelection();
	//}
}

void VisiteurSupprimer::visiter(NoeudRondelle* noeudRondelle)
{
	//if (noeudRondelle->estSelectionne())
	//{
		noeudRondelle->obtenirParent()->effacerSelection();
	//}
}

void VisiteurSupprimer::visiter(NoeudBut* noeudBut)
{
	/*if (noeudBut->estSelectionne())
	{
		noeudBut->obtenirParent()->effacerSelection();
	}*/
}

void VisiteurSupprimer::visiter(NoeudTable* noeudTable)
{
	/*if (noeudTable->estSelectionne())
	{
		noeudTable->effacerSelection();
	}*/
}