////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author Julien Gascon-Samson modifie par Equipe 05
/// @date 2016-11-06
/// @version 1.0
/// @INF2990
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"
#include "NoeudBonus.h"
#include "NoeudPortail.h"
#include "NoeudMuret.h"
#include "NoeudMaillet.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "NoeudTable.h"
#include "NoeudRondelle.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
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
void NoeudCompositeTest::setUp()
{
	table = std::make_unique<NoeudTable>(ArbreRenduINF2990::NOM_TABLE);
	nombreEnfants = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSupprimerTest::tearDown()
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
void NoeudCompositeTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacerSelection()
///
/// Cas de test: effacer une selection(un objet sélectionné) 
/// Ce test permet de tester si la fonction effacerSelection() fonctionne bien.
/// Il est utile de le tester, puisque l'édition d'une zone de jeu est une partie
/// importante du livrable 1. Pour éditer, la suppression d'un objet est une
/// partie très importante. De plus, il est aussi possible de vérifier en même
/// temps si la fonction ajouter(NoeudAbstrait* enfant) est fonctionnelle.
/// La fonction ajouter(...) est primordiale, car elle permet d'ajouter
/// différents enfants à notre arbre permettant alors de les manipuler
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacerSelection()
{
	// On vérifie qu'initialement, la table n'a pas d'enfant
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 1);

	// Essaie d'ajouter un noeud
	NoeudBonus* bonus = new NoeudBonus("bonus");
	table->ajouter(bonus);

	// On vérifie si le bonus a été ajouté
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 2);
	
	// On sélectionne le bonus et appeler la fonction pour le supprimer
	bonus->assignerSelection(true);
	table->effacerSelection();

	// On vérifie que la table n'a plus d'enfant après l'effacement
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 1);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testTuerRondelle()
///
/// Cas de test: tuer la rondelle
/// Ce test permet de tester si la fonction tuerRondelle() fonctionne bien.
/// Il est utile de le tester, puisque nous devons être capable de tuer la
/// rondelle lorsque nous passons du mode test au mode d'édition, ainsi que
/// lorsque nous sortons de partie rapide et de tournoi. En effet, nous ne
/// devons plus voir la rondelle sur la table rendu en mode d'édition.
/// De plus, il est intéressant de le tester, car le bon fonctionnement
/// de celle-ci implique que les fonctions pour tuer les 2 maillets sont
/// également fonctionnelles.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testTuerRondelle()
{
	// On vérifie qu'initialement, la table n'a pas d'enfant
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 1);

	// Essaie d'ajouter une rondelle
	NoeudRondelle* rondelle = new NoeudRondelle("rondelle");
	table->ajouter(rondelle);

	// On vérifie si la rondelle a été ajouté
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 2);

	// On appeler la fonction pour tuer la rondelle
	table->tuerRondelle();

	// On vérifie que la table n'a plus d'enfant après l'effacement
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testObtenirNombreEnfants()
///
/// Cas de test: nombre d'enfants du noeud Table
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testObtenirNombreEnfants()
{
	// 1er test: on verifie si le nombre d'enfants est initialement 0
	nombreEnfants = table->obtenirNombreEnfants();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(nombreEnfants - 0));

	// 2eme test: on ajoute un maillet et on teste si nombreEnfants vaut 1
	NoeudMaillet* mailletTest = new NoeudMaillet(ArbreRenduINF2990::NOM_MAILLET);
	table -> ajouter(mailletTest);
	nombreEnfants = table->obtenirNombreEnfants();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(nombreEnfants - 1));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testVider()
///
/// Cas de test: vider un noeud composite Table de ses enfants
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testVider()
{
	// 1er test: on verifie si on peut initialement vider la table de ses enfants
	nombreEnfants = table->obtenirNombreEnfants();
	table->vider();
	int nbEnfants = table->obtenirNombreEnfants();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(nbEnfants));

	// 2eme test: on verifie si on peut vider la table apres l'ajout d'un bonus accelerateur
	NoeudBonus* bonusTest = new NoeudBonus(ArbreRenduINF2990::NOM_BONUS);
	table->ajouter(bonusTest);
	table->vider();
	nombreEnfants = table->obtenirNombreEnfants();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(nombreEnfants));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::chercherTest()
///
/// Cas de test: chercher un noeud grace a son nom.on ajoute des noeuds 
/// a la table que nous avons initialisés puis on verifie que c est effectivement 
///ceux qui sont sur la table (on profitepour tester aussi ajouter())
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::chercherTest()
{
	NoeudAbstrait * noeud1 = { new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };
	NoeudAbstrait * noeud2 = { new NoeudMuret{ ArbreRenduINF2990::NOM_MURET } };
	NoeudAbstrait * noeud3 = { new NoeudPortail{ ArbreRenduINF2990:: NOM_PORTAIL } };

	table->ajouter(noeud1);
	table->ajouter(noeud2);
	table->ajouter(noeud3);
	//nous allons rechercher les neouds ajoutés ci haut par leur type 
	//et verifier aussi la valeur de retour si on cherche un noeud qui
	//n'a pas ete ajoute a notre arbre on s attent a avoir nullptr

	CPPUNIT_ASSERT(table->chercher(ArbreRenduINF2990::NOM_BONUS) == noeud1);
	CPPUNIT_ASSERT(table->chercher(ArbreRenduINF2990::NOM_MURET) == noeud2);
	CPPUNIT_ASSERT(table->chercher(ArbreRenduINF2990::NOM_PORTAIL) == noeud3);
	CPPUNIT_ASSERT(table->chercher(ArbreRenduINF2990::NOM_MAILLET) == nullptr);
	delete noeud1;
	delete noeud2;
	delete noeud3;
}





////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testDeselectionnerTout()
///
/// Cas de test: On test s'il est possible de déselectionner tous les objets sélectionnés
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testDeselectionnerTout()
{

	// On vérifie que le noeud composite n'est pas sélectionné, de même que ces enfants
	CPPUNIT_ASSERT(table->selectionExiste() == false);

	// On crée des objets, les ajoute au noeud composite, et on les sélectionne
	NoeudBonus* bonus1 = new NoeudBonus("bonus");
	NoeudBonus* bonus2 = new NoeudBonus("bonus");

	table->ajouter(bonus1);
	table->ajouter(bonus2);
	bonus1->assignerSelection(true);
	bonus2->assignerSelection(true);

	// On vérifie qu'il existe des objets sélectionnés
	CPPUNIT_ASSERT(table->selectionExiste() == true);
}

////////////////////////////////////////////////////////////////////////
///

/// @fn void NoeudCompositeTest::afficherConcretTest()
///
/// Cas de test: on teste la methode qui s'occupe d'afficher les enfant de l'arbre
///bien sure que cette derive de la la classe noeud abstrait.
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::afficherConcretTest()
{
//	//glm::mat4 a = glm::mat4(1.0f);
//	glm::mat4 a = { {1, 0,0,1}, { 0,1,0,1 }, {0,0,1,1}, {1,1,1,1} };
//	const bool & c = true;
//	//NoeudBonus * noeud1 = { new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS} };
//	NoeudBonus* bonus1 = new NoeudBonus("bonus");
//	table->ajouter(bonus1);
//	bonus1->afficherConcret(a, est);
//	CPPUNIT_ASSERT(bonus1 ->estAffiche() == true);
//
//	// On déselectionne tout, et on vérifie si le noeud composite ou ses enfants sont sélectionnés
//	table->deselectionnerTout();
//	CPPUNIT_ASSERT(table->selectionExiste() == false);
}
