
#include "../src/Mods/AdvancedMode/AdvancedMode.h"
#include "../src/Mods/AdvancedMode/MoodsList.h"
#include "../src/Models/IMoodsList.h"
#include "../src/Mods/AdvancedMode/Mood.h"
#include "../src/Models/IMood.h"
#include "../src/Mods/AdvancedMode/User.h"
#include "../src/Models/IUser.h"
#include "../src/Mods/AdvancedMode/Person.h"
#include "../src/Models/IPerson.h"
#include "../src/Mods/AdvancedMode/PendingGamesList.h"
#include "../src/Mods/AdvancedMode/NotificationsList.h"
#include "../src/Models/INotificationsList.h"
#include <iomanip>

int main() {
	AdvancedMode::AdvancedMode mode;
	int loginResult, moodComparisonResult, moodContainResult, moodLogoutResult, gameAmountResult, notificationsAmountResult;
	loginResult = mode.login("teste@teste.teste", "123456");
	if(loginResult != 1) {
		loginResult = 0;
	}
	int games1, games2, notifications1, notifications2;
	mode.load();
	games1 = mode.getPendingGames()->size();
	notifications1 = mode.getNotifications()->getUnreadCount();
	IMood * mood;
	IMoodsList * list = mode.getMoods();
	if(list->size()>0) {
		mood = (*list)[0];
		IUser * user = mode.getIdentity();
		user->setMood(mood);
		IPerson * person = user->getPerson();
		if(person->getMood()->getDescription() == mood->getDescription()) {
			moodComparisonResult = 1;
		} else {
			moodComparisonResult = 0;
		}
		if(list->contains(mood)) {
			moodContainResult = 1;
		} else {
			moodContainResult = 0;
		}
	}
	
	AdvancedMode::AdvancedMode mode1;
	mode1.login("teste@teste.teste", "123456");
	mode1.load();
	games2 = mode1.getPendingGames()->size();
	notifications2 = mode1.getNotifications()->getUnreadCount();
	
	if(games1 == games2) { 
		gameAmountResult = 1;
	} else {
		gameAmountResult = 0;
	}
	if(notifications1 == notifications2) {
		notificationsAmountResult = 1;
	} else {
		notificationsAmountResult = 0;
	}
	IUser * user = mode.getIdentity();
	IPerson * person = user->getPerson();
	if(person->getMood()->getDescription() == mood->getDescription()) {
			moodLogoutResult = 1;
	} else {
			moodLogoutResult = 0;
	}
	
	
	
	printf("%s\t%-40s\n", "Type", "Result");
	printf("%s\t%-40s\n", "Login", std::to_string(loginResult).c_str());
	printf("%s\t%-40s\n", "Mood Compare", std::to_string(moodComparisonResult).c_str());
	printf("%s\t%-40s\n", "Mood Contain", std::to_string(moodContainResult).c_str());
	printf("%s\t%-40s\n", "Mood Logout", std::to_string(moodLogoutResult).c_str());
	printf("%s\t%-40s\n", "Game Amount", std::to_string(gameAmountResult).c_str());
	printf("%s\t%-40s\n", "Notifications", std::to_string(notificationsAmountResult).c_str());
	return 1;
	
}