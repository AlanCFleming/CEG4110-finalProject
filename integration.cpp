#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

//Assume that stored vital information is the most resently validated information for the patient from their last visit
//Blood pressure is reffering to Systolic blood pressure
//Oxygen is a percentage with 1 representing 100%
struct patient{
	double bloodPressure;
	double temperature;
	double heartrate;
	double oxygen;
	int age;
	string name;
	string doctor;
} ;

//assume that this stucture stores identification information accuracy threasholds as doubles between 0 and 1 inclusively
//Identification accuracy will be recieved by the program to compare to threadholds
//For status, the sting available indicates the doctor is in office and availible.
struct doctor{
	double fingerprint;
	double iris;
	double voice;
	double signature;
	string name;
	string status;
} ;


//for simulation purposes, the patient and doctor information is recieved as command line arguments in the order given above.
int main(int argc, char **argv) {

	//check to see if enough arguments were given
	//We ignore any extra arguments
	if(argc < 13) {
		cout << "Please input all patient and doctor information as arguments\n";
	}

	//set up boolean to track validity
	bool doctorValid = true, patientValid = true;

	//initialize known patient record
	patient patientKnown;
	patientKnown.bloodPressure = 100;
	patientKnown.temperature = 98.6;
	patientKnown.heartrate = 80;
	patientKnown.oxygen = 0.95;
	patientKnown.age = 22;
	patientKnown.name = "John Smith";
	patientKnown.doctor = "Travis Doom";

	//initialize input patient record
	try {
		patient patientInput;
		patientInput.bloodPressure = stod(argv[1]);
		patientInput.temperature = stod(argv[2]);
		patientInput.heartrate = stod(argv[3]);
		patientInput.oxygen = stod(argv[4]);
		patientInput.age = stoi(argv[5]);
		patientInput.name = argv[6];
		patientInput.doctor = argv[7];
	} catch (...) {
		patientValid = false;
	}

	//initialize known doctor record
	doctor doctorKnown;
	doctorKnown.fingerprint = 0.95;
	doctorKnown.iris = 0.95;
	doctorKnown.voice = 0.95;
	doctorKnown.signature = 0.95;
	doctorKnown.name = "Travis Doom";
	doctorKnown.status = "available";

	//initialize input doctor record
	try {
		doctor doctorInput;
		doctorInput.fingerprint = stod(argv[8]);
		doctorInput.iris = stod(argv[9]);
		doctorInput.voice = stod(argv[10]);
		doctorInput.signature = stod(argv[11]);
		doctorInput.name = argv[12];
		doctorInput.status = argv[13];
	} catch(...) {
		doctorValid = false;
	}


	return 0;
}
