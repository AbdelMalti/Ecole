////////////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacementTest.cpp
/// @author Jackie Phung
/// @date 2016-11-05
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#include "VisiteurDeplacementTest.h"
#include "NoeudBonus.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "../Visiteurs/VisiteurDeplacement.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(VisiteurDeplacementTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacementTest::setUp()
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
void VisiteurDeplacementTest::setUp()
{
	noeud = std::make_unique<NoeudBonus>(ArbreRenduINF2990::NOM_BONUS);
	visiteur = new VisiteurDeplacement();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacementTest::tearDown()
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
void VisiteurDeplacementTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacementTest::testDeplacement()
///
/// Cas de test: assigner une position de deplacement � l'aide du visiteur d�placement
/// Ce test permet de tester si le visiteur d�placement fonctionne bien. Il est utile
///de le tester, puisque l'�dition d'une zone de jeu est une partie importante du
///livrable 1. Pour �diter, le d�placement d'objet est une partie tr�s importante.
///De plus, il est aussi possible de v�rifier en m�me temps si la fonction
///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
///de chaque noeud est primordiale, car elle permet d'acc�der � tous nos visiteurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacementTest::testDeplacement()
{
	//// Premier test : on v�rifie que la position initiale est un vector nul

	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getX()));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getY()));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getZ()));

	//// On modifie la position
	noeud->assignerPositionRelative(glm::dvec3{ 5.5, 5.5, 5.5 });

	//// Second test : on v�rifie que la position a �t� modifi�e
	
	noeud->accepter(visiteur);

	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getX() - 5.5));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getY() - 5.5));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getZ() - 5.5));
}