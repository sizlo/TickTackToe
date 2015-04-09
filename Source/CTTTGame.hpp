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

enum ETTTGameLocation
{
    kGameLocationLevel = kGameLocationDummy + 1
};

class CTTTGame : public CGame
{
public:
    // Go to a game location
    virtual void GoToLocation(int theLocation,
                              std::string filename = std::string());
};

#endif /* defined(__TickTackToe__CTTTGame__) */
