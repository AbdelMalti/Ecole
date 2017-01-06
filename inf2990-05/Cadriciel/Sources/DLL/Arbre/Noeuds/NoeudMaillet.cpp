///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMaillet.cpp
/// @author Equipe 05
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMaillet.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>
#include "FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::NoeudMaillet(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMaillet::NoeudMaillet(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	rayon_ = 0.6;
	couleur_[0] = 255;
	couleur_[1] = 0;
	couleur_[2] = 0;
	vitesseInitial_ = 2;
}

NoeudMaillet::NoeudMaillet(const std::string & typeNoeud, double rayon, double angle)
{
	rayon_ = rayon;
	angleRotation_ = angle;
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
NoeudMaillet::~NoeudMaillet()
{
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMaillet::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudMaillet::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
	glPushMatrix();
	
	auto modele = glm::translate(transformationRelative_, glm::vec3(0, 0, 1));
	modele = glm::scale(modele, glm::vec3(rayon_, rayon_, rayon_));

	GLubyte couleurNoeud[3];
	couleurNoeud[0] = couleur_[0];
	couleurNoeud[1] = couleur_[1];
	couleurNoeud[2] = couleur_[2];
	
	vbo_->dessiner(couleurNoeud, vueProjection * modele);
	glPopMatrix();

	glLoadIdentity();

}


//////////////////////////////////////////////////////////////////////////
/////
///// @fn void NoeudMaillet::animer(float temps)
/////
///// Cette fonction effectue l'animation du noeud pour un certain
///// intervalle de temps.
/////
///// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void NoeudMaillet::animer(float temps)
{
	if(FacadeModele::obtenirInstance()->collisionMaillet()) { FacadeModele::obtenirInstance()->sonRondeleMaillet(); }

}

//////////////////////////////////////////////////////////////////////////
/////
///// @fn void NoeudMaillet::accepter(VisiteurAbstrait &visiteur)
/////
///// Cette fonction va permettre au noeud d'accepter un visiteur
/////
///// @param[in] visiteur : visiteur qui visite le noeud
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void NoeudMaillet::accepter(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMaillet::setRayonMaillet(double rayon)
///
/// Cette fonction permet de modifier le rayon du maillet
///
/// @param[in] rayon : le rayon du maillet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMaillet::setRayonMaillet(double rayon)
{
	rayon_ = rayon;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudRondelle::getRayonMaillet()
///
/// Cette fonction permet d'obtenir le rayon du maillet
///
/// @return le rayon du maillet
///
////////////////////////////////////////////////////////////////////////
double NoeudMaillet::getRayonMaillet()
{
	return rayon_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudRondelle::getAngleRotation()
///
/// Cette fonction permet d'obtenir l'angle de rotation
///
/// @return l'angle de rotation
///
////////////////////////////////////////////////////////////////////////
double NoeudMaillet::getAngleRotation()
{
	return angleRotation_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMaillet::setAngleRotation(double angleRotation)
///
/// Cette fonction permet de modifier l'angle de rotation du maillet
///
/// @param[in] rayon : l'angle de rotation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMaillet::setAngleRotation(double angleRotation)
{
	angleRotation_ = angleRotation;
}

void NoeudMaillet::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	boiteMaillet_ = utilitaire::calculerCylindreEnglobant(*modele_);
}

utilitaire::CylindreEnglobant NoeudMaillet::getBoiteEnglobante()
{
	return boiteMaillet_;
}

double NoeudMaillet::getMasse() {
	return masseMaillet_;
}
