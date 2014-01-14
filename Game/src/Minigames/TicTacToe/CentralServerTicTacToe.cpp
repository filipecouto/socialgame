 
#include "CentralServerTicTacToe.h"

CentralServerTicTacToe::CentralServerTicTacToe(){

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
	string url = server + params;
	//printf("%s %s\n",server.c_str(),params.c_str());
	string resultJson = curl_httpget(url);
	/*rapidjson::Document d;
	d.Parse<0>(resultJson.c_str());
	string result = d["data"].GetString();*/
	return "1";
}