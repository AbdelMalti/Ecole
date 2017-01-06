////////////////////////////////////////////////
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include <iostream>

int NoeudAbstrait::cptSelection_=0;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
	const std::string& type //= std::string{ "" }
	) :
	type_( type ), coefficientFriction_(0.2), coefficientRebond_(1.25), acceleration_(2.5), facteurEchelle_(1)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide déclaré virtuel pour les classes dérivées.  La
/// libération des afficheurs n'est pas la responsabilité de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
	return 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par défaut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par défaut de la classe de base.
///
/// @param[in] noeud : Le noeud à effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer(const NoeudAbstrait* noeud)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donné parmi le noeud
/// lui-même et ses enfants.
///
/// Elle retourne donc le noeud lui-même si son type est celui passé en
/// paramètre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud) const
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donné parmi le noeud
/// lui-même et ses enfants.
///
/// Elle retourne donc le noeud lui-même si son type est celui passé en
/// paramètre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-ème enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// dernière ne possède pas d'enfant.
///
/// @param[in] indice : L'indice du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice) const
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-ème enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// dernière ne possède pas d'enfant.
///
/// @param[in] indice : L'indice du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice)
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
///
/// Cette fonction ajoute un enfant à ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud à ajouter.
///
/// @return Vrai si l'ajout a bien été effectué, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
{
	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Vrai si l'ajout a bien été effectué, faux autrement.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
	return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'état de sélection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
	selectionne_ = !selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacerSelection()
///
/// Cette fonction efface les noeuds qui sont sélectionnés parmi les
/// enfants de ce noeud.
///
/// Elle ne fait rien, car ce type de noeud abstrait ne peut pas avoir
/// d'enfant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacerSelection()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction sélectionne le noeud et ses enfants.
///
/// Elle ne fait que sélectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
	assignerSelection(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction désélectionne le noeud et ses enfants.
///
/// Elle ne fait que désélectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
	selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction vérifie si le noeud ou un de ses enfants est
/// sélectionné.
///
/// Elle ne fait que regarder si le noeud est sélectionné, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud sélectionné, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
	return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est sélectionné ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode même si le
///                      noeud n'est pas sélectionné.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones(bool estForce)
{
	if ((estForce) || (estSelectionne())) {
		if (modePolygones_ == GL_FILL)
			modePolygones_ = GL_LINE;
		else if (modePolygones_ == GL_LINE)
			modePolygones_ = GL_POINT;
		else
			modePolygones_ = GL_FILL;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones(GLenum modePolygones)
{
	// Le mode par défaut si on passe une mauvaise valeur est GL_FILL
	if ((modePolygones != GL_FILL) &&
		(modePolygones != GL_LINE) &&
		(modePolygones != GL_POINT)) {
		modePolygones = GL_FILL;
	}

	modePolygones_ = modePolygones;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher(const glm::mat4& vueProjection, const bool& estColore) const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// généralement à faire pour l'affichage, c'est-à-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit à sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'état.
///
/// L'affichage comme tel est confié à la fonction afficherConcret(const glm::mat4& vueProjection, const bool& estColore),
/// appelée par la fonction afficher(const glm::mat4& vueProjection, const bool& estColore).
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher(const glm::mat4& vueProjection, const bool& estColore) const
{
	if (affiche_) {
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

		// Assignation du mode d'affichage des polygones
		glPolygonMode(GL_FRONT_AND_BACK, modePolygones_);

		// Affichage concret
		afficherConcret(vueProjection, estColore);

		// Restauration
		glPopAttrib();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
///
/// Cette fonction effectue le véritable rendu de l'objet.  Elle est
/// appelée par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret(const glm::mat4& vueProjection, const bool& estColore) const
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise à être surcharger par
/// les classes dérivées.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer(float dt)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::accepter(VisiteurAbstrait &visiteur)
///
/// Cette fonction est abstraite et va être surchargé par ces dérivées
///dans le cas d'accepter les visiteurs
///
/// Elle ne fait rien pour cette classe et vise à être surcharger par
/// les classes dérivées.
///
/// @param[in] visiteur : visiteur qui visite le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::estDansZoneDeJeu()
///
///	Cette fonction indique si le noeud est dans la zone de jeu
///
/// @return retourne vrai si le noeud est dans la zone de jeu
///
////////////////////////////////////////////////////////////////////////
//bool NoeudAbstrait::estDansZoneDeJeu()
//{
//	return true;
//}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudAbstrait::obtenirFacteurEchelle( )
///
/// Cette accesseur retourne le facteurEchelle
///
/// @return facteur d'echelle
/////
//////////////////////////////////////////////////////////////////////////
//double NoeudAbstrait::obtenirFacteurEchelle()
//{
//	return facteurEchelle_;
//}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::modifierRayon(double rayon)
///
/// Fonction qui modifie le rayon du noeud
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
//void NoeudAbstrait::modifierRayon(double rayon)
//{
//	rayon_ = rayon;
//	estModifie_ = true;
//}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::modifierFacteurEchelle(double facteurEchelle)
///
/// Cette fonction modifie le facteur de mise à l'échelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
//void NoeudAbstrait::modifierFacteurEchelle(double facteurEchelle)
//{
//facteurEchelle_ = facteurEchelle;
//estModifie_ = true;
//}
//
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void NoeudAbstrait::modifierAngleRotation(GLfloat angle)
/////
///// Fonction qui permet de modifier l'angle de rotation
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
//void NoeudAbstrait::modifierAngleRotation(GLfloat angle)
//{
//	angleRotation_ = angle;
//}

////////////////////////////////////////////////////////////////////////
///
/// @fn  NoeudAbstrait::attribuerCouleurSelection( ) 
///
/// Cette fonction attribut une couleur des que l objet est selectionné
///
/// @param[in] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////

void NoeudAbstrait::setCouleurSel()
{
	if (NoeudAbstrait::compteurSelection_ < 100) 
	{ 
		coulSel_[0] = 255 - NoeudAbstrait::compteurSelection_ + 1;
		coulSel_[1] = NoeudAbstrait::cptSelection_;
		coulSel_[2] = 0;
	}
	else 
	{ 
		NoeudAbstrait::compteurSelection_ = 0; 
		NoeudAbstrait::cptSelection_++;
		coulSel_[0] = NoeudAbstrait::cptSelection_;
		coulSel_[1] = 255;
		coulSel_[2] = 0;
	}
}

float NoeudAbstrait::getCoefficientFriction()
{
	return coefficientFriction_;
}

void NoeudAbstrait::setCoefficientFriction(float friction) {
	coefficientFriction_ = friction;
	/*std::cout << "coefficientFriction_ = " << coefficientFriction_<<std::endl;*/
}

void NoeudAbstrait::setCoefficientRebond(double rebond) {
	coefficientRebond_ = rebond;
	/*std::cout << "coefficientRebond_ = " << coefficientRebond_ << std::endl;*/
}
double NoeudAbstrait::getCoefficientRebond() {
	return coefficientRebond_;
}

void NoeudAbstrait::setAcceleration(double acceleration) {
	acceleration_ = acceleration;
}
double NoeudAbstrait::getAcceleration() {
	return acceleration_;
}

double NoeudAbstrait::getVitesse() {
	return vitesseInitial_;
}

void NoeudAbstrait::setVitesse(double v) {
	vitesseInitial_ = v;
}


void NoeudAbstrait::setTempsInitial(double nouveauTempsInitial) {
	tempsInitial_ = nouveauTempsInitial;
}
double NoeudAbstrait::getTempsInitial() {
	return tempsInitial_;
}

void NoeudAbstrait::setPositionInitialX(double nouveauX) {
	positionInitialX_ = nouveauX;
}

double NoeudAbstrait::getPositionInitialX() {
	return positionInitialX_;
}

void NoeudAbstrait::setPositionInitialY(double nouveauY) {
	positionInitialY_ = nouveauY;
}

double NoeudAbstrait::getPositionInitialY() {
	return positionInitialY_;
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
