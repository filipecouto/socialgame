#include "InterfaceToPHP.h"

string interfaceLocation = "http://uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/InterfaceToBLL";

vector<Mood> getMoods(){
	vector<Mood> moods;
	string params= "?Theme=moods&Function=getAllMoods";
	string result = curl_httpget(interfaceLocation+params);

	rapidjson::Document d;
    d.Parse<0>(result.c_str());

	const rapidjson::Value& a = d["data"];
	assert(a.IsArray());
	for (rapidjson::SizeType i = 0; i < a.Size(); i++){
		Mood m = Mood(a[i]["description"].GetString());
		moods.push_back(m);
	}
	return moods;
}