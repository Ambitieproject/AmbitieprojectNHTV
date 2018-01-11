#include "HelperMethods.h"

//Constructor
HelperMethods::HelperMethods(){
	
}

//Destructor
HelperMethods::~HelperMethods() {

}

//Gets a random int between the given parameters
int HelperMethods::GetRandomInt(int min, int max) {
	//Create variable based on time
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//Put seed variable into standard random engine
	std::default_random_engine generator(seed);
	//Get double between min and max number
	std::uniform_real_distribution<double> distribution(min, max);
	//Return number
	return distribution(generator);
}
