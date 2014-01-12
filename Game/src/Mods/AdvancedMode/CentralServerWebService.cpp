/**
 * CentralServerWebService - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "CentralServerWebService.h"

CentralServerWebService::CentralServerWebService() : baseUrl("http://uvm001.dei.isep.ipp.pt/SocialGame/") {

}

int CentralServerWebService::login(string email, string password) {
	const rapidjson::Value & v = getData("Users", "doLogin", email + "^" + password)->operator[]("data");

	if (v.IsNull()) {
		return -1;
	} else {
		token = v.GetString();
		return 1;
	}
}

int CentralServerWebService::getUserId() {
	// TODO it should use a function that only returns the ID
	const rapidjson::Value & v = getData("Users", "getUserIdFromSession", token)->operator[]("data");

	if (v.IsNull()) {
		return -1;
	} else {
		return std::stoi(v.GetString());
	}
}

rapidjson::Value & CentralServerWebService::getPerson(const int id) {
	return getData("Users", "getUserInfo", std::to_string(id))->operator[]("data");
}

rapidjson::Value & CentralServerWebService::getMoods() {
	return getData("Moods", "getAllMoods", "")->operator[]("data");
}

bool CentralServerWebService::setMood(const int idMood) {
	execute("Users", "modifyUserMood", token + "^" + std::to_string(idMood));
	return true;
}

rapidjson::Value & CentralServerWebService::getConnection(const int id) {
	return getData("Connections", "returnConnection", std::to_string(id))->operator[]("data");
}

rapidjson::Value & CentralServerWebService::getConnectionsOfUser(const int userId) {
	return getData("Connections", "getConnectionsOfUser", std::to_string(userId))->operator[]("data");
}

bool CentralServerWebService::acceptFriendship(const int idConnection) {
	execute("Connections", "acceptFriendship", token + "^" + std::to_string(idConnection));
	return true;
}

bool CentralServerWebService::refuseFriendship(const int idConnection) {
	execute("Connections", "refuseFriendship", token + "^" + std::to_string(idConnection));
	return true;
}

bool CentralServerWebService::addFriend(const int idFriend) {
	execute("Connections", "addFriend", token + "^" + std::to_string(idFriend) + "^0^0");
	return true;
}

bool CentralServerWebService::removeFriend(const int idFriend) {
	execute("Connections", "removeFriend", token + "^" + std::to_string(idFriend));
	return true;
}

rapidjson::Value & CentralServerWebService::getNotification(const int id) {
	return getData("Notifications", "getNotification", token + "^" + std::to_string(id))->operator[]("data");
}

rapidjson::Value & CentralServerWebService::getNotificationBases() {
	return getData("Notifications", "getNotificationBasesForUser", token)->operator[]("data");
}

bool CentralServerWebService::setNotificationRead(const int id, const bool read) {
	execute("Notifications", "markNotificationRead", token + "^" + std::to_string(id) + (read ? "^1" : "^0"));
	return true;
}

rapidjson::Document * CentralServerWebService::getData(const string type, const string function, const string params) {
	std::string result = execute(type, function, params);

	rapidjson::Document * d = new rapidjson::Document();
	d->Parse<0>(result.c_str());

	return d;
}

std::string CentralServerWebService::execute(const string type, const string function, const string params) {
	std::string result = curl_httpget(baseUrl + type + '/' + (params.length() == 0 ? function : function + "?Params=" + params));
	printf("Queried %s...\nReceived: %s\n", (baseUrl + type + '/' + function + "?Params=" + params).c_str(), result.c_str());
	return result;
}
