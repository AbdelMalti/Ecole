#pragma once
///////////////////////////////////////////////////////////////////////////
/// @file NoeudPointDeControle.h
/// @author Equipe 05
/// @date 2016-09-18
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __POINT_DE_CONTROLE_H__
#define __POINT_DE_CONTROLE_H__


#include "NoeudAbstrait.h"
#include "Texture.h"
#include "Utilitaire.h"
#include "GL/glew.h"

class PointDeControle : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	PointDeControle(const std::string& typeNoeud);
	/// Destructeur.
	~PointDeControle();

	/// Affiche le point
	virtual void afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const;
	/// Effectue l'animation du point.
	virtual void animer(float temps);
	/// Modifie le rayon
	void setRayonPoint(double rayon);
	/// Obtient le rayon
	double getRayonPoint();

private:

	/// Rayon
	double rayon_;
	/// Couleur d'un point de controle
	GLubyte couleurPoint_[3];
};

#endif // __POINT_DE_CONTROLE_H__