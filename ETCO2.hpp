/*Jay Swaminarayan - Swami Shreeji*/


#ifndef ETCO2_HPP
#define ETCO2_HPP
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class ETCO2
{
private:
	double secs;    //kept as double instead of int to assist later on in calculations.
	double value;
	int counter;

public:
	
	ETCO2();
	void genVals();	//a public function to generate values
	double getSec();  
	double getVal();
};


#endif