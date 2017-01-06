///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMuret.cpp
/// @author Jackie Phung
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMuret.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>
#include "FacadeModele.h"

int NoeudMuret::compteurM_ = 0;
int NoeudAbstrait::compteurMa_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMuret::NoeudMuret(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMuret::NoeudMuret(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	coefficientRebond_ = 5; //A VOIR AVEC LE RESTE DE L'EQUIPE
	coefficientFriction_ = 0;
	acceleration_ = 0;

	longueur_ = 1.2;
	largueur_ = 0.4;
	profondeur_ = 0;
	angleRotation_ = 0;
	NoeudAbstrait::compteurMa_++;
	couleur_[0] = 0;
	couleur_[1] = 255 - NoeudAbstrait::compteurMa_ + 1;
	couleur_[2] = 0;
	coulSel_[1] = 0;
}

NoeudMuret::NoeudMuret(NoeudMuret * muretCopier)
	: NoeudAbstrait{ muretCopier->type_ }
{
	coefficientRebond_ = muretCopier->coefficientRebond_;

	coefficientFriction_ = 0;
	acceleration_ = 0;

	longueur_ = muretCopier->longueur_;
	largueur_ = muretCopier->largueur_;
	profondeur_ = muretCopier->largueur_;
	angleRotation_ = muretCopier->angleRotation_;

	NoeudAbstrait::compteurMa_++;
	couleur_[0] = muretCopier->couleur_[0];
	couleur_[1] = 255 - NoeudAbstrait::compteurMa_ + 1; //A revoir avec equipe!
	couleur_[2] = muretCopier->couleur_[2];

	coulSel_[1] = muretCopier->coulSel_[1];
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMuret::~NoeudMuret()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMuret::~NoeudMuret()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMuret::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMuret::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
	auto modele = glm::translate(transformationRelative_, glm::vec3(centreDeRotation_)); //0, 0, 0	
	modele = glm::rotate(modele, (float)angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::scale(modele, glm::vec3(largueur_, longueur_, largueur_));

	GLubyte couleurNoeud[3];
	couleurNoeud[0] = couleur_[0];
	couleurNoeud[1] = couleur_[1];
	couleurNoeud[2] = couleur_[2];

	GLubyte couleurSelection[3];
	couleurSelection[0] = coulSel_[0];
	couleurSelection[1] = coulSel_[1];
	couleurSelection[2] = coulSel_[2];

	// Affichage du modèle.
	vbo_->dessiner(estColore, estSelectionne(), couleurNoeud, couleurSelection, vueProjection * modele);
}


//////////////////////////////////////////////////////////////////////////
/////
///// @fn void NoeudMuret::animer(float temps)
/////
///// Cette fonction effectue l'animation du noeud pour un certain
///// intervalle de temps.
/////
///// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void NoeudMuret::animer(float temps)
{
	if (FacadeModele::obtenirInstance()->collisionMuret())
		FacadeModele::obtenirInstance()->sonRondeleMuret();
}

//////////////////////////////////////////////////////////////////////////
/////
///// @fn void NoeudMuret::accepter(VisiteurAbstrait* visiteur)
/////
///// Cette fonction va permettre au noeud d'accepter un visiteur
/////
///// @param[in] visiteur : visiteur qui visite le noeud
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void NoeudMuret::accepter(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}


void NoeudMuret::setLongueurMuret(double longueur)
{
	longueur_ = longueur;
}
double NoeudMuret::getLongueurMuret()
{
	return longueur_;
}
double NoeudMuret::getAngleRotation()
{
	return angleRotation_;
}
void NoeudMuret::setAngleRotation(double angle)
{
	angleRotation_ = angle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMuret::testerSelection(GLubyte ObjetColore[])
///
/// Permet de vérifier la selection
///
/// @return booléen.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMuret::testerSelection(GLubyte ObjetColore[])
{
	bool isClic = false;
	if (ObjetColore[0] == coulSel_[0] && ObjetColore[1] == coulSel_[1] && ObjetColore[2] == coulSel_[2])
		isClic = true;

	else if (ObjetColore[0] == couleur_[0] && ObjetColore[1] == couleur_[1] && ObjetColore[2] == couleur_[2])
	{
		isClic = true;
		if (coulSel_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			setCouleurSel();
		}
	}
	return isClic;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMuret::setCouleur()
///
/// Permet de définir des couleurs au objets pour la sélection par couleur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMuret::setCouleur()
{
	if (NoeudAbstrait::compteurMa_ < 60)
	{
		couleur_[0] = NoeudMuret::compteurM_;
		couleur_[1] = 255 - NoeudAbstrait::compteurMa_ + 1;
		couleur_[2] = 0;
	}
	else
	{
		NoeudAbstrait::compteurMa_ = 1;
		NoeudMuret::compteurM_++;
		couleur_[0] = 255;
		couleur_[1] = 0;
		couleur_[2] = NoeudMuret::compteurM_;
	}
}

void NoeudMuret::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	boiteMuret_ = utilitaire::calculerBoiteEnglobante(*modele_);
}

utilitaire::BoiteEnglobante NoeudMuret::getBoiteEnglobante()
{
	return boiteMuret_;
}

/////////////////////////////////////////////////////////////////////////////////
///// @}
/////////////////////////////////////////////////////////////////////////////////
