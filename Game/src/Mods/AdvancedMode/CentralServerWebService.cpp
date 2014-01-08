/**
 * CentralServerWebService - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "CentralServerWebService.h"

CentralServerWebService::CentralServerWebService() : baseUrl("http://172.31.100.1/SocialGame/") {

}

int CentralServerWebService::login(string email, string password) {
	const rapidjson::Value& v = getData("Users", "doLogin", email + "^" + password)->operator[]("data");

	if (v.IsNull()) {
		return -1;
	}
	else {
		token = v.GetString();
		//printf("My token is %s :D\n", token.c_str());
		return 1;
	}
}

rapidjson::Document * CentralServerWebService::getData(const string type, const string function, const string params) {
	std::string result = curl_httpget(baseUrl + type + '/' + function + "?Params=" + params);
	//printf("Received: %s\n", result.c_str());

	rapidjson::Document * d = new rapidjson::Document();
	d->Parse<0>(result.c_str());

	return d;
}
