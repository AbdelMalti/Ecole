////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
/// @author Julien Gascon-Samson modifie par Equipe 05
/// @date 2016-11-06
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_UTILITAIRETEST_H
#define _TESTS_UTILITAIRETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

///////////////////////////////////////////////////////////////////////////
/// @class UtilitaireTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe UtilitaireTest
///
/// @author Julien Gascon-Samson modifie par Equipe 05
/// @date 2016-11-06
///////////////////////////////////////////////////////////////////////////
class UtilitaireTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	// =================================================================
	CPPUNIT_TEST_SUITE(UtilitaireTest);
	CPPUNIT_TEST(testLimite);
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

	/// Cas de test: v�rifie s'il est dans l'intervalle 
	/// Ce test permet de tester si les objets mis sur la table sont dans
	/// la zone de jeu. En effet, nous avons d�limit� la table � l'aide
	/// de cette fonction, emp�chant les objets de sortir des limites impos�es
	void testLimite();

private:

};

#endif // _TESTS_UTILITAIRETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
