#pragma once
///////////////////////////////////////////////////////////////////////////
/// @file NoeudBonus.h
/// @author Jackie Phung
/// @date 2016-09-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBONUS_H__
#define __ARBRE_NOEUDS_NOEUDBONUS_H__


#include "NoeudComposite.h"
#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBonus
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Jackie Phung
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class NoeudBonus : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudBonus(const std::string& typeNoeud);
	/// Construteur copie de bonus.
	NoeudBonus(NoeudBonus* bonusCopier);
	/// Destructeur.
	~NoeudBonus();


	/// Affiche le bonus.
	virtual void afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const;
	/// Effectue l'animation du bonus.
	virtual void animer(float temps);

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	utilitaire::CylindreEnglobant getBoiteEnglobante();


	///Accepte visiteur
	virtual void accepter(VisiteurAbstrait* visiteur);
	

	void setRayonBonus(double rayon);
	double getRayonBonus();
	double getAngleRotation();
	void setAngleRotation(double angle);

	/// Obtenir la composante en x de la couleur
	GLubyte getCouleur1();
	/// Obtenir la composante en y de la couleur
	GLubyte getCouleur2();
	/// Obtenir la composante en z de la couleur
	GLubyte getCouleur3();
	/// Permet de définir des couleurs au objets pour la sélection par couleur
	bool testerSelection(GLubyte ObjetColore[]);

private:

	void setCouleur();
	int nbInstances_;
	GLubyte couleurBonusAcc_[3];
	static int compteur_;
	double rayon_;
	double angleRotation_;

	///Boite englobante
	utilitaire::CylindreEnglobant boiteBonus_;

};


#endif // __ARBRE_NOEUDS_NOEUDBONUS_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
