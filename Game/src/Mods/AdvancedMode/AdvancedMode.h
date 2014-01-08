/**
 * AdvancedMode - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef ADVANCEDMODE_H
#define ADVANCEDMODE_H

#include "../../Mods/GameMod.h"
#include "CentralServerWebService.h"

class AdvancedMode : public GameMod {
	public:
		AdvancedMode();
		
		int login(std::string email, std::string password);

		virtual void load();

		virtual void * getPendingGames();
		virtual std::vector< INotification * > * getNotifications();
		virtual IUser * getIdentity();
		
		virtual void setEventListener(GameModEventListener * listener);

		~AdvancedMode();

	private:
		CentralServerWebService service;
		GameModEventListener * listener;
};

#endif // ADVANCEDMODE_H
