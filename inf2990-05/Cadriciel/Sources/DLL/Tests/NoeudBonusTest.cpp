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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// Cas de test: définition/obtention des états de sélection du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudBonusTest::testAttribuerCouleur()
{
	// On récupère la première couleur de l'objet
	GLubyte testCouleur[3];
	testCouleur[0] = noeud->getCouleur1();
	testCouleur[1] = noeud->getCouleur2();
	testCouleur[2] = noeud->getCouleur3();

	// Test : on vérifie que la première couleur de l'objet est la bonne
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testCouleur[0] - 0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testCouleur[1] - 100));
	CPPUNIT_ASSERT(utilitaire::DANS_INTERVALLE(testCouleur[2], 155, 255));

}
