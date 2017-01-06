#include "VisiteurSelection.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////////////////////////////
///
/// VisiteurSelection::VisiteurSelection(glm::dvec3 & point, bool EstUneSelectionPourUnObjet, 
///			GLubyte couleur[], const bool& estInitialiser)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] point : Le point à selectionner
/// 
/// @param[in] EstUneSelectionPourUnObjet : récupère si un noeud sélectionnable est sélectionné
/// 
/// @param[in] couleur : récupère la couleur du noeud sélectionné
/// 
/// @param[in] estInitialiser : booléen qui dit si l'initialisation de la sélection est faite
///
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////////////////////////////
VisiteurSelection::VisiteurSelection(glm::dvec3 & point, bool EstUneSelectionPourUnObjet, GLubyte couleur[], const bool& estInitialiser)
{
	point_ = point;
	EstUneSelectionPourUnObjet_ = EstUneSelectionPourUnObjet;
	gardeSelection_ = false;
	for (unsigned int i = 0; i < 3; i++)
		couleur_[i] = couleur[i];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::~VisiteurSelection()
///
/// Destructeur qui détruit le visiteur.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::~VisiteurSelection()
{
}

void VisiteurSelection::visiter(NoeudComposite * noeudCompsite)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::visiter(NoeudBonus* noeudBonus)
///
/// Cette fonction va permettre au noeud d'être visité
///
/// @param[in] noeudBonus : le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudBonus* noeudBonus)
{
	/// Si le noeud est sélectionnable et sélectionné
	if (noeudBonus->estSelectionnable() && noeudBonus->testerSelection(couleur_))
	{
		if (EstUneSelectionPourUnObjet_)
		{
			noeudBonus->obtenirParent()->deselectionnerTout();
			noeudBonus->assignerSelection(true );
			gardeSelection_ = true;
		}
		else
			noeudBonus->obtenirParent()->selectionnerTout();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelection::visiter(NoeudBut * noeudBut)
///
/// Cette methode permet de selectionne à un objet de la classe NoeudMuret.
///
/// @param[in] noeudBut : le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudBut * noeudBut)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelection::visiter(NoeudMuret *noeudMuret)
///
/// Cette methode permet de selectionne à un objet de la classe NoeudMuret.
///
/// @param[in] noeudPortail : le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudMaillet * noeudMaillet)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelection::visiter(NoeudMuret *noeudMuret)
///
/// Cette methode permet de selectionne à un objet de la classe NoeudMuret.
///
/// @param[in] noeudPortail : le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudMailletOrdi * noeudMailletOrdi)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelection::visiter(NoeudPortail &noeudPortail)
///
/// Cette methode permet de selectionne à un objet de la classe NoeudPortail.
///
/// @param[in] noeudPortail : le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudPortail* noeudPortail)
{
	/// si le noeud est sélectionnable et sélectionné
	if (noeudPortail->estSelectionnable() && noeudPortail->testerSelection(couleur_))
	{
		if (EstUneSelectionPourUnObjet_)
		{
			noeudPortail->obtenirParent()->deselectionnerTout();
			noeudPortail->assignerSelection(true);
			gardeSelection_ = true;
		}
		else
			noeudPortail->obtenirParent()->selectionnerTout();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelection::visiter(NoeudMuret *noeudMuret)
///
/// Cette methode permet de selectionne à un objet de la classe NoeudMuret.
///
/// @param[in] noeudPortail : le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudMuret *noeudMuret)
{
	/// si le noeud est sélectionnable et sélectionné
	if (noeudMuret->estSelectionnable() && noeudMuret->testerSelection(couleur_)) 
	{
		if (EstUneSelectionPourUnObjet_)
		{
			noeudMuret->obtenirParent()->deselectionnerTout();
			noeudMuret->assignerSelection(true);
			gardeSelection_ = true;
		}
		else
			noeudMuret->inverserSelection();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelection::visiter(NoeudRondelle * noeudRondelle)
///
/// Cette methode permet de selectionne à un objet de la classe NoeudMuret.
///
/// @param[in] noeudRondelle : le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudRondelle * noeudRondelle)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelection::visiter(NoeudTable * noeudTable)
///
/// Cette methode permet de selectionne à un objet de la classe NoeudMuret.
///
/// @param[in] noeudTable : le noeud à visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudTable * noeudTable)
{
}
