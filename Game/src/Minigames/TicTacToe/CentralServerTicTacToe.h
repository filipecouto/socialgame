#ifndef CENTRALSERVERTICTACTOE_H
#define CENTRALSERVERTICTACTOE_H

#include <iostream>
#include <string>
#include "../IMinigame.h"
#include "../../Mods/AdvancedMode/dependencies/CurlHelper/CurlHelper.h"
#include "../../Mods/AdvancedMode/dependencies/rapidjson/document.h"
#include <math.h>
#include <string.h>
#include <algorithm> 

class CentralServerTicTacToe {
public:
    CentralServerTicTacToe();

    string game(string list);

    string first();

private:
    string server = "uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/InterfaceToBLL";
};
#endif
