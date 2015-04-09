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

void CTTTGame::GoToLocation(int theLocation,
                            std::string filename /* = std::string() */)
{
    // If we're already in a location leave it
    if (mCurrentLocation != NULL)
    {
        mCurrentLocation->Exit();
        SAFE_DELETE(mCurrentLocation);
    }
    
    switch (theLocation)
    {
        case kGameLocationLevel:
            DEBUG_LOG("Level requested");
            mCurrentLocation = new CLevel();
            break;
            
        default:
            DEBUG_LOG("Unimplemented game location - going to dummy location");
            mCurrentLocation = new CDummyGameLocation();
            break;
    }
    
    mCurrentLocation->Enter();
}

CLevel * CTTTGame::GetLevel()
{
    CLevel *result = NULL;
    
    if (HasAllGameStates(kGameStateInGame))
    {
        result = static_cast<CLevel *>(mCurrentLocation);
    }
    
    return result;
}