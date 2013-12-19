/**
 * GameController - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "GameController.h"

#include "Graphics/GraphicFactory.h"

GameController::GameController() {
	
}

void GameController::start(GameMod * mod) {
	if(_mod != NULL) {
		// TODO clean up
	}
	
	_mod = mod;
	_mod->load();
	
	start();
}

#include <cstdio>
#define DEBUG

void GameController::start() {
	#ifdef DEBUG
	printf("Starting game...\n");
	#endif
	
	_identity = _mod->getIdentity();
	
	#ifdef DEBUG
	printf("Loaded user's identity (%x): %s\n", _identity, _identity->getPerson()->getName().c_str());
	#endif
	
	_firstNode = GraphicFactory::build(_identity->getPerson());
	_currentNode = _firstNode;
}