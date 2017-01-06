#pragma once
#include "VisiteurAbstrait.h"

class VisiteurDeplacement : public VisiteurAbstrait
{
public:

	//Constructeur
	VisiteurDeplacement();

	//Destructeur
	~VisiteurDeplacement();

	//M�thode de modification
	void setX(double X);
	void setY(double Y);
	void setZ(double Z);

	//M�thode d'acc�s
	double getX() const;
	double getY() const;
	double getZ() const;

	void visiter(NoeudComposite* noeudComposite);
	void visiter(NoeudBonus* noeudBonus);
	void visiter(NoeudMaillet* noeudMaillet);
	void visiter(NoeudMailletOrdi* noeudMailletOrdi);
	void visiter(NoeudPortail* noeudPortail);
	void visiter(NoeudMuret* noeudMuret);
	void visiter(NoeudRondelle* noeudRondelle);
	void visiter(NoeudTable* noeudTable);
	void visiter(NoeudBut* noeudBut);

private:

	double X_;
	double Y_;
	double Z_;
};