#pragma once
///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.h
/// @author Jackie Phung
/// @date 2016-09-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPORTAIL_H__
#define __ARBRE_NOEUDS_NOEUDPORTAIL_H__


#include "NoeudComposite.h"
#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudPortail
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Jackie Phung
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class NoeudPortail : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudPortail(const std::string& typeNoeud);
	/// Constructeur copie pour la duplication
	NoeudPortail(NoeudPortail* portailCopier);
	/// Destructeur.
	~NoeudPortail();


	/// Affiche le portail.
	virtual void afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const;
	/// Effectue l'animation du portail.
	virtual void animer(float temps);

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	utilitaire::CylindreEnglobant getBoiteEnglobante();

	///Accepter visiteur
	virtual void accepter(VisiteurAbstrait* visiteur);
	

	void setRayonPortail(double rayon);
	double getRayonPortail();
	double getAngleRotation();
	void setAngleRotation(double angleRotation);

	/// Teste la selection
	bool testerSelection(GLubyte ObjetColore[]);

private:

	/// Permet de définir des couleurs au objets pour la sélection par couleur
	void setCouleur();
	/// Couleur du portail
	GLubyte couleurPo_[3];
	/// Compteur pour le nombre de portails ajouté
	static int compteurS_;
	/// Rayon du portail
	double rayon_;
	/// Angle de rotation du portail
	float angleRotation_;
	///Boite englobante
	utilitaire::CylindreEnglobant boitePortail_;
};


#endif // __ARBRE_NOEUDS_NOEUDPORTAIL_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
