///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"

#include <map>
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui représente l'arbre de rendu spécifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilisés par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par défaut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu à son état initial.
   void initialiser();

   // Ajoute un noeud sur la surface de la table
   //void ajouterNoeud(const std::string& nom, glm::dvec3 coordonnee);

	/// La chaîne représentant le type des tables.
   static const std::string NOM_TABLE;
	/// La chaîne représentant le type de rondelle.
   static const std::string NOM_RONDELLE;
   /// La chaîne représentant le type de maillet.
   static const std::string NOM_MAILLET;
   /// La chaîne représentant le type de maillet Ordi.
   static const std::string NOM_MAILLETORDI;
   /// La chaîne représentant le type de bonus accélérateur.
   static const std::string NOM_BONUS;
   static const std::string NOM_PORTAIL;
   static const std::string NOM_MURET;
   static const std::string NOM_POINT_CONTROLE;
   static const std::string NOM_BUT;

   void sauvegarderZoneXml(char destination[]);
   void restaurerZoneXml(char destination[]);
   void	nouvelleScene();
private:
	NoeudAbstrait* surface_;
};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
