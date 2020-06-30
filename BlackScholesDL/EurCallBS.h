/****************************************************************************************
* Project		:	Basic Numerical C++ Library for Finance
* File			:	EurCallBS.h
* Lenguaje		:	C++
* License		:	Apache License Ver 2.0, www.apache.org/licenses/LICENSE-2.0
* Description	:	Header file for the EurCallBS Class
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
#pragma once
#include "EurOptionBS.h"

/****************************************************************************************
*									CLASS DECLARATION									*
****************************************************************************************/

class EurCallBS : public EurOptionBS
{
    public:

    //constructors
    EurCallBS();
    EurCallBS(double T, double K);

    // Public Member functions
    double priceByBSFormula(double S0, double sigma, double r);
    double deltaByBSFormula(double S0, double sigma, double r);
    double gammaByBSFormula(double S0, double sigma, double r);
    double thetaByBSFormula(double S0, double sigma, double r);
};

