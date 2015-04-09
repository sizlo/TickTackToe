//
//  CLevel.cpp
//  TickTackToe
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CLevel.hpp"
#include "CTTTGame.hpp"


CLevel::CLevel()
{
    
}

CLevel::~CLevel()
{
    while (!mTacks.empty())
    {
        CTack *removed = mTacks.front();
        mTacks.pop_front();
        SAFE_DELETE(removed);
    }
}

void CLevel::Enter()
{
    CTTTGame::Get()->RegisterRenderable(this);
    CTTTGame::Get()->RegisterUpdateable(this);
    
    CTTTGame::Get()->SetGameState(kGameStateInGame);
}

void CLevel::Exit()
{
    CTTTGame::Get()->UnregisterRenderable(this);
    CTTTGame::Get()->UnregisterUpdateable(this);
    
    CTTTGame::Get()->UnsetGameState(kGameStateInGame);
}

void CLevel::Update(CTime elapsedTime)
{
    mTick.Update(elapsedTime);
    
    std::list<CTack *> tacksToRemove;
    for(CTack *tack: mTacks)
    {
        tack->Update(elapsedTime);
        if (tack->IsInFoot() || tack->IsOutOfBounds())
        {
            tacksToRemove.push_back(tack);
        }
        
    }
    for(CTack *tack: tacksToRemove)
    {
        mTacks.remove(tack);
        SAFE_DELETE(tack);
    }
}

void CLevel::Draw(CWindow *theWindow)
{
    mTick.Draw(theWindow);
    for(CTack *tack: mTacks)
    {
        tack->Draw(theWindow);
    }
}

void CLevel::AddTack(CTack *theTack)
{
    mTacks.push_back(theTack);
}