#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct patient{
	double bloodPressure;
	double temperature;
	double heartrate;
	double oxygen;
	int age;
	char* name;
	char* doctor;
} ;

//assume that this stucture stores identification information accuracy threasholds as doubles between 0 and 1 inclusively
//Identification accuracy will be recieved by the program to compare to threadholds
//For status, a True indicates the doctor is in office and availible.
struct doctor{
	double fingerprint;
	double iris;
	double voice;
	double signature;
	char* name;
	bool status;
} ;


int main(int argc, char **argv) {


	return 0;
}
