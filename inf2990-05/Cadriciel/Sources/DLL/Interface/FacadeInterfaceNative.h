////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__

extern "C" {

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();
	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void animer(double temps);
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();
	__declspec(dllexport) int obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
	__declspec(dllexport) void initialiserRectangle(int pX, int pY);
	__declspec(dllexport) void mettreAJourRectangle(int piX, int piY, int paX, int paY, int pdX, int pdY, bool enSelection);
	__declspec(dllexport) void terminerRectangle(int pIX, int pIY, int pFX, int pFY);
	__declspec(dllexport) void ajouterNoeudMuret(int posX, int posY);
	/*__declspec(dllexport) void ajouterNoeudRondelle();*/
	__declspec(dllexport) void ajouterNoeudBonus(int posX, int posY);
	__declspec(dllexport) void ajouterNoeudPortail(int posX, int posY);
	/*__declspec(dllexport) void ajouterNoeudMaillet();*/
	__declspec(dllexport) void selectionner(int i, int j, bool estSelectionne);
	__declspec(dllexport) void deplacerXY(double deplacementX, double deplacementY);
	__declspec(dllexport) void initialiserDeplacement(double x, double y);
	__declspec(dllexport) void deplacement(double x, double y);
	__declspec(dllexport) void miseAEchelle(double y);
	__declspec(dllexport) void supprimer();
	__declspec(dllexport) void rotation(double y);
	__declspec(dllexport) void duplication(double x, double y);
	__declspec(dllexport) void initialiserRotation(double y);
	__declspec(dllexport) double obtenirCoefficientFriction();
	__declspec(dllexport) void modifierCoefficientFriction(double friction);
	__declspec(dllexport) double obtenirAcceleration();
	__declspec(dllexport) void modifierAcceleration(double rebond);
	__declspec(dllexport) double obtenirCoefficientRebond();
	__declspec(dllexport) void modifierRebond(double rebond);
	__declspec(dllexport) void restaurerZoneXml(char destination[]);
	__declspec(dllexport) void sauvegarderZoneToXml(char destination[]);
	__declspec(dllexport) void	nouvelleScene();
	__declspec(dllexport) void deselectionnerTout();
	__declspec(dllexport) void tuerMaillet();
	__declspec(dllexport) void tuerMailletOrdi();
	__declspec(dllexport) void tuerRondelle();
	__declspec(dllexport) void genererMaillet();
	__declspec(dllexport) void genererMailletOrdi();
	__declspec(dllexport) void genererRondelle();
	__declspec(dllexport) void reinitialiserMailletOrdi();
	__declspec(dllexport) void reinitialiserMaillet();
	__declspec(dllexport) void reinitialiserRondelle();

	__declspec(dllexport) void deplacerMaillet(int x, int y);
	__declspec(dllexport) void bougerMaillet(int entrerUtilisateur);
	__declspec(dllexport) void animationJeu();
	__declspec(dllexport) void joueurVirtuel();
	__declspec(dllexport) void ConfigurationJoueurVirtuel(int porfilJoueurVirtuel[]);
//	__declspec(dllexport) void joueurUn(int xAvant, int yAvant, int xApres, int yApres);
	__declspec(dllexport) bool collisionBonus();
	__declspec(dllexport) bool collisionMailet();
	__declspec(dllexport) bool collisionMailetOrdi();
	__declspec(dllexport) bool collisionMuret();
	__declspec(dllexport) bool collisionPortail();
	__declspec(dllexport) bool collisionLimiteTable();
	__declspec(dllexport) void afficherPointsDeControle();
	__declspec(dllexport) void tuerPointsDeControle();
	__declspec(dllexport) void rotaterXY(double rotationX, double rotationY);
	__declspec(dllexport) void setOrbite(bool estOrbite);
	__declspec(dllexport) void estPartieRapide();
	__declspec(dllexport) void estTournoi();
	__declspec(dllexport) void estModeTest();
	__declspec(dllexport) void estEdition();
	__declspec(dllexport) void pasPartieRapide();
	__declspec(dllexport) void pasTournoi();
	__declspec(dllexport) void pasModeTest();
	__declspec(dllexport) void pasEdition();
	__declspec(dllexport) void chrono(int minutes, int secondes);
	__declspec(dllexport) void nomJoueurVirtuel1(char* nomJoueurVirtuel1);
	__declspec(dllexport) void nomJoueurVirtuel2(char* nomJoueurVirtuel2);
	__declspec(dllexport) void nomJoueurVirtuel3(char* nomJoueurVirtuel3);
	__declspec(dllexport) void nomJoueurVirtuel4(char* nomJoueurVirtuel4);
	__declspec(dllexport) void butGauche(int buts);
	__declspec(dllexport) void butDroit(int buts);
	__declspec(dllexport) double obtenirPosX();
	__declspec(dllexport) double obtenirPosY();
	__declspec(dllexport) double obtenirPosZ();
	__declspec(dllexport) int obtenirNombreObjetSelectionner();

	__declspec(dllexport) void assignerPosX(double x);
	__declspec(dllexport) void assignerPosY(double y);
	__declspec(dllexport) void assignerPosZ(double z);

	__declspec(dllexport) void assignerEchelle(double echelle);
	__declspec(dllexport) double obtenirEchelle();

	__declspec(dllexport) void assignerRotation(double rot);
	__declspec(dllexport) double obtenirRotation();
	__declspec(dllexport) void afficherButs();
	__declspec(dllexport) bool butCoteGauche();
	__declspec(dllexport) bool butCoteDroit();
	__declspec(dllexport) void nonButGauche();
	__declspec(dllexport) void nonButDroit();
	__declspec(dllexport) void sonJeuF();
	__declspec(dllexport) void dechargementSon();
}

#endif // __FACADE_INTERFACE_NATIVE_H__
