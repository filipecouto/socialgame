/**
* SimpleMode - Header
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#ifndef SIMPLEMODE_H
#define SIMPLEMODE_H

#include "../GameMod.h"
#include "User.h"

namespace SimpleMode {
	class MoodsList;
	class MessageNotification;
	class SimpleMode : public GameMod {
		public:

			SimpleMode();
			~SimpleMode();


			virtual void load();

			virtual IUser * getIdentity();
			virtual IMoodsList * getMoods();
			virtual INotificationsList * getNotifications();
			virtual IPendingGamesList * getPendingGames();

			virtual void setEventListener(GameModEventListener * listener);

		private:
			User * user = NULL;
			GameModEventListener * _listener;

			MoodsList * moodsList = NULL;



	};
}
#endif
