#include "VisiteurMiseEchelle.h"
#include "NoeudComposite.h"
#include "NoeudAbstrait.h"
#include "NoeudBonus.h"
#include "NoeudMaillet.h"
#include "NoeudMailletOrdi.h"
#include "NoeudPortail.h"
#include "NoeudMuret.h"
#include "NoeudRondelle.h"
#include "NoeudTable.h"
#include <iostream>
VisiteurMiseEchelle::VisiteurMiseEchelle(double deltaFacteur)
{
	 deltaFacteur_ = deltaFacteur;
}

void VisiteurMiseEchelle::visiter(NoeudAbstrait* noeud)
{

}

void VisiteurMiseEchelle::visiter(NoeudComposite* noeud)
{

}

void VisiteurMiseEchelle::visiter(NoeudTable* noeud)
{

}


void VisiteurMiseEchelle::visiter(NoeudBonus* noeud)
{
	/*if ((deltaFacteur_ > 1) && !noeud.estSelectionne())
	{
		return;
	}

	double facteurInit = noeud.getFacteur();

	if (facteurInit >= 0.40)
	{
		noeud.setFacteur(facteurInit*deltaFacteur_);
	}
	else
		noeud.setFacteur(0.40);

	if (!noeud.estDansLaZoneDeJeu())
	{
		noeud.setFacteur(facteurInit);
	}*/

	noeud->setRayonBonus(deltaFacteur_ * noeud->getRayonBonus());

	//noeud->setRayonBonus(5);

	//std::cout << deltaFacteur_ << std::endl;

}

void VisiteurMiseEchelle::visiter(NoeudMaillet* noeud)
{
	noeud->setRayonMaillet(deltaFacteur_ * noeud->getRayonMaillet());
}

void VisiteurMiseEchelle::visiter(NoeudMailletOrdi* noeud)
{
	noeud->setRayonMaillet(deltaFacteur_ * noeud->getRayonMaillet());
}

void VisiteurMiseEchelle::visiter(NoeudMuret* noeud)
{
	noeud->setLongueurMuret(deltaFacteur_ * noeud->getLongueurMuret());
}

void VisiteurMiseEchelle::visiter(NoeudRondelle* noeud)
{
	noeud->setRayonRondelle(deltaFacteur_ * noeud->getRayonRondelle());
}
void VisiteurMiseEchelle::visiter(NoeudPortail* noeud)
{
	noeud->setRayonPortail(deltaFacteur_ * noeud->getRayonPortail());
}
void VisiteurMiseEchelle::visiter(NoeudBut* noeud)
{

}
void VisiteurMiseEchelle::setFacteur(double facteur)
{
	deltaFacteur_ = facteur;
}

double VisiteurMiseEchelle::getFacteur()
{
	return deltaFacteur_;
}


