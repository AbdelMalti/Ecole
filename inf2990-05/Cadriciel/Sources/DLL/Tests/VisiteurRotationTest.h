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
///        m�thodes de la classe VisiteurRotationTest
///
/// @author Jackie Phung
/// @date 2016-11-05
///////////////////////////////////////////////////////////////////////////
class VisiteurRotationTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurRotationTest);
	CPPUNIT_TEST(testRotation);
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

	/// Cas de test: faire tourner un objet dans le sens horaire ou anti-horaire d'une montre
	/// � l'aide du visiteur roation.
	/// Ce test permet de tester si le visiteur rotation fonctionne bien. Il est utile
	///de le tester, puisque l'�dition d'une zone de jeu est une partie importante du
	///livrable 1. Pour �diter, la rotation d'un objet est une partie tr�s importante.
	///De plus, il est aussi possible de v�rifier en m�me temps si la fonction
	///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
	///de chaque noeud est primordiale, car elle permet d'acc�der � tous nos visiteurs.
	void testRotation();

private:
	VisiteurRotation* visiteur;
};

#endif // _TESTS_VISITEURROTATIONTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


