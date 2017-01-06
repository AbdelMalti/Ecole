///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRondelle.cpp
/// @author Equipe 05
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudRondelle.h"
#include "Utilitaire.h"
#include "FacadeModele.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>
#include "../Son/Son.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	rayon_ = 0.4;
	couleur_[0] = 255;
	couleur_[1] = 50;
	couleur_[2] = 0;
	vitesseInitial_ = 0;
	//masseRondelle_ = 3;
	directionRondelle_ = {0,0,0};
	estButGauche_ = false;
	estButDroit_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::~NoeudRondelle()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRondelle::~NoeudRondelle()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
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
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
	glPushMatrix();
	// Révolution autour du centre.
	auto modele = glm::translate(transformationRelative_, glm::vec3(0, 0, 1));
	modele = glm::scale(modele, glm::vec3(rayon_, rayon_, rayon_));
	GLubyte couleurNoeud[3];
	couleurNoeud[0] = couleur_[0];
	couleurNoeud[1] = couleur_[1];
	couleurNoeud[2] = couleur_[2];
	
	vbo_->dessiner(couleurNoeud, vueProjection * modele);
	glPopMatrix();
}



//////////////////////////////////////////////////////////////////////////
/////
///// @fn void NoeudRondelle::animer(float temps)
/////
///// Cette fonction effectue l'animation du noeud pour un certain
///// intervalle de temps.
/////
///// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void NoeudRondelle::animer(float temps)
{
	FacadeModele::obtenirInstance()->animationJeu();

	//std::cout << "vitesse rondelle : " << this->getVitesse() << std::endl;
	//std::cout << "Frottement : " << FacadeModele::obtenirInstance()->obtenirCoefficientFriction() << std::endl;

	//std::cout << "Direction : " << this->getDirection().x << " ; " << this->getDirection().y << std::endl;

	this->setVitesse(this->getVitesse() - FacadeModele::obtenirInstance()->obtenirCoefficientFriction());

	if (this->getVitesse() < 0) {
		this->setVitesse(0);
	}
	if (this->getVitesse() > 20) { //Afin de limiter la vitesse
		this->setVitesse(20);
	}

	glm::dvec3 newPosRondelle = this->obtenirPositionRelative();

	newPosRondelle[0] += this->getDirection().x * this->getVitesse();
	newPosRondelle[1] += this->getDirection().y * this->getVitesse();

	double rebond = (FacadeModele::obtenirInstance()->obtenirRebond());

	//std::cout << "Rebond : " << rebond;
	//std::cout << "\n";

	///////Pour but

	if (
		((newPosRondelle[1] + this->getRayonRondelle()) > -9.44 && (newPosRondelle[1] - this->getRayonRondelle()) < 10)
		&& ((newPosRondelle[0] - this->getRayonRondelle()) <= -66)
		)
	{
		/*std::cout << "\n\n\n\n Et le but Gauche! \n\n\n\n\n " << std::endl;*/
		estButGauche_ = true;
		//this->assignerPositionRelative(glm::vec3(0, 0, 0));
		newPosRondelle = { 0, 0, 0 };
		this->setVitesse(0);
	}

	if (
		((newPosRondelle[1] + this->getRayonRondelle()) > -9.44 && (newPosRondelle[1] - this->getRayonRondelle()) < 10)
		&& ((newPosRondelle[0] + this->getRayonRondelle()) >= 66)
		)
	{
		/*std::cout << "\n\n\n\n Et le but Droite! \n\n\n\n\n " << std::endl;*/
		estButDroit_ = true;
		//this->assignerPositionRelative(glm::vec3(0, 0, 0));
		newPosRondelle = { 0, 0, 0 };
		this->setVitesse(0);
	}

	if ((newPosRondelle[1]+ this->getRayonRondelle()) >= 50)//Limite superieur
	{
		glm::vec3 nouvelleDiection {this->getDirection().x, -this->getDirection().y, 0};

		//std::cout << "Hors Haut" << std::endl;

		this->setDirectionRondelle(nouvelleDiection);
		newPosRondelle[1] += this->getDirection().x * (this->getVitesse()+rebond);

		if ((newPosRondelle[1] - this->getRayonRondelle()) >= 55) {
			newPosRondelle[1] = 49;
		}
		Son::obtenirInstance()->jouerSon(8);
	}

	if ((newPosRondelle[1] - this->getRayonRondelle()) <= -50) //Limite inferieur
	{
		//std::cout << "Hors Bas" << std::endl;
		glm::vec3 nouvelleDiection{ this->getDirection().x, -this->getDirection().y, 0 };


		this->setDirectionRondelle(nouvelleDiection);
		newPosRondelle[1] += this->getDirection().x * (this->getVitesse() + rebond);

		if ((newPosRondelle[1] - this->getRayonRondelle()) <= -55) {
			newPosRondelle[1] = -49;
		}
		Son::obtenirInstance()->jouerSon(8);
	}
	
	if ((newPosRondelle[0] + this->getRayonRondelle()) >= 66) // Limite droite
	{
		//std::cout << "Hors Droite" << std::endl;

		glm::vec3 nouvelleDiection{ -this->getDirection().x, this->getDirection().y, 0 };


		this->setDirectionRondelle(nouvelleDiection);
		newPosRondelle[0] += this->getDirection().x * (this->getVitesse() + rebond);

		if ((newPosRondelle[0] + this->getRayonRondelle()) >= 70) {
			newPosRondelle[0] = 65;
		}
		Son::obtenirInstance()->jouerSon(8);
	}

	if ((newPosRondelle[0] - this->getRayonRondelle()) <= -66) // Limite gauche
	{
		//std::cout << "Hors Gauche" << std::endl;

		glm::vec3 nouvelleDirection{ -this->getDirection().x, this->getDirection().y, 0 };


		this->setDirectionRondelle(nouvelleDirection);
		newPosRondelle[0] += this->getDirection().x * (this->getVitesse() + rebond);

		if ((newPosRondelle[0] - this->getRayonRondelle()) <= -70) {
			newPosRondelle[0] = -65;
		}
		Son::obtenirInstance()->jouerSon(8);
	}

	//std::cout << "position Rondelle" << this->obtenirPositionRelative().x << " ; " << this->obtenirPositionRelative().y << std::endl;

	this->assignerPositionRelative(newPosRondelle);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::accepter(VisiteurAbstrait *visiteur)
///
/// Cette fonction va permettre au noeud d'accepter un visiteur
///
/// @param[in] visiteur : visiteur qui visite le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::accepter(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::setRayonRondelle(double rayon)
///
/// Cette fonction permet de modifier le rayon de la rondelle
///
/// @param[in] rayon : le rayon de la rondelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::setRayonRondelle(double rayon)
{
	rayon_ = rayon;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudRondelle::getRayonRondelle()
///
/// Cette fonction permet d'obtenir le rayon de la rondelle
///
/// @return le rayon de la rondelle.
///
////////////////////////////////////////////////////////////////////////
double NoeudRondelle::getRayonRondelle()
{
	return rayon_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudRondelle::getAngleRotation()
///
/// Cette fonction permet d'obtenir l'angle de rotation de la rondelle
///
/// @return l'angle de rotation de la rondelle.
///
////////////////////////////////////////////////////////////////////////
double NoeudRondelle::getAngleRotation()
{
	return angleRotation_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::setAngleRotation(double angleRotation)
///
/// Cette fonction permet de modifier l'angle de rotation de la rondelle
///
/// @param[in] angleRotation : l'angle de rotation de la rondelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::setAngleRotation(double angleRotation)
{
	angleRotation_ = angleRotation;
}


void NoeudRondelle::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	boiteRondelle_ = utilitaire::calculerCylindreEnglobant(*modele_);
}

utilitaire::CylindreEnglobant NoeudRondelle::getBoiteEnglobante()
{
	return boiteRondelle_;
}

//void NoeudRondelle::CalculerPhysique(glm::vec3 force, glm::vec3 acceleration, glm::vec3 vitesse, float masse, double temps)
//{
//	masse = masseRondelle_;
//	vitesse = vitesse_;
//	acceleration = acceleration_;
//
//	force = masse * acceleration;
//	
//}

double NoeudRondelle::getMasse() {
	return masseRondelle_;
}

void NoeudRondelle::setDirectionRondelle(glm::vec3 dir) 
{
	directionRondelle_ = dir;
}

glm::vec3 NoeudRondelle::getDirection()
{
	return directionRondelle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRondelle::getEstButGauche()
///
/// Cette fonction permet d'obtenir si but gauche
///
/// @return si but gauche
///
////////////////////////////////////////////////////////////////////////
bool NoeudRondelle::getEstButGauche()
{
	return estButGauche_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRondelle::getEstButDroit()
///
/// Cette fonction permet d'obtenir si but droit
///
/// @return si but gauche
///
////////////////////////////////////////////////////////////////////////
bool NoeudRondelle::getEstButDroit()
{
	return estButDroit_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::setEstButGauche(bool estButGauche)
///
/// Cette fonction permet de modifier si but gauche
///
/// @param[in] estButGauche :si but a gauche
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::setEstButGauche(bool estButGauche)
{
	estButGauche_ = estButGauche;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::setEstButDroit(bool estButDroit)
///
/// Cette fonction permet de modifier si but a droit
///
/// @param[in] estButDroit : si but droit
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::setEstButDroit(bool estButDroit)
{
	estButDroit_ = estButDroit;
}


/////////////////////////////////////////////////////////////////////////////////
///// @}
/////////////////////////////////////////////////////////////////////////////////
