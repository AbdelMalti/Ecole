//////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.cpp
/// @author groupe05
/// @date 2016-11-08
/// @version 1.0
/// @addtogroup inf2990 
//////////////////////////////////////////////////////////////////////////////


#include "..\Tests\ProjectionOrthoTest.h"
#include "vue.h"
#include "Vue\ProjectionOrtho.h"
#include <iostream>
// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ProjectionOrthoTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::setUp()
{

	uneProjection = new vue::ProjectionOrtho {
		
		500, 500,
		1,1000,
		1, 10000,
		1.25,
		200,
		200
	};
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseAEchelleTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::tearDown()
{
	delete uneProjection;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::ZoomInTest()
///
/// Effectue un test de la methode zoomIn() pour augmenter la taille notre scene avec tous  ses elements
///
/// @return Aucun.
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::ZoomInTest()
{

	//vecteur servant aux get du return des coordonnées de la fenetre virtuelle avant et apres le zoomIn
	glm::dvec2 dimFenetre1;
	glm::dvec2 dimFenetre2;
	//valeur de l'increment
	double increment = 1.25;

	//on recupere les coordonnées de la fenetre avant le zoomIn
	dimFenetre1 = uneProjection->obtenirDimensionFenetreVirtuelle();
	//on fait un zoom in
	uneProjection->zoomerIn();

	//on recupere les coordonnées de la fenetre apres le zoomIn
	dimFenetre2 = uneProjection->obtenirDimensionFenetreVirtuelle();

	// on s assure de l egalité avec les coordonnées ainsi obtenues
	CPPUNIT_ASSERT(dimFenetre2[0] == dimFenetre1[0] - (dimFenetre1[0] * (increment - 1)));
	CPPUNIT_ASSERT(dimFenetre2[1] == dimFenetre1[1] - (dimFenetre1[1] * (increment - 1)));
}

void ProjectionOrthoTest::ZoomOutTest()
{

	//vecteur servant aux get du return des coordonnées de la fenetre virtuelle avant et apres le zoomout
	//
	glm::dvec2 dimFenetre1;
	glm::dvec2 dimFenetre2;
	//valeur de l'increment
	double increment = 1.25;

	//on recupere les coordonnées de la fenetre avant le zoomOut
	dimFenetre1 = uneProjection->obtenirDimensionFenetreVirtuelle();
	//on fait un zoom out
	uneProjection->zoomerOut();

	//on recupere les coordonnées de la fenetre apres le zoomerOut
	dimFenetre2 = uneProjection->obtenirDimensionFenetreVirtuelle();

	// on s assure de l egalité avec les coordonnées ainsi obtenues
	CPPUNIT_ASSERT(dimFenetre2[0] == dimFenetre1[0] + (dimFenetre1[0] * (increment - 1)));
	CPPUNIT_ASSERT(dimFenetre2[1] == dimFenetre1[1] + (dimFenetre1[1] * (increment - 1)));
}

void ProjectionOrthoTest::RedimensionerFenetreTest()
{
	glm::dvec2 dimFenetre1;
	glm::dvec2 dimFenetre2;
	glm::dvec2 dimCloture1;
	glm::dvec2 dimCloture2;
	dimCloture1 = uneProjection->obtenirDimensionCloture();
	dimFenetre1 = uneProjection->obtenirDimensionFenetreVirtuelle();
	int largeur1 = 255;
	int hauteur1 = 255;
	uneProjection->redimensionnerFenetre(largeur1, hauteur1);
	dimCloture2 = uneProjection->obtenirDimensionCloture();
	dimFenetre2 = uneProjection->obtenirDimensionFenetreVirtuelle();
	CPPUNIT_ASSERT(dimFenetre2[0] == dimFenetre1[0] + ((dimFenetre1[0] / dimCloture1[0])* largeur1 - dimFenetre1[0]));
	CPPUNIT_ASSERT(dimFenetre2[1] == dimFenetre1[1] + ((dimFenetre1[1] / dimCloture1[1])* hauteur1 - dimFenetre1[1]));
	CPPUNIT_ASSERT(dimCloture2[0] == largeur1);
	CPPUNIT_ASSERT(dimCloture2[1] == hauteur1);
	

}