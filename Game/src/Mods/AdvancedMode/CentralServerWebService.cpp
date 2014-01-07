/**
 * CentralServerWebService - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "CentralServerWebService.h"

CentralServerWebService::CentralServerWebService() : baseUrl("http://uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/") {

}

rapidjson::Document * CentralServerWebService::getData(const string type, const string function) {
	std::string result = curl_httpget(baseUrl + type + '/' + function);

	rapidjson::Document * d = new rapidjson::Document();
	d->Parse<0>(result.c_str());
	
	return d;
}
