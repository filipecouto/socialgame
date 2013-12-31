#ifndef INTERFACETOPHP_H
#define INTERFACETOPHP_H

#include "Mood.h"
#include <document.h> //Rapidjson
#include <CurlHelper.h>
#include <vector>
#include <iostream>
using namespace std;

vector<Mood> getMoods();

#endif