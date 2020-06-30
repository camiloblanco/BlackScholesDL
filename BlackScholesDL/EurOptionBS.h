/****************************************************************************************
* Project		:	Basic Numerical C++ Library for Finance
* Lenguaje		:	C++
* Description	:	Header file for the EurOptionBS Abstract Class
*					
* References	:	- Instruction and some code by Dr. Michael Philips @qmul.ac.uk
*					- M.Capinski and T.Zastawniak, Numerical Methods in Finance with C++,
*					  Cambridge, 2012, code: http://www.cambridge.org/9780521177160
*                   - Greeks from P. Wilmott Introduces Quantitative Finance, Second Ed.
* Git Control	:	https://github.com/camiloblanco/BlackScholesDL/
* Author - Year	:	Camilo Blanco Vargas - 2020
* Mail - Web	:	mail@camiloblanco.com - www.camiloblanco.com
****************************************************************************************/

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#pragma once
#include <cmath>
#include <string>

using namespace std;

/****************************************************************************************
*									CLASS DECLARATION									*
****************************************************************************************/
class EurOptionBS
{
    public:    

        //constructors
        EurOptionBS();
        EurOptionBS(double T, double K);

        //accessors
        void setT(double T);
        void setK(double K);
        double getT();
        double getK();
        string getType();

        // Public Member functions
        virtual double priceByBSFormula(double S0, double sigma, double r) = 0;
        virtual double deltaByBSFormula(double S0, double sigma, double r) = 0;
        virtual double gammaByBSFormula(double S0, double sigma, double r) = 0;
        virtual double thetaByBSFormula(double S0, double sigma, double r) = 0;

        //destructors
        ~EurOptionBS();

    protected:

        // protected Member functions
        double dPlus(double S0, double sigma, double r);
        double dMinus(double S0, double sigma, double r);
        double normalCDF(double x);
        double normalPDF(double x);

        // protected  Member variables
        double m_T;  // Time to maturity in years 
        double m_K;  // Strike (Exercise) Price
        string m_type; // String for option type
};

