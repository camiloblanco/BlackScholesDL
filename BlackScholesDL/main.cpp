/****************************************************************************************
* Project		:	Machine Learning and modern numerical techniques for high-dimensional
*					option pricing - Financial Computing MSc. Dissertation QMUL 2019/2020
* License		:	MIT License, https://opensource.org/licenses/MIT
* Copyright (c) :	2020 Camilo Blanco 
* Mail - Web	:	mail@camiloblanco.com - www.camiloblanco.com
* Lenguaje / Env:	C++ / Microsoft Visual Studio Community 2019
* Git Control	:	https://github.com/camiloblanco/BlackScholesDL
* Description	:	main CPP file for the program BlackScholesDL, entry point.
*
* 
****************************************************************************************/

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/

#include<iostream>
#include<stdlib.h>
#include <random>
#include <iomanip>
#include <fstream>
#include <vector>

#include "EurOptionBS.h"
#include "EurCallBS.h"
#include "EurPutBS.h"

using namespace std;

/****************************************************************************************
*										FUNCTIONS									*
****************************************************************************************/

// Clear the console in any plataform
void clearConsole() {
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

// Pause execution waiting for a key
void menuPause() {
	cout << endl << "Press any key to continue..." << endl;
	cin.ignore();
	cin.get();
}

// Read a line from the console including spaces
void readLine(string& description) {
	cin.ignore();
	getline(cin, description);
}

//Menu for pricing an European Call and Put Options using the Black-Scholes model
void priceEurOptionBS() {
	//Declare Variables
	double T = 0, K = 0, S0 = 0, sigma = 0, r = 0;
	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "	Price european optiosn using the Black-Scholes model" << endl << endl;
	cout << "Please enter the Time to maturity in years (T): " << endl;
	cin >> T;
	cout << "Please enter the Strike (Exercise) Price (K): " << endl;
	cin >> K;
	cout << "Please enter the Initial Stock Price (S0): " << endl;
	cin >> S0;
	cout << "Please enter the Annualized volatility (sigma): " << endl;
	cin >> sigma;
	cout << "Please enter the Annual risk-free interest rate (r): " << endl;
	cin >> r;
	if (T >= 0 && K >= 0 && S0 >= 0 && sigma >= 0 && r >= 0) {

		// Declare qn optionsPTRvec pointers vector, an EurCallBS, and an EurPutBS Objects
		vector<EurOptionBS*> optionsPTRvec;
		EurOptionBS* eurCallPTR = new EurCallBS(T, K);
		EurOptionBS* eurPutPRT = new EurPutBS(T, K);
		optionsPTRvec.push_back(eurCallPTR);
		optionsPTRvec.push_back(eurPutPRT);

		//Loop over the vector of options types
		for (auto& option : optionsPTRvec) {
			option->setK(K);
			option->setT(T);
			// Price the options, calculate the greeks and display
			cout << endl << "The Black-Scholes formula results for this " << option->getType() << " option are:" << endl;
			cout << "The option price is: " << option->priceByBSFormula(S0, sigma, r) << endl;
			cout << "The option Delta is: " << option->deltaByBSFormula(S0, sigma, r) << endl;
			cout << "The option Gamma is: " << option->gammaByBSFormula(S0, sigma, r) << endl;
			cout << "The option Theta is: " << option->thetaByBSFormula(S0, sigma, r) << endl;
		}
		
		//Delete EurOptionBS Objects
		for (auto pointer : optionsPTRvec)
		{
			delete pointer;
		}
		optionsPTRvec.clear();
	}
	else {
		cout << "All parameters must be positive. " << endl;
	}
	menuPause();
}

// Funtion to round up double values
double roundUp(double num, int places) {
	int factor = pow(10,places);
	return (places < 1) ? num : (ceil(num * factor) / (factor));
}

//Menu for Generating an European Options Datasets using the Black-Scholes model
void generateEurOptionBS() {

	//Declare Variables
	vector<EurOptionBS*> optionsPTRvec;
	const double nMin = 0.00000001;
	int numSamples=0;
	double T = 0, K = 0, S0 = 0, sigma = 0, r = 0;
	double tMax = 2.0, pMax=500.0, sigmaMax=1.0, rMax = 0.1;
	
	//Display menu and read number of samples for Dataset
	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "	Generate an European Vanilla Options Dataset using the Black-Scholes model" << endl << endl;
	cout << "Please enter the number of samples you want to generate (N): " << endl;
	cin >> numSamples;
	/*Personalize simulation parameters*/
	cout << endl << "For the next parameters the default minmum is 0.00000001 " << endl;
	cout << "Please enter the Maximun Time to maturity in years (tMax): " << endl;
	cin >> tMax;
	cout << "Please enter the Maximun Price (pMax for Strike and Stock): " << endl;
	cin >> pMax;
	cout << "Please enter the Maximun Annualized volatility (sigmaMax): " << endl;
	cin >> sigmaMax;
	cout << "Please enter the Maximun Annual risk-free interest rate (rMax): " << endl;
	cin >> rMax;
	/**/
	// Initialize random engine
	//Code derived from: https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
	random_device random_device; // create object for seeding
	mt19937 mt_engine(random_device()); // create engine and seed it with the previous object
	uniform_real_distribution<double> dist_time(nMin, tMax);
	uniform_real_distribution<double> dist_price(nMin, pMax);
	uniform_real_distribution<double> dist_sigma(nMin, sigmaMax);
	uniform_real_distribution<double> dist_rate(nMin, rMax);

	// Declare a EurCallBS, and a  EurPutBS Objects and store the in the optionsPTRvec pointers vector
	EurOptionBS* eurCallPTR = new EurCallBS(T, K);
	EurOptionBS* eurPutPRT = new EurPutBS(T, K);
	optionsPTRvec.push_back(eurCallPTR);
	optionsPTRvec.push_back(eurPutPRT);

	string fileName = "BSdataSet.csv";

	//First Open bsOptionsDataset.csv in new mode and save the header to clean the file
	ofstream fileStream(fileName);

	if (fileStream.is_open()) {
		// write the file headers and the simulation parameters:
		fileStream << "time" << "," << "strike_price" << "," << "stock_price" << "," << "volatility" << "," << "interest_rate" << ",";
		fileStream << "type_o1" << "," << "price_o1" << "," << "delta_o1" << "," << "gamma_o1" << "," << "theta_o1" << ",";
		fileStream << "type_o2" << "," << "price_o2" << "," << "delta_o2" << "," << "gamma_o2" << "," << "theta_o12" << endl;
		fileStream << "numSamples" << "," << "tMax" << "," << "pMax" << "," << "sigmaMax" << "," << "rMax" << endl;
		fileStream << numSamples << "," << tMax << "," << pMax << "," << sigmaMax << "," << rMax << endl;

		//Loop for each Sample
		for (int sample = 0; sample < numSamples; ++sample) {

			//Generate Random inputs and store to file
			T = roundUp(dist_time(mt_engine),6);
			K = roundUp(dist_price(mt_engine), 2);
			S0 = roundUp(dist_price(mt_engine), 2);
			sigma = roundUp(dist_sigma(mt_engine), 4);
			r = roundUp(dist_rate(mt_engine), 4);
			//cout<<"Sample: "<<sample<<", T=" << T << ", K=" << K << ", S0=" << S0 << ", sig=" << sigma << ", r=" << r << ", "<<endl;
			fileStream << T << "," << K << "," << S0 << "," << sigma << "," << r << ",";
			// Set Output precision to 8 decimals
			fileStream << fixed << setprecision(8);

			//Loop over the vector of options types
			for (auto& option : optionsPTRvec) {
				option->setK(K);
				option->setT(T);
				// Price the options, calculate the greeks and save results to file			
				fileStream << option->getType() << ",";
				fileStream << option->priceByBSFormula(S0, sigma, r) << ",";
				fileStream << option->deltaByBSFormula(S0, sigma, r)<< ",";
				fileStream << option->gammaByBSFormula(S0, sigma, r)<< ",";
				fileStream << option->thetaByBSFormula(S0, sigma, r) << ",";
			}
			// End of the dataser line
			fileStream << endl;
		}
	}
	fileStream.close();

	//Delete EurOptionBS Objects
	for (auto pointer: optionsPTRvec)
	{
		delete pointer;
	}
	optionsPTRvec.clear();
	menuPause();
}


/****************************************************************************************
*											 MAIN										*
****************************************************************************************/

int main()
{
	int option = 9;

	while (option != 0) {
		//clearConsole();
		cout << "****************************************************************************" << endl;
		cout << "		Black-Scholes calculator and dataset generator		 " << endl << endl;
		cout << "Select an option by entering the given number:" << endl << endl;
		cout << "1. Price an european option using the Black-Scholes formula" << endl;
		cout << "2. Generate an European options dataset using the Black-Scholes formula" << endl;
		cout << "0. To exit the program" << endl;
		cout << "****************************************************************************" << endl;
		cout << endl << "Please enter the option number:" << endl;
		cin >> option;
		if (option == 1) {
			priceEurOptionBS();
		}
		else if (option == 2) {
			generateEurOptionBS();
		}
		else if (option == 0) {
			cout << endl << "Thank you for using this program, have a nice day. " << endl << endl;
		}
		else {
			cout << "Invalid Option" << endl;
			menuPause();
		}

	}
}


