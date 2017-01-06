#pragma once
///////////////////////////////////////////////////////////////////////////////
/// @file Textures.h
/// @author equipe 05
/// @date 2016-09-23
/// @version 1.0
///
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "AideGL.h"

///////////////////////////////////////////////////////////////////////////
/// @class Textures
/// @brief cette classe nous permet de charger toutes les textures en une fois
/// @author equipe 05
/// @date 2016-09-23
///////////////////////////////////////////////////////////////////////////
class Texture
{
public:
	/// Obtient l'instance unique de la classe.
	static Texture* obtenirInstance();

	/// Libere l'instance unique de la classe.
	static void libererInstance();
	/// Charge la texture
	void chargerTexture();
	/// retourne la texture des murets
	unsigned int obtenirTextureMuret() const;
	/// retourne la texture de la surface de la table
	unsigned int obtenirTextureSurfaceTable() const;
	/// retourne la texture de la bordure de la table
	unsigned int obtenirTextureBordureTable(int index) const;
	/// retourne la texture de la bordure de la ligne separatrice de la table
	unsigned int obtenirTextureLigneSeparatriceTable() const;

private:
	Texture();
	~Texture() {};

	/// Instance unique de la classe
	static Texture* instance_;
	/// texture des murets
	unsigned int textureMuret_;
	/// texture de la surface de la table
	unsigned int textureSurfaceTable_;
	/// texture de la bordure de la table
	unsigned int textureBordureTable_[3];
	/// texture de la ligne separatrice de la table
	unsigned int textureLigneSeparatriceTable_;
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
