#pragma once
////////////////////////////////////////////////
/// @file   Son.h
/// @author INF2990-05
/// @date   2016-11-16
///
////////////////////////////////////////////////
#ifndef __SON_H__
#define __SON_H__
#include "fmod.h"
#include"fmod.hpp"
#include"Singleton.h"

class Son : public Singleton<Son>
{
	SINGLETON_DECLARATION_CLASSE(Son);

public:
	void initialiserSon(void);
	void chargerSon();
	void dechargerSon(void);
	void jouerSon(int objet);
	void pauserSon(bool a);
	void sonModeJeu(bool jouerSon);

private:
	/// Initialisation 
	//FMOD_RESULT resultat;
	FMOD::System * fsystem;
	FMOD::Sound * son;
	FMOD::Channel *canal0, *canal1, *canal2, *canal3, *canal4, *canal5, *canal6,*canal7, *canal8; //des canaux
	FMOD::Sound *leSon1, *leSon2, *leSon3, *leSon4, *leSon5, *leSon6, *leSon7, *leSon8; //des musiques
	bool estActif = true;
};
#endif
