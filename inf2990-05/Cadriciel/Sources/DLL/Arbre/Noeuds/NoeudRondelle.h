///////////////////////////////////////////////////////////////////////////
/// @file NoeudRondelle.h
/// @author Equipe 05
/// @date 2016-09-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDRONDELLE_H__
#define __ARBRE_NOEUDS_NOEUDRONDELLE_H__


#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudRondelle
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe 05
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class NoeudRondelle : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudRondelle(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRondelle();


	/// Affiche la rondelle.
	virtual void afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const;
	/// Effectue l'animation de la rondelle.
	virtual void animer(float temps);

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	utilitaire::CylindreEnglobant getBoiteEnglobante();

	///Accepter visiteur
	virtual void accepter(VisiteurAbstrait* visiteur);
	

	/// Modifie le rayon
	void setRayonRondelle(double rayon);
	/// Obtient le rayon
	double getRayonRondelle();
	/// Obtient l'angle de rotation
	double getAngleRotation();
	/// Modifie l'angle de rotation
	void setAngleRotation(double angleRotation);

	double getMasse();

	//void CalculerPhysique(glm::vec3 force, glm::vec3 acceleration, glm::vec3 vitesse, float masse, double temps);

	void setDirectionRondelle(glm::vec3 dir);
	glm::vec3 getDirection();
	/// Obtenir si but gauche
	bool getEstButGauche();
	/// Obtenir si but droit
	bool getEstButDroit();
	/// Modifier si but gauche
	void setEstButGauche(bool estButGauche);
	/// Modifier si but droit
	void setEstButDroit(bool estButDroit);

private:

	/// Angle de rotation.
	float angleRotation_{ 0.f };
	/// Rayon de la rondelle
	double rayon_;
	/// Couleur de la rondelle
	GLubyte couleur_[3];

	double masseRondelle_ = 3;
	//glm::vec3 vitesse_;
	//glm::vec3 acceleration_;
	///Boite englobante
	utilitaire::CylindreEnglobant boiteRondelle_;
	glm::vec3 directionRondelle_;
	/// But cote gauche
	bool estButGauche_;
	/// But cote droit
	bool estButDroit_;
};


#endif // __ARBRE_NOEUDS_NOEUDRONDELLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
