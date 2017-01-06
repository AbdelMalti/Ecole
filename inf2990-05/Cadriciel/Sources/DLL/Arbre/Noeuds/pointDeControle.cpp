///////////////////////////////////////////////////////////////////////////////
/// @file pointDeControle.cpp
/// @author Equipe 5
/// @date 2016-11-04
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "pointDeControle.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn PointDeControle::PointDeControle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
PointDeControle::PointDeControle(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }, rayon_(0.7)
{
	couleurPoint_[0] = 255;
	couleurPoint_[1] = 0;
	couleurPoint_[2] = 127;
}

////////////////////////////////////////////////////////////////////////
///
///PointDeControle::~PointDeControle()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
PointDeControle::~PointDeControle()
{}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void PointDeControle::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
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
void PointDeControle::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
	glPushMatrix();
	
	auto modele = glm::translate(transformationRelative_, glm::vec3(0, 0, 1));
	modele = glm::scale(modele, glm::vec3(rayon_, rayon_, rayon_ + 0.3));

	GLubyte couleurNoeud[3];
	couleurNoeud[0] = couleurPoint_[0];
	couleurNoeud[1] = couleurPoint_[1];
	couleurNoeud[2] = couleurPoint_[2];
	
	vbo_->dessiner(couleurNoeud, vueProjection * modele);
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void PointDeControle::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PointDeControle::animer(float temps)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PointDeControle::setRayonPoint(double rayon)
///
/// Cette fonction effectue la modification du rayon
///
/// @param[in] rayon : valeur du rayon
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PointDeControle::setRayonPoint(double rayon)
{
	rayon_ = rayon;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PointDeControle::getRayonPoint(double rayon)
///
/// Cette fonction effectue l'obtention du rayon
///
/// @return la moitié de l'arrete du cube representant 
///		le point de controle.
///
////////////////////////////////////////////////////////////////////////
double PointDeControle::getRayonPoint()
{
	return rayon_;
}


