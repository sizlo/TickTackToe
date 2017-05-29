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

class CTTTGame : public CGame
{
public:
    static CTTTGame * Get();
    
    CTTTGame();
    
    CLevel * GetLevel();
};

#endif /* defined(__TickTackToe__CTTTGame__) */
