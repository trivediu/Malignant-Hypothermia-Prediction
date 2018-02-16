/*Jay Swaminarayan - Swami Shreeji*/
#include "ETCO2.hpp"

ETCO2::ETCO2()
{
	//PART 1 - GENERATE TIME

	//generate a value for the time the measurement 
	//value must be from January 1, 2000


	time_t timer;			//timer variable to store current time in seconds since epoch
	struct tm mill = { 0 };	//initialize a tm object for the millenium (Jan 1, 2000)

							//Set the values of the mill variable 
	mill.tm_hour = 0;	//hours since midnight
	mill.tm_min = 0;	//minutes after the hour 
	mill.tm_sec = 0;	//seconds after the minute	
	mill.tm_year = 100;	//years since 1900 
	mill.tm_mon = 0;	//Months since January (range: 0-11)
	mill.tm_mday = 1;	//Days of the month (range: 1-31)

						//get and set current time 


						//Wait 1 Second Before Proceeding Because Data is being outputted per second
						//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	timer = time(0);

	//Now we simply calculate total seconds that have elapsed since Jan 1, 2000
	secs = difftime(timer, mktime(&mill));

	//thus above we have created a temporary start time
	secs += 3;



	//Also seed the random number generator
	unsigned seed;
	seed = time(NULL);
	srand(seed);

	//reset counter
	counter = 0;

}

double ETCO2::getSec()
{
	return secs;
}

double ETCO2::getVal()
{
	return value;
}

void ETCO2::genVals()
{
	//for the purpose of simulation increment the time counter by one on each cycle
	counter++;

	//if we have reached ten readings, increment seconds by 10 to get to the next batch of 10 seconds
	if (counter >= 10) {
		secs += 10;
	}
	
	//add one to the current second measurement
	secs += 1;

	//***********************************************************************************
	//PART 2: GENERATE A RANDOM ETCO2 Value 

	/*Brief research I did shows that 35-45 mm Hg is considered normal ETCO2
	Anything above 45 mg Is Considered Abnormal.  Within the context of this problem
	we will not concern ourselves with values below 35 as we are dealing with 
	Malignant Hyperthermia.  Our max value will be 57 mm Hg*/


	//We will now proceed to generate a random number between 35-57

	//we now randomly generate a value between 35-57 mm Hg for the ETCO2
	int max = 60;
	int min = 35;
	
	value = (rand() % (max - min + 1)) + min;
	cout << "Generated Data secs/val: " << secs << "\t" << value << endl << endl;

	return;
}