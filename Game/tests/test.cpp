
#include "../src/Mods/AdvancedMode/AdvancedMode.h"
#include "../src/Mods/AdvancedMode/MoodsList.h"
#include "../src/Models/IMoodsList.h"
#include "../src/Mods/AdvancedMode/Mood.h"
#include "../src/Models/IMood.h"
#include "../src/Mods/AdvancedMode/User.h"
#include "../src/Models/IUser.h"
#include "../src/Mods/AdvancedMode/Person.h"
#include "../src/Models/IPerson.h"
#include <iomanip>

int main() {
	AdvancedMode::AdvancedMode mode;
	int loginResult, moodComparisonResult, moodContainResult;
	loginResult = mode.login("teste@teste.teste", "123456");
	if(loginResult != 1) {
		loginResult = 0;
	}
	mode.load();
	IMoodsList * list = mode.getMoods();
	if(list->size()>0) {
		IMood * mood = (*list)[0];
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
	
	printf("%s\t%-40s\n", "Type", "Result");
	printf("%s\t%-40s\n", "Login", std::to_string(loginResult).c_str());
	printf("%s\t%-40s\n", "Mood Compare", std::to_string(moodComparisonResult).c_str());
	printf("%s\t%-40s\n", "Mood Contain", std::to_string(moodContainResult).c_str());
	return 1;
	
}