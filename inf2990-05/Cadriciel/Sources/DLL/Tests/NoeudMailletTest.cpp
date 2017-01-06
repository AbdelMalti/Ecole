#include "NoeudMailletTest.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include"NoeudMaillet.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NoeudMailletTest);


void NoeudMailletTest::setUp()
{
	rayonTest = 8.0;
	angleTest = 60;
	maillet = std::make_unique<NoeudMaillet>(ArbreRenduINF2990::NOM_MAILLET, rayonTest, angleTest);
}

void NoeudMailletTest::tearDown()
{
}

void NoeudMailletTest::testGetRayonMaillet()
{
	double rayonTest_ = maillet->getRayonMaillet();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(rayonTest_ - rayonTest));
	
}

void NoeudMailletTest::testSetRayonMaillet()
{
	double rayonTest_ = 40;
	maillet->setRayonMaillet(rayonTest_);
	double rayonGet_ = maillet->getRayonMaillet();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(rayonGet_ - rayonTest_));
}

void NoeudMailletTest::testGetAngle()
{
	double angleTest_ = maillet->getAngleRotation();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(angleTest_ - angleTest));
}

void NoeudMailletTest::testSetAngle()
{
	double angleTest_ = 60;
	maillet->setAngleRotation(angleTest_);
	double angleGet_ = maillet->getAngleRotation();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(angleGet_ - angleTest_));
}
