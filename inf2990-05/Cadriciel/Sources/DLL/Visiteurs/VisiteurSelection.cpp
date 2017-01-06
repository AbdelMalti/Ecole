#include "VisiteurSelection.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////////////////////////////
///
/// VisiteurSelection::VisiteurSelection(glm::dvec3 & point, bool EstUneSelectionPourUnObjet, 
///			GLubyte couleur[], const bool& estInitialiser)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] point : Le point � selectionner
/// 
/// @param[in] EstUneSelectionPourUnObjet : r�cup�re si un noeud s�lectionnable est s�lectionn�
/// 
/// @param[in] couleur : r�cup�re la couleur du noeud s�lectionn�
/// 
/// @param[in] estInitialiser : bool�en qui dit si l'initialisation de la s�lection est faite
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
/// Destructeur qui d�truit le visiteur.
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
/// Cette fonction va permettre au noeud d'�tre visit�
///
/// @param[in] noeudBonus : le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudBonus* noeudBonus)
{
	/// Si le noeud est s�lectionnable et s�lectionn�
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
/// Cette methode permet de selectionne � un objet de la classe NoeudMuret.
///
/// @param[in] noeudBut : le noeud � visiter
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
/// Cette methode permet de selectionne � un objet de la classe NoeudMuret.
///
/// @param[in] noeudPortail : le noeud � visiter
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
/// Cette methode permet de selectionne � un objet de la classe NoeudMuret.
///
/// @param[in] noeudPortail : le noeud � visiter
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
/// Cette methode permet de selectionne � un objet de la classe NoeudPortail.
///
/// @param[in] noeudPortail : le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudPortail* noeudPortail)
{
	/// si le noeud est s�lectionnable et s�lectionn�
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
/// Cette methode permet de selectionne � un objet de la classe NoeudMuret.
///
/// @param[in] noeudPortail : le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudMuret *noeudMuret)
{
	/// si le noeud est s�lectionnable et s�lectionn�
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
/// Cette methode permet de selectionne � un objet de la classe NoeudMuret.
///
/// @param[in] noeudRondelle : le noeud � visiter
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
/// Cette methode permet de selectionne � un objet de la classe NoeudMuret.
///
/// @param[in] noeudTable : le noeud � visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudTable * noeudTable)
{
}
