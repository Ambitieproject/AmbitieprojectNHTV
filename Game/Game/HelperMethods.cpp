#include "HelperMethods.h"

//Constructor
HelperMethods::HelperMethods()
{
	
}

//Destructor
HelperMethods::~HelperMethods()
{
}

//Gets a random int between the given parameters
int HelperMethods::GetRandomInt(int min, int max) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}
