//
//  Hedger.h
//  HedgeClass
//
//  Created by Superfish on 14-9-4.
//  Copyright (c) 2014年 Superfish. All rights reserved.
//

#ifndef __HedgeClass__Hedger__
#define __HedgeClass__Hedger__

#include <iostream>



class Hegdger
{
public:
    Hegdger(double H0_);
    double delta(double time, double UnderPrice);
    double InstantPrice(double UnderPrice);
    
private:
    const double H0;
};






#endif /* defined(__HedgeClass__Hedger__) */
