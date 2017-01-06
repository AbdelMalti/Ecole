//////////////////////////////////////////////////////////////////////////////
/// @file NoeudMailletTest.h
/// @author Equipe 05
/// @date 2016-11-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDMAILLET_TEST_H
#define _TESTS_NOEUDMAILLET_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
class NoeudMaillet;

#pragma once
class NoeudMailletTest : public CppUnit::TestFixture
{

	CPPUNIT_TEST_SUITE(NoeudMailletTest);
	CPPUNIT_TEST(testGetRayonMaillet);
	CPPUNIT_TEST(testSetRayonMaillet);
	CPPUNIT_TEST(testGetAngle);
	CPPUNIT_TEST(testSetAngle);
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void testGetRayonMaillet();
	void testSetRayonMaillet();

	void testGetAngle();
	void testSetAngle();

private:
	std::unique_ptr<NoeudMaillet> maillet;
	//NoeudMaillet* maillet;
	double rayonTest;
	double angleTest;
};

#endif // _TESTS_NOEUDMAILLET_TEST_H