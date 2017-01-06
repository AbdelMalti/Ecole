#pragma once

class NoeudAbstrait;
class NoeudComposite;
class NoeudBonus;
class NoeudBut;
class NoeudMaillet;
class NoeudMailletOrdi;
class NoeudMuret;
class NoeudPortail;
class NoeudRondelle;
class NoeudTable;

class VisiteurAbstrait
{

public: 

	//constructeur
	VisiteurAbstrait() {};

	//destructeur
	~VisiteurAbstrait() {};

	virtual void visiter(NoeudComposite* noeudComposite)=0;
	virtual void visiter(NoeudBonus* noeudBonus) = 0;
	virtual void visiter(NoeudMaillet* noeudMaillet) = 0;
	virtual void visiter(NoeudMailletOrdi* noeudMailletOrdi) = 0;
	virtual void visiter(NoeudPortail* noeudPortail) = 0;
	virtual void visiter(NoeudMuret* noeudMuret) = 0;
	virtual void visiter(NoeudRondelle* noeudRondelle) = 0;
	virtual void visiter(NoeudTable* noeudTable) = 0;
	virtual void visiter(NoeudBut* noeudBut) = 0;

};