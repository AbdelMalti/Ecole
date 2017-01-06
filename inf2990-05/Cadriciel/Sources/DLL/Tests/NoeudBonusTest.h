//////////////////////////////////////////////////////////////////////////////
/// @file NoeudBonusTest.h
/// @author Equipe 05
/// @date 2016-11-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDBONUSTEST_H
#define _TESTS_NOEUDBONUSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class NoeudBonus;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe NoeudAbstrait
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class NoeudBonusTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudBonusTest);
	CPPUNIT_TEST(testAttribuerCouleur);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	/// Cas de test: attribution de couleur au noeud
	void testAttribuerCouleur();

private:
	/// Instance d'un noeud abstrait
	std::unique_ptr<NoeudBonus> noeud;
};

#endif // _TESTS_NOEUDBONUSTEST_H