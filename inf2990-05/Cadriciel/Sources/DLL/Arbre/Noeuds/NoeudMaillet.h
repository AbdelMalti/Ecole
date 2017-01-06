///////////////////////////////////////////////////////////////////////////
/// @file NoeudMaillet.h
/// @author Equipe 05
/// @date 2016-09-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMAILLET_H__
#define __ARBRE_NOEUDS_NOEUDMAILLET_H__


#include "NoeudComposite.h"
#include "Utilitaire.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMaillet
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe 05
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class NoeudMaillet : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudMaillet(const std::string& typeNoeud);
	/// Construteur expret pour les tests : 
	NoeudMaillet(const std::string& typeNoeud, double rayon, double angle);
	/// Destructeur.
	~NoeudMaillet();


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
	void setRayonMaillet(double rayon);
	/// Obtient le rayon
	double getRayonMaillet();
	/// Obtient l'angle de rotation
	double getAngleRotation();
	/// Modifie l'angle de rotation
	void setAngleRotation(double angleRotation);
	
	double getMasse();

private:

	/// Angle de rotation.
	//float angleRotation_{ 0.f };
	/// Rayon du maillet
	double rayon_;
	/// Couleur du maillet
	GLubyte couleur_[3];

	const double masseMaillet_ = 6;

	///Boite englobante pour l'objet maillet
	utilitaire::CylindreEnglobant boiteMaillet_;


};


#endif // __ARBRE_NOEUDS_NOEUDMAILLET_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
