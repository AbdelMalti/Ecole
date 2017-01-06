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
///        m�thodes de la classe VisiteurDeplacement
///
/// @author Jackie Phung
/// @date 2016-11-05
///////////////////////////////////////////////////////////////////////////
class VisiteurDeplacementTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurDeplacementTest);
	CPPUNIT_TEST(testDeplacement);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test: assigner une position de deplacement � l'aide du visiteur d�placement
	/// Ce test permet de tester si le visiteur d�placement fonctionne bien. Il est utile
	///de le tester, puisque l'�dition d'une zone de jeu est une partie importante du
	///livrable 1. Pour �diter, le d�placement d'objet est une partie tr�s importante.
	///De plus, il est aussi possible de v�rifier en m�me temps si la fonction
	///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
	///de chaque noeud est primordiale, car elle permet d'acc�der � tous nos visiteurs.
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
