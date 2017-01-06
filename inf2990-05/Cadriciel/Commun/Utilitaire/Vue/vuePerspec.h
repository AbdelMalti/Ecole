//////////////////////////////////////////////////////////////////////////////
/// @file vuePerspec.h
/// @author Equipe 05
/// @date 2016-11-23
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUEPERSPEC_H__
#define __UTILITAIRE_VUEPERSPEC_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionPerspec.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class vuePerspec
	/// @brief Classe concrète de vue perspective.
	///
	/// Cette classe implante le comportement attendu d'une vue perspective.
	///
	/// @author Equipe 05
	/// @date 2016-11-23
	////////////////////////////////////////////////////////////////////////
	class VuePerspec : public Vue
	{
	public:
		/// Constructeur.
		VuePerspec(Camera const& camera, ProjectionPerspec const& projection);

		/// Obtention de la projection.
		virtual const ProjectionPerspec& obtenirProjection() const;

		/// Modification de la clotûre.
		virtual void redimensionnerFenetre(int largeur, int hauteur);

		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Zoom in élastique.
		virtual void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);
		/// Zoom out élastique.
		virtual void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);

		/// Déplacement dans le plan XY par rapport à la vue.
		virtual void deplacerXY(double deplacementX, double deplacementY);
		/// Déplacement dans le plan XY par rapport à la vue.
		virtual void deplacerXY(const glm::ivec2& deplacement);
		/// Déplacement selon l'axe des Z par rapport à la vue.
		virtual void deplacerZ(double deplacement);
		/// Rotation selon les axes des X et des Y par rapport à la vue.
		virtual void rotaterXY(double rotationX, double rotationY);
		/// Rotation selon les axes des X et des Y par rapport à la vue.
		virtual void rotaterXY(const glm::ivec2& rotation);
		/// Rotation selon l'axe des Z par rapport à la vue.
		virtual void rotaterZ(double rotation);


	private:
		/// Projection utilisée pour cette vue.
		ProjectionPerspec projection_;

	};


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUEPERSPEC_H__


   ///////////////////////////////////////////////////////////////////////////
   /// @}
   ///////////////////////////////////////////////////////////////////////////
