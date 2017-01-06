///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBonus.cpp
/// @author Jackie Phung
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBonus.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>
#include "FacadeModele.h"

int NoeudBonus::compteur_ = 0;
int NoeudAbstrait::compteurB_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonus::NoeudBonus(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonus::NoeudBonus(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	acceleration_ = 2;
	coefficientFriction_ = 0;
	coefficientRebond_ = 0;

	rayon_ = 1.2;
	angleRotation_ = 0;
	NoeudAbstrait::compteurB_++;
	couleurBonusAcc_[0] = 0; 
	couleurBonusAcc_[1] = 100;
	couleurBonusAcc_[2] = 255 - NoeudAbstrait::compteurB_ + 1;
	coulSel_[1] = 0;

	setCouleur();
}

NoeudBonus::NoeudBonus(NoeudBonus * bonusCopier)
	: NoeudAbstrait{ bonusCopier->type_ }
{
	rayon_ = bonusCopier->rayon_;
	angleRotation_ = bonusCopier->angleRotation_;
	NoeudAbstrait::compteurB_++;
	couleurBonusAcc_[0] = bonusCopier->couleurBonusAcc_[0];
	couleurBonusAcc_[1] = bonusCopier->couleurBonusAcc_[1];
	couleurBonusAcc_[2] = 255 - NoeudAbstrait::compteurB_ + 1;
	coulSel_[1] = bonusCopier->coulSel_[1];

	setCouleur();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonus::~NoeudBonus()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonus::~NoeudBonus()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAraignee::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonus::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
	auto modele = glm::translate(transformationRelative_, glm::vec3(centreDeRotation_));
	modele = glm::rotate(modele, (float)angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::scale(modele, glm::vec3(rayon_, rayon_, rayon_));

	GLubyte couleurNoeud[3];
	couleurNoeud[0] = couleurBonusAcc_[0];
	couleurNoeud[1] = couleurBonusAcc_[1];
	couleurNoeud[2] = couleurBonusAcc_[2];

	GLubyte couleurSelection[3];
	couleurSelection[0] = coulSel_[0];
	couleurSelection[1] = coulSel_[1];
	couleurSelection[2] = coulSel_[2];

	// Affichage du modèle.
	vbo_->dessiner(estColore, 
		estSelectionne(), 
		couleurNoeud, 
		couleurSelection, 
		vueProjection * modele);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonus::testerSelection(GLubyte ObjetColore[])
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return booléen.
///
////////////////////////////////////////////////////////////////////////
bool NoeudBonus::testerSelection(GLubyte ObjetColore[])
{
	bool isClic = false;
	
	if (ObjetColore[0] == coulSel_[0] && ObjetColore[1] == coulSel_[1] && ObjetColore[2] == coulSel_[2])
		isClic = true;

	else if (ObjetColore[0] == couleurBonusAcc_[0] && ObjetColore[1] == couleurBonusAcc_[1] && ObjetColore[2] == couleurBonusAcc_[2])
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

//////////////////////////////////////////////////////////////////////////
/////
///// @fn void NoeudCube::animer(float temps)
/////
///// Cette fonction effectue l'animation du noeud pour un certain
///// intervalle de temps.
/////
///// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void NoeudBonus::animer(float temps)
{
	angleRotation_ = fmod(angleRotation_ + temps * 2 * (float)utilitaire::PI, 2 * (float)utilitaire::PI);

	if( FacadeModele::obtenirInstance()->collisionBonus()) { FacadeModele::obtenirInstance()->sonRondeleBonus(); }

}

//////////////////////////////////////////////////////////////////////////
/////
///// @fn void NoeudBonus::accepter(VisiteurAbstrait* visiteur)
/////
///// Cette fonction va permettre au noeud d'accepter un visiteur
/////
///// @param[in] visiteur : visiteur qui visite le noeud
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void NoeudBonus::accepter(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

void NoeudBonus::setRayonBonus(double rayon)
{
	rayon_ = rayon;
}

double NoeudBonus::getRayonBonus()
{
	return rayon_;
}
double NoeudBonus::getAngleRotation()
{
	return angleRotation_;
}
void NoeudBonus::setAngleRotation(double angle)
{
	angleRotation_ = angle;
}

GLubyte NoeudBonus::getCouleur1()
{
	return couleurBonusAcc_[0];
}

GLubyte NoeudBonus::getCouleur2()
{
	return couleurBonusAcc_[1];
}

GLubyte NoeudBonus::getCouleur3()
{
	return couleurBonusAcc_[2];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonus::setCouleur()
///
/// Permet de définir des couleurs au objets pour la sélection par couleur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonus::setCouleur()
{
	if (NoeudAbstrait::compteurB_ < 100)
	{
		couleurBonusAcc_[0] = 0;
		couleurBonusAcc_[1] = 100 + NoeudBonus::compteur_;
		couleurBonusAcc_[2] = 255 - NoeudAbstrait::compteurB_ + 1;
	}
	else
	{
		NoeudAbstrait::compteurB_ = 1;
		NoeudBonus::compteur_++;
		couleurBonusAcc_[0] = NoeudBonus::compteur_;
		couleurBonusAcc_[1] = 0;
		couleurBonusAcc_[2] = 255;
	}
}

void NoeudBonus::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	boiteBonus_ = utilitaire::calculerCylindreEnglobant(*modele_);
}

utilitaire::CylindreEnglobant NoeudBonus::getBoiteEnglobante()
{
	return boiteBonus_;
}

/////////////////////////////////////////////////////////////////////////////////
///// @}
/////////////////////////////////////////////////////////////////////////////////
