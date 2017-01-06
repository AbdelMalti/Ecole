///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author Equipe 05
/// @date 2016-09-18
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTable.h"
#include "Texture.h"
#include "ArbreRenduINF2990.h"
#include "NoeudMaillet.h"
#include "NoeudRondelle.h"

#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "OpenGL_Programme.h"
#include "OpenGL_Nuanceur.h"

using namespace opengl;

static Programme programme_;
static Nuanceur nuanceurFragment_;
static Nuanceur nuanceurSommet_;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::NoeudTable(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(const std::string& typeNoeud) : NoeudComposite{ typeNoeud }
{
	pointDeControle_[0] = glm::vec3(70, -54, 0.0);        // Sommet P0
	pointDeControle_[1] = glm::vec3(70, 0.0, 0.0);        // Sommet P1
	pointDeControle_[2] = glm::vec3(70, 54, 0.0);         // Sommet P2
	pointDeControle_[3] = glm::vec3(0.0, -54, 0.0);       // Sommet P3
	pointDeControle_[4] = glm::vec3(0.0, 54, 0.0);        // Sommet P4
	pointDeControle_[5] = glm::vec3(-70, -54, 0.0);       // Sommet P5
	pointDeControle_[6] = glm::vec3(-70, 0.0, 0.0);       // Sommet P6
	pointDeControle_[7] = glm::vec3(-70, 54, 0.0);        // Sommet P7
	pointDeControle_[8] = glm::vec3(0.0, 0.0, 0.0);       // Sommet P8
	
	//coefficientFriction_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::~NoeudTable()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::getPositionX() const
///
/// Cet fonction permet d'obtenir la position en X
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
double NoeudTable::getPositionX() const
{
	return pointDeControle_[1].x;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::getPositionY() const
///
/// Cet fonction permet d'obtenir la position en Y
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
double NoeudTable::getPositionY() const
{
	return pointDeControle_[4].y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::getPositionZ() const
///
/// Cet fonction permet d'obtenir la position en Z
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
double NoeudTable::getPositionZ() const
{
	return pointDeControle_[1].z;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::getCoefficientFriction()
///
/// Cet fonction permet d'obtenir le coefficient de friction de la table
///
/// @return le coefficient de friction.
///
////////////////////////////////////////////////////////////////////////
float NoeudTable::getCoefficientFriction()
{
	return coefficientFriction_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @param[in] estColore : Permet de savoir selection par couleur est active pour l'objet
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
	/// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(vueProjection, estColore);
	
	Programme::Start(programme_);
	programme_.assignerUniforme("modelViewProjection", vueProjection);

	if (!programme_.estInitialise())
	{
		// Initialisation des nuanceurs OpenGL_VBO.cpp
		nuanceurSommet_.initialiser(Nuanceur::Type::NUANCEUR_VERTEX, "nuanceurs/sommet.glsl");
		nuanceurFragment_.initialiser(Nuanceur::Type::NUANCEUR_FRAGMENT, "nuanceurs/table_fragment.glsl");
		programme_.initialiser();
		programme_.attacherNuanceur(nuanceurFragment_);
		programme_.attacherNuanceur(nuanceurSommet_);
	}

	glPushMatrix(); 

	GLuint connecTable[] = { 0, 1, 3,                // Connexion triangle t0t1t3
		1, 2, 4,                // Connexion triangle t1t2t4
		3, 1, 4,                // Connexion triangle t3t1t4
		6, 4, 7,                // Connexion triangle t6t4t7
		6, 3, 4,                // Connexion triangle t6t3t4
		3, 6, 5 };              // Connexion triangle t3t6t5


								/// Les points de controle internes
	glm::vec3 t0 = glm::vec3(pointDeControle_[0].x, pointDeControle_[0].y, pointDeControle_[0].z);
	glm::vec3 t1 = glm::vec3(pointDeControle_[1].x, pointDeControle_[1].y, pointDeControle_[1].z);
	glm::vec3 t2 = glm::vec3(pointDeControle_[2].x, pointDeControle_[2].y, pointDeControle_[2].z);
	glm::vec3 t3 = glm::vec3(pointDeControle_[3].x, pointDeControle_[3].y, pointDeControle_[3].z);
	glm::vec3 t4 = glm::vec3(pointDeControle_[4].x, pointDeControle_[0].y, pointDeControle_[0].z);
	glm::vec3 t5 = glm::vec3(pointDeControle_[5].x, pointDeControle_[5].y, pointDeControle_[5].z);
	glm::vec3 t6 = glm::vec3(pointDeControle_[6].x, pointDeControle_[6].y, pointDeControle_[6].z);
	glm::vec3 t7 = glm::vec3(pointDeControle_[7].x, pointDeControle_[7].y, pointDeControle_[7].z);



	/// Les points de controle externes
	glm::vec3 p0 = glm::vec3(t0.x + 4, t0.y - 4, t0.z);
	glm::vec3 p1 = glm::vec3(t1.x + 4, t1.y, t1.z);
	glm::vec3 p2 = glm::vec3(t2.x + 4, t2.y + 4, t2.z);
	glm::vec3 p3 = glm::vec3(t3.x, t3.y - 4, t3.z);
	glm::vec3 p4 = glm::vec3(t4.x, t4.y + 4, t4.z);
	glm::vec3 p5 = glm::vec3(t5.x - 4, t5.y - 4, t5.z);
	glm::vec3 p6 = glm::vec3(t6.x - 4, t6.y, t6.z);
	glm::vec3 p7 = glm::vec3(t7.x - 4, t7.y + 4, t7.z);

	/// Les points pour les goals
	glm::vec3 g1 = glm::vec3(t1.x, t1.y + 10, t1.z); // Pour le goal droit
	glm::vec3 g2 = glm::vec3(t1.x, t1.y - 10, t1.z); // Pour le goal droit
	glm::vec3 g3 = glm::vec3(t6.x, t6.y + 10, t6.z); // Pour le goal gauche
	glm::vec3 g4 = glm::vec3(t6.x, t6.y - 10, t6.z); // Pour le goal gauche

   // Tableau des sommets pour dessiner la bordure externe de la table
	GLfloat bordureExt[] = { p0.x, p0.y, p0.z + 5, p0.x, p0.y, p0.z - 5, p2.x, p2.y, p2.z - 5, p2.x, p2.y, p2.z + 5, //Bordure exterieure de droite
		p2.x, p2.y, p2.z + 5, p2.x, p2.y, p2.z - 5, p7.x, p7.y, p7.z - 5, p7.x, p7.y, p7.z + 5, //Bordure exterieure du haut
		p7.x, p7.y, p7.z + 5, p7.x, p7.y, p7.z - 5, p5.x, p5.y, p5.z - 5, p5.x, p5.y, p5.z + 5, //Bordure exterieure de gauche
		p5.x, p5.y, p5.z + 5, p5.x, p5.y, p5.z - 5, p0.x, p0.y, p0.z - 5, p0.x, p0.y, p0.z + 5  //Bordure exterieure du bas
	};


	// Tableau des sommets pour dessiner la bordure interne de la table
	GLfloat bordureInt[] = { t0.x, t0.y, t0.z - 5, t0.x, t0.y, t0.z + 5, g2.x, g2.y, g2.z + 5, g2.x, g2.y, g2.z - 5, //Bordure interieure de droite1
		g1.x, g1.y, g1.z - 5, g1.x, g1.y, g1.z + 5, t2.x, t2.y, t2.z + 5, t2.x, t2.y, t2.z - 5, //Bordure interieure de droite2
		t2.x, t2.y, t2.z - 5, t2.x, t2.y, t2.z + 5, t7.x, t7.y, t7.z + 5, t7.x, t7.y, t7.z - 5, //Bordure interieure du haut
		t7.x, t7.y, t7.z - 5, t7.x, t7.y, t7.z + 5, g3.x, g3.y, g3.z + 5, g3.x, g3.y, g3.z - 5, //Bordure interieure de gauche1
		g4.x, g4.y, g4.z - 5, g4.x, g4.y, g4.z + 5, t5.x, t5.y, t5.z + 5, t5.x, t5.y, t5.z - 5, //Bordure interieure de gauche2                     
		t5.x, t5.y, t5.z - 5, t5.x, t5.y, t5.z + 5, t0.x, t0.y, t0.z + 5, t0.x, t0.y, t0.z - 5  //Bordure interieure du bas
	};



	// Tableau des sommets pour dessiner la couronne des bordures de la table
	GLfloat bordureCour[] = { p0.x, p0.y, p0.z, p2.x, p2.y, p2.z, t2.x, t2.y, t2.z, t0.x, t0.y, t0.z, //Couronne de droite
		t2.x, t2.y, t2.z, p2.x, p2.y, p2.z, p7.x, p7.y, p7.z, t7.x, t7.y, t7.z, //Couronne du haut
		p7.x, p7.y, p7.z, p5.x, p5.y, p5.z, t5.x, t5.y, t5.z, t7.x, t7.y, t7.z, //Couronne de gauche
		p5.x, p5.y, p5.z, p0.x, p0.y, p0.z, t0.x, t0.y, t0.z, t5.x, t5.y, t5.z  //Couronne du bas
	};



	// Tableau des sommets pour dessiner les goals
	GLfloat goals[] = { g1.x, g1.y, g1.z + 5, g1.x, g1.y, g1.z - 5, g2.x, g2.y, g2.z - 5, g2.x, g2.y, g2.z + 5, //Pour le goal de droite
		g4.x, g4.y, g4.z + 5, g4.x, g4.y, g4.z - 5, g3.x, g3.y, g3.z - 5, g3.x, g3.y, g3.z + 5, //Pour le goal de gauche                    
	};



	GLuint vao = 0;
	// initialiser le VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo[6];
	glGenBuffers(6, vbo);

	//** Dessin de la surface de la table **//

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureSurfaceTable());

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //vbo pour sommets
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointDeControle_), pointDeControle_, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]); //vbo pour connectivité
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(connecTable), connecTable, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisable(GL_TEXTURE_2D);


	//** Dessin de la bordure exterieure de la table **//
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordureTable(3));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bordureExt), bordureExt, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_QUADS, 0, 16);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisable(GL_TEXTURE_2D);


	//** Dessin de la bordure interieure de la table **//
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordureTable(3));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bordureInt), bordureInt, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisable(GL_TEXTURE_2D);


	//** Dessin de la couronne de la bordure de la table **//
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordureTable(3));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bordureCour), bordureCour, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_QUADS, 0, 16);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisable(GL_TEXTURE_2D);



	//** Dessin de goals **//
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordureTable(2));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(goals), goals, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_QUADS, 0, 8);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisable(GL_TEXTURE_2D);




	//** Dessin de la ligne separatrice de la table **//
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureLigneSeparatriceTable());

	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex3f(pointDeControle_[3].x, pointDeControle_[3].y, pointDeControle_[3].z + 0.1);
	glVertex3f(pointDeControle_[4].x, pointDeControle_[4].y, pointDeControle_[4].z + 0.1);
	glEnd();

	glDisable(GL_TEXTURE_2D);



	/*/// Bordures de la table avec les glVertex

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordureTable(3));

	/// Bordure gauche
	glBegin(GL_QUADS); glVertex3f(pointDeControle_[7].x, pointDeControle_[7].y, pointDeControle_[7].z - 5); glVertex3f(pointDeControle_[7].x, pointDeControle_[7].y, pointDeControle_[7].z + 5);
	glVertex3f(pointDeControle_[5].x, pointDeControle_[5].y, pointDeControle_[5].z + 5); glVertex3f(pointDeControle_[5].x, pointDeControle_[5].y, pointDeControle_[5].z - 5); glEnd();

	glBegin(GL_QUADS); glVertex3f(pointDeControle_[7].x - 4, pointDeControle_[7].y + 4, pointDeControle_[7].z - 5); glVertex3f(pointDeControle_[7].x - 4, pointDeControle_[7].y + 4, pointDeControle_[7].z + 5);
	glVertex3f(pointDeControle_[5].x - 4, pointDeControle_[5].y + 4, pointDeControle_[5].z + 5); glVertex3f(pointDeControle_[5].x - 4, pointDeControle_[5].y + 4, pointDeControle_[5].z - 5); glEnd();

	glBegin(GL_QUADS); glVertex3f(pointDeControle_[7].x, pointDeControle_[7].y, pointDeControle_[7].z + 5); glVertex3f(pointDeControle_[7].x - 4, pointDeControle_[7].y + 4, pointDeControle_[7].z + 5);
	glVertex3f(pointDeControle_[5].x - 4, pointDeControle_[5].y + 4, pointDeControle_[5].z + 5); glVertex3f(pointDeControle_[5].x, pointDeControle_[5].y, pointDeControle_[5].z + 5); glEnd();

	glDisable(GL_TEXTURE_2D); */


	Programme::Stop(programme_);
	glPopMatrix();

}

//////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
