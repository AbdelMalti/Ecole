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
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
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
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
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
/// Cas de test: v�rifie s'il est dans l'intervalle 
/// Ce test permet de tester si les objets mis sur la table sont dans
/// la zone de jeu. En effet, nous avons d�limit� la table � l'aide
/// de cette fonction, emp�chant les objets de sortir des limites impos�es
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testLimite()
{
	//On v�rifie si une valeur quelconque se retrouve � l'int�rieur de la zone de jeu
	// Dans notre cas, la zone de jeu (table) est d�finie de -70 � 70 en x et -16 � 16 en y
	CPPUNIT_ASSERT(utilitaire::DANS_LIMITESXY(5, -70, 70, 5, -16, 16) == true);

	//On v�rifie si une valeur quelconque se retrouve bel et bien � l'ext�rieur de la zone de jeu
	CPPUNIT_ASSERT(utilitaire::DANS_LIMITESXY(-80, -70, 70, 5, -16, 16) == false);
}
