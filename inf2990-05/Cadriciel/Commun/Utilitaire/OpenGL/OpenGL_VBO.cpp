#include "OpenGL_VBO.h"

///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorage_VBO.cpp
/// @author Martin Paradis
/// @date 2015-08-28
/// @version 1.0
///
/// @addtogroup modele Modele
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Modele3D.h"
#include "AideGL.h"
#include "Utilitaire.h"
#include <iostream>

/// Position de l'attribut de location dans le nuanceur de sommet
#define VERTEX_LOCATION 0
#define TEXCOORD_LOCATION 1
#define NORMAL_LOCATION 2

namespace opengl{

	Programme VBO::programme_;
	Nuanceur VBO::nuanceurFragment_;
	Nuanceur VBO::nuanceurSommet_;

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VBO::VBO(modele::Modele3D const* modele)
	///
	/// Assigne le modèle 3D.
	///
	/// @param[in] modele : le modele 3D à dessiner.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	VBO::VBO(modele::Modele3D const* modele)
		: modele_{ modele }
	{}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VBO::~VBO()
	///
	/// Destructeur, relâche le VBO.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	VBO::~VBO()
	{
		liberer();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::charger()
	///
	/// Charge les données du modèles 3D sur la mémoire de la carte graphique
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::charger()
	{
		if(!programme_.estInitialise())
		{
			// Initialisation des nuanceurs
			nuanceurFragment_.initialiser(Nuanceur::Type::NUANCEUR_FRAGMENT, "nuanceurs/fragment.glsl");
			nuanceurSommet_.initialiser(Nuanceur::Type::NUANCEUR_VERTEX, "nuanceurs/sommet.glsl");
			programme_.initialiser();
			programme_.attacherNuanceur(nuanceurFragment_);
			programme_.attacherNuanceur(nuanceurSommet_);
			
		}
		creerVBO(modele_->obtenirNoeudRacine());
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::creerVBO(modele::Noeud const& noeud)
	///
	/// Création des VBO selon les données propres à chaque Mesh. L'ordre 
	/// des identifiants OpenGL se calque sur le modèle 3D, en prenant pour
	/// acquis que la hiérarchie interne des noeuds internes n'est pas 
	/// modifiée.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::creerVBO(modele::Noeud const& noeud)
	{
		for (auto const& mesh : noeud.obtenirMeshes())
		{
			enregistrerTampon(mesh.obtenirSommets());
			if (mesh.possedeNormales())
				enregistrerTampon(mesh.obtenirNormales());
			if (mesh.possedeTexCoords())
				enregistrerTampon(mesh.obtenirTexCoords());
			if (mesh.possedeFaces())
				enregistrerTampon(mesh.obtenirFaces());
		}
		/// Création récursive.
		for (auto const& n : noeud.obtenirEnfants())
		{
			creerVBO(n);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessiner() const
	///
	/// Appelle le dessin du modèle à partir des VBO.  Utilise le modèle 3D
	/// pour obtenir la matériau propre à chaque Mesh.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessiner(bool estCouleur, bool estSelectionne, GLubyte couleur[], GLubyte couleurSelectionne[], const glm::mat4& transformation) const
	{
		programme_.assignerUniforme("estSelectionne", int(estSelectionne));
		unsigned int bufferIndex = 0;
		dessiner(modele_->obtenirNoeudRacine(), bufferIndex, estCouleur, estSelectionne, couleur, couleurSelectionne, transformation);

	}

	void VBO::dessiner(GLubyte couleur[], const glm::mat4& transformation) const
	{
		unsigned int bufferIndex = 0;
		dessiner(modele_->obtenirNoeudRacine(), bufferIndex, couleur, transformation);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex) const
	///
	/// Dessin récursif du modèle 3D.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex, bool estCouleur, bool estSelectionne, GLubyte couleur[], GLubyte couleurSelectionne[], const glm::mat4& transformation) const
	{
		// Matrice de transformation
		glm::mat4x4 const& m{ transformation * noeud.obtenirTransformation() };

		glm::mat3 const& vm = glm::mat3(m);
		glm::mat3 const& normal = glm::inverse(vm);

		// Appliquer le nuanceur
		Programme::Start(programme_);
		programme_.assignerUniforme("modelViewProjection", m);
		programme_.assignerUniforme("matrNormale", normal);

		/// Empiler la transformation courante
		glPushMatrix();
		glMultMatrixf(glm::value_ptr(m));

		for (auto const& mesh : noeud.obtenirMeshes())
		{
			// Appliquer le matériau pour le mesh courant
			appliquerMateriau(mesh.obtenirMateriau());

			bool possedeNormales{ mesh.possedeNormales() };
			bool possedeCouleurs{ mesh.possedeCouleurs() };
			bool possedeTexCoords{ mesh.possedeTexCoords() };
			bool possedeSommets{ mesh.possedeSommets() };
			bool possedeFaces{ mesh.possedeFaces() };

			if (estSelectionne)
			{
				glVertexAttrib3f(3, couleurSelectionne[0], couleurSelectionne[1], couleurSelectionne[2]);
			}
			else if (estCouleur)
			{
				glVertexAttrib3f(3, couleur[0] / 255.0, couleur[1] / 255.0, couleur[2] / 255.0);
			}
	
			else
			{
				if (possedeCouleurs)
					glEnable(GL_COLOR_MATERIAL);
				else 
					glDisable(GL_COLOR_MATERIAL);
				
				
				if (possedeNormales)
					glEnable(GL_LIGHTING);
				else
					glDisable(GL_LIGHTING);
			}

			if (possedeSommets)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableVertexAttribArray(VERTEX_LOCATION);
				glVertexAttribPointer(VERTEX_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, 0, nullptr);
			}
			if (possedeNormales)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				/// À Faire: Envoyer les normales aux nuanceurs si nécessaire
				glEnableVertexAttribArray(NORMAL_LOCATION);
				glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, 0, nullptr);
			}
			if (possedeTexCoords)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableVertexAttribArray(TEXCOORD_LOCATION);
				glVertexAttribPointer(TEXCOORD_LOCATION, 2, GL_FLOAT,	GL_FALSE, 0, nullptr);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
			}
			if (possedeFaces)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(3 * mesh.obtenirFaces().size()), GL_UNSIGNED_INT, nullptr);
			}

			if (possedeSommets)
				glDisableVertexAttribArray(VERTEX_LOCATION);
			if (possedeTexCoords)
				glDisableVertexAttribArray(TEXCOORD_LOCATION);
			if (possedeCouleurs)
				glDisable(GL_COLOR_MATERIAL);
			if (possedeNormales)
				glDisable(GL_LIGHTING);

			glMatrixMode(GL_TEXTURE);
			//glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
		Programme::Stop(programme_);

		/// Dessin récursif.
		for (auto const& n : noeud.obtenirEnfants())
		{
			dessiner(n, bufferIndex, estCouleur, estSelectionne, couleur, couleurSelectionne, m);
		}
		/// On dépile la transformation courant
		glPopMatrix();
	}

	void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex, GLubyte couleur[], const glm::mat4& transformation) const
	{
		// Matrice de transformation
		glm::mat4x4 const& m{ transformation * noeud.obtenirTransformation() };

		glm::mat3 const& vm = glm::mat3(m);
		glm::mat3 const& normal = glm::inverse(vm);

		// Appliquer le nuanceur
		Programme::Start(programme_);
		programme_.assignerUniforme("modelViewProjection", m);
		programme_.assignerUniforme("matrNormale", normal);

		for (auto const& mesh : noeud.obtenirMeshes())
		{
			// Appliquer le matériau pour le mesh courant
			appliquerMateriau(mesh.obtenirMateriau());

			bool possedeNormales{ mesh.possedeNormales() };
			bool possedeCouleurs{ mesh.possedeCouleurs() };
			bool possedeTexCoords{ mesh.possedeTexCoords() };
			bool possedeSommets{ mesh.possedeSommets() };
			bool possedeFaces{ mesh.possedeFaces() };

			glVertexAttrib3f(3, couleur[0] / 255.0, couleur[1] / 255.0, couleur[2] / 255.0);

			if (possedeSommets)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableVertexAttribArray(VERTEX_LOCATION);
				glVertexAttribPointer(VERTEX_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			}
			if (possedeNormales)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				/// À Faire: Envoyer les normales aux nuanceurs si nécessaire
			}
			if (possedeTexCoords)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableVertexAttribArray(TEXCOORD_LOCATION);
				glVertexAttribPointer(TEXCOORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
			}
			if (possedeFaces)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(3 * mesh.obtenirFaces().size()), GL_UNSIGNED_INT, nullptr);
			}

			if (possedeSommets)
				glDisableVertexAttribArray(VERTEX_LOCATION);
			if (possedeTexCoords)
				glDisableVertexAttribArray(TEXCOORD_LOCATION);
		}
		Programme::Stop(programme_);

		/// Dessin récursif.
		for (auto const& n : noeud.obtenirEnfants())
		{
			dessiner(n, bufferIndex, couleur, m);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::liberer()
	///
	/// Relâche la mémoire sur la carte graphique.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::liberer()
	{
		for (auto const& handle : handles_)
		{
			glDeleteBuffers(static_cast<GLsizei>(handles_.size()), handles_.data());
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::appliquerMateriau(modele::Materiau const& materiau) const
	///
	/// Assigne un matériau OpenGL selon la méthode dépréciée d'illumination
	/// d'OpenGL
	///
	/// @param[in] materiau : le materiau à assigner
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::appliquerMateriau(modele::Materiau const& materiau) const
	{
		/// Vérifier si texture existe
		if (modele_->possedeTexture(materiau.nomTexture_)) {
			// Activer le texturage OpenGL et lier la texture appropriée
			glEnable(GL_TEXTURE_2D);
			glScalef(1.0, -1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, modele_->obtenirTextureHandle(materiau.nomTexture_));
		}
		else {
			// Désactiver le texturage OpenGL puisque cet objet n'a aucune texture
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

		/// Assigner le matériau
		///LUMIERE
		glm::vec3 positionL = glm::vec3(4.0, 1.0, 15.0);
		glm::vec3 diffuseL = glm::vec3(1.0, 1.0, 1.0);
		glm::vec3 speculaireL = glm::vec3(1.0, 1.0, 1.0);
		glm::vec3 ambiantL = glm::vec3(1.0, 1.0, 1.0);
		glm::vec3 directionSpot1 = glm::vec3(-5.0, -2.0, -10.0);
		glm::vec3 directionSpot2 = glm::vec3(3.0, 1.0, 15.0);
		float angleSpot1 = 20.0;
		float angleSpot2 = 10.0;
		float exposantSpot1 = 1.0;
		float exposantSpot2 = 1.0;


		programme_.assignerUniforme("positionL", positionL);
		programme_.assignerUniforme("diffuseL", diffuseL);
		programme_.assignerUniforme("speculaireL", speculaireL);
		programme_.assignerUniforme("ambiantL", ambiantL);
		programme_.assignerUniforme("directionSpot1", directionSpot1);
		programme_.assignerUniforme("directionSpot2", directionSpot2);
		programme_.assignerUniforme("angleSpot1", angleSpot1);
		programme_.assignerUniforme("angleSpot2", angleSpot2);
		programme_.assignerUniforme("exposantSpot1", exposantSpot1);
		programme_.assignerUniforme("exposantSpot2", exposantSpot2);


		///MATERIAU
		programme_.assignerUniforme("diffuse", materiau.diffuse_);
		programme_.assignerUniforme("speculaire", materiau.speculaire_);
		programme_.assignerUniforme("ambiant", materiau.ambiant_);
		programme_.assignerUniforme("emission", materiau.emission_);
		programme_.assignerUniforme("shininess", materiau.shininess_);

		///Modele de lumiere
		glm::vec3 ambient = glm::vec3(0.0, 0.0, 0.0);
		int obsLocal = 0;


		programme_.assignerUniforme("ambient", ambient);
		programme_.assignerUniforme("obsLocal", obsLocal);

		glPolygonMode(
			GL_FRONT_AND_BACK,
			materiau.filDeFer_ ? GL_LINE : GL_FILL);

		materiau.afficherDeuxCotes_ ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

	}
}