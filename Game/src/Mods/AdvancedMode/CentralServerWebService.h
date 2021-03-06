/**
 * CentralServerWebService - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef CENTRALSERVERWEBSERVICE_H
#define CENTRALSERVERWEBSERVICE_H

#include <string>
#include <vector>
#include "dependencies/CurlHelper/CurlHelper.h"
#include "dependencies/rapidjson/document.h"

class CentralServerWebService {
	public:
		CentralServerWebService();

		int login(std::string email, std::string password);
		int getUserId();
		rapidjson::Value & getPerson(const int id);

		rapidjson::Value & getMoods();
		bool setMood(const int idMood);

		rapidjson::Value & getTag(const int id);
		rapidjson::Value & getUserTags(const int userId);
		bool setTags(const vector< string > tags);

		rapidjson::Value & getConnection(const int id);
		rapidjson::Value & getConnectionsOfUser(const int userId);
		bool acceptFriendship(const int idConnection);
		bool acceptFriendshipWithChallenge(const int idConnection, const std::string minigame, const int level);
		bool refuseFriendship(const int idConnection);
		bool addFriend(const int idFriend);
		bool removeFriend(const int idFriend);

		rapidjson::Value & getNotification(const int id);
		rapidjson::Value & getNotificationBases();
		bool setNotificationRead(const int id, const bool read);
		
		rapidjson::Value & getPendingGames();
		bool setGameScore(const int connectionId, const int minigameId, const int score);

	private:
		std::string baseUrl;
		std::string token;

		/**
		 * Gets a parsed rapidjson Document containing the requested data.
		 */
		rapidjson::Document * getData(const std::string type, const std::string function, const std::string params);
		std::string execute(const string type, const string function, const string params);
};

#endif // CENTRALSERVERWEBSERVICE_H
