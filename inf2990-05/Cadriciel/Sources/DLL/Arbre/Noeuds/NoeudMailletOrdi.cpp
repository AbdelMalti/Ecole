///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMailletOrdi.cpp
/// @author Equipe 05
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMailletOrdi.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>
#include "FacadeModele.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMailletOrdi::NoeudMailletOrdi(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMailletOrdi::NoeudMailletOrdi(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	rayon_ = 0.6;
	couleur_[0] = 255;
	couleur_[1] = 0;
	couleur_[2] = 0;
	vitesseInitial_ = 8;
	estOrdi_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMailletOrdi::~NoeudMailletOrdi()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMailletOrdi::~NoeudMailletOrdi()
{
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletOrdi::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudMailletOrdi::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
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

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletOrdi::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletOrdi::animer(float temps)
{

	if (FacadeModele::obtenirInstance()->collisionMailletOrdi()) { FacadeModele::obtenirInstance()->sonRondeleMaillet(); }

	if (estOrdi_)
	{

	NoeudAbstrait* mailletOrdi;
	NoeudAbstrait* rondelle;
	mailletOrdi = obtenirParent()->chercher("mailletOrdi");
	rondelle = obtenirParent()->chercher("rondelle");

	glm::vec3 posMaillet, posRondelle;
	posMaillet = mailletOrdi->obtenirPositionRelative();
	posRondelle = rondelle->obtenirPositionRelative();

	double posXtableX_ = 62.0;
	glm::vec3 posMailletInitial = glm::vec3(posXtableX_, 0.0, 1.0);

	if (utilitaire::DANS_LIMITESXY(posRondelle.x, -66.0, 0.0, posRondelle.y, -50, 50))	//Coté gauche table scénario défensif
	{
		if (utilitaire::DANS_LIMITESXY(posRondelle.x, -64, 0.0, posRondelle.y, -48, 48))	//coté gauche
		{
			if (posMaillet.x != posMailletInitial.x)
			{
				posMaillet.x += vitesseMailletOrdi_;
				posMaillet.y = posRondelle.y;
			}
			posMaillet.y = posRondelle.y;
			if (utilitaire::DANS_LIMITESXY(posMaillet.x, 0.1, 63.0, posMaillet.y, -48, 48))
				mailletOrdi->assignerPositionRelative(posMaillet);
		}
	}
	else if (utilitaire::DANS_LIMITESXY(posRondelle.x, 0.0, 66.0, posRondelle.y, -50, 50))	//Coté droit table scénario offensif
	{
		if (utilitaire::DANS_LIMITESXY(posMaillet.x, 0.0, 63.0, posMaillet.y, -48, 48))	//coté droit table
		{
			if (posMaillet.x > posRondelle.x)
				posMaillet.x -= vitesseMailletOrdi_;
			if (posMaillet.y < posRondelle.y)
				posMaillet.y += vitesseMailletOrdi_;
			if (posMaillet.x < posRondelle.x)
				posMaillet.x += vitesseMailletOrdi_;
			if (posMaillet.y > posRondelle.y)
				posMaillet.y -= vitesseMailletOrdi_;

			rondelle->setVitesse(vitesseMailletOrdi_+3);
			if (utilitaire::DANS_LIMITESXY(posRondelle.x, 0.0, 66.0, posRondelle.y, -50, 50))
				mailletOrdi->assignerPositionRelative(posMaillet);
		}
	}
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletOrdi::accepter(VisiteurAbstrait &visiteur)
///
/// Cette fonction va permettre au noeud d'accepter un visiteur
///
/// @param[in] visiteur : visiteur qui visite le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletOrdi::accepter(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletOrdi::setRayonMaillet(double rayon)
///
/// Cette fonction permet de modifier le rayon du maillet de l'ordinateur
///
/// @param[in] rayon : le rayon du maillet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletOrdi::setRayonMaillet(double rayon)
{
	rayon_ = rayon;
}
double NoeudMailletOrdi::getRayonMaillet()
{
	return rayon_;
}
double NoeudMailletOrdi::getAngleRotation()
{
	return angleRotation_;
}
void NoeudMailletOrdi::setAngleRotation(double angleRotation)
{
	angleRotation_ = angleRotation;
}

void NoeudMailletOrdi::setPosition(glm::vec3 position)
{
	positionMailletOrdi_ = position;
}

glm::vec3 NoeudMailletOrdi::getPosition() const
{
	return positionMailletOrdi_;
}

void NoeudMailletOrdi::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) 
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	boiteMailletOrdi_ = utilitaire::calculerCylindreEnglobant(*modele_);
}

utilitaire::CylindreEnglobant NoeudMailletOrdi::getBoiteEnglobante()
{
	return boiteMailletOrdi_;
}

double NoeudMailletOrdi::getMasse() {
	return masseMailletOrdi_;
}

void NoeudMailletOrdi::setEstOrdi(bool estOrdi)
{
	estOrdi_ = estOrdi;
}



/////////////////////////////////////////////////////////////////////////////////
///// @}
/////////////////////////////////////////////////////////////////////////////////
