#include "CentralServerMaze.h"

CentralServerMaze::CentralServerMaze() {

}

CentralServerMaze::~CentralServerMaze() {

}



vector<int*> CentralServerMaze::calculatePath(vector<int> start, vector<int> end, bool ** matrix, vector<int> dimensions) {
	std::string matriz = convert(matrix, dimensions);
	std::string url = "http://uvm001.dei.isep.ipp.pt/SocialGame/Minigames/Maze/Solve/" + std::to_string(start.at(0)) + "," + std::to_string(start.at(1)) + "/" + std::to_string(end.at(0)) + "," + std::to_string(end.at(1)) + "/";
	std::string serverResponse = curl_httppost(url, "maze="+matriz);
	printf("%s\n", url.c_str());
	printf("%s\n", matriz.c_str());
 	printf("%s\n", serverResponse.c_str());
	std::vector<int*> result;
	return result;
}

string CentralServerMaze::convert(bool ** matrix, vector<int> dimensions) {
	std::string output = "[";
	int width = dimensions.at(0);
	int height = dimensions.at(1);
	for(int i = 0; i < height; i++) {
		output += "[";
		for(int j = 0; j < width; j++) {
			output += matrix[j][i] ? "1" : "0";
			if( (j+1) < width) {
				output += ",";
			}
		}
		output+="]";
		if( (i+1) < height ) {
			output+=",";
		}
	}
	output +="]";
	return output;
}

