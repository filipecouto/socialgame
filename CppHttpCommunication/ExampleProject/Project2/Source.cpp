#include <stdio.h>
#include <iostream>
#include <curl.h> 
using namespace std;


int main(void)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/InterfaceToBLL?Theme=moods&Function=getAllMoods");
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
	system("pause");
    return 0;
}