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
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
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
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
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
/// Cas de test: effacer une selection(un objet s�lectionn�) 
/// Ce test permet de tester si la fonction effacerSelection() fonctionne bien.
/// Il est utile de le tester, puisque l'�dition d'une zone de jeu est une partie
/// importante du livrable 1. Pour �diter, la suppression d'un objet est une
/// partie tr�s importante. De plus, il est aussi possible de v�rifier en m�me
/// temps si la fonction ajouter(NoeudAbstrait* enfant) est fonctionnelle.
/// La fonction ajouter(...) est primordiale, car elle permet d'ajouter
/// diff�rents enfants � notre arbre permettant alors de les manipuler
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacerSelection()
{
	// On v�rifie qu'initialement, la table n'a pas d'enfant
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 1);

	// Essaie d'ajouter un noeud
	NoeudBonus* bonus = new NoeudBonus("bonus");
	table->ajouter(bonus);

	// On v�rifie si le bonus a �t� ajout�
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 2);
	
	// On s�lectionne le bonus et appeler la fonction pour le supprimer
	bonus->assignerSelection(true);
	table->effacerSelection();

	// On v�rifie que la table n'a plus d'enfant apr�s l'effacement
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 1);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testTuerRondelle()
///
/// Cas de test: tuer la rondelle
/// Ce test permet de tester si la fonction tuerRondelle() fonctionne bien.
/// Il est utile de le tester, puisque nous devons �tre capable de tuer la
/// rondelle lorsque nous passons du mode test au mode d'�dition, ainsi que
/// lorsque nous sortons de partie rapide et de tournoi. En effet, nous ne
/// devons plus voir la rondelle sur la table rendu en mode d'�dition.
/// De plus, il est int�ressant de le tester, car le bon fonctionnement
/// de celle-ci implique que les fonctions pour tuer les 2 maillets sont
/// �galement fonctionnelles.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testTuerRondelle()
{
	// On v�rifie qu'initialement, la table n'a pas d'enfant
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 1);

	// Essaie d'ajouter une rondelle
	NoeudRondelle* rondelle = new NoeudRondelle("rondelle");
	table->ajouter(rondelle);

	// On v�rifie si la rondelle a �t� ajout�
	CPPUNIT_ASSERT(table->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(table->calculerProfondeur() == 2);

	// On appeler la fonction pour tuer la rondelle
	table->tuerRondelle();

	// On v�rifie que la table n'a plus d'enfant apr�s l'effacement
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
/// a la table que nous avons initialis�s puis on verifie que c est effectivement 
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
	//nous allons rechercher les neouds ajout�s ci haut par leur type 
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
/// Cas de test: On test s'il est possible de d�selectionner tous les objets s�lectionn�s
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testDeselectionnerTout()
{

	// On v�rifie que le noeud composite n'est pas s�lectionn�, de m�me que ces enfants
	CPPUNIT_ASSERT(table->selectionExiste() == false);

	// On cr�e des objets, les ajoute au noeud composite, et on les s�lectionne
	NoeudBonus* bonus1 = new NoeudBonus("bonus");
	NoeudBonus* bonus2 = new NoeudBonus("bonus");

	table->ajouter(bonus1);
	table->ajouter(bonus2);
	bonus1->assignerSelection(true);
	bonus2->assignerSelection(true);

	// On v�rifie qu'il existe des objets s�lectionn�s
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
//	// On d�selectionne tout, et on v�rifie si le noeud composite ou ses enfants sont s�lectionn�s
//	table->deselectionnerTout();
//	CPPUNIT_ASSERT(table->selectionExiste() == false);
}
