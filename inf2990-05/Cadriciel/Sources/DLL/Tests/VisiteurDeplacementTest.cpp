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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// Cas de test: assigner une position de deplacement à l'aide du visiteur déplacement
/// Ce test permet de tester si le visiteur déplacement fonctionne bien. Il est utile
///de le tester, puisque l'édition d'une zone de jeu est une partie importante du
///livrable 1. Pour éditer, le déplacement d'objet est une partie très importante.
///De plus, il est aussi possible de vérifier en même temps si la fonction
///accepter(VisiteurAbstrait* visiteur) est fonctionnelle. La fonction accepter(...)
///de chaque noeud est primordiale, car elle permet d'accéder à tous nos visiteurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacementTest::testDeplacement()
{
	//// Premier test : on vérifie que la position initiale est un vector nul

	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getX()));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getY()));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getZ()));

	//// On modifie la position
	noeud->assignerPositionRelative(glm::dvec3{ 5.5, 5.5, 5.5 });

	//// Second test : on vérifie que la position a été modifiée
	
	noeud->accepter(visiteur);

	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getX() - 5.5));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getY() - 5.5));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(visiteur->getZ() - 5.5));
}