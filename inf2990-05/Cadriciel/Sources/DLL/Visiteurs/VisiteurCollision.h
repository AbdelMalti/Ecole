
#include "VisiteurAbstrait.h"
#include "AideCollision.h"

using namespace aidecollision;

class VisiteurCollision : public VisiteurAbstrait
{
public:

	//Constructeur
	VisiteurCollision(NoeudRondelle* r); //Passer la rondelle ---> calculerCollision

	//Destructeur
	~VisiteurCollision();

	void visiter(NoeudBonus* noeudBonus);
	void visiter(NoeudMaillet* noeudMaillet);
	void visiter(NoeudMailletOrdi* noeudMailletOrdi);
	void visiter(NoeudPortail* noeudPortail);
	void visiter(NoeudRondelle* noeudRondelle);
	void visiter(NoeudMuret* noeudMuret);
	void visiter(NoeudComposite* noeudComposite);
	void visiter(NoeudBut* noeudBut);
	void visiter(NoeudTable* noeudTable);

	bool getSiCollisionBonus();
	bool getSiCollisionMuret();
	bool getSiCollisionPortail();
	bool getSiCollisionLimiteTable();
	bool getSiCollisionAvecMailletOrdi();
	bool getSiCollisionAvecMaillet();

	void calculerVecteurUnitaire(glm::dvec3 v1, glm::dvec3 v2);
	bool verifierVecteurUnitairePareil(glm::dvec3 v1, glm::dvec3 v2);

	void physiqueMaillet(double masse, double vitesse);

	glm::vec3 physiqueRondelle();

	glm::vec3 getVecteurRondelleDirection();

	
private:

	glm::vec3 centre_;
	double rayon_;
	double coefficientFriction_ = 0;
	double coefficientRebond_ = 0;

	NoeudTable* table_;
	NoeudRondelle* rondelle_;

	// servent a detecter s'il y a une collision entre la rondelle et les objets sur la table.
	bool estCollisionEntreRondelleEtBonus = false;
	bool estCollisionEntreRondelleEtMaillet = false;
	bool estCollisionEntreRondelleEtPortail = false;
	bool estCollisionEntreRondelleEtLimiteTable = false;
	bool estCollisionEntreRondelleEtMuret = false;
	bool estCollisionEntreRondelleEtMailletOrdi = false;

	double duree;
	double temps1;
	double temps2;
	glm::vec3 vecteurRondelleDirection = { 0.0,0.0,0.0 };
};