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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// à l'aide du visiteur roation.
/// Ce test permet de tester si le visiteur rotation fonctionne bien. Il est utile
///de le tester, puisque l'édition d'une zone de jeu est une partie importante du
///livrable 1. Pour éditer, la rotation d'un objet est une partie très importante.
///De plus, il est aussi possible de vérifier en même temps si la fonction
///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
///de chaque noeud est primordiale, car elle permet d'accéder à tous nos visiteurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotationTest::testRotation()
{
	//// on vérifie si l'angle de rotation est nul au départ à la création de l'objet
	
	NoeudBonus* bonus = new NoeudBonus("bonus");

	CPPUNIT_ASSERT(bonus->getAngleRotation() == 0);

	//// on vérifie si l'angle de rotation est plus grand que son angle de départ
	//// lorsqu'on donne un delta de 0.1. C'est-à-dire lorsqu'il tourne dans le sens
	//// horaire d'une montre à une indentation de 0.1.

	bonus->setAngleRotation(0);
	visiteur->setDelta(0.1);

	bonus->accepter(visiteur);

	CPPUNIT_ASSERT(bonus->getAngleRotation() > 0);

}