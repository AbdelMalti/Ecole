////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
/// @author Julien Gascon-Samson modifie par Equipe 05
/// @date 2016-11-06
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDCOMPOSITETEST_H
#define _TESTS_NOEUDCOMPOSITETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "NoeudTable.h"
#include "NoeudMaillet.h"
#include "NoeudBonus.h"
#include "ArbreRenduINF2990.h"

class NoeudComposite;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCompositeTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe NoeudCompositeTest
///
/// @author Julien Gascon-Samson modifie par Equipe 05
/// @date 2016-11-06
///////////////////////////////////////////////////////////////////////////
class NoeudCompositeTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudCompositeTest);
	CPPUNIT_TEST(testEffacerSelection);
	CPPUNIT_TEST(testTuerRondelle);
	CPPUNIT_TEST(testObtenirNombreEnfants);
	CPPUNIT_TEST(testVider);
	CPPUNIT_TEST(chercherTest);
	CPPUNIT_TEST(testDeselectionnerTout);
	//CPPUNIT_TEST(afficherConcretTest);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================

	/// Cas de test: effacer une selection(un objet sélectionné) 
	/// Ce test permet de tester si la fonction effacerSelection() fonctionne bien.
	/// Il est utile de le tester, puisque l'édition d'une zone de jeu est une partie
	/// importante du livrable 1. Pour éditer, la suppression d'un objet est une
	/// partie très importante. De plus, il est aussi possible de vérifier en même
	/// temps si la fonction ajouter(NoeudAbstrait* enfant) est fonctionnelle.
	/// La fonction ajouter(...) est primordiale, car elle permet d'ajouter
	/// différents enfants à notre arbre permettant alors de les manipuler
	void testEffacerSelection();

	/// Cas de test: tuer la rondelle
	/// Ce test permet de tester si la fonction tuerRondelle() fonctionne bien.
	/// Il est utile de le tester, puisque nous devons être capable de tuer la
	/// rondelle lorsque nous passons du mode test au mode d'édition, ainsi que
	/// lorsque nous sortons de partie rapide et de tournoi. En effet, nous ne
	/// devons plus voir la rondelle sur la table rendu en mode d'édition.
	/// De plus, il est intéressant de le tester, car le bon fonctionnement
	/// de celle-ci implique que les fonctions pour tuer les 2 maillets sont
	/// également fonctionnelles.
	void testTuerRondelle();

	/// Cas de test: On teste le nombre d'enfants d'un noeud composite (NoeudTable )
	void testObtenirNombreEnfants();

	/// Cas de test: On teste la methode qui vide un noeud derivant du noeud composite de
	/// ses enfants
	void testVider();

	///cas de test: on teste la methode qui s'occupe de la recherche des enfants de 
	///l arbre selon leurs noms et renvoie un null si l enfant n est pas dans l arbre
	///ou l enfant s il est dans l arbre
	void chercherTest();

	///cas de test: on teste la methode qui s'occupe d'afficher les enfant de l'arbre
	///bien sure que cette derive de la la classe noeud abstrait. 
	void afficherConcretTest();

	/// Cas de test: On test s'il est possible de déselectionner tous les objets sélectionnés
	void testDeselectionnerTout();

private:
	std::unique_ptr<NoeudComposite> table;
	int nombreEnfants;
};

#endif // _TESTS_NOEUDCOMPOSITETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////




