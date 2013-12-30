#include <stdio.h>
#include <string>
#include <iostream>
#include <document.h> //Rapidjson
#include <CurlHelper.h>
using namespace std;

string interfaceLocation = "http://uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/InterfaceToBLL";
string params1 = "?Theme=moods&Function=getParams&Params=ola^mundo";
string params2 = "?Theme=moods&Function=getAllMoods";

int main(int argc, char *argv[])
{
	//Get the result
	string result = curl_httpget(interfaceLocation+params2);

	//Print the result
    cout << result << endl;

	//Creating a json result - example
	//const char json[] = "{ \"hello\" : \"world\" }";

	//Parse the result
    rapidjson::Document d;
    d.Parse<0>(result.c_str());

	//Example with single return
	//Test with params1
    //printf("%s\n", d["data"].GetString());

	//Example with array return
	//Test with params2
	const rapidjson::Value& a = d["data"]; // Using a reference for consecutive access is handy and faster.
	assert(a.IsArray());
	for (rapidjson::SizeType i = 0; i < a.Size(); i++){ // rapidjson uses SizeType instead of size_t.
		printf("a[%d] = ", i);
		printf("%s = ",a[i]["id"]);
		printf("%s\n",a[i]["description"]);
		cout << a[i]["id"].GetString() << " " << a[i]["description"].GetString() << endl;
	}

	system("pause");
}