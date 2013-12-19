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

void GameController::start() {
	_identity = _mod->getIdentity();
	
	_firstNode = GraphicFactory::build(_identity->getPerson());
	_currentNode = _firstNode;
}