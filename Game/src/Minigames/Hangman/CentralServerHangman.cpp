 
#include "CentralServerHangman.h"

CentralServerHangman::CentralServerHangman() : url("http://uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/PrologService/Minigames/interfaceToHangmanMinigame.php") {

}

bool CentralServerHangman::findLetterInWord(string letter, string word)
{
    transform(letter.begin(), letter.end(), letter.begin(),(int (*)(int))tolower);
    transform(word.begin(), word.end(), word.begin(),(int (*)(int))tolower);
    string params = letter+","+ word;
    std::string result = execute("move", params);
    string answer = result.substr(2,1);
    if(answer.compare("0")) {
        return true;
    }
    if(answer.compare("1")) {
        return false;
    }
	return false;
}

string CentralServerHangman::getWordAndCategory()
{
	printf("Hello\n");
    // const rapidjson::Value & v = getData("beginGame","")->operator[]("data");
    std::string result = execute("beginGame", "");
    return result;
}

std::string CentralServerHangman::execute( const string function, const string params) {
    std::string result = curl_httpget(url  +"?method="+ (params.length() == 0 ? function : function + "&params=" + params));
    printf("Queried %s...\nReceived: %s\n", (url  + +"?method="+function + "&params=" + params).c_str(), result.c_str());
    return result;
}