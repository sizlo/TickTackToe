//
//  CTTTGame.hpp
//  TickTackToe
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __TickTackToe__CTTTGame__
#define __TickTackToe__CTTTGame__

#include "CGame.hpp"
#include "CLevel.hpp"

enum ETTTGameLocation
{
    kGameLocationLevel = kGameLocationDummy + 1
};

class CTTTGame : public CGame
{
public:
    static CTTTGame * Get();
    
    CTTTGame();
    
    // Go to a game location
    virtual void GoToLocation(int theLocation,
                              std::string filename = std::string());
    
    CLevel * GetLevel();
};

#endif /* defined(__TickTackToe__CTTTGame__) */
