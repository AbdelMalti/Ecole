///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

*/

#include <windows.h>
#include <cassert>

#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"
#include <iostream>

#include "vuePerspec.h"
#include "VueOrtho.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"

#include "../Visiteurs/VisiteurDeplacement.h"
#include "../Visiteurs/VisiteurMiseEchelle.h"
#include "../Visiteurs/VisiteurSupprimer.h"
#include "../Visiteurs/VisiteurRotation.h"
#include "../Visiteurs/VisiteurDuplication.h"
#include "../Visiteurs/VisiteurSelection.h"
#include "../Visiteurs/VisiteurCollision.h"
#include"../Son/Son.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml2.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "FTGL\ftgl.h"

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };

/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };

const double BORDUREINTERIEUR = 7;
const double BORDUREEXTERIEUR = 11;

FTGLPixmapFont font("C:/Windows/Fonts/arial.ttf");
//const double VITESSEMAX = 4;

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == nullptr)
		instance_ = new FacadeModele;

	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libère l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur libère les objets du modèle.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	delete arbre_;
	//delete table_;
	delete vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur de modèles) et assigne des 
/// paramètres du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être créé.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);

	// Qualité
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Création de l'arbre de rendu.  À moins d'être complètement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de créer
	// l'arbre après avoir créé le contexte OpenGL.

	arbre_ = new ArbreRenduINF2990; //Ici on doit modifier l'arbre pour que la table s'affiche (je pense que c'est ca)
	arbre_->initialiser();
	table_ = dynamic_cast<NoeudTable*>(arbre_->chercher("table"));
	// On crée une vue par défaut.
	if (vueOrtho_ != NULL)
		delete vueOrtho_;
	if (vuePers_ != NULL)
		delete vuePers_;

	vueOrtho_ = new vue::VueOrtho{
		vue::Camera{
		glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
		glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0) },
		vue::ProjectionOrtho{
		500, 500,
		1, 1000, 400, 600, 1.25,
		200, 200 }
	};

	vuePers_ = new vue::VuePerspec{
		vue::Camera{
		glm::dvec3(0, -200, 200), glm::dvec3(0, 0, 0),
		glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0)},
		vue::ProjectionPerspec{
		500, 500,
		1, 1000, 1, 10000, 1.25,
		200, 200 }
	};
	vue_ = vueOrtho_;

	tableX_ = table_->getPositionX() - BORDUREINTERIEUR;
	tableY_ = table_->getPositionY() - BORDUREINTERIEUR;
	tableZ_ = table_->getPositionZ();
	font.FaceSize(32);

	///@ Source des images: http://www.humus.name

	unsigned int dimension = 2048;

	const std::string& fichierXpos1("media/1textureSkyboxDroit.jpg");
	const std::string& fichierXneg1("media/1textureSkyboxGauche.jpg");
	const std::string& fichierYpos1("media/1textureSkyboxHaut.jpg");
	const std::string& fichierYneg1("media/1textureSkyboxBas.jpg");
	const std::string& fichierZpos1("media/1textureSkyboxAvant.jpg");
	const std::string& fichierZneg1("media/1textureSkyboxArriere.jpg");

	skyboxEditeur_ = new utilitaire::BoiteEnvironnement(fichierXpos1, fichierXneg1, fichierYpos1, fichierYneg1,
		fichierZpos1, fichierZneg1, dimension);

	const std::string& fichierXpos2("media/2textureSkyboxDroit.jpg");
	const std::string& fichierXneg2("media/2textureSkyboxGauche.jpg");
	const std::string& fichierYpos2("media/2textureSkyboxHaut.jpg");
	const std::string& fichierYneg2("media/2textureSkyboxBas.jpg");
	const std::string& fichierZpos2("media/2textureSkyboxAvant.jpg");
	const std::string& fichierZneg2("media/2textureSkyboxArriere.jpg");

	skyboxTournoi_ = new utilitaire::BoiteEnvironnement(fichierXpos2, fichierXneg2, fichierYpos2, fichierYneg2,
		fichierZpos2, fichierZneg2, dimension);
	Son::obtenirInstance()->initialiserSon();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// Vérification de l'existance du ficher

	// Si le fichier n'existe pas, on le crée.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les différentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	tinyxml2::XMLDocument document;
	// Écrire la déclaration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	
	// On enregistre les différentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);

	// Écrire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On libère les instances des différentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être détruit.");

	FreeImage_DeInitialise();

	tableX_ = 0.0;
	tableY_ = 0.0;
	tableZ_ = 0.0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Afficher la scène
	afficherBase();

	GLint fenetre[4];
	glGetIntegerv(GL_VIEWPORT, fenetre);
	GLint hauteurFenetre = fenetre[3];
	GLint largeurFenetre = fenetre[2];

	if (estPartieRapide_)
	{
		font.Render("Joueur 1", -1, FTPoint(20, 50));
		font.Render("Joueur 2", -1, FTPoint((int)largeurFenetre - 150 , 50));
	}

	const char* nomJoueur1 = nomJoueurVirtuel1_.c_str();
	const char* nomJoueur2 = nomJoueurVirtuel2_.c_str();

	if (estTournoi_)
	{
		font.Render(nomJoueur1, -1, FTPoint(20, 50));
		font.Render(nomJoueur2, -1, FTPoint((int)largeurFenetre - nomJoueurVirtuel2_.length()*20 , 50));
	}

	string minutes = to_string(chronoMinutes_);
	string secondes = to_string(chronoSecondes_);

	const char* chronometreMinutes = minutes.c_str();
	const char* chronometreSecondes = secondes.c_str();

	string butGauche = to_string(butGauche_);
	string butDroit = to_string(butDroit_);

	const char* butMailletGauche = butGauche.c_str();
	const char* butMailletDroit = butDroit.c_str();

	if (estPartieRapide_ || estTournoi_)
	{
		font.Render(chronometreMinutes, -1, FTPoint((int)largeurFenetre / 2 - 20, 50));
		font.Render(" : ", -1, FTPoint((int)largeurFenetre / 2, 50));
		font.Render(chronometreSecondes, -1, FTPoint((int)largeurFenetre / 2 + 20, 50));
		font.Render(butMailletGauche, -1, FTPoint(50, 20));
		font.Render(butMailletDroit, -1, FTPoint((int)largeurFenetre - 70, 20));
	}

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la caméra
	glm::mat4 vueProjection(vue_->obtenirProjection().obtenirMatrice() * vue_->obtenirCamera().obtenirMatrice());
	
	
	/// Affichage de notre skybox
	// les deux mat4 parametres glm::mat4 const& matriceProjection  et glm::mat4 const& matriceCamera
	// de la methode afficher de la classe BoiteEnvironnement

	glm::mat4 matriceCamera = vue_->obtenirCamera().obtenirMatrice();

	if (orbite_) {
		glm::mat4 matriceProjection = vue_->obtenirProjection().obtenirMatrice();

		if (estEdition_)
			skyboxEditeur_->afficher(matriceProjection, matriceCamera);

		if (estTournoi_)
			skyboxTournoi_->afficher(matriceProjection, matriceCamera);
	}
	else {
		glm::mat4 matriceProjection = vue_->obtenirProjection().obtenirMatrice() * vue_->obtenirCamera().obtenirMatrice();

		if (estEdition_)
			skyboxEditeur_->afficher(matriceProjection, matriceCamera);

		if (estTournoi_)
			skyboxTournoi_->afficher(matriceProjection, matriceCamera);
	}


	bool estColore = false;
	if (edition_ == 'e')
		estColore = true;
	// Afficher la scène.
	arbre_->afficher(vueProjection, estColore);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Réinitialisation de la scène.
	NoeudAbstrait::compteurP_ = 0;

	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise à jour des objets.
	arbre_->animer(temps);
	// Verification du type de vue courante
	if (!orbite_)
	{
		vue_ = vueOrtho_;
		vue_->obtenirCamera().setEstOrbite(false);
	}
		
	else
	{
		vue_ = vuePers_;
		vue_->obtenirCamera().setEstOrbite(true);
	}
	// Mise à jour de la vue.
	vue_->animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserRectangle(int pX, int pY)
///
/// Cette fonction permet d'initialiser le rectangle élastique
///
/// @param[in] pX : position X de la souris
/// @param[in] pY : position Y de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserRectangle(int pX, int pY)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(pX, pY, point);

	const glm::ivec2 pointR = { point.x, point.y};

	unsigned short patron = 0x3333;
	int facteur = 1;

	const glm::ivec2 pointD = {pX, pY};

	aidegl::initialiserRectangleElastique(pointD);

	conteneur_enfants vecteurEnfants = arbre_->getEnfants();

	int compteurSelectionner = 0;

	//cout << "Limite x : " << pointAncrageR.x << " ; " << pointAvantR.x << " ; " << pointApresR.x << endl;
	//cout << "Limite y : " << pointAncrageR.y << " ; " << pointAvantR.y << " ; " << pointApresR.y << endl;

	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
			//cout << "Pas dans selection : " << vecteurEnfants[i]->obtenirType() << endl;
			vecteurEnfants[i]->assignerSelection(false);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::mettreAJourRectangle(int piX, int piY, int paX, int paY, int pdX, int pdY)
///
/// Cette fonction permet de mettre à jour le rectangle élastique
///
/// @param[in] piX : point d'ancrage X
/// @param[in] piY : point d'ancrage Y
/// @param[in] paX : point avant X
/// @param[in] paY : point avant Y
/// @param[in] pdX : point après X
/// @param[in] pdY : point après Y
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void FacadeModele::mettreAJourRectangle(int piX, int piY, int paX, int paY, int pdX, int pdY, bool enSelection)
{
	glm::dvec3 pointAncrage{};
	glm::dvec3 pointAvant{};
	glm::dvec3 pointApres{};
	//vue_->convertirClotureAVirtuelle()
	vue_->convertirClotureAVirtuelle(piX, piY, pointAncrage);
	vue_->convertirClotureAVirtuelle(paX, paY, pointAvant);
	vue_->convertirClotureAVirtuelle(pdX, pdY, pointApres);

	const glm::ivec2 pointAncrageR{ pointAncrage .x, pointAncrage .y};
	const glm::ivec2 pointAvantR{ pointAvant.x, pointAvant.y };
	const glm::ivec2 pointApresR{ pointApres.x, pointApres.y };

	const glm::ivec2 pointAncrageD = { piX, piY };
	const glm::ivec2 pointAvantD = { paX, paY };
	const glm::ivec2 pointApresD = { pdX, pdY };

	aidegl::mettreAJourRectangleElastique(pointAncrageD, pointAvantD, pointApresD);

	//-----------------------------------------------------
	
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();

	int compteurSelectionner = 0;

	//cout << "Limite x : " << pointAncrageR.x << " ; " << pointAvantR.x << " ; " << pointApresR.x << endl;
	//cout << "Limite y : " << pointAncrageR.y << " ; " << pointAvantR.y << " ; " << pointApresR.y << endl;

	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		//cout << "enfant x : " << vecteurEnfants[i]->obtenirPositionRelative().x << "; y : "<< vecteurEnfants[i]->obtenirPositionRelative().y << endl;

		//utilitaire::DANS_LIMITESXY(vecteurEnfants[i]->obtenirPositionRelative().x, (coordPoint.x - 3), (coordPoint.x + 3), vecteurEnfants[i]->obtenirPositionRelative().y, (coordPoint.y - 3), (coordPoint.y + 3))
		if (
			((vecteurEnfants[i]->obtenirPositionRelative().x > pointAncrageR.x  && vecteurEnfants[i]->obtenirPositionRelative().x < pointApresR.x)
				||
			(vecteurEnfants[i]->obtenirPositionRelative().x < pointAncrageR.x  && vecteurEnfants[i]->obtenirPositionRelative().x > pointApresR.x)
				)
			&&
			(
			(vecteurEnfants[i]->obtenirPositionRelative().y > pointAncrageR.y && vecteurEnfants[i]->obtenirPositionRelative().y < pointApresR.y)
				||
				(vecteurEnfants[i]->obtenirPositionRelative().y < pointAncrageR.y && vecteurEnfants[i]->obtenirPositionRelative().y > pointApresR.y)
			))//utilitaire::DANS_LIMITESXY(vecteurEnfants[i]->obtenirPositionRelative().x, pointAncrageR.x, pointApresR.x, vecteurEnfants[i]->obtenirPositionRelative().y, pointAncrageR.x, pointApresR.y))
		{
			//arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
			++compteurSelectionner;
			//cout << "Dans selection : " <<vecteurEnfants[i]->obtenirType() << endl;
			vecteurEnfants[i]->assignerSelection(true);
		}
		else
		{
			//cout << "Pas dans selection : " << vecteurEnfants[i]->obtenirType() << endl;
			vecteurEnfants[i]->assignerSelection(false);
		}
	}

	//cout << "-----------------------------------" << endl;
}

/////////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::terminerRectangle(int pIX, int pIY, int pFX, int pFY)
///
/// Cette fonction permet de terminer le rectangle élastique
///
/// @param[in] pIX : point ancrage X
/// @param[in] pIY : point ancrage Y
/// @param[in] pFX : point final X
/// @param[in] pFY : point final Y
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void FacadeModele::terminerRectangle(int pIX, int pIY, int pFX, int pFY)
{
	glm::dvec3 pointAncrage{};
	glm::dvec3 pointFinal{};

	vue_->convertirClotureAVirtuelle(pIX, pIY, pointAncrage);
	vue_->convertirClotureAVirtuelle(pFX, pFY, pointFinal);

	const glm::ivec2 pointAncrageR = { pointAncrage.x, pointAncrage.y };
	const glm::ivec2 pointFinalR = { pointFinal.x, pointFinal.y };

	const glm::ivec2 pointAncrageD = { pIX, pIY };
	const glm::ivec2 pointFinalD = { pFX, pFY };

	aidegl::terminerRectangleElastique(pointAncrageD, pointFinalD);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeudBonus(int posX, int posY)
///
/// Cette fonction permet d'ajouter un noeud bonus à l'arbre
///
/// @param[in] posX : position X de la souris
/// @param[in] posY : position Y de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNoeudBonus(int posX, int posY)
{
	glm::dvec3 points;
	vue_->convertirClotureAVirtuelle(posX,posY, points);
	NoeudAbstrait* noeudAjoute{ arbre_->creerNoeud(arbre_->NOM_BONUS) };
	
	if (estDansZoneDeJeu(points))
	{
		noeudAjoute->assignerPositionRelative(points);
		arbre_->ajouter(noeudAjoute);

		arbre_->animer(0);

		vue_->animer(0);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeudMuret(int posX, int posY)
///
/// Cette fonction permet d'ajouter un noeud muret à l'arbre
///
/// @param[in] posX : position X de la souris
/// @param[in] posY : position Y de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNoeudMuret(int posX, int posY)
{
	glm::dvec3 points;
	vue_->convertirClotureAVirtuelle(posX, posY, points);
	NoeudAbstrait* noeudAjoute{ arbre_->creerNoeud(arbre_->NOM_MURET) };
	
	if (estDansZoneDeJeu(points))
	{
		noeudAjoute->assignerPositionRelative(points);
		arbre_->ajouter(noeudAjoute);

		arbre_->animer(0);

		vue_->animer(0);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeudPortail(int posX, int posY)
///
/// Cette fonction permet d'ajouter un noeud portail à l'arbre
///
/// @param[in] posX : position X de la souris
/// @param[in] posY : position Y de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNoeudPortail(int posX, int posY)
{
	glm::dvec3 points;
	vue_->convertirClotureAVirtuelle(posX, posY, points);
	NoeudAbstrait* noeudAjoute{ arbre_->creerNoeud(arbre_->NOM_PORTAIL) };
	
	if (estDansZoneDeJeu(points))
	{
		noeudAjoute->assignerPositionRelative(points);
		arbre_->ajouter(noeudAjoute);

		arbre_->animer(0);

		vue_->animer(0);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::estDansZoneDeJeu()
///
///	Cette fonction indique si le noeud est dans la zone de jeu
///
/// @return retourne vrai si le noeud est dans la zone de jeu
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::estDansZoneDeJeu(glm::vec3 point)
{
	if ((-tableX_-3 < point.x && point.x < tableX_+3) && (-tableY_-3 < point.y && point.y < tableY_+3))
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserDeplacement(double x, double y)
///
/// Fonction qui permet d'initialiser le déplacement d'un objet
///
///@param[in/out] l'emplacement initial x et y du déplacement
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserDeplacement(double x, double y)
{
	glm::dvec3 positionInitialSouris;
	vue_->convertirClotureAVirtuelle(x, y, positionInitialSouris);
	pointInitSourisX_ = positionInitialSouris.x;
	pointInitSourisY_ = positionInitialSouris.y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacement(double x, double y)
///
/// Fonction qui permet de faire déplacer un objet
///
///@param[in/out] l'emplacement x et y du déplacement
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacement(double x, double y)
{
	//NoeudComposite* table = dynamic_cast<NoeudComposite*>(arbre_->getEnfants()[0]);

	//conteneur_enfants vecteurEnfants = table->getEnfants();

	conteneur_enfants vecteurEnfants = arbre_->getEnfants();

	VisiteurDeplacement* visiteurDeplacement = new VisiteurDeplacement();
	glm::dvec3 delta;
	glm::dvec3 position; //position de la souris

	//double deltaX = (pointInitSourisX_ - x); ///4
	//double deltaY = (pointInitSourisY_ - y);///2

	//position[0] = -deltaX; // il y a un -, car sinon il va dans l'autre sens
	//[1] = deltaY;
	//std::cout << "HI" << std::endl;
	vue_->convertirClotureAVirtuelle(x, y, position);
	delta.x = position.x - pointInitSourisX_;
	delta.y = position.y - pointInitSourisY_;

	/*std::cout << delta.x << std::endl;
	std::cout << delta.y << std::endl;*/

	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (utilitaire::DANS_LIMITESXY(position.x, -65.0, 65.0, position.y, -50, 50))
		{
			visiteurDeplacement->setX(delta.x);
			visiteurDeplacement->setY(delta.y);
			if (vecteurEnfants[i]->estSelectionne())
				vecteurEnfants[i]->accepter(visiteurDeplacement);
		}
		//std::cout << vecteurEnfants[i]->obtenirType() << std::endl;
		
	}

	pointInitSourisX_ = position.x;
	pointInitSourisY_ = position.y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::miseAEchelle(double y)
///
/// Fonction qui permet de faire la mise à échelle d'un objet
///
///@param[in/out] l'emplacement y de la mise à échelle
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::miseAEchelle(double y)
{
	//NoeudComposite* table = dynamic_cast<NoeudComposite*>(arbre_->getEnfants()[0]);

	//conteneur_enfants vecteurEnfants = table->getEnfants();
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();

	VisiteurMiseEchelle* visiteurMiseAEchelle = new VisiteurMiseEchelle();
	//std::cout << y << std::endl;
	if (y > 0)
	{
		visiteurMiseAEchelle->setFacteur(1.01);
	}
	if (y < 0)
		visiteurMiseAEchelle->setFacteur(0.99);

	//visiteurMiseAEchelle->setFacteur(2);

	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if(vecteurEnfants[i]->estSelectionne())
			vecteurEnfants[i]->accepter(visiteurMiseAEchelle);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::supprimer()
///
/// Fonction qui permet d'appeler la fonction effacerSelection() de
/// NoeudComposite
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimer()
{
	//arbre_->selectionnerTout(); // a supprimer des que la selection est fonctionnelle. Juste pour test 
	arbre_->effacerSelection();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserRotation(double y)
///
/// Fonction qui permet d'initialiser la rotation
///
///@param[in/out] l'emplacement initial de la sourie en y pour la rotation
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserRotation(double y)
{
	pointInitSourisY_ = y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::rotation(double y)
///
/// Fonction qui permet de faire tourner un objet
///
///@param[in/out] l'emplacement y de la rotation
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::rotation(double y)
{
	//NoeudComposite* table = dynamic_cast<NoeudComposite*>(arbre_->getEnfants()[0]);

	//conteneur_enfants vecteurEnfants = table->getEnfants();
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();

	VisiteurRotation* visiteurRotation = new VisiteurRotation();
	//std::cout << y << std::endl;
	double deltaY = pointInitSourisY_ - y;

	if (deltaY > 0)
	{
		deltaY = 0.1;
	}
	else if (deltaY < 0)
	{
		deltaY = -0.1;
	}

	visiteurRotation->setDelta(deltaY);

	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->estSelectionne())
			vecteurEnfants[i]->accepter(visiteurRotation);
	}

	pointInitSourisY_ = y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserDuplication(double x, double y)
///
/// Fonction qui permet d'initialiser la duplication d'un objet
///
///@param[in/out] l'emplacement initial de la duplication x et y
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserDuplication(double x, double y)
{
	VisiteurDuplication* visiteurDuplication = new VisiteurDuplication();
	visiteurDuplication->initialisation(x, y);
}
//void FacadeModele::selectionner(int i, int j) 
//{
//	//Todo:
//}


//void FacadeModele::miseAEchelle(double changementEchelle)
//{
//	//Todo:
//}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::duplication(double x, double y)
///
/// Fonction qui permet de dupliquer un objet
///
///@param[in/out] l'emplacement de la duplication x et y
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::duplication(double x, double y)
{
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();

	VisiteurDuplication* visiteurDuplication = new VisiteurDuplication();

	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(x, y, point);

	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->estSelectionne())
			vecteurEnfants[i]->accepter(visiteurDuplication);
	}

	visiteurDuplication->deplacementDeEtampe(point[0], point[1]);
	visiteurDuplication->estPossibleDeDupliquer(point[0], point[1]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::determinerCouleur(int sourisX, int sourisY, GLubyte  couleurDUnPixel[])
///
/// Cette fonction permet la determination de la couleur d'un pixel
///
/// @param[in] sourisX : position X de la souris
/// @param[in] sourisY : position Y de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::determinerCouleur(int sourisX, int sourisY, GLubyte couleurDUnPixel[])
{
	GLubyte couleur[3];

	for (unsigned int i = 0; i < 3; i++)
		couleur[i] = couleurDUnPixel[i];
	glFlush();
	glFinish();
	GLint cloture[4]; 
	glGetIntegerv(GL_VIEWPORT, cloture);
	GLint posX = sourisX, posY = cloture[3] - sourisY;
	glReadBuffer(GL_BACK);
	glReadPixels(posX, posY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, couleur);

	for (unsigned int i = 0; i < 3; i++)
		couleurDUnPixel[i] = couleur[i];

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectionner(int posX, int posY, bool estSelectionne)
///
/// Fonction qui permet de sélectionner les objets sur la table
///
///@param[in/out] la position en x (int) et en y (int) de la position de la
///				  sélection et le booléen pour dire qu'il est sélectionné (bool)
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectionner(int posX, int posY, bool estSelectionne)
{
	glm::dvec3 coordPoint;
	vue_->convertirClotureAVirtuelle(posX, posY, coordPoint);
	GLubyte  couleur[3];
	determinerCouleur(posX, posY, couleur);
	bool estHorsTable = (couleur[0] == 0 && couleur[1] == 0 && couleur[2] == 0);

	if (!estHorsTable)
	{
		auto visiteur = new VisiteurSelection(coordPoint, estSelectionne, couleur, true);
		arbre_->accepterVisi(visiteur, estSelectionne);
		delete visiteur;

		visiteur = new VisiteurSelection(coordPoint, estSelectionne, couleur, false);
		arbre_->accepterVisi(visiteur, estSelectionne);

		if (!visiteur->obtenirGardeSelection() && estSelectionne)
			arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
		delete visiteur;

		conteneur_enfants vecteurEnfants = arbre_->getEnfants();

		//cout << "MinX : " << (coordPoint.x - 3) << " ; MaxX : " << (coordPoint.x + 3) << endl;
		//cout << "MinY : " << (coordPoint.y - 3) << " ; MaxY : " << (coordPoint.y + 3) << endl;

		int compteurNonSelectionner = 0;

		for (size_t i = 0; i < vecteurEnfants.size(); i++)
		{
			//cout << i << endl;

			//utilitaire::DANS_LIMITESXY(vecteurEnfants[i]->obtenirPositionRelative().x, (coordPoint.x - 3), (coordPoint.x + 3), vecteurEnfants[i]->obtenirPositionRelative().y, (coordPoint.y - 3), (coordPoint.y + 3))
			if (!utilitaire::DANS_LIMITESXY(vecteurEnfants[i]->obtenirPositionRelative().x, (coordPoint.x - 3), (coordPoint.x + 3), vecteurEnfants[i]->obtenirPositionRelative().y, (coordPoint.y - 3), (coordPoint.y + 3)))
			{
				//arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
				++compteurNonSelectionner;
				/*cout << "Pas choisi" << endl;*/
				vecteurEnfants[i]->assignerSelection(false);
			}
			else
			{
				/*cout << "CHOISI : " << vecteurEnfants[i]->obtenirType() << endl;*/
				//vecteurEnfants[i]->assignerSelection(true);
				vecteurEnfants[i]->assignerSelection(true);
				posX = vecteurEnfants[i]->obtenirPositionRelative().x;
				posY = vecteurEnfants[i]->obtenirPositionRelative().y;
				posZ = vecteurEnfants[i]->obtenirPositionRelative().z;
				nombreObjetSelectioner = 1;
			}
			//cout << "enfant X : " << vecteurEnfants[i]->obtenirPositionRelative().x << endl;
			//cout << "enfant Y : " << vecteurEnfants[i]->obtenirPositionRelative().y << endl;
		}

		if (compteurNonSelectionner == vecteurEnfants.size())
		{
			//cout << "Rien n'est selectionner" << endl;
			nombreObjetSelectioner = 0;

		}

	}
	else if (estSelectionne)
	{
		arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deselectionnerTout()
///
/// Fonction qui permet d'appeler la fonction deselectionnerTout() dans NoeudComposite
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deselectionnerTout()
{
	//arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		vecteurEnfants[i]->assignerSelection(false);
	}

	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::CoefficientFriction()
///
/// Fonction qui permet d'obtenir le coefficient de friction de la table
///
///@param[in/out] aucun
///
/// @return double coefficientFriction
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirCoefficientFriction()
{
	return  arbre_->chercher(arbre_->NOM_TABLE)->getCoefficientFriction();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::modifierCoefficientFriction(double friction)
///
/// Fonction qui permet de modifier le coefficient de friction de la table
///
///@param[in/out] double friction
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::modifierCoefficientFriction(double friction) 
{
	arbre_->chercher(arbre_->NOM_TABLE)->setCoefficientFriction(friction);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirAcceleration()
///
/// Fonction qui permet d'obtenir l'acceleration des objets
///
///@param[in/out] aucun
///
/// @return double acceleration
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirAcceleration() {
	return arbre_->chercher(arbre_->NOM_TABLE)->getAcceleration();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::modifierAcceleration(double acceleration)
///
/// Fonction qui permet de modifier l'acceleration des objets
///
///@param[in/out] double acceleration
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::modifierAcceleration(double acceleration) {
	arbre_->chercher(arbre_->NOM_TABLE)->setAcceleration(acceleration);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirRebond()
///
/// Fonction qui permet d'obtenir le coefficient de rebond
///
///@param[in/out] aucun
///
/// @return double rebond
///
////////////////////////////////////////////////////////////////////////

double FacadeModele::obtenirRebond() {
	return arbre_->chercher(arbre_->NOM_TABLE)->getCoefficientRebond();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::modifierRebond(double rebond)
///
/// Fonction qui permet de modifier le coefficient de rebond
///
///@param[in/out] double rebond
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::modifierRebond(double rebond) {

	arbre_->chercher(arbre_->NOM_TABLE)->setCoefficientRebond(rebond);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::tuerRondelle( )
///
/// Fonction qui permet d'appeler la fonction tuerRondelle() du
/// NoeudComposite
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::tuerRondelle()
{
	//conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	//for (conteneur_enfants::iterator it{ vecteurEnfants.begin() };
	//it != vecteurEnfants.end();
	//	) {
	//	if ((*it)->obtenirType() == arbre_->NOM_RONDELLE) {
	//		NoeudAbstrait* enfant{ (*it) };
	//		vecteurEnfants.erase(it);
	//		delete enfant;
	//		it = vecteurEnfants.begin();
	//	}
	//	else {
	//		++it;
	//	}
	//}

	arbre_->tuerRondelle();
}

//void FacadeModele::ajoutRondelleMaillet()
//{
//	table_->ajoutRondelleMaillet();
//}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::tuerMaillet( )
///
/// Fonction qui permet d'appeler la fonction tuerMaillet() du
/// NoeudComposite
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::tuerMaillet()
{
	/*conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	for (conteneur_enfants::iterator it{ vecteurEnfants.begin() };
	it != vecteurEnfants.end();
		) {
		if ((*it)->obtenirType() == arbre_->NOM_MAILLET) {
			NoeudAbstrait* enfant{ (*it) };
			vecteurEnfants.erase(it);
			delete enfant;
			it = vecteurEnfants.begin();
		}
		else {
			++it;
		}
	}*/

	arbre_->tuerMaillet();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::tuerMailletOrdi( )
///
/// Fonction qui permet d'appeler la fonction tuerMailletOrdi() du
/// NoeudComposite
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::tuerMailletOrdi()
{
	/*conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	for (conteneur_enfants::iterator it{ vecteurEnfants.begin() };
	it != vecteurEnfants.end();
		) {
		if ((*it)->obtenirType() == arbre_->NOM_MAILLETORDI) {
			NoeudAbstrait* enfant{ (*it) };
			vecteurEnfants.erase(it);
			delete enfant;
			it = vecteurEnfants.begin();
		}
		else {
			++it;
		}
	}*/

	arbre_->tuerMailletOrdi();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::genererMaillet( )
///
/// Fonction qui permet de générer le maillet pour partie rapide, tournoi
/// et mode test
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::genererMaillet()
{
	glm::vec3 posMaillet;
	NoeudAbstrait* maillet{ arbre_->creerNoeud(arbre_->NOM_MAILLET) };
	arbre_->ajouter(maillet);
	posMaillet.x = -62;
	posMaillet.y = 0;
	maillet->assignerPositionRelative(posMaillet);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::genererMailletOrdi( )
///
/// Fonction qui permet de générer le maillet ordi pour partie rapide,
/// tournoi et mode test
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::genererMailletOrdi()
{
	glm::vec3 posMaillet;
	NoeudAbstrait* maillet{ arbre_->creerNoeud(arbre_->NOM_MAILLETORDI) };
	arbre_->ajouter(maillet);
	posMaillet.x = 62;
	posMaillet.y = 0;
	maillet->assignerPositionRelative(posMaillet);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::genererRondelle( )
///
/// Fonction qui permet de générer la rondelle pour partie rapide,
/// tournoi et mode test
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::genererRondelle()
{
	glm::vec3 posRondelle;
	NoeudAbstrait* rondelle{ arbre_->creerNoeud(arbre_->NOM_RONDELLE) };
	arbre_->ajouter(rondelle);
	posRondelle.x = 0;
	posRondelle.y = 0;
	rondelle->assignerPositionRelative(posRondelle);
}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::bougerMaillet(int direction)
///
/// Fonction qui permet de déplacer le maillet ordi en considérant la direction
///
///@param[in] la direction du mouvement du maillet ordi selon le clavier et
///l'énumération fait dans Édition.cs
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////////////
void FacadeModele::bougerMaillet(int direction)
{
		switch (direction)
		{
		case 1: //Haut
			//std::cout << "haut" << std::endl;
			deplacerMailletOrdi(0.0, 2.0);
				break;
		case 2: //Bas
			//std::cout << "bas" << std::endl;
			deplacerMailletOrdi(0.0, -2.0);
				break;
		case 3: //Gauche
			//std::cout << "gauche" << std::endl;
			deplacerMailletOrdi(-2.0, 0.0);
				break;
		case 4: //Droite
			//std::cout << "droite" << std::endl;
			deplacerMailletOrdi(2.0, 0.0);
				break;
		case 5:
			//std::cout << "hautGauche" << std::endl;
			deplacerMailletOrdi(-1.0, 1.0);
			break;
		case 6:
			//std::cout << "hautDroit" << std::endl;
			deplacerMailletOrdi(1.0, 1.0);
			break;
		case 7:
			//std::cout << "basGauche" << std::endl;
			deplacerMailletOrdi(-1.0, -1.0);
			break;
		case 8:
			//std::cout << "basDroit" << std::endl;
			deplacerMailletOrdi(1.0, -1.0);
			break;

		default:
				break;
		}
}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animationJeu()
///
/// Cette fonction permet de détecter les différentes collisions entre les objets
/// présents sur la table avec la rondelle.
///
///@param[in/out] aucun.
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////////////
void FacadeModele::animationJeu() 
{
	NoeudRondelle* n = (NoeudRondelle*)arbre_->chercher("rondelle");

	conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	VisiteurCollision* visiteurCollision = new VisiteurCollision(n);
	NoeudMaillet* maillet = (NoeudMaillet*)arbre_->chercher("maillet");
	NoeudMaillet* mailletOrdi = (NoeudMaillet*)arbre_->chercher("mailletOrdi");
	
	
	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->obtenirType() == "bonus") { ///Détecte les collisions Rondelle-Bonus accélérateur
			vecteurEnfants[i]->accepter(visiteurCollision);
			//visiteurCollision->physiqueBonusRondelle(); // Cela sert a calculer la physique uniquement apres que la rondelle ait toucher un bonus.
			estCollisionBonus = visiteurCollision->getSiCollisionBonus();
			//std::cout << "estCollisionBonus dans FacadeModele : " << estCollisionBonus << std::endl;
		}
		else if (vecteurEnfants[i]->obtenirType() == "maillet") { ///Détecte les collisions Rondelle-maillet humain
			vecteurEnfants[i]->accepter(visiteurCollision);
			estCollisionMaillet = visiteurCollision->getSiCollisionAvecMaillet();
			if (estCollisionMaillet)
			{
				visiteurCollision->physiqueMaillet(maillet->getMasse(), maillet->getVitesse());
			}
		}
		else if (vecteurEnfants[i]->obtenirType() == "portail") { ///Détecte les collisions Rondelle-Portail
			vecteurEnfants[i]->accepter(visiteurCollision);
			//estCollisionPortail = visiteurCollision->getSiCollisionPortail();
		}
		else if (vecteurEnfants[i]->obtenirType() == "mailletOrdi") { ///Détecte les collisions Rondelle-maillet ordinateur
			vecteurEnfants[i]->accepter(visiteurCollision);
			estCollisionMailletOrdi = visiteurCollision->getSiCollisionAvecMailletOrdi();
			if (estCollisionMailletOrdi)
			{
				visiteurCollision->physiqueMaillet(3, mailletOrdi->getVitesse());
			}
		}
			
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::estDansZoneGauche(glm::vec3 point)
///
/// Fonction qui permet de délimiter la zone de gauche de la table pour 
/// le maillet de gauche
///
///@param[in/out] la position de l'objet(glm::vec3)
///
/// @return si l'objet est dans la zone de gauche (double)
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::estDansZoneGauche(glm::vec3 point)
{
	/*if ((-1.0 <= point.x && point.x <= (tableX_ / 2) - 5) && (-(tableY_ / 2) < point.y && point.y < (tableY_ / 2)))*/
	if (utilitaire::DANS_LIMITESXY(point.x, -tableX_, -BORDUREINTERIEUR+1, point.y, -tableY_, tableY_))
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::estDansZoneDroit(glm::vec3 point)
///
/// Fonction qui permet de délimiter la zone de droite de la table pour 
/// le maillet de droite
///
///@param[in/out] la position de l'objet(glm::vec3)
///
/// @return si l'objet est dans la zone de droite (double)
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::estDansZoneDroit(glm::vec3 point)
{
	/*if ((rayon <= point.x && point.x <= (tableX_-rayon)) && (-(tableY_- rayon) <= point.y && point.y <= (tableY_ - rayon)))*/
	if (utilitaire::DANS_LIMITESXY(point.x, BORDUREINTERIEUR-1, tableX_, point.y, -tableY_, tableY_))
	{
		/*std::cout << "zoneDroit true\n";*/
		return true;
	}
	else
	{
		/*std::cout << "zoneDroit false\n";*/
		return false;
	}
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerMaillet(int x, int y)
///
/// Fonction qui permet de deplacer le maillet du premier joueur avec
/// la souris
///
///@param[in] la position en x et y
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerMaillet(int x, int y) {

	NoeudAbstrait* maillet;
	maillet = arbre_->chercher(arbre_->NOM_MAILLET);

	glm::dvec3 posMaillet;

	vue_->convertirClotureAVirtuelle(x, y, posMaillet);


	if (estDansZoneGauche(posMaillet))
	{
		maillet->assignerPositionRelative(posMaillet);
	}	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerMailletOrdi(double dx, double dy )
///
/// Fonction qui permet de deplacer le maillet adverse selon les touches
/// configurees lorsqu'il est en mode humain
///
///@param[in/out] le deplacement du maillet en x et y
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerMailletOrdi(double dx, double dy ) {
	NoeudMailletOrdi* mailletOrdi;
	mailletOrdi = (NoeudMailletOrdi*)arbre_->chercher("mailletOrdi");
	mailletOrdi->setEstOrdi(false);
	glm::vec3 posMaillet;
	posMaillet = mailletOrdi->obtenirPositionRelative();

	//std::cout << "posMaillet avant (" << posMaillet.x << ", " << posMaillet.y << ", " << posMaillet.z << ")\n";
	posMaillet.x += dx;
	posMaillet.y += dy;
	//std::cout << "posMaillet apres (" << posMaillet.x << ", " << posMaillet.y << ", " << posMaillet.z << ")\n";

	if (estDansZoneDroit(posMaillet))
		mailletOrdi->assignerPositionRelative(posMaillet);
}


void FacadeModele::joueurVirtuel(/*glm::vec2 vitesse, double passivite*/)
{
	NoeudMailletOrdi* mailletOrdi;
	mailletOrdi = (NoeudMailletOrdi*)arbre_->chercher("mailletOrdi");
	mailletOrdi->setEstOrdi(true);

}

void FacadeModele::ConfigurationJoueurVirtuel(int porfilJoueurVirtuel[])
{
	//Implementer les changements pour le comportement du joueur virtuel
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherPointsDeControle( )
///
/// Fonction qui permet d'afficher les points de contrôle de la table
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherPointsDeControle()
{
	glm::vec3 points[8] = { glm::vec3((tableX_ + BORDUREEXTERIEUR), -(tableY_ + BORDUREEXTERIEUR), 0.0), glm::vec3((tableX_ + BORDUREEXTERIEUR), 0.0, 0.0), glm::vec3((tableX_ + BORDUREEXTERIEUR), (tableY_ + BORDUREEXTERIEUR), 0.0),
		glm::vec3(0.0, -(tableY_ + BORDUREEXTERIEUR), 0.0), glm::vec3(0.0, (tableY_ + BORDUREEXTERIEUR), 0.0), glm::vec3(-(tableX_ + BORDUREEXTERIEUR), -(tableY_ + BORDUREEXTERIEUR), 0.0),
		glm::vec3(-(tableX_ + BORDUREEXTERIEUR), 0.0, 0.0), glm::vec3(-(tableX_ + BORDUREEXTERIEUR), (tableY_ + BORDUREEXTERIEUR), 0.0) };
	
	for (int i = 0; i < 8; i++)
	{
		NoeudAbstrait* noeudAjoute{ arbre_->creerNoeud(arbre_->NOM_POINT_CONTROLE) };
		noeudAjoute->assignerPositionRelative(points[i]);
		arbre_->ajouter(noeudAjoute);
	}
	
	arbre_->animer(0);
	vue_->animer(0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::tuerPointsDeControle( )
///
/// Fonction qui permet d'effacer les points de contrôle de la table
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::tuerPointsDeControle()
{
	arbre_->tuerPointsDeControle();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getTableX( )
///
/// Fonction qui permet de retourner la coordonnée de la table en x
///
///@param[in/out] aucun
///
/// @return coordonnée en x de la table (double)
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getTableX()
{
	return tableX_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getTableY( )
///
/// Fonction qui permet de retourner la coordonnée de la table en y
///
///@param[in/out] aucun
///
/// @return coordonnée en y de la table (double)
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getTableY()
{
	return tableY_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getTableZ( )
///
/// Fonction qui permet de retourner la coordonnée de la table en z
///
///@param[in/out] aucun
///
/// @return coordonnée en z de la table (double)
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getTableZ()
{
	return tableZ_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setOrbite(bool estOrbite)
///
/// Fonction qui permet de savoir si nous sommes en mode orbite
///
///@param[in] estOrbite: booléen pour le mode orbite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setOrbite(bool estOrbite)
{
	orbite_ = estOrbite;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiserMailletOrdi( )
///
/// Fonction qui permet de replacer le maillet ordi à son point de départ
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiserMailletOrdi()
{
	NoeudAbstrait* mailletOrdi;
	mailletOrdi = arbre_->chercher("mailletOrdi");
	glm::vec3 posMaillet;

	posMaillet.x = tableX_;
	posMaillet.y = 0;

	mailletOrdi->assignerPositionRelative(posMaillet);
	//visiteurCollision = new VisiteurCollision(n);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiserMaillet( )
///
/// Fonction qui permet de replacer le maillet à son point de départ
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiserMaillet()
{
	NoeudAbstrait* maillet;
	maillet = arbre_->chercher("maillet");
	glm::vec3 posMaillet;

	posMaillet.x = -tableX_;
	posMaillet.y = 0;

	maillet->assignerPositionRelative(posMaillet);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiserRondelle( )
///
/// Fonction qui permet de replacer la rondelle à son point de départ
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiserRondelle() {
	NoeudAbstrait* rondelle;
	rondelle = arbre_->chercher("rondelle");
	glm::vec3 posRondelle;

	posRondelle.x = 0;
	posRondelle.y = 0;
	rondelle->setVitesse(0);
	rondelle->assignerPositionRelative(posRondelle);
}

bool FacadeModele::collisionBonus() { return estCollisionBonus; }
bool FacadeModele::collisionMaillet() { return estCollisionMaillet; }
bool FacadeModele::collisionPortail() { return estCollisionPortail; }
bool FacadeModele::collisionMuret() { return estCollisionMuret; }
bool FacadeModele::collisionLimite() { return estCollisionLimite; }
bool FacadeModele::collisionMailletOrdi() { return estCollisionMailletOrdi; }

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::estPartieRapide()
///
/// Fonction qui met partie rapide à true
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::estPartieRapide()
{
	estPartieRapide_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::estTournoi()
///
/// Fonction qui met tournoi à true
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::estTournoi()
{
	estTournoi_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::estEdition()
///
/// Fonction qui met edition à true
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::estEdition()
{
	estEdition_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::estModeTest()
///
/// Fonction qui met mode test à true
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::estModeTest()
{
	estModeTest_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::pasModeTest()
///
/// Fonction qui met mode test à false
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::pasModeTest()
{
	estModeTest_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::pasEdition()
///
/// Fonction qui met édition à false
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::pasEdition()
{
	estEdition_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::pasTournoi()
///
/// Fonction qui met tournoi à false
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::pasTournoi()
{
	estTournoi_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::pasPartieRapide()
///
/// Fonction qui met partie rapide à false
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::pasPartieRapide()
{
	estPartieRapide_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chrono()
///
/// Fonction qui met le timer dans chrono_
///
///@param[in/out] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chrono(int minutes, int secondes)
{
	chronoMinutes_ = minutes;
	chronoSecondes_ = secondes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::nomJoueurVirtuel(char nomJoueurVirtuel)
///
/// Fonction qui met le nom du joueur virtuel dans nomJoueurVirtuel_
///
///@param[in/out] nomJoueurVirtuel (char)
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::nomJoueurVirtuel1(string nomJoueurVirtuel1)
{
	nomJoueurVirtuel1_ = nomJoueurVirtuel1;
	/*cout << nomJoueurVirtuel1_;*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::nomJoueurVirtuel(char nomJoueurVirtuel)
///
/// Fonction qui met le nom du joueur virtuel dans nomJoueurVirtuel_
///
///@param[in/out] nomJoueurVirtuel (char)
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::nomJoueurVirtuel2(string nomJoueurVirtuel2)
{
	nomJoueurVirtuel2_ = nomJoueurVirtuel2;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::nomJoueurVirtuel(char nomJoueurVirtuel)
///
/// Fonction qui met le nom du joueur virtuel dans nomJoueurVirtuel_
///
///@param[in/out] nomJoueurVirtuel (char)
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::nomJoueurVirtuel3(string nomJoueurVirtuel3)
{
	nomJoueurVirtuel3_ = nomJoueurVirtuel3;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::nomJoueurVirtuel(char nomJoueurVirtuel)
///
/// Fonction qui met le nom du joueur virtuel dans nomJoueurVirtuel_
///
///@param[in/out] nomJoueurVirtuel (char)
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::nomJoueurVirtuel4(string nomJoueurVirtuel4)
{
	nomJoueurVirtuel4_ = nomJoueurVirtuel4;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::butGauche(int buts)
///
/// Fonction qui met le nombre de buts du maillet gauche dans butGauche_
///
///@param[in/out] nombre de buts (int)
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::butGauche(int buts)
{
	butGauche_ = buts;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::butDroit(int buts)
///
/// Fonction qui met le nombre de buts du maillet droit dans butDroit_
///
///@param[in/out] nombre de buts (int)
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::butDroit(int buts)
{
	butDroit_ = buts;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::modifierCoordonnerObjetSelectionner()
///
/// Fonction qui change les coordonnees d'un objet selectionner.
///
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::modifierCoordonnerObjetSelectionner()
{
	const glm::vec3& positionRelative{posX, posY, posZ};
	//cout << "POSITION XYZ : " << posX << " ; " << posY << " ; " << posZ << endl;

	conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	for (size_t i = 0; i < vecteurEnfants.size(); i++) 
	{
		if (vecteurEnfants[i]->estSelectionne())
		{
			vecteurEnfants[i]->assignerPositionRelative(positionRelative);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::obtenirCoordonnerObjetSelectionner()
///
/// Fonction qui retourne les coordonnees (x,y,z) d'un objet selectionner.
///
///
/// @return une vecteur a 3 dimensions representant la position de l'objet selectionner.
///
////////////////////////////////////////////////////////////////////////
glm::vec3 FacadeModele::obtenirCoordonnerObjetSelectionner()
{


	conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->estSelectionne())
		{
			return vecteurEnfants[i]->obtenirPositionRelative();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirCoordonnerX()
///
/// Fonction qui retourne la coordonnee en X d'un objet selectionner.
/// Si l'objet n'est pas selectionner, 0 est retourner.
///
///
/// @return la coordonne en X ou 0.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirCoordonnerX()
{
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->estSelectionne())
		{
			posY = vecteurEnfants[i]->obtenirPositionRelative().y;
			posZ = vecteurEnfants[i]->obtenirPositionRelative().z;

			return vecteurEnfants[i]->obtenirPositionRelative().x;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirCoordonnerY()
///
/// Fonction qui retourne la coordonnee en Y d'un objet selectionner.
/// Si l'objet n'est pas selectionner, 0 est retourner.
///
///
/// @return la coordonne en Y ou 0.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirCoordonnerY()
{
	//cout << "obtenirCoord y dans y : " << posY << endl;
	return posY;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerFacteurEchelle(double echelle)
///
/// Fonction qui modifie l'echelle d'un objet selectionner.
///
/// param[in] : echelle : nouvelle echelle de l'objet
///
/// @return rien.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerFacteurEchelle(double echelle)
{
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();

	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->estSelectionne())
		{

			vecteurEnfants[i]->setFacteurEchelle(echelle);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirFacteurEchelle()
///
/// Fonction qui retourne l'echelle d'un objet selectionner.
///
///
/// @return l'echelle de l'objet ou 0.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirFacteurEchelle()
{
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->estSelectionne())
		{
			/*std::cout << "Echelle : " << vecteurEnfants[i]->getFacteurEchelle() << std::endl;*/
			return vecteurEnfants[i]->getFacteurEchelle();
		}
	}
	return 0;
}


void FacadeModele::afficherButs()
{
	glm::vec3 points[8] = { glm::vec3(-(tableX_ + 10), -3.0, 0.0), glm::vec3((tableX_ + 4), -3.0, 0.0) };

	for (int i = 0; i < 2; i++)
	{
		NoeudAbstrait* noeudAjoute{ arbre_->creerNoeud(arbre_->NOM_BUT) };
		noeudAjoute->assignerPositionRelative(points[i]);
		arbre_->ajouter(noeudAjoute);
	}

	arbre_->animer(0);
	vue_->animer(0);
}


bool FacadeModele::butCoteGauche()
{
	NoeudAbstrait* rondelle;
	rondelle = arbre_->chercher("rondelle");
	NoeudRondelle* noeud = (NoeudRondelle*)rondelle;
	return noeud->getEstButGauche();
}

bool FacadeModele::butCoteDroit()
{
	NoeudAbstrait* rondelle;
	rondelle = arbre_->chercher("rondelle");
	NoeudRondelle* noeud = (NoeudRondelle*)rondelle;
	return noeud->getEstButDroit();
}

void FacadeModele::nonButGauche()
{
	NoeudRondelle* rondelle;
	rondelle = (NoeudRondelle*)arbre_->chercher("rondelle");
	rondelle->setEstButGauche(false);
}

void FacadeModele::nonButDroit()
{
	NoeudRondelle* rondelle;
	rondelle = (NoeudRondelle*)arbre_->chercher("rondelle");
	rondelle->setEstButDroit(false);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerRotation(double rot)
///
/// Fonction qui modifie la rotation d'un objet selectionner.
///
/// param[in] : rot : nouvelle rotation de l'objet
///
/// @return rien.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerRotation(double rot)
{
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();

	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->estSelectionne())
		{

			vecteurEnfants[i]->setAngleRotation(rot);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirRotation()
///
/// Fonction qui retourne la rotation d'un objet selectionner.
///
///
/// @return la rotation de l'objet ou 0.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirRotation()
{
	conteneur_enfants vecteurEnfants = arbre_->getEnfants();
	for (size_t i = 0; i < vecteurEnfants.size(); i++)
	{
		if (vecteurEnfants[i]->estSelectionne())
		{
			/*std::cout << "Rotation : " << vecteurEnfants[i]->getAngleRotation() << std::endl;*/
			return vecteurEnfants[i]->getAngleRotation();
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonRondeleMaillet()
///
/// Fonction jouant un son lors de la collision rondelle.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sonRondeleMaillet()
{
	Son::obtenirInstance()->jouerSon(6);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonRondeleMailletOrdi()
///
/// Fonction jouant un son lors de la collision rondelle mailletOrdi.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sonRondeleMailletOrdi()
{
	Son::obtenirInstance()->jouerSon(9);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonRondeleBonus()
///
/// Fonction jouant un son lors de la collision rondelle bonus.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sonRondeleBonus()
{
	Son::obtenirInstance()->jouerSon(4);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonRondeleBut()
///
/// Fonction jouant un son lors de la collision rondelle et but.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sonRondeleBut()
{
	Son::obtenirInstance()->jouerSon(2);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonRondeleBordure()
///
/// Fonction jouant un son lors de la collision rondelle  et bordure de la table.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sonRondeleBordure()
{
	Son::obtenirInstance()->jouerSon(8);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonRondelePortail()
///
/// Fonction jouant un son lors de la collision rondelle portail.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sonRondelePortail()
{
	Son::obtenirInstance()->jouerSon(5);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonRondeleFrappee()
///
/// Fonction jouant un son lorsque la rondelle est frappee.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sonRondeleFrappee()
{
	Son::obtenirInstance()->jouerSon(1);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonJeuF()
///
/// Fonction jouant un son en tout temps lors d un tournoi ou d une partie rapide
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::sonJeuF()
{
	Son::obtenirInstance()->sonModeJeu(true);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::dechargementSon()
///
/// Fonction qui decharge tout les sons pour l initialisation.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::dechargementSon()
{
	Son::obtenirInstance()->dechargerSon();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::sonRondeleMuret()
///
/// Fonction jouant un son lors de la collision rondelle et muret.
///
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sonRondeleMuret()
{
	Son::obtenirInstance()->jouerSon(3);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
