#pragma once
#ifndef	VISITEURSELECTION_H
#define VISITEURSELECTION_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudAbstrait.h"
//#include <vector>
#include "../Arbre/Noeuds/NoeudTypes.h" 

using namespace std;

class VisiteurSelection : public VisiteurAbstrait
{

public:

	///constructeur
	VisiteurSelection(glm::dvec3 & point, bool EstUneSelectionPourUnObjet, GLubyte couleur[], const bool& estInitialiser);
	
	///destructeur
	~VisiteurSelection();

	///visite noeudCompsite
	virtual void visiter(NoeudComposite *noeudCompsite);
	///visite noeudBonus
	virtual void visiter(NoeudBonus* noeudBonus);
	///visite noeudBut
	virtual void visiter(NoeudBut *noeudBut);
	///visite noeudMaillet
	virtual void visiter(NoeudMaillet *noeudMaillet);
	///visite noeudMailletOrdi
	virtual void visiter(NoeudMailletOrdi *noeudMailletOrdi);
	///visite NoeudPortail
	virtual void visiter(NoeudPortail *noeudPortail);
	///visite noeudMuret
	virtual void visiter(NoeudMuret *noeudMuret);
	///visite noeudRondelle
	virtual void visiter(NoeudRondelle *noeudRondelle);

	virtual void visiter(NoeudTable *noeudTable);

	///Retourne gardeSelection_
	bool obtenirGardeSelection() {
		return gardeSelection_;
	};

private:

	///Point selectionne.
	glm::dvec3 point_;
	///couleur du noeud selectionne
	GLubyte couleur_[3];
	/// vérifie l'initialisation d'un visiteur
	bool estInitialiser_;
	///Booleen representant une selection
	bool EstUneSelectionPourUnObjet_;
	///Booleen pour vérification de l'existante d'une selection 
	bool gardeSelection_;
};
#endif