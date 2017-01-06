///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.cpp
/// @author Jackie Phung
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPortail.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>

#include"FacadeModele.h"

int NoeudAbstrait::compteurP_ = 0;
int NoeudPortail::compteurS_ = 0;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::NoeudPortail(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::NoeudPortail(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	acceleration_ = 0;
	coefficientFriction_ = 0;
	coefficientRebond_ = 0;

	rayon_ =0.5;
	angleRotation_ = 0;
	NoeudAbstrait::compteurP_++;
	couleurPo_[0] = 0;
	couleurPo_[1] = 0;
	couleurPo_[2] = 255 ;
	coulSel_[1] = 0;

	setCouleur();
}

NoeudPortail::NoeudPortail(NoeudPortail * portailCopier) : NoeudAbstrait{ portailCopier->type_ } 
{
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::~NoeudPortail()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::~NoeudPortail()
{
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @param[in] estColore : Permet de savoir selection par couleur est active pour l'objet
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudPortail::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
	glPushMatrix();

	auto modele = glm::translate(transformationRelative_, glm::vec3(centreDeRotation_));
	modele = glm::rotate(modele, (float)angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::scale(modele, glm::vec3(rayon_, rayon_, rayon_));

	GLubyte couleurNoeud[3];
	couleurNoeud[0] = couleurPo_[0];
	couleurNoeud[1] = couleurPo_[1];
	couleurNoeud[2] = couleurPo_[2];

	GLubyte couleurSelection[3]; 
	couleurSelection[0] = coulSel_[0];
	couleurSelection[1] = coulSel_[1];
	couleurSelection[2] = coulSel_[2];

	// Affichage du modèle
	vbo_->dessiner(estColore, estSelectionne(), couleurNoeud, couleurSelection, vueProjection * modele);
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::animer(float temps)
{
	angleRotation_ = fmod(angleRotation_ + temps/2.0f * 2 * (float)utilitaire::PI, 2 * (float)utilitaire::PI);

	if(FacadeModele::obtenirInstance()->collisionPortail())  
		FacadeModele::obtenirInstance()->sonRondelePortail();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::accepter(VisiteurAbstrait &visiteur)
///
/// Cette fonction va permettre au noeud d'accepter un visiteur
///
/// @param[in] visiteur : visiteur qui visite le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::accepter(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}


///
void NoeudPortail::setRayonPortail(double rayon)
{
	rayon_ = rayon;
}
double NoeudPortail::getRayonPortail()
{
	return rayon_;
}
double NoeudPortail::getAngleRotation()
{
	return angleRotation_;
}
void NoeudPortail::setAngleRotation(double angleRotation)
{
	angleRotation_ = angleRotation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::testerSelection(GLubyte ObjetColore[])
///
/// Permet de vérifier la selection
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPortail::testerSelection(GLubyte ObjetColore[])
{
	bool isClic = false;
	if (ObjetColore[0] == coulSel_[0] && ObjetColore[1] == coulSel_[1] && ObjetColore[2] == coulSel_[2])
		isClic = true;

	else if (ObjetColore[0] == couleurPo_[0] && ObjetColore[1] == couleurPo_[1] && ObjetColore[2] == couleurPo_[2])
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
/// @fn NoeudPortail::setCouleur()
///
/// Permet de définir des couleurs au objets pour la sélection par couleur
///
/// @return booléen.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::setCouleur()
{
	if (NoeudAbstrait::compteurP_ < 60)
	{
		couleurPo_[0] = NoeudPortail::compteurS_;
		couleurPo_[1] = 0;
		couleurPo_[2] = 255 - NoeudAbstrait::compteurP_ + 1;
	}
	else
	{
		NoeudAbstrait::compteurP_ = 1;
		NoeudPortail::compteurS_++;
		couleurPo_[0] = NoeudPortail::compteurS_;
		couleurPo_[1] = 0;
		couleurPo_[2] = 255;
	}
}

void NoeudPortail::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	boitePortail_ = utilitaire::calculerCylindreEnglobant(*modele_);
}

utilitaire::CylindreEnglobant NoeudPortail::getBoiteEnglobante()
{
	return boitePortail_;
}

/////////////////////////////////////////////////////////////////////////////////
///// @}
/////////////////////////////////////////////////////////////////////////////////
