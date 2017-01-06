////////////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotationTest.h
/// @author Jackie Phung
/// @date 2016-11-05
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VISITEURROTATIONTEST_H
#define _TESTS_VISITEURROTATIONTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class VisiteurRotation;
class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurRotationTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe VisiteurRotationTest
///
/// @author Jackie Phung
/// @date 2016-11-05
///////////////////////////////////////////////////////////////////////////
class VisiteurRotationTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurRotationTest);
	CPPUNIT_TEST(testRotation);
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

	/// Cas de test: faire tourner un objet dans le sens horaire ou anti-horaire d'une montre
	/// à l'aide du visiteur roation.
	/// Ce test permet de tester si le visiteur rotation fonctionne bien. Il est utile
	///de le tester, puisque l'édition d'une zone de jeu est une partie importante du
	///livrable 1. Pour éditer, la rotation d'un objet est une partie très importante.
	///De plus, il est aussi possible de vérifier en même temps si la fonction
	///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
	///de chaque noeud est primordiale, car elle permet d'accéder à tous nos visiteurs.
	void testRotation();

private:
	VisiteurRotation* visiteur;
};

#endif // _TESTS_VISITEURROTATIONTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


