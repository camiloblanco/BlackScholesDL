/****************************************************************************************
* Project		:	Basic Numerical C++ Library for Finance
* File			:	EurOptionBS.cpp
* Lenguaje		:	C++
* License		:	Apache License Ver 2.0, www.apache.org/licenses/LICENSE-2.0
* Description	:	Implemenation of member functions for the EurOptionBS Abstract Class
*
* References	:	- Instruction and some code by Dr. Michael Philips @qmul.ac.uk
*					- M.Capinski and T.Zastawniak, Numerical Methods in Finance with C++,
*					  Cambridge, 2012, code: http://www.cambridge.org/9780521177160
*                   - Greeks from P. Wilmott Introduces Quantitative Finance, Second Ed.
* Other files	:
* Git Control	:	https://github.com/camiloblanco/finlib/
* Author - Year	:	Camilo Blanco Vargas - 2020
* Mail - Web	:	mail@camiloblanco.com - www.camiloblanco.com
****************************************************************************************/

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#include "EurOptionBS.h"

/****************************************************************************************
*									MEMBER FUNCTIONS									*
****************************************************************************************/

//Default constructor
EurOptionBS::EurOptionBS(): m_T (0), m_K(0) {
    m_type = "";
}

//Parametrized constructor
EurOptionBS::EurOptionBS(double T, double K): m_T(T), m_K(K) {
    m_type = "";
}

//accessors
void EurOptionBS::setT(double T){ m_T = T; }
void EurOptionBS::setK(double K){ m_K = K; }
double EurOptionBS::getT() { return m_T; }
double EurOptionBS::getK(){ return m_K; }
string EurOptionBS::getType() { return m_type; }



// Calculate the d+ (d1) coeficient for the BS formula.
double EurOptionBS::dPlus(double S0, double sigma, double r) {
	return (log(S0 / m_K) + (r + 0.5 * pow(sigma, 2.0)) * m_T) / (sigma * sqrt(m_T));
}

// Calculate the d- (d2) coeficient for the BS formula.
double EurOptionBS::dMinus(double S0, double sigma, double r) {
	return dPlus(S0, sigma, r) - sigma * sqrt(m_T);
}

// Aproximate the valude of the normal CDF at a given point x.
double EurOptionBS::normalCDF(double x) {
    double gamma = 0.2316419;     double a1 = 0.319381530;
    double a2 = -0.356563782;   double a3 = 1.781477937;
    double a4 = -1.821255978;   double a5 = 1.330274429;
    double pi = 4.0 * atan(1.0); double k = 1.0 / (1.0 + gamma * x);
    if (x >= 0.0)
    {
        return 1.0 - ((((a5 * k + a4) * k + a3) * k + a2) * k + a1) * k * exp(-x * x / 2.0) / sqrt(2.0 * pi);
    }
    else return 1.0 - normalCDF(-x);
}

// Aproximate the valude of the normal PDF at a given point x.
double EurOptionBS::normalPDF(double x) {

    double pi = 4.0 * atan(1.0); 
    return exp(-(x*x) / 2.0) / sqrt(2.0 * pi);
}

//Default destructor
EurOptionBS::~EurOptionBS() {}