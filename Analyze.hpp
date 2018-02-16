/*Uday Trivedi - Jan 12, 2018*/



#ifndef ANALYZE_HPP
#define ANALYZE_HPP

#include <iostream>
#include <vector>
#include "ETCO2.hpp"

#include <cstdlib> 
#include <ctime>   


using namespace std;

class Analyze{

private:
	
	//PRIVATE VARIABLES
	double r2;						//the official value of R2
	double slope;					//the slope calculated by linear regression
	
	double startTimeSecs;			//a variable that stores an official "start" time in secs
									//this is initialized within the constructor. Kept as double instead
									//of int to assist later on in calculations. 
	
	vector<ETCO2> dataSet;			//vector to hold a set of ETCO2 objects (10 objects)

	vector<ETCO2> dataMaxes;		/*this vector will store the max valued ETCO2 objects from each
									10-second interval in the dataSet vector above - this vector
									will store upto 10 objects also*/


	//PRIVATE FUNCTIONS
	void setStartTimeSecs();		/*Calculate the start time (assumption) from which we will begin
									all measurements.  Calculated by subtracting time at object 
									creation from Jan 1, 2000.*/
	
	
	double convertTime(ETCO2);		/*This will take the current ETCO2 object, and convert it's
									time value to the number of seconds that have elapsed since
									we began measuring ("began measuring" equals setStartTimeSecs)
									Again double used to assist later on in calculations, could have
									been int with a static cast later on.*/
	
	void findInsertMax();			/*This will find the max in the dataSet vector (which contains 
									10 second interval readings - and push this value in to the 
									dataMaxes vector which keeps track of the max value in each
									of the 10-second intervals*/ 

	void calcData();				/*Calculates r^2 with datapoints from the dataMaxes vector
									by using a linear regression*/


public:
	
	Analyze();						//constructor which simply ensures vector is cleared and sets start time
	
	void processETCO2(ETCO2);		//the primary function we are concerned with to execute all
									//general calculations

	void resetData();
};


#endif