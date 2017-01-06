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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// Cas de test: agrandir ou diminuer un objet à l'aide du visiteur mise à l'échelle.
/// Ce test permet de tester si le visiteur mise à l'échelle fonctionne bien. Il est utile
///de le tester, puisque l'édition d'une zone de jeu est une partie importante du
///livrable 1. Pour éditer, une mise à échelle d'un objet est une partie très importante.
///De plus, il est aussi possible de vérifier en même temps si la fonction
///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
///de chaque noeud est primordiale, car elle permet d'accéder à tous nos visiteurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelleTest::testMiseAEchelle()
{
	//// on vérifie si le rayon est plus grand que son rayon initial que
	////nous donnons lorsque nous forçons un facteur d'échelle
	NoeudBonus* bonus = new NoeudBonus("bonus");
	bonus->setRayonBonus(1);
	visiteur->setFacteur(2);
	
	bonus->accepter(visiteur);

	CPPUNIT_ASSERT(bonus->getRayonBonus() > 1);

}