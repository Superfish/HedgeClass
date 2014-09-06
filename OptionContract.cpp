//
//  OptionContract2.cpp
//  HedgeClass
//
//  Created by Superfish on 14-9-4.
//  Copyright (c) 2014年 Superfish. All rights reserved.
//

#include "OptionContract.h"
#include <cmath>

double phi(double x)
{
    // constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;
    
    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x)/sqrt(2.0);
    
    // A&S formula 7.1.26
    double t = 1.0/(1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);
    
    return 0.5*(1.0 + sign*y);
}



CallContract::CallContract(int ContractUnit_, double strike_, double r_, double sigma_, double expiry_): ContractUnit(ContractUnit_), strike(strike_), r(r_), sigma(sigma_),expiry(expiry_)
{
}

double CallContract::delta(double time, double SpotPirce)
{
    double d1;
    d1 = (log(SpotPirce/strike) + (r + sigma*sigma/2)*time)/(sigma*sqrt(time));
    return(phi(d1) * ContractUnit);
}

double CallContract::GetInterest()
{
    return r;
}

double CallContract::GetSigma()
{
    return sigma;
}

double CallContract::GetExpiry()
{
    return expiry;
}

double CallContract::GetStrike()
{
    return strike;
}

double CallContract::GetUnit()
{
    return ContractUnit;
}










