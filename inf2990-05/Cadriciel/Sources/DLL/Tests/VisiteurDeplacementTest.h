////////////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacementTest.h
/// @author Jackie Phung
/// @date 2016-11-05
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VISITEURDEPLACEMENTTEST_H
#define _TESTS_VISITEURDEPLACEMENTTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class VisiteurDeplacement;
class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeplacementTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe VisiteurDeplacement
///
/// @author Jackie Phung
/// @date 2016-11-05
///////////////////////////////////////////////////////////////////////////
class VisiteurDeplacementTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurDeplacementTest);
	CPPUNIT_TEST(testDeplacement);
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

	/// Cas de test: assigner une position de deplacement à l'aide du visiteur déplacement
	/// Ce test permet de tester si le visiteur déplacement fonctionne bien. Il est utile
	///de le tester, puisque l'édition d'une zone de jeu est une partie importante du
	///livrable 1. Pour éditer, le déplacement d'objet est une partie très importante.
	///De plus, il est aussi possible de vérifier en même temps si la fonction
	///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
	///de chaque noeud est primordiale, car elle permet d'accéder à tous nos visiteurs.
	void testDeplacement();

private:
	/// Instance d'un noeud abstrait
	std::unique_ptr<NoeudAbstrait> noeud;
	VisiteurDeplacement* visiteur;
};

#endif // _TESTS_VISITEURDEPLACEMENTTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
