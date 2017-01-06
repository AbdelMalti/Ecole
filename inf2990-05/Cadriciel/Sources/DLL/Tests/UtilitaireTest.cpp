////////////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.cpp
/// @author Julien Gascon-Samson modifie par Equipe 05
/// @date 2016-11-06
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#include "UtilitaireTest.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(UtilitaireTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::setUp()
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
void UtilitaireTest::setUp()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::tearDown()
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
void UtilitaireTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testLimite()
///
/// Cas de test: vérifie s'il est dans l'intervalle 
/// Ce test permet de tester si les objets mis sur la table sont dans
/// la zone de jeu. En effet, nous avons délimité la table à l'aide
/// de cette fonction, empêchant les objets de sortir des limites imposées
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testLimite()
{
	//On vérifie si une valeur quelconque se retrouve à l'intérieur de la zone de jeu
	// Dans notre cas, la zone de jeu (table) est définie de -70 à 70 en x et -16 à 16 en y
	CPPUNIT_ASSERT(utilitaire::DANS_LIMITESXY(5, -70, 70, 5, -16, 16) == true);

	//On vérifie si une valeur quelconque se retrouve bel et bien à l'extérieur de la zone de jeu
	CPPUNIT_ASSERT(utilitaire::DANS_LIMITESXY(-80, -70, 70, 5, -16, 16) == false);
}
