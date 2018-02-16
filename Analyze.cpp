/*Uday Trivedi - Jan 12, 2018*/


#include "Analyze.hpp"

/************************************************************************
  Method: Constructor
  Inputs: N/A
  Return: N/A
  Description: Basic Constructor to initialize the variables and vectors
  **********************************************************************/
Analyze::Analyze() {
	
	dataSet.clear();	//clear ETCO2 vector upon creation of analyze object
	dataMaxes.clear();	//clear dataMaxes vector upon creation of analyze object
	r2 =    0;			//initialize variable for r squared
	slope = 0;			//initialize variable for the slope

	/*Below we set the official start time in seconds since Jan 1,2000.  This
	time is assumed to be the time in seconds (since Jan 1, 2000) that 
	we start measurements at.*/
	setStartTimeSecs();

	return;
}


/************************************************************************
Method: processETCO2
Inputs: ETCO2 Object (Object must contains time and value)
Return: void
Description: Processes the ETCO2 object and calls helper functions 
to calculate the slope and r^2 via linear regression
**********************************************************************/
void Analyze::processETCO2(ETCO2 breathData){
	
	//insert the current breath CO2 value into the vector
	dataSet.push_back(breathData);

	//if I reach a set of 10 data points in the vector execute the remaining
	//calculations
	if (dataSet.size() == 10) {
		
		//Find the maximum value in the vector and insert it into the dataMaxes vector
		findInsertMax();

		//Now check to see if we have filled up the dataMaxes vector with 10 measurements
		if (dataMaxes.size() == 10) {
			calcData();
			
			/*Uncomment below to debug/view data*/
			//cout << "R Squared: " << r2 << endl;
			//cout << "Slope is : " << slope << endl;
			
			if (slope > 1.5 && r2 > 0.64) {
				cout << "Alarm Activated" << endl;
				dataSet.clear();
				dataMaxes.clear(); //reset dataMaxes vector 
			}

			else {
				dataSet.clear();   //reset dataSet vector
				dataMaxes.clear(); //reset dataMaxes vector 
			}
		}

		//else if the size of dataMaxes is less than 10 we simply exit this function below
		else {
			dataSet.clear(); //clear because we've already read 10 data points, now reset for next 10
			return;
		}
	}

	//else if the data set is less than 10 we still can add more to be analyzed
	return;		//exit the function as we still haven't reached 10 data points
}



/************************************************************************
Method: setStartTimeSec (Set The Starting Time in Seconds)
Inputs: N/A
Return: void
Description: This method is called by the constructor and sets the 
official starting time which will be based as a reference for upcoming
measurements.  This is calculated by taking the time to object is created
and subtracting it front Jan 1, 2000.  This starting time is also used 
as a base time reference for inputted ETCO2 readings
**********************************************************************/
void Analyze::setStartTimeSecs() {
	time_t timer;			//timer variable to store current time in seconds since epoch
	
	struct tm mill = { 0 };	//initialize a tm object for the millenium (Jan 1, 2000)

	//Set the values of the mill variable 
	mill.tm_hour = 0;	//hours since midnight
	mill.tm_min  = 0;	//minutes after the hour 
	mill.tm_sec  = 0;	//seconds after the minute	
	mill.tm_year = 100;	//years since 1900 
	mill.tm_mon  = 0;	//Months since January (range: 0-11)
	mill.tm_mday = 1;	//Days of the month (range: 1-31)

	//get and set current time 
	timer = time(NULL);

	//calculate the total number of seconds that have elapsed since Jan 1, 2000 and set 
	//that as the private variable startTimeSecs.  Done by subtracting current time from
	//millenium time (seconds)
	startTimeSecs = difftime(timer, mktime(&mill));

	return;
}


/************************************************************************
Method: Convert Time
Inputs: ETCO2 object 
Return: double value (seconds)
Description: This simply converts the ETCO2 object's time value in to 
the current time that has elapsed since measurement has begun.  This 
function is called from within the calcData() function
**********************************************************************/
double Analyze::convertTime(ETCO2 breathData) {

	//Calculate actual seconds that measurement was taken at by simply subtracting time that has 
	//elapsed since Jan 1, 2000 by our official startTime
	double actualSecs = breathData.getSec() - startTimeSecs;

	return actualSecs;
}

/************************************************************************
Method: findInsertMax (find and insert the maximum)
Inputs: n/a
Return: void
Description: This function scans the current data set of 10 points to
find the greatest value.  When that value is found, that specific ETCO2
object will be placed in a new vector called dataMaxes.  DataMaxes vector
will only receive 1 value for every ten values that are read into the 
DataSet vector.
**********************************************************************/
void Analyze::findInsertMax() {
	
	//Set the default max value to be the first element of the dataSet vector
	double max = dataSet[0].getVal();
	
	//Also intialize a variable to remember the index value of the object that contained the max
	int maxIndex = 0;

	//this for loop will scan through all 10 values
	for (int i = 0; i < 10; i++) {
		
		//if the current value is greater than the current max set it to the max value
		if (dataSet[i].getVal() > max) {
			max = dataSet[i].getVal();
			maxIndex = i;
		}
			
	}

	/*Now push the ETCO2 object that contains the maximum value into the dataMaxes vector
	the reason I am pushing the object is because I want to store not only the max, but it's time
	value also*/
	dataMaxes.push_back(dataSet[maxIndex]);

	return;
}



/************************************************************************
Method: calcData (Calculate Data)
Inputs: n/a
Return: void
Description: This function calculates the slope and r^2 through linear
regression by drawing data from the dataMaxes vector.
**********************************************************************/
void Analyze::calcData(){

	double n = 10;		//we have a total of 10 data points, hence n is set equal to 10 (kept as double for convenience)
	double x = 0.0;		//initialize a variable to store the time in minutes for each measurement
	double y = 0.0;		//initialize a variable for the ETCO2 reading (assumption integer)

	double sumX = 0.0;  //sum of x
	double sumXX = 0.0;  //sum of individual x data points squared then added
	
	
	double sumY = 0.0;  //sum of y
	double sumYY = 0.0; //sum of individual y data points squared then added
	double sumXY = 0.0;	//sum of x*y
	

	double sumX2 = 0.0;  // value when the total sum of all x's is squared
	double sumY2 = 0.0;  // value when the total sum of all x's is squared

	cout << endl;		//create a new line to output vector data
	cout.precision(5);
	cout << fixed;
	//Calculate Sigma Values
	for (int i = 0; i < 10; i++) {

		x = convertTime(dataMaxes[i]) / 60.0; //get time in minutes for current datapoint
		y = dataMaxes[i].getVal();			//get ETCO2 value for current datapoint
		
		cout << "X: " << x << "\t" << "y:" << y << endl;

		sumX  += x;	
		sumXX += (x*x);
		
		sumY  += y;
		sumYY += (y*y);

		sumXY += (x*y);
	}

	//Last of all calculate these variables now that we have the individual totals
	sumX2 = sumX * sumX;   //sum of all x values squared
	sumY2 = sumY * sumY;   //sum of all y values squared

	//Now we calculate the value of r^2
	double rNum = (n * sumXY) - (sumX * sumY);
	double rDen = sqrt(((n * sumXX) - sumX2) * ((n * sumYY) - sumY2));
	double r = rNum / rDen;
	r2 = r * r;

	//Now we calculate the value of the slope
	double slopeNum = (n*sumXY) - (sumX*sumY);
	
	double slopeDen = (n * sumXX) - (sumX2);
	
	slope = slopeNum / slopeDen;


	return;
}


/************************************************************************
Method: resetData (Reset Data)
Inputs: n/a
Return: void
Description: This simply resets all variables and vectors.  This is the
same as what happens in the constructor, but for the convenience of the
user who can call this during the program just incase.
**********************************************************************/
void Analyze::resetData() {

	dataSet.clear();	//clear ETCO2 vector upon creation of analyze object
	dataMaxes.clear();	//clear dataMaxes vector upon creation of analyze object
	r2 = 0;			//initialize variable for r squared
	slope = 0;			//initialize variable for the slope

						/*Below we set the official start time in seconds since Jan 1,2000.  This
						time is assumed to be the time in seconds (since Jan 1, 2000) that
						we start measurements at.*/
	setStartTimeSecs();

	return;
}
