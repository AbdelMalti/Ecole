////////////////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAEchelleTest.cpp
/// @author Jackie Phung
/// @date 2016-11-05
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#include "VisiteurMiseAEchelleTest.h"
#include "NoeudBonus.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "../Visiteurs/VisiteurMiseEchelle.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(VisiteurMiseAEchelleTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseAEchelleTest::setUp()
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
void VisiteurMiseAEchelleTest::setUp()
{
	visiteur = new VisiteurMiseEchelle();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseAEchelleTest::tearDown()
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
void VisiteurMiseAEchelleTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseAEchelleTest::testMiseAEchelle()
///
/// Cas de test: agrandir ou diminuer un objet � l'aide du visiteur mise � l'�chelle.
/// Ce test permet de tester si le visiteur mise � l'�chelle fonctionne bien. Il est utile
///de le tester, puisque l'�dition d'une zone de jeu est une partie importante du
///livrable 1. Pour �diter, une mise � �chelle d'un objet est une partie tr�s importante.
///De plus, il est aussi possible de v�rifier en m�me temps si la fonction
///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
///de chaque noeud est primordiale, car elle permet d'acc�der � tous nos visiteurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelleTest::testMiseAEchelle()
{
	//// on v�rifie si le rayon est plus grand que son rayon initial que
	////nous donnons lorsque nous for�ons un facteur d'�chelle
	NoeudBonus* bonus = new NoeudBonus("bonus");
	bonus->setRayonBonus(1);
	visiteur->setFacteur(2);
	
	bonus->accepter(visiteur);

	CPPUNIT_ASSERT(bonus->getRayonBonus() > 1);

}