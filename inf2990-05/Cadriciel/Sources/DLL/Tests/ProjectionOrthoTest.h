#pragma once
////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// @author groupe05
/// @date 2016-11-08
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_PROJECTIONORTHOTEST_H
#define _TESTS_PROJECTIONORTHOTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include<ProjectionOrtho.h>

///////////////////////////////////////////////////////////////////////////
/// @class ProjectionOrthoTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe ZoomIn
///
/// @author GROUPE05
/// @date 2016-11-08
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(ProjectionOrthoTest);
	CPPUNIT_TEST(ZoomOutTest);
	CPPUNIT_TEST(ZoomInTest);
	CPPUNIT_TEST(RedimensionerFenetreTest);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================

	/// Cas de test: agrandir, diminuer la zonne de jeu et tous les elements qui s y trouve.
	/// la classe Projection Ortho nous permet de faire plusieurs operations sur notre fenetre 
	///nous permet en fait d agrandir notre surface de jeu. et c est une classe  
	///importante pour notre livrable 1.

	/// Cas de test: agrandir la zone de jeu et tous les elements qui s y trouve et s assurer que cela se fait correctement.
	void ZoomInTest();
	/// Cas de test: diminuer la zone de jeu et tous les elements qui s y trouveet s assurer que cela se fait correctement.
	void ZoomOutTest();
	/// /// Cas de test:ajuster la fenetre virtuelle et s assurer que cela se fait correctement.
	void RedimensionerFenetreTest();

private:
	vue::ProjectionOrtho *uneProjection;
};

#endif // _TESTS_PROJECTIONORTHOTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


