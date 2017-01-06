///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeud.h"
#include "EtatOpenGL.h"
#include "Noeuds/NoeudTypes.h"
#include "tinyxml2.h"


/// La chaîne représentant le type des tables.
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
/// La chaîne représentant le type de rondelle.
const std::string ArbreRenduINF2990::NOM_RONDELLE{ "rondelle" };
/// La chaîne représentant le type de maillet.
const std::string ArbreRenduINF2990::NOM_MAILLET{ "maillet" };
/// La chaîne représentant le type de maillet ordi.
const std::string ArbreRenduINF2990::NOM_MAILLETORDI{ "mailletOrdi" };
/// La chaîne représentant le type de bonus accélérateur.
const std::string ArbreRenduINF2990::NOM_BONUS{ "bonus" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_MURET{ "muret" };
const std::string ArbreRenduINF2990::NOM_POINT_CONTROLE{ "pointDeControle" };
const std::string ArbreRenduINF2990::NOM_BUT{ "but" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_TABLE, new UsineNoeud<NoeudTable>{ NOM_TABLE, std::string{ /*"media/table.obj"*/ } });
	ajouterUsine(NOM_RONDELLE, new UsineNoeud<NoeudRondelle>{ NOM_RONDELLE, std::string{ "media/rondelle.obj" } });
	ajouterUsine(NOM_MAILLET, new UsineNoeud<NoeudMaillet>{ NOM_MAILLET, std::string{ "media/maillet.obj" } });
	ajouterUsine(NOM_MAILLETORDI, new UsineNoeud<NoeudMailletOrdi>{ NOM_MAILLETORDI, std::string{ "media/maillet.obj" } });
	ajouterUsine(NOM_BONUS, new UsineNoeud<NoeudBonus>{ NOM_BONUS, std::string{ "media/bonus.obj" } });//****
	ajouterUsine(NOM_PORTAIL, new UsineNoeud<NoeudPortail>{ NOM_PORTAIL, std::string{ "media/portail.obj" } });
	ajouterUsine(NOM_MURET, new UsineNoeud<NoeudMuret>{ NOM_MURET, std::string{ "media/Muret.obj" } });
	ajouterUsine(NOM_POINT_CONTROLE, new UsineNoeud<PointDeControle>{ NOM_POINT_CONTROLE, std::string{ "media/pointDeControle.obj" } });
	ajouterUsine(NOM_BUT, new UsineNoeud<NoeudBut>{ NOM_BUT, std::string{ "media/bordure.obj" } });
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	// On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
	NoeudAbstrait* noeudTable{ creerNoeud(NOM_TABLE) };
	//NoeudAbstrait* noeudMailet2{ creerNoeud(NOM_MAILLET) };
	//ajouter(creerNoeud(NOM_RONDELLE));
	//ajouter(creerNoeud(NOM_MAILLET));
	//ajouter(creerNoeud(NOM_MAILLETORDI));
	
	//noeudMailet2->assignerPositionRelative({ 50, 0, 0 });
	//noeudTable->ajouter(noeudMailet2);

	ajouter(noeudTable);
}
/////////////////////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::sauvegarderZoneXml()
///
/// @description: Cette fonction permet de restaurer la zone de jeu  
///                     
/// @return type de retour: Aucun.
///
//////////////////////////////////////////////////////////////////////////////////////////

void ArbreRenduINF2990::restaurerZoneXml(char fichXml[])
{
	 vider();
	 NoeudAbstrait* table{ creerNoeud(NOM_TABLE) };
	 table->assignerEstSelectionnable(false);
	 ajouter(table);

	 std::string typeObjet = "";
	 glm::dvec3 position;
	 float positionx = 0, positiony = 0, positionz = 0;
	 float angle = 0;
	 double echelle = 0.0;
	 std::string nameFileToLoad = fichXml;
	 const char*	FileName = nameFileToLoad.c_str();
	 tinyxml2::XMLDocument fichierZoneXML;
	 tinyxml2::XMLNode * racine;
	 tinyxml2::XMLElement* element;


	 tinyxml2::XMLError success = fichierZoneXML.LoadFile(FileName);
	 if (success == tinyxml2::XML_SUCCESS) {

		 racine = fichierZoneXML.FirstChildElement("racine");
		 element = racine->FirstChildElement();

		 while (element) {
			 typeObjet = element->Name();


			 element->QueryFloatAttribute("x", &positionx);
			 element->QueryFloatAttribute("y", &positiony);
			 //element->QueryFloatAttribute("z", &positionz);
			 element->QueryFloatAttribute("angle", &angle);
			 element->QueryDoubleAttribute("echelle", &echelle);
			 position = { positionx, positiony, 0 };

			 NoeudAbstrait* noeud{ creerNoeud(typeObjet) };
			 noeud->assignerPositionRelative(position);
			 noeud->setAngleRotation(angle);
			 noeud->setFacteurEchelle(echelle);
			 ajouter(noeud);
			 element = element->NextSiblingElement();
		}

	}
 
}
/////////////////////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::sauvegarderZoneXml()
///
/// @description: Cette fonction qui permet de sauvegarder la zone de jeu  
///                      
/// @return type de retour: Aucun.
///
//////////////////////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::sauvegarderZoneXml(char destination[])
{
	glm::dvec3 point = { 0, 0, 0 };
	GLfloat angleRotation = 0;
	double echelle = 0;
	tinyxml2::XMLDocument documentXml;

	tinyxml2::XMLNode * racine = documentXml.NewElement("racine");
	tinyxml2::XMLElement * circuit;
	tinyxml2::XMLElement * typeOBjet;
	documentXml.InsertFirstChild(racine);
	
	//parcours des enfants lies a la table selon linitialisation faite dans la methode initialiser
	for (NoeudAbstrait* enfant : enfants_)
	{
		 point = enfant->obtenirPositionRelative();
		 angleRotation = enfant->getAngleRotation();
		 echelle = enfant->getFacteurEchelle();
		 typeOBjet = documentXml.NewElement(enfant->obtenirType().c_str());
		 typeOBjet->SetAttribute("x", point[0]);
		 typeOBjet->SetAttribute("y", point[1]);
		 typeOBjet->SetAttribute("z", point[2]);
		 typeOBjet->SetAttribute("angle", angleRotation);
		 typeOBjet->SetAttribute("echelle", echelle);

		 racine->InsertEndChild(typeOBjet);
	}

	 std::string emplacement = destination;
	 documentXml.SaveFile(emplacement.c_str());
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeud(const std::string& nom, glm::dvec3 coordonnee)
///
/// Cette fonction permet d'ajouter un noeud à la surface de la table
///
/// @param[in] posX : position X de la souris
/// @param[in] posY : position Y de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
//void ArbreRenduINF2990::ajouterNoeud(const std::string& nom, glm::dvec3 coordonnee)
//{
//	NoeudAbstrait* noeud{ creerNoeud(nom) };
//	noeud->assignerPositionRelative(coordonnee);
//	surface_->ajouter(noeud);
//}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::nouvelleScene()
///
/// Cette fonction permet de charger une nouvelle scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::nouvelleScene()
{
	for (NoeudAbstrait * enfant : enfants_)
	{
		if (enfant->obtenirType() != "table")
			enfant->assignerSelection(true);
		else
		{
			enfant->assignerSelection(false);
			if (enfant->obtenirType() == "NOM_BONUS")
				enfant->assignerPositionRelative({ 0, 0, -32 });
			else
				enfant->assignerPositionRelative({ 0, 0, 0 });
			enfant->setAngleRotation(0);
		}
	}
	this->effacerSelection();


}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
