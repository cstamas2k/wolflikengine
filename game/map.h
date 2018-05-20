#pragma once

#include <string>
#include <iostream>
#include <fstream>

//std::ifstream in("map1.dat");
//std::string map_data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

std::string map_data;

std::string loadMap() { //TODO: different maps
	std::string mapthing;
	std::ifstream mapFile("map1.dat");
	mapFile >> mapthing;
	return mapthing;
}

//the map size MUST BE 16x16 tile