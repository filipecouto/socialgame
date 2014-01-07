#include "CurlHelper.h"

string curl_httpget(const string &url)
{
    string buffer;
 
    CURL *curl;
    CURLcode result;
 
    curl = curl_easy_init();
 
    if (curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_HEADER, 0);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
 
      result = curl_easy_perform(curl);//http get performed
 
      curl_easy_cleanup(curl);//must cleanup
 
      //error codes: http://curl.haxx.se/libcurl/c/libcurl-errors.html
      if (result == CURLE_OK)
          return buffer;
      //curl_easy_strerror was added in libcurl 7.12.0
      cerr << "error: " << result << " " << curl_easy_strerror(result) <<endl;
      return "";
    }
 
    cerr << "error: could not initalize curl" << endl;
    return "";
}
 
int writer(char *data, size_t size, size_t nmemb, string *buffer)
{
  int result = 0;
  if (buffer != NULL)
  {
      buffer->append(data, size * nmemb);
      result = size * nmemb;
  }
  return result;
}