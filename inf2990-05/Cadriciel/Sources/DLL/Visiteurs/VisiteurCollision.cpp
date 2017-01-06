#include "../Visiteurs/VisiteurCollision.h"
#include "../Arbre/Noeuds/NoeudTypes.h"
#include "Utilitaire.h"
#include "AideCollision.h"
#include "FacadeModele.h"
#include <iostream>

using namespace std;
using namespace aidecollision;

VisiteurCollision::VisiteurCollision(NoeudRondelle* r)
{
	rondelle_ = r;
}


VisiteurCollision::~VisiteurCollision() { }


void VisiteurCollision::visiter(NoeudBonus *noeudBonus)
{
	glm::dvec2 centreObj, centreRondelle;
	double rayonObj, rayonRondelle;

	centreObj = glm::dvec2(noeudBonus->obtenirPositionRelative());
	rayonObj = noeudBonus->getRayonBonus();
		//noeudBonus->NoeudBonus::getBoiteEnglobante().rayon;
		

	centreRondelle = glm::dvec2(rondelle_->obtenirPositionRelative());
	rayonRondelle = rondelle_->getBoiteEnglobante().rayon;

	DetailsCollision infoCollision;

	infoCollision = aidecollision::calculerCollisionCercle(centreObj, rayonObj, centreRondelle, rayonRondelle);

	double distance = sqrt(pow(infoCollision.direction[0], 2) + pow(infoCollision.direction[1], 2));
	double sommeR = rayonObj + rayonRondelle;
	glm::vec3 positionR = rondelle_->obtenirPositionRelative();
	estCollisionEntreRondelleEtBonus = false;
	if (infoCollision.enfoncement >= 0 && distance <= sommeR)
	{
		estCollisionEntreRondelleEtBonus = true;
		//FacadeModele::obtenirInstance()->sonRondeleBonus();
		//cout << "Collision Rondelle - Bonus accelerateur " << endl;
		rondelle_->setVitesse(rondelle_->getVitesse()*noeudBonus->getAcceleration());
		//glm::dvec3 newPosRondelle = {-30.0, 0.0, 0.0};
		//rondelle_->assignerPositionRelative(newPosRondelle);
	}
}

void VisiteurCollision::visiter(NoeudMuret* noeudMuret)
{
	//Nothing to do ! 
	const glm::dvec2 pointSuperieurGauche = { -table_->getPositionX(),table_->getPositionY() };
	const glm::dvec2 pointInferieurGauche = { -table_->getPositionX(),-table_->getPositionY() };
	const glm::dvec2 pointSuperieurDroit = { table_->getPositionX(),table_->getPositionY() };
	const glm::dvec2 pointInferieurDroit = { table_->getPositionX(),-table_->getPositionY() };

	const glm::dvec2 positionRondelle = { rondelle_->obtenirPositionRelative().x, rondelle_->obtenirPositionRelative().y };

	bool collisionGauche = false;
	bool collisionDroit = false;
	bool collisionHaut = false;
	bool collisionBas = false;

	DetailsCollision infoCollisionLigneGauche = aidecollision::calculerCollisionSegment(pointSuperieurGauche, pointInferieurGauche, positionRondelle, rondelle_->getRayonRondelle(), collisionGauche);
	DetailsCollision infoCollisionLigneDroite = aidecollision::calculerCollisionSegment(pointSuperieurDroit, pointInferieurDroit, positionRondelle, rondelle_->getRayonRondelle(), collisionDroit);
	DetailsCollision infoCollisionLigneHaute = aidecollision::calculerCollisionSegment(pointSuperieurGauche, pointSuperieurDroit, positionRondelle, rondelle_->getRayonRondelle(), collisionHaut);
	DetailsCollision infoCollisionLigneBas = aidecollision::calculerCollisionSegment(pointInferieurGauche, pointInferieurDroit, positionRondelle, rondelle_->getRayonRondelle(), collisionBas);

	coefficientRebond_ = table_->getCoefficientRebond();

	estCollisionEntreRondelleEtMuret = false;

	if (infoCollisionLigneGauche.enfoncement <= 0) {
		//Dans le cas qu'il y a une collision avec la ligne de gauche
		estCollisionEntreRondelleEtMuret = true;
		//FacadeModele::obtenirInstance()->sonRondeleMuret();
	}

	if (infoCollisionLigneDroite.enfoncement <= 0) {
		//Dans le cas qu'il y a une collision avec la ligne de doite
		estCollisionEntreRondelleEtMuret = true;
		//FacadeModele::obtenirInstance()->sonRondeleMuret();
	}

	if (infoCollisionLigneHaute.enfoncement <= 0) {
		//Dans le cas qu'il y a une collision avec la ligne de haut
		estCollisionEntreRondelleEtMuret = true;
		//FacadeModele::obtenirInstance()->sonRondeleMuret();
	}

	if (infoCollisionLigneBas.enfoncement <= 0) {
		//Dans le cas qu'il y a une collision avec la ligne de bas
		estCollisionEntreRondelleEtMuret = true;
		//FacadeModele::obtenirInstance()->sonRondeleMuret();
	}

	//Va assigner une nouvelle position a la rondelle si il y a collision
	if (FacadeModele::obtenirInstance()->estDansZoneDeJeu(rondelle_->obtenirPositionRelative()) && estCollisionEntreRondelleEtMuret)
	{
		//Modifier la position de la rondelle : 
		const glm::vec3 nouvellePositionRondelle = { /*X , Y , 0.0 */};
		rondelle_->assignerPositionRelative(nouvellePositionRondelle);
	}
}

void VisiteurCollision::visiter(NoeudComposite* noeudComposite)
{
	//Nothing to do !
}

void VisiteurCollision::visiter(NoeudTable* noeudTable)
{
	//Va servir afin d'obtenir le coefficient de friction de la table.
	table_ = noeudTable;
}

void VisiteurCollision::visiter(NoeudBut* noeudBut)
{
	//Nothing to do !
}

void VisiteurCollision::visiter(NoeudMaillet* noeudMaillet)
{

	glm::dvec2 centreObj, centreRondelle;
	double rayonObj, rayonRondelle;

	centreObj = glm::dvec2(noeudMaillet->NoeudAbstrait::obtenirPositionRelative());
	rayonObj = noeudMaillet->getRayonMaillet();
		//noeudMaillet->NoeudMaillet::getBoiteEnglobante().rayon;

	centreRondelle = glm::dvec2(rondelle_->obtenirPositionRelative());
	rayonRondelle = rondelle_->getBoiteEnglobante().rayon;
		//rondelle_->getRayonRondelle();
	
	DetailsCollision infoCollision;
	infoCollision = aidecollision::calculerCollisionCercle(centreObj, rayonObj, centreRondelle, rayonRondelle);
	double distance = glm::length(infoCollision.direction);
	double sommeR = rayonObj + rayonRondelle;
	glm::dvec3 newPosRondelle = { 0.0, 0.0, 0.0 };

	estCollisionEntreRondelleEtMaillet = false;
	if (infoCollision.enfoncement >= 0 && distance <= sommeR) //Le rayon du maillet ne fait pas de sens...
	{
		double nouvelleVitesse = noeudMaillet->getVitesse() * noeudMaillet->getMasse() / rondelle_->getMasse();
		
		//rondelle_->setVitesse(nouvelleVitesse);
		estCollisionEntreRondelleEtMaillet = true;
		//FacadeModele::obtenirInstance()->sonRondeleMaillet(); 
		//FacadeModele::obtenirInstance()->sonRondeleMailletOrdi(); 

		glm::dvec3 vecUni;

		double normeVecteur = sqrt(pow(infoCollision.direction.x, 2) + pow(infoCollision.direction.y, 2));

		vecUni.x = (infoCollision.direction.x / normeVecteur);
		vecUni.y = (infoCollision.direction.y / normeVecteur);
		vecUni.z = 0;

		rondelle_->setDirectionRondelle(vecUni);

	}
}

void VisiteurCollision::visiter(NoeudMailletOrdi* noeudMailletOrdi)
{
	glm::dvec2 centreObj, centreRondelle;
	double rayonObj, rayonRondelle;

	centreObj = glm::dvec2(noeudMailletOrdi->NoeudAbstrait::obtenirPositionRelative());
	rayonObj = noeudMailletOrdi->getRayonMaillet();
		//NoeudMailletOrdi::getBoiteEnglobante().rayon;

	centreRondelle = glm::dvec2(rondelle_->obtenirPositionRelative());
	rayonRondelle = rondelle_->getBoiteEnglobante().rayon;

	DetailsCollision infoCollision;
	//plusGrandRayon = rayonRondelle > rayonObj ? rayonRondelle : rayonObj;

	infoCollision = aidecollision::calculerCollisionCercle(centreObj, rayonObj, centreRondelle, rayonRondelle);
	double distance = glm::length(infoCollision.direction);
	double sommeR = rayonObj + rayonRondelle;
	glm::dvec3 newPosRondelle = { 0.0, 0.0, 0.0 };

	estCollisionEntreRondelleEtMailletOrdi = false;
	if (infoCollision.enfoncement >= 0 && distance <= sommeR) //Le rayon du maillet ne fait pas de sens...
	{
		estCollisionEntreRondelleEtMailletOrdi = true;
		//FacadeModele::obtenirInstance()->sonRondeleFrappee();
		//cout << "Collision Rondelle - Maillet ordinateur " << endl;

		/*newPosRondelle[0] += 5 * infoCollision.direction[0];
		newPosRondelle[1] += 5 * infoCollision.direction[1];
		rondelle_->assignerPositionRelative(newPosRondelle);*/


		double nouvelleVitesse = noeudMailletOrdi->getVitesse() * noeudMailletOrdi->getMasse() / rondelle_->getMasse();

		glm::dvec3 vecUni;

		double normeVecteur = sqrt(pow(infoCollision.direction.x, 2) + pow(infoCollision.direction.y, 2));

		vecUni.x = (infoCollision.direction.x / normeVecteur);
		vecUni.y = (infoCollision.direction.y / normeVecteur);
		vecUni.z = 0;

		//cout << "Direction rondelle Ordi : " << vecUni.x << " ; " << vecUni.y << endl;

		rondelle_->setDirectionRondelle(vecUni);
	}
}

void VisiteurCollision::visiter(NoeudPortail* noeudPortail)
{
	glm::dvec2 centreObj, centreRondelle;
	double rayonObj, rayonRondelle;

	centreObj = glm::dvec2(noeudPortail->NoeudAbstrait::obtenirPositionRelative());
	rayonObj = noeudPortail->NoeudPortail::getRayonPortail();

	centreRondelle = glm::dvec2(rondelle_->obtenirPositionRelative());
	rayonRondelle = rondelle_->getBoiteEnglobante().rayon;

	DetailsCollision infoCollision;
	infoCollision = aidecollision::calculerCollisionCercle(centreRondelle, rayonRondelle, centreObj, rayonObj);
	estCollisionEntreRondelleEtPortail = false;

	double sommeR = rayonObj + rayonRondelle;
	double distance = sqrt(pow(infoCollision.direction[0], 2) + pow(infoCollision.direction[1], 2));

	if (infoCollision.enfoncement >= 0 && distance <= sommeR)
	{
		estCollisionEntreRondelleEtPortail = true;
		//FacadeModele::obtenirInstance()->sonRondelePortail();
		//cout << "Collision Rondelle - Portail " << endl;
		glm::dvec3 ajout = { 5.0, 0.0, 0.0 };
		glm::dvec3 posPortail = noeudPortail->obtenirPositionRelative();
		glm::dvec3 newPosRondelle;

	}
}

void VisiteurCollision::visiter(NoeudRondelle* noeudRondelle)
{
	//Nothing to do !
}


bool VisiteurCollision::getSiCollisionBonus()
{
	return estCollisionEntreRondelleEtBonus;
}

bool VisiteurCollision::getSiCollisionAvecMaillet()
{
	return estCollisionEntreRondelleEtMaillet;
}

bool VisiteurCollision::getSiCollisionMuret()
{
	return estCollisionEntreRondelleEtMuret;
}

bool VisiteurCollision::getSiCollisionPortail()
{
	return estCollisionEntreRondelleEtPortail;
}

bool VisiteurCollision::getSiCollisionLimiteTable()
{
	return estCollisionEntreRondelleEtLimiteTable;
}

bool VisiteurCollision::getSiCollisionAvecMailletOrdi()
{
	return estCollisionEntreRondelleEtMailletOrdi;
}


void VisiteurCollision::calculerVecteurUnitaire(glm::dvec3 v1, glm::dvec3 v2) {
	double normeVecteur = sqrt(pow(v1.x, 2) + pow(v1.y, 2));


	v2.x = (v1.x / normeVecteur);
	v2.y = (v1.y / normeVecteur);
	v2.z = 0;

}

bool VisiteurCollision::verifierVecteurUnitairePareil(glm::dvec3 v1, glm::dvec3 v2) {
	if (v1.x == v2.x && v1.y == v2.y) {
		return true;
	}
	return false;
}

void VisiteurCollision::physiqueMaillet(double masse, double vitesse)
{
	double masseRondelle = rondelle_->getMasse();
	rondelle_->setVitesse(masse*vitesse / masseRondelle);
}

glm::vec3 VisiteurCollision::physiqueRondelle()
{
	glm::vec3 v2 = { 0,0,0 };
	calculerVecteurUnitaire(vecteurRondelleDirection, v2);
	v2[0] *= rondelle_->getVitesse();
	v2[1] *= rondelle_->getVitesse();
	v2[2] *= rondelle_->getVitesse();

	rondelle_->assignerPositionRelative(v2);

	return vecteurRondelleDirection;
}

glm::vec3 VisiteurCollision::getVecteurRondelleDirection() {
	return vecteurRondelleDirection;
}
