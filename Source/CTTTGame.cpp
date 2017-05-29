//
//  CTTTGame.cpp
//  TickTackToe
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CTTTGame.hpp"
#include "CLevel.hpp"

CTTTGame * CTTTGame::Get()
{
    return static_cast<CTTTGame *>(CGame::Get());
}

CTTTGame::CTTTGame()
:   CGame("Tick Tack Toe")
{
    mClearColour = CColour::White;
}

CLevel * CTTTGame::GetLevel()
{
    CLevel *result = NULL;
    
    if (HasAllGameStates(kGameStateInGame))
    {
        result = static_cast<CLevel *>(mGameLocations.top());
    }
    
    return result;
}
