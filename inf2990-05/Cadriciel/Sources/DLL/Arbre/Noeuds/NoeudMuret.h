#pragma once
///////////////////////////////////////////////////////////////////////////
/// @file NoeudMuret.h
/// @author Jackie Phung
/// @date 2016-09-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMURET_H__
#define __ARBRE_NOEUDS_NOEUDMURET_H__

#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMuret
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Jackie Phung
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class NoeudMuret : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudMuret(const std::string& typeNoeud);
	/// Constructeur copie de noeud
	NoeudMuret(NoeudMuret* muretCopier);
	/// Destructeur.
	~NoeudMuret();


	/// Affiche le muret.
	virtual void afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const;
	/// Effectue l'animation du muret.
	virtual void animer(float temps);

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	/// Obtient la boite englobante du muret
	utilitaire::BoiteEnglobante getBoiteEnglobante();

	///Accepter visiteur
	virtual void accepter(VisiteurAbstrait* visiteur);
	
	/// Modifie la longueur du muret
	void setLongueurMuret(double longueur);
	/// Obtient la longueur du muret
	double  getLongueurMuret();
	/// Obtient l'angle de rotation
	double getAngleRotation();
	/// Modifie l'angle de rotation
	void setAngleRotation(double angle);

	/// Permet de vérifier la selection
	bool testerSelection(GLubyte ObjetColore[]);


private:

	double longueur_;
	double largueur_;
	double profondeur_;
	float angleRotation_;
	void setCouleur();
	int nbInstances_;
	GLubyte couleur_[3];
	static int compteurM_;

	///Boite englobante pour le muret
	utilitaire::BoiteEnglobante boiteMuret_;

};


#endif // __ARBRE_NOEUDS_NOEUDMURET_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
