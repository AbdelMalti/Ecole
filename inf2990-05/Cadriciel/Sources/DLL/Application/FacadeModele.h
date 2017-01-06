//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__


#include <windows.h>
#include <string>
#include "GL\glew.h"
#include "NoeudTable.h"
#include "BoiteEnvironnement.h"

class NoeudAbstrait;
class ArbreRenduINF2990;

namespace vue {
   class Vue;
}


///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une fa�ade) sur l'ensemble
///        du mod�le et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.
   static FacadeModele* obtenirInstance();
   /// Lib�re l'instance unique de la classe.
   static void libererInstance();

   /// Cr�e un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration � partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Lib�re le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du mod�le.
   void afficher() const;
   /// Affiche la base du contenu du mod�le.
   void afficherBase() const;
 
   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

   /// R�initialise la sc�ne.
   void reinitialiser();

   /// Anime la sc�ne.
   void animer(float temps);

   void initialiserRectangle(int pX, int pY);
   void mettreAJourRectangle(int piX, int piY, int paX, int paY, int pdX, int pdY, bool enSelection);
   void terminerRectangle(int pIX, int pIY, int pFX, int pFY);

   /// Ajoute un bonus accelerateur
   void ajouterNoeudBonus(int posX, int posY);
   /// Ajoute un portail
   void ajouterNoeudPortail(int posX, int posY);
   /*void ajouterNoeudMaillet();
   void ajouterNoeudMailletOrdi(int posX, int posY);
   void ajouterNoeudRondelle();*/
   /// Verifie si l'objet ajoute se trouve dans la zone de jeu
   bool estDansZoneDeJeu(glm::vec3 point);

   void initialiserDeplacement(double x, double y);
   void deplacement(double x, double y);
   
   void miseAEchelle(double y);
   void supprimer();
   void ajouterNoeudMuret(int posX, int posY);
   void initialiserRotation(double y);
   void rotation(double y);
   void initialiserDuplication(double x, double y);
   void duplication(double x, double y);
   ///Permet la selectionne de noeud
   void selectionner(int posX, int posY, bool estSelectionne);
   double obtenirCoefficientFriction();
   void modifierCoefficientFriction(double friction);
   /// D�s�lectionne tous les enfants de m�me que le noeud.
   void deselectionnerTout();

   double obtenirAcceleration();
   void modifierAcceleration(double acceleration);
   double obtenirRebond();
   void modifierRebond(double rebond);
   ///Permet la determination de la couleur d'un pixel
   void determinerCouleur(int sourisX, int sourisY, GLubyte couleurDUnPixel[]);

   ///Tuer rondelle et maillet lors du retour au mode edition
   void tuerMaillet();
   void tuerMailletOrdi();
   void tuerRondelle();

   ///G�n�rer rondelle et maillet en mode edition
   void genererMaillet();
   void genererMailletOrdi();
   void genererRondelle();

   ///r�initialiser la partie
   void reinitialiserRondelle();
   void reinitialiserMaillet();
   void reinitialiserMailletOrdi();

   /*///
   void ajoutRondelleMaillet();*/

   void deplacerMailletOrdi(double dx, double dy);
   void deplacerMaillet(int x, int y);
   void bougerMaillet(int direction);
   void animationJeu();


   bool estDansZoneGauche(glm::vec3 point);

   bool estDansZoneDroit(glm::vec3 point);

   void joueurVirtuel();

   void ConfigurationJoueurVirtuel(int porfilJoueurVirtuel[]);

  // void joueurUnAction(int xAvant, int yAvant, int xApres, int yApres);

   bool collisionBonus();
   bool collisionMaillet();
   bool collisionPortail();
   bool collisionMuret();
   bool collisionLimite();
   bool collisionMailletOrdi();
   void afficherPointsDeControle();

   void tuerPointsDeControle();

   double getTableX();
   double getTableY();
   double getTableZ();

   /// Permet de modifier le mode de vue
   void setOrbite(bool estOrbite);
   //NoeudRondelle* getRondellePourCollision();

   void estPartieRapide();
   void estTournoi();
   void estEdition();
   void estModeTest();

   void pasPartieRapide();
   void pasTournoi();
   void pasEdition();
   void pasModeTest();

   void chrono(int minutes, int secondes);

   void nomJoueurVirtuel1(std::string nomJoueurVirtuel1);
   void nomJoueurVirtuel2(std::string nomJoueurVirtuel2);
   void nomJoueurVirtuel3(std::string nomJoueurVirtuel3);
   void nomJoueurVirtuel4(std::string nomJoueurVirtuel4);

   void butGauche(int buts);
   void butDroit(int buts);

   int nombreObjetSelectioner = 0;
   double posX;
   double posY;
   double posZ;

   void modifierCoordonnerObjetSelectionner();
   glm::vec3 obtenirCoordonnerObjetSelectionner();
   double obtenirCoordonnerX();
   double obtenirCoordonnerY();

   void assignerFacteurEchelle(double rot);

   void assignerRotation(double echelle);

   double obtenirRotation();

   double obtenirFacteurEchelle();
   /// Affiche les buts
   void afficherButs();
   /// but cote gauche
   bool butCoteGauche();
   /// but cote droit
   bool butCoteDroit();
   /// Ramene la but gauche a false
   void nonButGauche();
   /// Ramene la but droit a false
   void nonButDroit();
   // methodes pour jouer le son
   void sonRondeleMaillet();
   void sonRondeleBonus();
   void sonRondeleBut();
   void sonRondeleBordure();
   void sonRondeleMailletOrdi();
   void sonRondelePortail();
   void sonRondeleFrappee();
   void sonJeuF();
   void dechargementSon();
   void sonRondeleMuret();
   
private:
   /// Constructeur par d�faut.
   FacadeModele() = default;
   /// Destructeur.
   ~FacadeModele();
   /// Constructeur copie d�sactiv�.
   FacadeModele(const FacadeModele&) = delete;
   /// Op�rateur d'assignation d�sactiv�.
   FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   /// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poign�e ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poign�e ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la sc�ne.
   vue::Vue* vue_{ nullptr };
   /// Vue orthographique de la sc�ne.
   vue::Vue* vueOrtho_{ nullptr };
   /// Vue perspective de la sc�ne.
   vue::Vue* vuePers_{ nullptr };

   /// Arbre de rendu contenant les diff�rents objets de la sc�ne.
   ArbreRenduINF2990* arbre_{ nullptr };

   NoeudTable* table_{ nullptr };
   /// Permet de dire si on est en mode edition
   char edition_{ 'e' };

   double pointInitSourisX_;
   double pointInitSourisY_;
   double tableX_;
   double tableY_;
   double tableZ_;
   //NoeudRondelle* rondelle_;
   bool estCollisionMaillet = false;
   bool estCollisionMuret = false;
   bool estCollisionBonus = false;
   bool estCollisionPortail  = false;
   bool estCollisionLimite = false;
   bool estCollisionMailletOrdi = false;
   bool orbite_;

   bool estPartieRapide_ = false;
   bool estTournoi_ = false;
   bool estModeTest_ = false;
   bool estEdition_ = false;

   int chronoMinutes_ = 0;
   int chronoSecondes_ = 0;

   std::string nomJoueurVirtuel1_;
   std::string nomJoueurVirtuel2_;
   std::string nomJoueurVirtuel3_;
   std::string nomJoueurVirtuel4_;

   // Les skybox
   utilitaire::BoiteEnvironnement* skyboxEditeur_;
   utilitaire::BoiteEnvironnement* skyboxTournoi_;

   int butGauche_ = 0;
   int butDroit_ = 0;

};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est pr�sentement utilis�e pour
/// voir la sc�ne.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
