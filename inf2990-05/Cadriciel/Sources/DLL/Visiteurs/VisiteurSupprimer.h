#pragma once
#include "VisiteurAbstrait.h"

class VisiteurSupprimer : public VisiteurAbstrait
{
public:

	//Constructeur
	VisiteurSupprimer() {};

	//Destructeur
	~VisiteurSupprimer() {};

	void visiter(NoeudComposite* noeudComposite);
	void visiter(NoeudAbstrait* noeudAbstrait);
	void visiter(NoeudBonus* noeudBonus);
	void visiter(NoeudMaillet* noeudMaillet);
	void visiter(NoeudMailletOrdi* noeudMailletOrdi);
	void visiter(NoeudPortail* noeudPortail);
	void visiter(NoeudMuret* noeudMuret);
	void visiter(NoeudRondelle* noeudRondelle);
	void visiter(NoeudBut* noeudBut);
	void visiter(NoeudTable* noeudTable);
};