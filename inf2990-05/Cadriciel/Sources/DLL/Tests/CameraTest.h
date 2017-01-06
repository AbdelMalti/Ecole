//////////////////////////////////////////////////////////////////////////////
/// @file CameraTest.h
/// @author Equipe 05
/// @date 2016-11-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_CAMERATEST_H
#define _TESTS_CAMERATEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "Vue.h"

class Camera;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe NoeudAbstrait
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class CameraTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(CameraTest);
	CPPUNIT_TEST(testDeplacerXY);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	/// Cas de test: S'assure du d�placement de la camera dans le plan
	void testDeplacerXY();

private:
	/// Instance d'un noeud abstrait
	std::unique_ptr<vue::Camera> noeud;
};

#endif // _TESTS_CAMERATEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
