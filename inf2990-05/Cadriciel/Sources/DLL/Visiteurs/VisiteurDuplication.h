#pragma once
#include "VisiteurAbstrait.h"
#include <vector>

using namespace std;

class VisiteurDuplication : public VisiteurAbstrait
{
public:

	//Constructeur
	VisiteurDuplication();

	//Destructeur
	~VisiteurDuplication();

	void visiter(NoeudComposite* noeudComposite);
	void visiter(NoeudBonus* noeudBonus);
	void visiter(NoeudMaillet* noeudMaillet);
	void visiter(NoeudMailletOrdi* noeudMailletOrdi);
	void visiter(NoeudPortail* noeudPortail);
	void visiter(NoeudMuret* noeudMuret);
	void visiter(NoeudRondelle* noeudRondelle);
	void visiter(NoeudTable* noeudTable);
	void visiter(NoeudBut* noeudBut);

	void deplacementDeEtampe(double x, double y);
	void effacerEtampe();
	bool estPossibleDeDupliquer(double x, double y);
	void initialisation(double centre_X, double centreY);//, NoeudComposite* noeudComposite

private:
	double centre_[2];
	NoeudComposite* noeudComposite_;
	vector<NoeudAbstrait*> noeudEtampe_;

};