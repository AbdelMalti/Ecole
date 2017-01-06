///////////////////////////////////////////////////////////////////////////////
/// @file Texture.cpp
/// @author Equipe 05
/// @date 2016-09-23
/// @version 1.0
/// @addtogroup inf2990 INF2990
///
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Texture.h"
#include <windows.h>
#include <GL/gl.h>

// Definition prise de l'en-tete de la version 1.2 d'OpenGL.
#define GL_CLAMP_TO_EDGE 0x812F

Texture* Texture::instance_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn Texture* Texture::obtenirInstance()
/// @return l'instance unique de la classe
///
////////////////////////////////////////////////////////////////////////
Texture* Texture::obtenirInstance()
{
	if (instance_ == 0)
	{
		instance_ = new Texture();
	}

	return instance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Texture::libererInstance()
///
/// libere l'instance unique de cette classe
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Texture::libererInstance()
{
	delete instance_;
	instance_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Texture::Texture()
///
/// constructeur par defaut qui charge les Textures
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
Texture::Texture()
{
	chargerTexture();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Texture::chargerTexture()
///
/// charge les Texture du jeu
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Texture::chargerTexture()
{
	aidegl::glLoadTexture("media/beige.jpg", textureSurfaceTable_);
	aidegl::glLoadTexture("media/rose.jpg", textureLigneSeparatriceTable_);
	aidegl::glLoadTexture("media/textBordHautEtBasTable.jpg", textureBordureTable_[0]);
	aidegl::glLoadTexture("media/textBordCouronneTable.png", textureBordureTable_[1]);
	aidegl::glLoadTexture("media/textureDesGoals.png", textureBordureTable_[2]);	

}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int Texture::obtenirTextureMuret() const
///
/// retourne la texture des murets
///
/// @return la texture des murets
///
////////////////////////////////////////////////////////////////////////
unsigned int Texture::obtenirTextureMuret() const
{
	return textureMuret_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int Texture::obtenirTextureSurfaceTable() const
///
/// @return la texture de la surface de la table
///
////////////////////////////////////////////////////////////////////////
unsigned int Texture::obtenirTextureSurfaceTable() const
{
	return textureSurfaceTable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int Texture::obtenirTextureBordureTable(int index) const
///
/// retourne la texture de la bordure de la table
///
/// @param[in] index : index de la texture
///
/// @return la texture de la bordure de la table
///
////////////////////////////////////////////////////////////////////////
unsigned int Texture::obtenirTextureBordureTable(int index) const
{
	return textureBordureTable_[index];
}




////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int Texture::obtenirTextureBordureTable(int index) const
///
/// @param[in] index : index de la texture
///
/// @return la texture de la ligne separatrice de la table
///
////////////////////////////////////////////////////////////////////////
unsigned int Texture::obtenirTextureLigneSeparatriceTable() const
{
	return textureLigneSeparatriceTable_;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////