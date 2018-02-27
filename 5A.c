// usage: ./5A <number of digits> <number of simulations> <any character for single precision, no argument for double>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned long int SinglePrecisionMC(double target, int digitsofPrecision);
unsigned long int DoublePrecisionMC(double target, int digitsofPrecision);

int main(int argc, char *argv[]) {

	double pi = 3.1415926535897932;					// pi to 16 digits for comparison
	unsigned long long Sum = 0;						// stores the number of terms required for simulation
	int NS = 0;										// counter variable for while loop
	int digits = atof(argv[1]);						// parsing command line 
	int numSimulations = atoi(argv[2]);				// parsing command line
	char *string;									
	
	srand(time(NULL));
	
	if (argc > 3) {
		string = "Single";
		while (NS < numSimulations) {
			Sum += SinglePrecisionMC(pi, digits);
			NS += 1; }
	}
	else {
		string = "Double";
		while (NS < numSimulations) {
			Sum += DoublePrecisionMC(pi, digits);
			NS += 1; }
	}
	// compute the average number of terms for the specified number of simulations and output to screen
	double average = (double)Sum/(double)numSimulations;
	printf("Precision = %s\nNumber of Simulations = %d\nDecimal Places of Pi = %d\n",string,numSimulations,digits);
	printf("Average number of terms: %lf\n",average);
	return 0;
}

unsigned long int SinglePrecisionMC(double target, int digitsofPrecision)	{
	// "compare" ensures that the digit of interest is correct
	double compare = 0.5*pow(10,-1*(digitsofPrecision+1));
	float x,y;
	float piApprox = 1.0;
	unsigned long long Acircle = 0;					// possibly a necessity to use ull
	unsigned long long Atotal = 0;
	
	while (fabs(piApprox - target) > compare) {
		x = (float)rand()/(float)RAND_MAX;	
		y = (float)rand()/(float)RAND_MAX;
		if (x*x + y*y < 1.0)
			Acircle += 1;
		Atotal += 1;
		piApprox = 4.0*(float)Acircle/(float)Atotal;
		}
	return Atotal;
}

unsigned long int DoublePrecisionMC(double target, int digitsofPrecision)	{

	double compare = 0.5*pow(10,-1*(digitsofPrecision+1));
	double x,y;
	double piApprox = 1.0;
	unsigned long long Acircle = 0;
	unsigned long long Atotal = 0;
	
	while (fabs(piApprox - target) > compare) {
		x = (double)rand()/(double)RAND_MAX;
		y = (double)rand()/(double)RAND_MAX;
		if (x*x + y*y < 1.0)
			Acircle += 1;
		Atotal += 1;
		piApprox = 4.0*(double)Acircle/(double)Atotal;
		}
	return Atotal;
}
		
	




