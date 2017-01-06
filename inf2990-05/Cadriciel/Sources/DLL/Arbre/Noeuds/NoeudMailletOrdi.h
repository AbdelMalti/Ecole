///////////////////////////////////////////////////////////////////////////
/// @file NoeudMailletOrdi.h
/// @author Equipe 05
/// @date 2016-09-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMAILLETORDI_H__
#define __ARBRE_NOEUDS_NOEUDMAILLETORDI_H__


#include "NoeudComposite.h"
#include "Utilitaire.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMailletOrdi
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe 05
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class NoeudMailletOrdi : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudMailletOrdi(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMailletOrdi();


	/// Affiche la rondelle.
	virtual void afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const;
	/// Effectue l'animation de la rondelle.
	virtual void animer(float temps);

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	utilitaire::CylindreEnglobant getBoiteEnglobante();

	virtual void accepter(VisiteurAbstrait* visiteur);
	
	void setRayonMaillet(double rayon);
	double getRayonMaillet();
	double getAngleRotation();
	void setAngleRotation(double angleRotation);

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;

	double getMasse();
	void setEstOrdi(bool estOrdi);

private:

	/// Angle de rotation du maillet ordinateur
	float angleRotation_{ 0.f };
	/// Rayon du maillet ordinateur
	double rayon_;
	/// Couleur du maillet ordinateur
	GLubyte couleur_[3];

	double vitesseMailletOrdi_ = 1;

	glm::vec3 positionMailletOrdi_;

	const double masseMailletOrdi_ = 6;

	///Boite englobante pour l'objet maillet ordinateur
	utilitaire::CylindreEnglobant boiteMailletOrdi_;
	bool estOrdi_ = false;

}; 


#endif // __ARBRE_NOEUDS_NOEUDMAILLETORDI_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
