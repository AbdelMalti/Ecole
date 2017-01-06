#pragma once
#ifndef __VISITEUR_Mise_Echelle_H__
#define __VISITEUR_Mise_Echelle_H__

#include "VisiteurAbstrait.h"

class VisiteurMiseEchelle : public VisiteurAbstrait
{
public:
	VisiteurMiseEchelle(double deltaFacteur = 1.0); //: deltaFacteur_(deltaFacteur);
	~VisiteurMiseEchelle() {};

	virtual void visiter(NoeudAbstrait* noeud);

	virtual void visiter(NoeudComposite* noeud);

	virtual void visiter(NoeudTable* noeud);

	virtual void visiter(NoeudMuret* noeud);

	virtual void visiter(NoeudRondelle* noeud);

	virtual void visiter(NoeudBonus* noeud);

	virtual void visiter(NoeudBut* noeud);

	virtual void visiter(NoeudPortail* noeud);

	virtual void visiter(NoeudMaillet* noeud);

	virtual void visiter(NoeudMailletOrdi* noeud);

	 void setFacteur(double facteur);
	 double getFacteur();

private:
	double deltaFacteur_;
};

#endif

