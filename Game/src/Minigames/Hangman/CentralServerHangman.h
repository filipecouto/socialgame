#ifndef CENTRALSERVERHANGMAM_H
#define CENTRALSERVERHANGMAM_H

#include <string>#include "../IMinigame.h"
#include "../../Mods/AdvancedMode/dependencies/CurlHelper/CurlHelper.h"
#include "../../Mods/AdvancedMode/dependencies/rapidjson/document.h"
#include <math.h>
#include <string.h>
#include <algorithm> 
class CentralServerHangman {
public:
    CentralServerHangman();

    bool findLetterInWord(string letter, string word);

    string getWordAndCategory();

    std::string execute( const string function, const string params) ;

private:
    string url;
};
#endif
