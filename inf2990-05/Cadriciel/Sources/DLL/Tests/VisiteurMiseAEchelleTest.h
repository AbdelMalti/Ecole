////////////////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAEchelleTest.h
/// @author Jackie Phung
/// @date 2016-11-05
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VISITEURMISEAECHELLETEST_H
#define _TESTS_VISITEURMISEAECHELLETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class VisiteurMiseEchelle;
class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurMiseAEchelleTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe VisiteurMiseAEchelleTest
///
/// @author Jackie Phung
/// @date 2016-11-05
///////////////////////////////////////////////////////////////////////////
class VisiteurMiseAEchelleTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurMiseAEchelleTest);
	CPPUNIT_TEST(testMiseAEchelle);
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

	/// Cas de test: agrandir ou diminuer un objet à l'aide du visiteur mise à l'échelle.
	/// Ce test permet de tester si le visiteur mise à l'échelle fonctionne bien. Il est utile
	///de le tester, puisque l'édition d'une zone de jeu est une partie importante du
	///livrable 1. Pour éditer, une mise à échelle d'un objet est une partie très importante.
	///De plus, il est aussi possible de vérifier en même temps si la fonction
	///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
	///de chaque noeud est primordiale, car elle permet d'accéder à tous nos visiteurs.
	void testMiseAEchelle();

private:
	VisiteurMiseEchelle* visiteur;
};

#endif // _TESTS_VISITEURMISEAECHELLETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

