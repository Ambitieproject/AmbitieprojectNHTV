#pragma once

#include <iostream>
#include <random>
#include <chrono>

//Class that holds helper methods
class HelperMethods {
public:
	//Constructor
	HelperMethods();
	//Destructor
	~HelperMethods();

	//Gets a random int between the given parameters
	static int GetRandomInt(int min, int max);
};

