//
//  main.cpp
//  HedgeClass
//
//  Created by Superfish on 14-9-4.
//  Copyright (c) 2014年 Superfish. All rights reserved.
//

#include <iostream>
#include "OptionContract.h"
#include "Hedging.h"
#include "Random.h"
#include <vector>
#include <numeric>
#include <ctime>

int main(int argc, const char * argv[])
{
    // insert code here...
    double strike = 100;
    double interest = 0.05;
    double vol=0.2;
    double expiry=1;
    int covernum=1;
    CallContract testOC(covernum, strike, interest, vol, expiry);
    double H0 = 100;
    Hegdger testHed(H0);
    double testS0 = 100;
    unsigned long testHedgeTime = 3;

    double result = Hedging(testOC,
                            testHed,
                            testS0,
                            testHedgeTime);
    
    std::cout << result <<std::endl;
    
    
    std::vector<double> v(300);
    for (unsigned long i = 3; i < 300; i++)
    {
        srand( static_cast<unsigned int>(time(NULL)));
        v[i] = Hedging(testOC,testHed,testS0,i);

    }
    double sum = accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();
    std::cout << mean <<std::endl;
    
    return 0;
}

