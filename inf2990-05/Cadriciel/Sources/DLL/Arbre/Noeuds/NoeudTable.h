///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author Equipe 05
/// @date 2016-09-18
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDTABLE_H__
#define __ARBRE_NOEUDS_NOEUDTABLE_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudTable
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe 05
/// @date 2016-09-18
///////////////////////////////////////////////////////////////////////////
class NoeudTable : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudTable(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudTable();

	/// Obtenir les coordonnees du point en x de la table
	double getPositionX() const;
	/// Obtenir les coordonnees du point en y de la table
	double getPositionY() const;
	/// Obtenir les coordonnees du point en z de la table
	double getPositionZ() const;

	/// Obtient le coefficient de friction
	float getCoefficientFriction();

	/// Affiche la table.
	virtual void afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const;

private:
	/// Poisitions des points de la table
	glm::vec3 pointDeControle_[9];
};



#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

