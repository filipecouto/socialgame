#include <curl.h>
#include <string>
#include <iostream> //cerr
using namespace std;

int writer(char *data, size_t size, size_t nmemb, string *buffer);
string curl_httpget(const string &url);