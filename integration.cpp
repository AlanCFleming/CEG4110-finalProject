#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>


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
//For status, the sting available indicates the doctor is in office and available.
struct doctor{
	double fingerprint;
	double iris;
	double voice;
	double signature;
	string name;
	string status;
};


//function for checking patient information

bool checkPatient(patient unknown, patient known) {
	
	bool valid = true;
	
	if(unknown.bloodPressure <= 0) { 
		valid = false;
	}

	if(isnan(unknown.temperature)) {
		valid = false;
	}

	if(unknown.heartrate < 0) {
		valid = false;
	}

	if(unknown.oxygen < 0) {
		valid = false;
	}

	if(unknown.age < 0) {
		valid = false;
	}

	//copy and transform names for comparison
	string temp1 = unknown.name, temp2 = known.name;

	transform(temp1.begin(), temp1.end(), temp1.begin(), ::tolower);
	transform(temp2.begin(), temp2.end(), temp2.begin(), ::tolower);

	if(temp1.compare(temp2) != 0) {
		valid = false;
	}

	//copy and transform doctor names for comparison
	temp1 = unknown.doctor;
	temp2 = known.doctor;

	transform(temp1.begin(), temp1.end(), temp1.begin(), ::tolower);
	transform(temp2.begin(), temp2.end(), temp2.begin(), ::tolower);

	if(temp1.compare(temp2) != 0) {
		valid = false;
	}

	//return validity
	return valid;
}

bool checkDoctor( doctor unknown, doctor known) {
	
	bool valid = true;
	
	if(unknown.fingerprint < known.fingerprint) {
		valid = false;
	}

	if(unknown.iris < known.iris) {
		valid = false;
	}

	if(unknown.voice < known.voice) {
		valid = false;
	}

	if(unknown.signature < known.signature) {
		valid = false;
	}
	
	//copy and transform names for comparison
	string temp1 = unknown.name, temp2 = known.name;

	transform(temp1.begin(), temp1.end(), temp1.begin(), ::tolower);
	transform(temp2.begin(), temp2.end(), temp2.begin(), ::tolower);

	if(temp1.compare(temp2) != 0) {
		valid = false;
	}

	//copy and transform status for comparison
	temp1 = unknown.status;
	temp2 = known.status;

	transform(temp1.begin(), temp1.end(), temp1.begin(), ::tolower);
	transform(temp2.begin(), temp2.end(), temp2.begin(), ::tolower);

	if(temp1.compare(temp2) != 0 || temp1.compare("available") != 0) {
		valid = false;
	}

	return valid;
}

bool comparePatientDoctor(patient p, doctor d) {
		
	bool valid = true;

	//copy and transform doctor name for comparison
	string temp1 = p.doctor, name2 = d.name;

	transform(temp1.begin(), temp1.end(), temp1.begin(), ::tolower);
	transform(name2.begin(), name2.end(), name2.begin(), ::tolower);

	if(temp1.compare(name2) != 0) {
		valid = false;
	}

	return valid;
}

//for simulation purposes, the patient and doctor information is recieved as command line arguments in the order given above.
int main(int argc, char **argv) {

	//check to see if enough arguments were given
	//We ignore any extra arguments
	if(argc < 13) {
		cout << "Please input all patient and doctor information as arguments\n";
		return 1;
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
	patient patientInput;
	try {
		
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
	doctor doctorInput;
	try {
		
		doctorInput.fingerprint = stod(argv[8]);
		doctorInput.iris = stod(argv[9]);
		doctorInput.voice = stod(argv[10]);
		doctorInput.signature = stod(argv[11]);
		doctorInput.name = argv[12];
		doctorInput.status = argv[13];
	} catch(...) {
		doctorValid = false;
	}

	//check patient and doctor validity
	if(patientValid) {
		patientValid = checkPatient(patientInput, patientKnown);
	}

	if(doctorValid) {
		doctorValid = checkDoctor(doctorInput, doctorKnown);
	}

	//no need to cross reference a invalid doctor or patient
	if(doctorValid && patientValid) {
		//If the entries dont match assume the doctor is not the correct doctor
		doctorValid = comparePatientDoctor(patientKnown, doctorKnown);
	}

	//print message based on validity class
	if(!patientValid && !doctorValid){
		cout << "The patient information does not match known records or was invalid and the doctor was not able to be authenticated or unavailable\n";
	} else if (!patientValid) {
		cout << "The patient information does not match known records or was invalid; however, the doctor was able to be authenticated\n";
	} else if (!doctorValid) {
		cout << "The patient information does match known records; however, the doctor was not able to be authenticated or unavailable\n";
	} else { 
		cout << "The patient information does match known records and the doctor was able to be authenticated\n";
	}

	return 0;
}
