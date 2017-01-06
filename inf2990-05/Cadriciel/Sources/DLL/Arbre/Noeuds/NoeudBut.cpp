///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBut.cpp
/// @author Jackie Phung
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBut.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBut::NoeudBut(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBut::NoeudBut(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	longueur_ = 1.2;
	/*largueur_ = 0.4;*/
	couleur_[0] = 255;
	couleur_[1] = 0;
	couleur_[2] = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBut::~NoeudBut()
///
/// Ce destructeur désallouee la liste d'affichage du but.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBut::~NoeudBut()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBut::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBut::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
	auto modele = glm::translate(transformationRelative_, glm::vec3(centreDeRotation_)); //0, 0, 0	
	/*modele = glm::rotate(modele, (float)angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));*/
	modele = glm::scale(modele, glm::vec3(longueur_, longueur_, longueur_));

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


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBut::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBut::animer(float temps)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBut::accepter(VisiteurAbstrait &visiteur)
///
/// Cette fonction va permettre au noeud d'accepter un visiteur
///
/// @param[in] visiteur : visiteur qui visite le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBut::accepter(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBut::accepter(VisiteurAbstrait &visiteur)
///
/// Cette fonction va permettre au noeud d'accepter un visiteur
///
/// @param[in] modele : modele de la boite englobante
/// @param[in] liste : liste
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBut::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	boiteBut_ = utilitaire::calculerBoiteEnglobante(*modele_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBut::accepter(VisiteurAbstrait &visiteur)
///
/// Cette fonction va permettre au noeud d'accepter un visiteur
///
/// @return utilitaire::BoiteEnglobante boiteBut
///
////////////////////////////////////////////////////////////////////////
utilitaire::BoiteEnglobante NoeudBut::getBoiteEnglobante()
{
	return boiteBut_;
}


/////////////////////////////////////////////////////////////////////////////////
///// @}
/////////////////////////////////////////////////////////////////////////////////
