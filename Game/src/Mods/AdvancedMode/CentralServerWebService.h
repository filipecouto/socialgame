/**
 * CentralServerWebService - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef CENTRALSERVERWEBSERVICE_H
#define CENTRALSERVERWEBSERVICE_H

#include "dependencies/CurlHelper/CurlHelper.h"
#include "dependencies/rapidjson/document.h"

class CentralServerWebService {
public:
	CentralServerWebService();
	
	/**
	 * Gets a parsed rapidjson Document containing the requested data.
	 * important: do not forget to free the document from memory
	 */
	rapidjson::Document * getData(const std::string type, const std::string function, const std::string params);
	
	int login(std::string email, std::string password);
	
private:
	std::string baseUrl;
	std::string token;
};

#endif // CENTRALSERVERWEBSERVICE_H
