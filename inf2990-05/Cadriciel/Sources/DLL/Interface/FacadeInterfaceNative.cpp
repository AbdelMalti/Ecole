////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"

#include "BancTests.h"

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fen�tre
	/// identifi�e par le handle pass� en param�tre.  Cette fonction doit
	/// �tre la premi�re � �tre appel�e, car la cr�ation de l'objet du mod�le
	/// C++ s'attend � avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction lib�re le contexte OpenGL. Cette fonction doit �tre la
	/// derni�re � �tre appel�e, car elle lib�re �galement l'objet du mod�le
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// D�sinitialisation de la fa�ade.  Le fait de le faire apr�s la
		// d�sinitialisation du contexte OpenGL aura pour cons�quence que la
		// lib�ration des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la sc�ne.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la sc�ne.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour d�tecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit �tre appel�e lorsque la fen�tre est
	/// redimensionn�e afin d'ajuster les param�tres de la machine � �tats
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fen�tre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fen�tre.
	/// @param[in] hauteur : La nouvelle hauteur de la fen�tre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		if (FacadeModele::obtenirInstance()->obtenirVue() != nullptr)
			FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(largeur, hauteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
	///
	/// Cette fonction effectue les diff�rents calculs d'animations
	/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
	/// physique du jeu.
	///
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float)temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le pr�sent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arri�re sur le pr�sent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'ex�cuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont r�ussi, 1 si au moins un test a �chou�
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void initialiserRectangle(int pX, int pY)
	///
	/// Cette fonction initialise le rectangle �lastique
	///
	/// @param[in] pX : point initial de la souris en x
	/// @param[in] pY : point initial de la souris en y
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserRectangle(int pX, int pY)
	{
		FacadeModele::obtenirInstance()->initialiserRectangle(pX, pY);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void mettreAJourRectangle(int piX, int piY, int paX, int paY, int pdX, int pdY)
	///
	/// Cette fonction met � jour le rectangle �lastique
	///
	/// @param[in] piX : point initial en x
	/// @param[in] piY : point initial en y
	/// @param[in] paY : point avant en x
	/// @param[in] paY : point avant en y
	/// @param[in] pdY : point apr�s en x
	/// @param[in] pdY : point apr�s en y
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void mettreAJourRectangle(int piX, int piY, int paX, int paY, int pdX, int pdY, bool enSelection)
	{
		FacadeModele::obtenirInstance()->mettreAJourRectangle(piX, piY, paX, paY, pdX, pdY, enSelection);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void terminerRectangle(int pIX, int pIY, int pFX, int pFY)
	///
	/// Cette fonction termine le rectangle �lastique
	///
	/// @param[in] pIX : point ancrage en x
	/// @param[in] pIY : point ancrage en y
	/// @param[in] pIY : point final en x
	/// @param[in] pIY : point final en y
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void terminerRectangle(int pIX, int pIY, int pFX, int pFY)
	{
		FacadeModele::obtenirInstance()->terminerRectangle(pIX, pIY, pFX, pFY);
	}

	//__declspec(dllexport) void convertirPoints(int x, int y)
	//{
	//	//vue::Vue::convertirClotureAVirtuelle(x, y,); //A faire quand le fichier va etre mis a jour
	//}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void ajouterNoeudBonus(int posX, int posY)
	///
	/// Cette fonction permet d'ajouter un noeud dans l'arbre
	///
	/// @param[in] posX : position de l'ajout en x
	/// @param[in] posY : position de l'ajout en y
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void ajouterNoeudBonus(int posX, int posY)
	{
		 FacadeModele::obtenirInstance()->ajouterNoeudBonus(posX, posY);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void initialiserDeplacement(double x, double y)
	///
	/// Cette fonction initialise le d�placement
	///
	/// @param[in] x : point initial du d�placement en x
	/// @param[in] y : point initial du d�placement en y
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserDeplacement(double x, double y)
	{
		FacadeModele::obtenirInstance()->initialiserDeplacement(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void deplacement(double x, double y)
	///
	/// Cette fonction permet d'effectuer le d�placement
	///
	/// @param[in] x : position en x lors du d�placement
	/// @param[in] y : position en y lors du d�placement
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void deplacement(double x, double y)
	{
		FacadeModele::obtenirInstance()->deplacement(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void miseAEchelle(double y)
	///
	/// Cette fonction permet de mettre � l'�chelle les objets qui vont �tre sur la table
	///
	/// @param[in] y : position en y lors de la mise � l'�chelle
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void miseAEchelle(double y)
	{
		FacadeModele::obtenirInstance()->miseAEchelle(y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void supprimer()
	///
	/// Cette fonction permet de mettre supprimer des objets sur la table
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void supprimer()
	{
		FacadeModele::obtenirInstance()->supprimer();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void ajouterNoeudPortail(int posX, int posY)
	///
	/// Cette fonction permet d'ajouter des noeuds portails
	///
	/// @param[in] posX : position en x de l'ajout
	/// @param[in] posY : position en y de l'ajout
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void ajouterNoeudPortail(int posX, int posY)
	{
		FacadeModele::obtenirInstance()->ajouterNoeudPortail(posX, posY);
	}

	//////////////////////////////////////////////////////////////////////////
	/////
	///// @fn	__declspec(dllexport) void ajouterNoeudMaillet()
	/////
	///// Cette fonction permet d'ajouter un noeud maillet
	/////
	///// @return Aucune.
	/////
	//////////////////////////////////////////////////////////////////////////
	//__declspec(dllexport) void ajouterNoeudMaillet()
	//{
	//	FacadeModele::obtenirInstance()->ajouterNoeudMaillet();
	//}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void ajouterNoeudMuret(int posX, int posY)
	///
	/// Cette fonction permet d'ajouter des noeuds murets
	///
	/// @param[in] posX : position en x de l'ajout
	/// @param[in] posY : position en y de l'ajout
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void ajouterNoeudMuret(int posX, int posY)
	{
		FacadeModele::obtenirInstance()->ajouterNoeudMuret(posX, posY);
	}

	//////////////////////////////////////////////////////////////////////////
	/////
	///// @fn	__declspec(dllexport)  void ajouterNoeudRondelle()
	/////
	///// Cette fonction permet d'ajouter un noeud rondelle
	/////
	///// @return Aucune.
	/////
	//////////////////////////////////////////////////////////////////////////
	//__declspec(dllexport)  void ajouterNoeudRondelle()
	//{
	//	FacadeModele::obtenirInstance()->ajouterNoeudRondelle();
	//}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void rotation(double y)
	///
	/// Cette fonction permet de faire une rotation
	///
	/// @param[in] y : position en y de la rotation
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void rotation(double y)
	{
		FacadeModele::obtenirInstance()->rotation(y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void initialiserRotation(double y)
	///
	/// Cette fonction permet d'initialiser la rotation
	///
	/// @param[in] y : position initial en y de la rotation
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserRotation(double y)
	{
		FacadeModele::obtenirInstance()->initialiserRotation(y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void initialiserDuplication(double x, double y)
	///
	/// Cette fonction permet d'initialiser la duplication
	///
	/// @param[in] x : position initial en x de la duplication
	/// @param[in] y : position initial en y de la duplication
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserDuplication(double x, double y)
	{
		FacadeModele::obtenirInstance()->initialiserDuplication(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void duplication(double x, double y)
	///
	/// Cette fonction permet de faire la duplication
	///
	/// @param[in] x : position en x de la duplication
	/// @param[in] y : position en y de la duplication
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void duplication(double x, double y)
	{
		FacadeModele::obtenirInstance()->duplication(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void deplacerXY(double deplacementX, double deplacementY)
	///
	/// Cette fonction permet de deplacer la vue en x et en y
	///
	/// @param[in] deplacementX : deplacement en x
	/// @param[in] deplacementY : deplacement en y
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void deplacerXY(double deplacementX, double deplacementY)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void selectionner(int i, int j, bool estSelectionne)
	///
	/// Cette fonction permet de faire une s�lection
	///
	/// @param[in] i : emplacement i de la s�lection
	/// @param[in] j : emplacement j de la s�lection
	/// @param[in] estSelectionne : bool�en pour affirmer sa s�lection
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void selectionner(int i, int j, bool estSelectionne)
	{
		FacadeModele::obtenirInstance()->selectionner(i, j, estSelectionne);
	}

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport)double __cdecl obtenirCoefficientFriction()
	 ///
	 /// Cette fonction permet d'obtenir le coefficient de friction
	 ///
	 /// @return le coefficient de friction (double)
	 ///
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport)double __cdecl obtenirCoefficientFriction()
	 {
		 return FacadeModele::obtenirInstance()->obtenirCoefficientFriction();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport)void __cdecl  modifierCoefficientFriction(double friction)
	 ///
	 /// Cette fonction permet de modifier le coefficient de friction
	 ///
	 /// @param[in] friction : la valeur de la friction
	 /// 
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport)void __cdecl  modifierCoefficientFriction(double friction)
	 {
		 FacadeModele::obtenirInstance()->modifierCoefficientFriction(friction);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport)double __cdecl obtenirAcceleration()
	 ///
	 /// Cette fonction permet d'obtenir la valeur de l'acc�l�ration
	 /// 
	 /// @return la valeur de l'acc�l�ration (double)
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport)double __cdecl obtenirAcceleration()
	 {
		 return FacadeModele::obtenirInstance()->obtenirAcceleration();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport)void __cdecl modifierAcceleration(double acceleration)
	 ///
	 /// Cette fonction permet de modifier l'acc�l�ration
	 ///
	 /// @param[in] acceleration : la valeur de l'acc�l�ration
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport)void __cdecl modifierAcceleration(double acceleration)
	 {
		 FacadeModele::obtenirInstance()->modifierAcceleration(acceleration);
	 }
	 
	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport)double __cdecl obtenirCoefficientRebond() 
	 ///
	 /// Cette fonction permet d'obtenir le coefficient de rebond
	 ///
	 /// @return le coefficient de rebond (double)
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport)double __cdecl obtenirCoefficientRebond() 
	 {
		 return FacadeModele::obtenirInstance()->obtenirRebond();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport)void __cdecl modifierCoefficientRebond(double rebond)
	 ///
	 /// Cette fonction permet de modifier le coefficent de rebond
	 ///
	 /// @param[in] rebond : la valeur du rebond
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport)void __cdecl modifierCoefficientRebond(double rebond)
	 {
		 FacadeModele::obtenirInstance()->modifierRebond(rebond);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport)  void sauvegarderZoneToXml(char destination[])
	 ///
	 /// Cette fonction permet de sauvegarder la zone en xml
	 ///
	 /// @param[in] destination[] : la destination de la sauvegarde
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport)  void sauvegarderZoneToXml(char destination[])
	 {
		 FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->sauvegarderZoneXml(destination);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport)  void restaurerZoneXml(char destination[])
	 ///
	 /// Cette fonction permet de restaurer la zone xml
	 ///
	 /// @param[in] destination[] : la destination de la zone
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport)  void restaurerZoneXml(char destination[])
	 {
		 FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->restaurerZoneXml(destination);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void	nouvelleScene()
	 ///
	 /// Cette fonction permet de charger une nouvelle sc�ne
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void	nouvelleScene()
	 {
		 FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->nouvelleScene();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void deselectionnerTout()
	 ///
	 /// Cette fonction permet de d�s�lectionner tout les enfants et le noeud
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void deselectionnerTout()
	 {
		 FacadeModele::obtenirInstance()->deselectionnerTout();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void tuerRondelle()
	 ///
	 /// Cette fonction permet d'effacer la rondelle
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void tuerRondelle()
	 {
		 FacadeModele::obtenirInstance()->tuerRondelle();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void tuerMaillet()
	 ///
	 /// Cette fonction permet d'effacer le maillet
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void tuerMaillet()
	 {
		 FacadeModele::obtenirInstance()->tuerMaillet();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void tuerMailletOrdi()
	 ///
	 /// Cette fonction permet d'effacer le maillet ordi
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void tuerMailletOrdi()
	 {
		 FacadeModele::obtenirInstance()->tuerMailletOrdi();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void genererRondelle()
	 ///
	 /// Cette fonction permet de g�n�rer la rondelle sur la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void genererRondelle()
	 {
		 FacadeModele::obtenirInstance()->genererRondelle();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void genererMaillet()
	 ///
	 /// Cette fonction permet de g�n�rer le maillet sur la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void genererMaillet()
	 {
		 FacadeModele::obtenirInstance()->genererMaillet();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void genererMailletOrdi()
	 ///
	 /// Cette fonction permet de g�n�rer le maillet ordi sur la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void genererMailletOrdi()
	 {
		 FacadeModele::obtenirInstance()->genererMailletOrdi();
	 }
	 
	/* __declspec(dllexport) void ajoutRondelleMaillet()
	 {
		 FacadeModele::obtenirInstance()->ajoutRondelleMaillet();
	 }*/

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void __cdecl bougerMaillet(int entrerUtilisateur)
	 ///
	 /// Cette fonction permet de bouger le maillet
	 ///
	 /// @param[in] entrerUtilisateur : l'entr�e de l'utilisateur selon un integer
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl bougerMaillet(int entrerUtilisateur)
	 {
			 FacadeModele::obtenirInstance()->bougerMaillet(entrerUtilisateur);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void __cdecl deplacerMaillet(int x, int y)
	 ///
	 /// Cette fonction permet de d�placer le maillet
	 ///
	 /// @param[in] x : position en x du maillet
	 /// @param[in] y : position en y du maillet
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl deplacerMaillet(int x, int y)
	 {
		 FacadeModele::obtenirInstance()->deplacerMaillet(x, y);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void __cdecl animationJeu()
	 ///
	 /// Cette fonction permet d'animer le jeu
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl animationJeu()
	 {
			 FacadeModele::obtenirInstance()->animationJeu();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void __cdecl joueurVirtuel() 
	 ///
	 /// Cette fonction permet de d�crire les d�placement du joueur virtuel
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl joueurVirtuel() 
	{
		 FacadeModele::obtenirInstance()->joueurVirtuel();
	}

	 __declspec(dllexport) void __cdecl ConfigurationJoueurVirtuel(int porfilJoueurVirtuel[])
	 {

	 }
	
	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void __cdecl afficherPointsDeControle()
	 ///
	 /// Cette fonction permet d'afficher les points de contr�le de la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl afficherPointsDeControle()
	 {
		 FacadeModele::obtenirInstance()->afficherPointsDeControle();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void __cdecl tuerPointsDeControle()
	 ///
	 /// Cette fonction permet d'effacer les points de contr�le de la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl tuerPointsDeControle()
	 {
		 FacadeModele::obtenirInstance()->tuerPointsDeControle();
	 }

	 ////////////////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void __cdecl rotaterXY(double rotationX, double rotationY)
	 ///
	 /// Cette fonction permet de faire des rotations de la cam�ra autour du point vis�
	 ///
	 /// @param[in]  rotationX : Rotation en X
	 /// @param[in]  rotationY : Rotation en Y
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl rotaterXY(double rotationX, double rotationY)
	 {
		 FacadeModele::obtenirInstance()->obtenirVue()->rotaterXY(rotationX, rotationY);
	 }

	 ////////////////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void __cdecl setOrbite(bool estOrbite)
	 ///
	 /// Cette fonction permet de savoir si nous sommes en mode orbite
	 ///
	 /// @param[in]  estOrbite : valeur du bool�en
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl setOrbite(bool estOrbite)
	 {
		 FacadeModele::obtenirInstance()->setOrbite(estOrbite);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) void reinitialiserMailletOrdi()
	 ///
	 /// Cette fonction permet de r�initialiser le maillet ordi � son emplacement de d�part
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void reinitialiserMailletOrdi()
	 {
		 FacadeModele::obtenirInstance()->reinitialiserMailletOrdi();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void __cdecl reinitialiserMaillet()
	 ///
	 /// Cette fonction permet de r�initialiser le maillet � son emplacement de d�part
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl reinitialiserMaillet()
	 {
		 FacadeModele::obtenirInstance()->reinitialiserMaillet();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void __cdecl reinitialiserRondelle()
	 ///
	 /// Cette fonction permet de r�initialiser la rondelle � son emplacement de d�part
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl reinitialiserRondelle()
	 {
		 FacadeModele::obtenirInstance()->reinitialiserRondelle();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn 	 __declspec(dllexport) bool __cdecl collisionBonus()
	 ///
	 /// Cette fonction permet de d�tecter la collision avec le bonus
	 ///
	 /// @return s'il y a une collision avec le bonus
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) bool __cdecl collisionBonus()
	 {
		 return FacadeModele::obtenirInstance()->collisionBonus();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) bool __cdecl collisionMailet()
	 ///
	 /// Cette fonction permet de d�tecter la collision avec le maillet
	 ///
	 /// @return s'il y a une collision avec le maillet
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) bool __cdecl collisionMailet()
	 {
		 return FacadeModele::obtenirInstance()->collisionMaillet();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn  __declspec(dllexport) bool __cdecl collisionMuret()
	 ///
	 /// Cette fonction permet de d�tecter la collision avec le muret
	 ///
	 /// @return s'il y a une collision avec le muret
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) bool __cdecl collisionMuret()
	 {
		 return FacadeModele::obtenirInstance()->collisionMuret();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) bool __cdecl collisionPortail()
	 ///
	 /// Cette fonction permet de d�tecter la collision avec le portail
	 ///
	 /// @return s'il y a une collision avec le portail
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) bool __cdecl collisionPortail()
	 {
		 return FacadeModele::obtenirInstance()->collisionPortail();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) bool __cdecl collisionLimiteTable()
	 ///
	 /// Cette fonction permet de d�tecter la collision avec la limite de la table
	 ///
	 /// @return s'il y a une collision avec la limite de la table
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) bool __cdecl collisionLimiteTable()
	 {
		 return FacadeModele::obtenirInstance()->collisionLimite();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) bool __cdecl collisionMailetOrdi()
	 ///
	 /// Cette fonction permet de d�tecter la collision avec le maillet ordi
	 ///
	 /// @return s'il y a une collision avec le maillet ordi
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) bool __cdecl collisionMailetOrdi()
	 {
		 return FacadeModele::obtenirInstance()->collisionMailletOrdi();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void estPartieRapide()
	 ///
	 /// Cette fonction permet d'envoyer le booleen de partie rapide
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void estPartieRapide()
	 {
		 FacadeModele::obtenirInstance()->estPartieRapide();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void estTournoi()
	 ///
	 /// Cette fonction permet d'envoyer le booleen de tournoi
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void estTournoi()
	 {
		 FacadeModele::obtenirInstance()->estTournoi();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void estModeTest()
	 ///
	 /// Cette fonction permet d'envoyer le booleen de modeTest
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void estModeTest()
	 {
		 FacadeModele::obtenirInstance()->estModeTest();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void estEdition()
	 ///
	 /// Cette fonction permet d'envoyer le booleen d'�dition
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void estEdition()
	 {
		 FacadeModele::obtenirInstance()->estEdition();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void pasPartieRapide()
	 ///
	 /// Cette fonction permet d'envoyer le booleen de partie rapide
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void pasPartieRapide()
	 {
		 FacadeModele::obtenirInstance()->pasPartieRapide();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void pasTournoi()
	 ///
	 /// Cette fonction permet d'envoyer le booleen de tournoi
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void pasTournoi()
	 {
		 FacadeModele::obtenirInstance()->pasTournoi();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void pasModeTest()
	 ///
	 /// Cette fonction permet d'envoyer le booleen de mode test
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void pasModeTest()
	 {
		 FacadeModele::obtenirInstance()->pasModeTest();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void pasEdition()
	 ///
	 /// Cette fonction permet d'envoyer le booleen d'�dition
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void pasEdition()
	 {
		 FacadeModele::obtenirInstance()->pasEdition();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void chrono()
	 ///
	 /// Cette fonction permet d'envoyer le chrono
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void chrono(int minutes, int secondes)
	 {
		 FacadeModele::obtenirInstance()->chrono(minutes, secondes);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void nomJoueurVirtuel1(char* nomJoueurVirtuel1)
	 ///
	 /// Cette fonction permet d'envoyer le nom du joueur virtuel 1
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void nomJoueurVirtuel1(char* nomJoueurVirtuel1)
	 {
		 FacadeModele::obtenirInstance()->nomJoueurVirtuel1(nomJoueurVirtuel1);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void nomJoueurVirtuel2(char* nomJoueurVirtuel2)
	 ///
	 /// Cette fonction permet d'envoyer le nom du joueur virtuel 2
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void nomJoueurVirtuel2(char* nomJoueurVirtuel2)
	 {
		 FacadeModele::obtenirInstance()->nomJoueurVirtuel2(nomJoueurVirtuel2);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void nomJoueurVirtuel3(char* nomJoueurVirtuel3)
	 ///
	 /// Cette fonction permet d'envoyer le nom du joueur virtuel 3
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void nomJoueurVirtuel3(char* nomJoueurVirtuel3)
	 {
		 FacadeModele::obtenirInstance()->nomJoueurVirtuel3(nomJoueurVirtuel3);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void nomJoueurVirtuel4(char* nomJoueurVirtuel4)
	 ///
	 /// Cette fonction permet d'envoyer le nom du joueur virtuel 4
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void nomJoueurVirtuel4(char* nomJoueurVirtuel4)
	 {
		 FacadeModele::obtenirInstance()->nomJoueurVirtuel4(nomJoueurVirtuel4);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void butGauche(int buts)
	 ///
	 /// Cette fonction permet d'envoyer le nom nombre de but du maillet gauche
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void butGauche(int buts)
	 {
		 FacadeModele::obtenirInstance()->butGauche(buts);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void butDroit(int buts)
	 ///
	 /// Cette fonction permet d'envoyer le nom nombre de but du maillet droit
	 ///
	 /// @return Aucune
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void butDroit(int buts)
	 {
		 FacadeModele::obtenirInstance()->butDroit(buts);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) double obtenirPosX()
	 ///
	 /// Cette fonction permet d'envoyer la position en x de l'objet selectionne.
	 ///
	 /// @return La position en x de l'objet selectionner.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) double obtenirPosX()
	 {
		 return FacadeModele::obtenirInstance()->obtenirCoordonnerX();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) double obtenirPosY()
	 ///
	 /// Cette fonction permet d'envoyer la position en y de l'objet selectionne.
	 ///
	 /// @return La position en y de l'objet selectionner.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) double obtenirPosY()
	 {
		 return FacadeModele::obtenirInstance()->obtenirCoordonnerY();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) double obtenirPosZ()
	 ///
	 /// Cette fonction permet d'envoyer la position en z de l'objet selectionne.
	 ///
	 /// @return La position en z de l'objet selectionner.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) double obtenirPosZ()
	 {
		 return 0;
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) int obtenirNombreObjetSelectionner()
	 ///
	 /// Cette fonction permet de retourner le nombre d'objet qui sont selectionner afin de gerer les cas
	 /// ou il y en a plus qu'un.
	 ///
	 /// @return Le nombre d'objet qui sont selectionner.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) int obtenirNombreObjetSelectionner() 
	 {
		 return FacadeModele::obtenirInstance()->nombreObjetSelectioner;
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void assignerPosX(double x)
	 ///
	 /// Cette fonction permet d'assigner une nouvelle position en x a l'objet selectionner.
	 /// 
	 /// @param[in] : x : position en x qui sera assigner a l'objet selectionner.
	 ///
	 /// @return Aucun.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void assignerPosX(double x)
	 {
		 FacadeModele::obtenirInstance()->posX = x;
		 FacadeModele::obtenirInstance()->modifierCoordonnerObjetSelectionner();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void assignerPosY(double y)
	 ///
	 /// Cette fonction permet d'assigner une nouvelle position en y a l'objet selectionner.
	 /// 
	 /// @param[in] : y : position en y qui sera assigner a l'objet selectionner.
	 ///
	 /// @return Aucun.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void assignerPosY(double y)
	 {
		 FacadeModele::obtenirInstance()->posY = y;
		 FacadeModele::obtenirInstance()->modifierCoordonnerObjetSelectionner();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void assignerPosZ(double z)
	 ///
	 /// Cette fonction permet d'assigner une nouvelle position en z a l'objet selectionner.
	 /// 
	 /// @param[in] : z : position en z qui sera assigner a l'objet selectionner.
	 ///
	 /// @return Aucun.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void assignerPosZ(double z)
	 {
		 FacadeModele::obtenirInstance()->posZ = z;
		 FacadeModele::obtenirInstance()->modifierCoordonnerObjetSelectionner();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void assignerEchelle(double echelle)
	 ///
	 /// Cette fonction permet d'assigner une nouvelle echelle a l'objet selectionner.
	 ///
	 /// @param[in] : echelle : nouvelle valeur a l'echelle.
	 /// @return Aucun.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void assignerEchelle(double echelle)
	 {
		 FacadeModele::obtenirInstance()->assignerFacteurEchelle(echelle);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) double obtenirEchelle()
	 ///
	 /// Cette fonction permet d'obtenir une nouvelle echelle a l'objet selectionner.
	 ///
	 /// @return nouvelle echelle a l'objet
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) double obtenirEchelle()
	 {
		 return FacadeModele::obtenirInstance()->obtenirFacteurEchelle();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) void assignerRotation(double rot)
	 ///
	 /// Cette fonction permet d'assigner une nouvelle rotation a l'objet selectionner.
	 /// 
	 /// @param[in] : rot : nouvelle rotation de l'objet.
	 ///
	 /// @return Aucun.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void assignerRotation(double rot)
	 {
		 FacadeModele::obtenirInstance()->assignerRotation(rot);
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn __declspec(dllexport) double obtenirRotation(double rot)
	 ///
	 /// Cette fonction permet retourne  la rotation de l'objet selectionner.
	 ///
	 /// @return valeur de la rotation de l'objet selectionner.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) double obtenirRotation()
	 {
		 return FacadeModele::obtenirInstance()->obtenirRotation();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void __cdecl afficherPointsDeControle()
	 ///
	 /// Cette fonction permet d'afficher les points de contr�le de la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl afficherButs()
	 {
		 FacadeModele::obtenirInstance()->afficherButs();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) bool __cdecl butCoteGauche()
	 ///
	 /// Cette fonction permet d'afficher les points de contr�le de la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) bool __cdecl butCoteGauche()
	 {
		 return FacadeModele::obtenirInstance()->butCoteGauche();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) bool __cdecl butCoteDroit()
	 ///
	 /// Cette fonction permet d'afficher les points de contr�le de la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) bool __cdecl butCoteDroit()
	 {
		 return FacadeModele::obtenirInstance()->butCoteDroit();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void __cdecl nonButGauche()
	 ///
	 /// Cette fonction permet d'afficher les points de contr�le de la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl nonButGauche()
	 {
		 FacadeModele::obtenirInstance()->nonButGauche();
	 }

	 ////////////////////////////////////////////////////////////////////////
	 ///
	 /// @fn   __declspec(dllexport) void __cdecl nonButDroit()
	 ///
	 /// Cette fonction permet d'afficher les points de contr�le de la table
	 ///
	 /// @return Aucune.
	 /// 
	 ////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void __cdecl nonButDroit()
	 {
		 FacadeModele::obtenirInstance()->nonButDroit();
	 }

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn   	 __declspec(dllexport) void sonJeuF()
	///
	/// Cette fonction permet de jouer un son en fond lorsqu on joue
	///
	/// @return Aucune.
	/// 
	////////////////////////////////////////////////////////////////////////
	 __declspec(dllexport) void sonJeuF()
	 {

		 FacadeModele::obtenirInstance()->sonJeuF();
	 }
}
////////////////////////////////////////////////////////////////////////
///
/// @fn   	 __declspec(dllexport) void dechargementSon()
///
/// Cette fonction permet de pauser un son en fond lorsqu on joue
///
/// @return Aucune.
/// 
////////////////////////////////////////////////////////////////////////
__declspec(dllexport) void dechargementSon()
{
	FacadeModele::obtenirInstance()->dechargementSon();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////