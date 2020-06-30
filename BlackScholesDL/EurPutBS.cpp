/****************************************************************************************
* Project		:	Basic Numerical C++ Library for Finance
* File			:	EurPutBS.cpp
* Lenguaje		:	C++
* License		:	Apache License Ver 2.0, www.apache.org/licenses/LICENSE-2.0
* Description	:	Implemenation of member functions for the EurPutBS Class
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
#include "EurPutBS.h"

/****************************************************************************************
*									MEMBER FUNCTIONS									*
****************************************************************************************/

//constructors
EurPutBS::EurPutBS() :EurOptionBS() { m_type = "put"; }
EurPutBS::EurPutBS(double T, double K) : EurOptionBS(T, K) { m_type = "put"; }

// Exact price using the Black-Scholes model
double EurPutBS::priceByBSFormula(double S0, double sigma, double r) {
    // S0   : Initial Stock Price
    // sigma: Annualized volatility
    // r    : Annual risk-free interest rate
   // return S0 * normalCDF(dPlus(S0, sigma, r)) - m_K * exp(-r * m_T) * normalCDF(dMinus(S0, sigma, r));
    return -S0 * normalCDF(-dPlus(S0, sigma, r)) + m_K * exp(-r * m_T) * normalCDF(-dMinus(S0, sigma, r));
}

// Calculate the Delta of using the Black-Scholes model.
double EurPutBS::deltaByBSFormula(double S0, double sigma, double r) {
    return -normalCDF(-dPlus(S0, sigma, r));
}

// Calculate the Gamma of using the Black-Scholes model.
double EurPutBS::gammaByBSFormula(double S0, double sigma, double r) {
    return normalPDF(dPlus(S0, sigma, r)) / (sigma * S0 * sqrt(m_T));
}

// Calculate the Theta of using the Black-Scholes model.
double EurPutBS::thetaByBSFormula(double S0, double sigma, double r) {
    return -((sigma * S0) / (2*sqrt(m_T)))* normalPDF(-dPlus(S0, sigma, r)) + r * m_K * exp(-r * m_T) * normalCDF(-dMinus(S0, sigma, r));
}