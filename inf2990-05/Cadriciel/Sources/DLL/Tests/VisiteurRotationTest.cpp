////////////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotationTest.cpp
/// @author Jackie Phung
/// @date 2016-11-05
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#include "VisiteurRotationTest.h"
#include "NoeudBonus.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "../Visiteurs/VisiteurRotation.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(VisiteurRotationTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotationTest::setUp()
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
void VisiteurRotationTest::setUp()
{
	visiteur = new VisiteurRotation();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotationTest::tearDown()
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
void VisiteurRotationTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotationTest::testRotation()
///
/// Cas de test: faire tourner un objet dans le sens horaire ou anti-horaire d'une montre
/// � l'aide du visiteur roation.
/// Ce test permet de tester si le visiteur rotation fonctionne bien. Il est utile
///de le tester, puisque l'�dition d'une zone de jeu est une partie importante du
///livrable 1. Pour �diter, la rotation d'un objet est une partie tr�s importante.
///De plus, il est aussi possible de v�rifier en m�me temps si la fonction
///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
///de chaque noeud est primordiale, car elle permet d'acc�der � tous nos visiteurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotationTest::testRotation()
{
	//// on v�rifie si l'angle de rotation est nul au d�part � la cr�ation de l'objet
	
	NoeudBonus* bonus = new NoeudBonus("bonus");

	CPPUNIT_ASSERT(bonus->getAngleRotation() == 0);

	//// on v�rifie si l'angle de rotation est plus grand que son angle de d�part
	//// lorsqu'on donne un delta de 0.1. C'est-�-dire lorsqu'il tourne dans le sens
	//// horaire d'une montre � une indentation de 0.1.

	bonus->setAngleRotation(0);
	visiteur->setDelta(0.1);

	bonus->accepter(visiteur);

	CPPUNIT_ASSERT(bonus->getAngleRotation() > 0);

}