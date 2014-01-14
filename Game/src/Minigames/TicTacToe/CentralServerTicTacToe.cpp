 
#include "CentralServerTicTacToe.h"

CentralServerTicTacToe::CentralServerTicTacToe() : server("uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/InterfaceToBLL") {

}

string CentralServerTicTacToe::game(string list)
{
	string params ="?Theme=TicTacToe&Function=Game&Params=" + list;
	string resultJson = curl_httpget(server + params);
	rapidjson::Document d;
	d.Parse<0>(resultJson.c_str());
	string result = d["data"].GetString();
	return result;
}

string CentralServerTicTacToe::first()
{
	string params = "?Theme=TicTacToe&Function=First";
	string resultJson = curl_httpget(server + params);
	rapidjson::Document d;
	d.Parse<0>(resultJson.c_str());
	string result = d["data"].GetString();
	return result;
}