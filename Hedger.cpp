//
//  Hedger.cpp
//  HedgeClass
//
//  Created by Superfish on 14-9-4.
//  Copyright (c) 2014年 Superfish. All rights reserved.
//

#include "Hedger.h"

Hegdger::Hegdger(double H0_): H0(H0_)
{
}

double Hegdger::delta(double time, double UnderPrice)
{
    return 1;
}

double Hegdger::InstantPrice(double UnderPrice)
{
    return UnderPrice;
}

