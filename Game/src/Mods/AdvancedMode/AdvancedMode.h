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

namespace AdvancedMode {
	class NotificationsList;
	class MoodsList;
	class Cache;
	
	class AdvancedMode : public GameMod {
		public:
			AdvancedMode();

			int login(std::string email, std::string password);

			virtual void load();

			virtual IUser * getIdentity();
			
			virtual void * getPendingGames();
			virtual INotificationsList * getNotifications();
			virtual IMoodsList * getMoods();

			virtual void setEventListener(GameModEventListener * listener);

			~AdvancedMode();

		private:
			CentralServerWebService service;
			GameModEventListener * listener;
			
			Cache * cache = NULL;

			IUser * user = NULL;
			MoodsList * moods = NULL;
			
			NotificationsList * notificationsList = NULL;
	};
}

#endif // ADVANCEDMODE_H
