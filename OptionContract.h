//
//  OptionContract2.h
//  HedgeClass
//
//  Created by Superfish on 14-9-4.
//  Copyright (c) 2014年 Superfish. All rights reserved.
//

#ifndef __HedgeClass__OptionContract__
#define __HedgeClass__OptionContract__

#include <iostream>

class OptionContract
{
public:
    OptionContract(){};
    virtual double delta(double time, double SpotPrice) = 0;
    virtual double GetInterest()= 0;
    virtual double GetSigma()= 0;
    virtual double GetExpiry()= 0;
    virtual double GetStrike()= 0;
    virtual double GetUnit()= 0;
private:
};

class CallContract: public OptionContract
{
public:
    CallContract(int ContractUnit_, double strike_, double r_, double sigma_, double expiry_);
    double delta(double time, double SpotPrice);
    double GetInterest();
    double GetSigma();
    double GetExpiry();
    double GetStrike();
    double GetUnit();
    
private:
    int ContractUnit;
    double strike;
    double r;
    double sigma;
    double expiry;
};


double phi(double x);


#endif /* defined(__HedgeClass__OptionContract2__) */
