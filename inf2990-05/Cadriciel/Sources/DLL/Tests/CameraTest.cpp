////////////////////////////////////////////////////////////////////////////////////
/// @file CameraTest.cpp
/// @author Equipe 05
/// @date 2016-11-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "CameraTest.h"
#include "Camera.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(CameraTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::setUp()
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
void CameraTest::setUp()
{
	noeud = std::make_unique<vue::Camera>(glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
		glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::tearDown()
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
void CameraTest::tearDown()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void CameraTest::testDeplacerXY()
///
/// Cas de test: S'assure du déplacement de la camera dans le plan
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CameraTest::testDeplacerXY()
{
	glm::dvec3 testPosition = noeud->obtenirPosition();
	glm::dvec3 testPointtVise = noeud->obtenirPointVise();
	
	// Premier Test: valeurs initiales pour le déplacement de la camera
	// Test pour la position de la camera
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPosition[0] - 0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPosition[1] - 0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPosition[2] - 200));

	// Test pour le point visé par la camera
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPointtVise[0] - 0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPointtVise[1] - 0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPointtVise[2] - 0));

	// On modifie la position et le point visé
	noeud->assignerPosition(glm::dvec3(50, 100, 250));
	noeud->assignerPointVise(glm::dvec3(20, 30, 0));

	testPosition = noeud->obtenirPosition();
	testPointtVise = noeud->obtenirPointVise();

	// Deuxieme test: on vérifie que la position et le point visé ont été modifiés
	// Test pour la position de la camera
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPosition[0] - 50));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPosition[1] - 100));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPosition[2] - 250));

	// Test pour le point visé par la camera
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPointtVise[0] - 20));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPointtVise[1] - 30));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(testPointtVise[2] - 0));

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
