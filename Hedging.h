//
//  Hedging.h
//  HedgeClass
//
//  Created by Superfish on 14-9-4.
//  Copyright (c) 2014年 Superfish. All rights reserved.
//

#ifndef __HedgeClass__Hedging__
#define __HedgeClass__Hedging__

#include <iostream>
#include "OptionContract.h"
#include "Hedger.h"



double Hedging(OptionContract& OC,
               Hegdger& Hed,
               double S0,
               unsigned long HedgeTime);



#endif /* defined(__HedgeClass__Hedging__) */
