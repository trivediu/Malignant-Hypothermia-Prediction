/*Jay Swaminaryan*/
//Uday S. Trivedi


#include <iostream>
//#include "ETCO2.hpp"
#include "Analyze.hpp"

//#include <chrono> //for sleep function - already included in ETC02 hpp file
//#include <thread> //for sleep function - already included in ETC02 hpp file

int main()
{
	ETCO2 breath;
	Analyze calc;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			breath.genVals();
			calc.processETCO2(breath);
		}
	}

	return 0;

}