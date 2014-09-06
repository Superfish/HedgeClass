//
//  Hedging.cpp
//  HedgeClass
//
//  Created by Superfish on 14-9-4.
//  Copyright (c) 2014年 Superfish. All rights reserved.
//

#include "Hedging.h"
#include <cmath>
#include "Random.h"
#include <vector>

using namespace std;

double Hedging(OptionContract& OC,
               Hegdger& Hed,
               double S0,
               unsigned long HedgeTime)
{
    double vol = OC.GetSigma();
    double r = OC.GetInterest();
    double expiry = OC.GetExpiry();
    double strike = OC.GetStrike();
 
    double interveltime = expiry/(HedgeTime-1);
    double variance;
    double RootVariance;
    double MarginTradingRate = r * 2;
    double ShortSellingRate = 0.08;
    double DividendRate = 0;
    double ThisSpot = S0;
    double TimeSlot = 0;
    double ThisGaussian;
    double Dsum;
    double Dh;
    double result;
    
    vector<double> UnderPrice(HedgeTime);
    vector<double> delta(HedgeTime);
    vector<double> purchased(HedgeTime);
    vector<double> PurchasedCost(HedgeTime);
    vector<double> CumCost(HedgeTime);
    vector<double> MTaccount(HedgeTime); //MarginTrading, positive means borrow money from bank
    vector<double> SSaccount(HedgeTime); //ShortSelling, positive means borrow from brokerage
    vector<double> ULaccount(HedgeTime); //UnderLyign
    
    for (unsigned long i=0; i < HedgeTime; i++)
    {
        //Calculate
        //Presion error
        Dsum=OC.delta(expiry + 0.001 - TimeSlot, ThisSpot);
        Dh=Hed.delta(expiry + 0.001 - TimeSlot, ThisSpot);
        variance = vol*vol*interveltime;
        RootVariance = sqrt(variance);
        //Record
        UnderPrice[i] = ThisSpot;
        delta[i] = Dsum;
        //Renew
        TimeSlot += interveltime;
        ThisGaussian = GetOneGaussianByBoxMuller();
        ThisSpot = ThisSpot * exp(RootVariance*ThisGaussian);
        
        if(i>=1)
        {
            //The delta here is the delta of the portfolio
            //It can decide the number of the underlying need to purchased
            purchased[i] = (delta[i] - delta[i-1])/Dh;
            //Go buying
            PurchasedCost[i] = purchased[i] * UnderPrice[i];
            SSaccount[i] = SSaccount[i-1] - purchased[i];
            //The cost of lending is calculated every time stamp.
            //If just sell the partial position we have, there is no lending cost outside.
            if(MTaccount[i-1] < 0){
                //save money in the bank
                if (SSaccount[i-1]<0) {
                    MTaccount[i] = MTaccount[i-1] + PurchasedCost[i] + (SSaccount[i-1]*UnderPrice[i-1]*DividendRate - MTaccount[i-1]*r)*interveltime;
                } else {
                    MTaccount[i] = MTaccount[i-1] + PurchasedCost[i] + (SSaccount[i-1]*UnderPrice[i-1]*ShortSellingRate - MTaccount[i-1]*r)*interveltime;
                }
            }else{
                //borrow money from others
                if (SSaccount[i-1]<0) {
                    MTaccount[i] = MTaccount[i-1] + PurchasedCost[i] + (SSaccount[i-1]*UnderPrice[i-1]*DividendRate + MTaccount[i-1]*MarginTradingRate)*interveltime;
                }else{
                    MTaccount[i] = MTaccount[i-1] + PurchasedCost[i] + (SSaccount[i-1]*UnderPrice[i-1]*ShortSellingRate + MTaccount[i-1]*MarginTradingRate)*interveltime;
                }
            }
        }else if(i == 0)
        {
            purchased[i] = delta[i]/Dh;
            PurchasedCost[i] = purchased[i] * UnderPrice[i];
            SSaccount[i] = -purchased[i];
            MTaccount[i] = PurchasedCost[i];
        }
        
        result = MTaccount[HedgeTime - 1];
        //Can be taken away or not
        if (i == HedgeTime - 1 & UnderPrice[i] > strike) {
            //Modified the result
            result = MTaccount[i] - strike * (-SSaccount[i]) * OC.GetUnit();
        }
    }
    
    
    if(HedgeTime==24){
     
        
    }
    

    return result;
}

