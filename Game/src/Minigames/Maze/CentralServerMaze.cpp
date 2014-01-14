#include "CentralServerMaze.h"

CentralServerMaze::CentralServerMaze() {

}

CentralServerMaze::~CentralServerMaze() {

}



vector<int*> CentralServerMaze::calculatePath(vector<int> start, vector<int> end, bool ** matrix, vector<int> dimensions) {
	std::string matriz = convert(matrix, dimensions);
	std::string url = "http://uvm001.dei.isep.ipp.pt/SocialGame/Minigames/Maze/Solve/" + std::to_string(start.at(0)) + "," + std::to_string(start.at(1)) + "/" + std::to_string(end.at(0)) + "," + std::to_string(end.at(1)) + "/";
	std::string serverResponse = curl_httppost(url, "maze="+matriz);
// 	printf("%s\n", url.c_str());
// 	printf("%s\n", matriz.c_str());
//  	printf("%s\n", serverResponse.c_str());
	std::vector<int*> result = convertResult(serverResponse);
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

std::vector< int * > CentralServerMaze::convertResult(string response) {
	vector<int*> result;
	int pos1, pos2, temp1;
	while(pos1 = response.find_first_of("(") != -1) {
		pos2 = response.find_first_of(")");
		std::string temp = response.substr(pos1, pos2);
		pos1 = temp.find_first_of(",");
		temp1 = pos1 - temp.find_first_of("(") - 1;
		std::string num1 = temp.substr(temp.find_first_of("(")+1,temp1);
		std::string num2 = temp.substr(pos1+1,temp.size());
		response = response.substr(pos2+1, response.size());
		int * nums = new int[2];
		nums[0] = atoi(num1.c_str());
		nums[1] = atoi(num2.c_str());
		result.push_back(nums);
	}
	return result;
}
