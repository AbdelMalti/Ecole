
#include "Son.h"
SINGLETON_DECLARATION_CPP(Son);

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::initialiserSon()
///
/// Cette fonction initialise le system FMOD
///
/// @param[ void ] 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Son::initialiserSon(void)
{

	//resultat = FMOD_System_Create(&fsystem);
	FMOD::System_Create(&fsystem);
	fsystem->init( 20, FMOD_INIT_NORMAL, 0);
	chargerSon();
}

////////////////////////////////////////////////////////////////////////
///
///void Son::chargerMusique()
///
/// Cette fonction charge tous les sons disponibles dans le système FMOD
///
/// @param[Aucun] 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Son::chargerSon() {
	if (estActif) {

		// plusieurs sons ci dessous ont été prise a l'adresse http://www.sound-fishing.net/sons/hockey-sur-glace

		fsystem->createSound("media/Son/sonRondelleFrappee.mp3", FMOD_DEFAULT, 0, &leSon1);
		fsystem->createSound("media/Son/sonRondelleBut.mp3", FMOD_DEFAULT, 0, &leSon2);
		fsystem->createSound("media/Son/sonRondelleMuret.mp3", FMOD_DEFAULT, 0, &leSon3);
		fsystem->createSound("media/Son/sonRondelleBonus.mp3", FMOD_DEFAULT, 0, &leSon4);
		fsystem->createSound("media/Son/sonRondellePortail.mp3", FMOD_DEFAULT, 0, &leSon5);
		//fsystem->createSound("media/Son/sonRondelleMaillet.mp3", FMOD_DEFAULT, 0, &leSon6);
		fsystem->createSound("media/Son/son1.mp3", FMOD_DEFAULT, 0, &leSon7);
		fsystem->createSound("media/Son/son.mp3",/*FMOD_HARDWARE*/FMOD_DEFAULT, 0, &son);
		fsystem->createSound("media/Son/sonBordure.mp3", FMOD_DEFAULT, 0, &leSon8);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::dechargerSon(void)
///
/// Cette fonction decharge les éléments du systèmes FMOD
///
/// @param [Aucun]
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void Son::dechargerSon(void)
{
	//fsystem->close();
	//fsystem->release();
	canal6->setPaused(true);

	
}

////////////////////////////////////////////////////////////////////////
///
/// void Son::jouerSon(int objet)
///
/// Cette fonction joue les sons qui ont été chargés
///
/// @param[ int objet] 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Son::jouerSon(int objet)
{
	if (estActif)
	{
		switch (objet)
		{

			case 1: //la rondelle est frappee
			{
				//try
				//{
					fsystem->playSound(FMOD_CHANNEL_FREE, leSon1, false, 0);
			//	}
				//catch (const std::exception&)
			
				
			}
			break;
			case 2: //la rondelle touche le but
			{
				fsystem->playSound(FMOD_CHANNEL_FREE, leSon2, false, 0);
			}
			break;
			case 3: //la rondelle touche un muret
			{
				fsystem->playSound(FMOD_CHANNEL_FREE, leSon3, false, 0);
			}
			break;

			case 4://la rondelle touche un bonus
			{
				fsystem->playSound(FMOD_CHANNEL_FREE, leSon4, false, 0);
			}
			break;
			case 5: //la rondelle touche un portail
			{
				fsystem->playSound(FMOD_CHANNEL_FREE, leSon5, false, 0);
			}
			break;
			case 6:  //la rondelle touche un maillet
			{
				fsystem->playSound(FMOD_CHANNEL_FREE, leSon5, false, 0);
			}
			break;

			case 7: //son en mode jeu
			{
				fsystem->playSound(FMOD_CHANNEL_FREE, son, false, &canal6);
			}
			break;
			case 8:  //son mode test
				fsystem->playSound(FMOD_CHANNEL_FREE, leSon8, false, 0);
				break;
			case 9:  //la rondelle touche un maillet
			{
				fsystem->playSound(FMOD_CHANNEL_FREE, leSon7, false, 0);
			}
			break;

			}
		}
}

////////////////////////////////////////////////////////////////////////
///
/// void Son::pauserSon(bool a);
///
/// Cette fonction coupe un son si nous sommes en pause dansle mode partie rapide ou tournoi.
///
/// @param[bool a] 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Son::pauserSon(bool a)
{
 // setPaused(a);

}
////////////////////////////////////////////////////////////////////////
///
/// Son::sonModeJeu(bool mode)
///
/// Cette fonction joue un son si nous sommes en mode partie rapide ou tournoi.
///
/// @param[bool jouerSon] 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Son::sonModeJeu(bool mode)
{
	son->setMode(FMOD_LOOP_NORMAL);
	jouerSon(7);
	
}
