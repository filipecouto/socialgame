#ifndef CENTRALSERVERMAZE_H
#define CENTRALSERVERMAZE_H
#include "../../Mods/AdvancedMode/dependencies/CurlHelper/CurlHelper.h"
#include "../../Mods/AdvancedMode/dependencies/rapidjson/document.h"
#include <vector>

class CentralServerMaze {

	public:
		CentralServerMaze();
		virtual ~CentralServerMaze();
		
		vector<int*> calculatePath(vector<int> start, vector<int> end, bool ** matrix, vector<int> dimensions);
	private:
		std::string convert(bool **matrix, vector<int> dimensions);
		vector<int*> convertResult(std::string response);
};

#endif // CENTRALSERVERMAZE_H
