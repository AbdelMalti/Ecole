//////////////////////////////////////////////////////////////////////////////
/// @file NoeudBonusTest.cpp
/// @author Equipe 05
/// @date 2016-11-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "NoeudBonusTest.h"
#include "NoeudBonus.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudBonusTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusTest::setUp()
{
	noeud = std::make_unique<NoeudBonus>(ArbreRenduINF2990::NOM_BONUS);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusTest::testAttribuerCouleur()
///
/// Cas de test: d�finition/obtention des �tats de s�lection du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudBonusTest::testAttribuerCouleur()
{
	// On r�cup�re la premi�re couleur de l'objet
	GLubyte testCouleur[3];
	testCouleur[0] = noeud->getCouleur1();
	testCouleur[1] = noeud->getCouleur2();
	testCouleur[2] = noeud->getCouleur3();

	// Test : on v�rifie que la premi�re couleur de l'objet est la bonne
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testCouleur[0] - 0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testCouleur[1] - 100));
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(testCouleur[2], 155, 255));

}
