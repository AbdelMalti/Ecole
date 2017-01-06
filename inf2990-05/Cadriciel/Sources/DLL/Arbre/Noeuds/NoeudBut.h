#pragma once
///////////////////////////////////////////////////////////////////////////
/// @file NoeudBut.h
/// @author Jackie Phung
/// @date 2016-09-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBUT_H__
#define __ARBRE_NOEUDS_NOEUDBUT_H__


#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBut
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Jackie Phung
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class NoeudBut : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudBut(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudBut();

	/// Affiche le but.
	virtual void afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const;
	/// Effectue l'animation du but.
	virtual void animer(float temps);

	///Accepte visiteur
	virtual void accepter(VisiteurAbstrait* visiteur);

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	/// Obtient la boite englobante du but
	utilitaire::BoiteEnglobante getBoiteEnglobante();

private:
	/// Longueur du but
	double longueur_;
	///// Largueur du but
	/*double largueur_;*/
	/// Couleur du but
	GLubyte couleur_[3];
	///Boite englobante pour le but
	utilitaire::BoiteEnglobante boiteBut_;
};


#endif // __ARBRE_NOEUDS_NOEUDBUT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
