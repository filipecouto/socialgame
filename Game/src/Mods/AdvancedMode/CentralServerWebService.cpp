/**
 * CentralServerWebService - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "CentralServerWebService.h"

CentralServerWebService::CentralServerWebService() : baseUrl("http://uvm001.dei.isep.ipp.pt//SocialGame/") {

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

rapidjson::Value & CentralServerWebService::getConnectionsOfUser(const int userId) {
	return getData("Connections", "getConnectionsOfUser", std::to_string(userId))->operator[]("data");
}

rapidjson::Document * CentralServerWebService::getData(const string type, const string function, const string params) {
	std::string result = curl_httpget(baseUrl + type + '/' + (params.length() == 0 ? function : function + "?Params=" + params));
	printf("Queried %s...\nReceived: %s\n", (baseUrl + type + '/' + function + "?Params=" + params).c_str(), result.c_str());

	rapidjson::Document * d = new rapidjson::Document();
	d->Parse<0>(result.c_str());

	return d;
}
