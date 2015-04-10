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
    
    while (!mToes.empty())
    {
        CToe *removed = mToes.front();
        mToes.pop_front();
        SAFE_DELETE(removed);
    }
}

void CLevel::Enter()
{
    CTTTGame::Get()->RegisterRenderable(this);
    CTTTGame::Get()->RegisterUpdateable(this);
    
    CTTTGame::Get()->SetGameState(kGameStateInGame);
    
    SpawnToe();
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
        if (tack->IsDead())
        {
            tacksToRemove.push_back(tack);
        }
        
    }
    for(CTack *tack: tacksToRemove)
    {
        mTacks.remove(tack);
        SAFE_DELETE(tack);
    }
    
    mToeSpawnCooldown -= elapsedTime;
    if (mToeSpawnCooldown <= CTime::Zero)
    {
        SpawnToe();
    }
    std::list<CToe *> toesToRemove;
    for (CToe *toe: mToes)
    {
        toe->Update(elapsedTime);
        if (toe->IsDead())
        {
            toesToRemove.push_back(toe);
        }
    }
    for (CToe *toe: toesToRemove)
    {
        mToes.remove(toe);
        SAFE_DELETE(toe);
    }
}

void CLevel::Draw(CWindow *theWindow)
{
    mTick.Draw(theWindow);
    for(CTack *tack: mTacks)
    {
        tack->Draw(theWindow);
    }
    for (CToe *toe: mToes)
    {
        toe->Draw(theWindow);
    }
}

void CLevel::AddTack(CTack *theTack)
{
    mTacks.push_back(theTack);
}

CVector2f CLevel::GetTickPosition()
{
    return mTick.GetPosition();
}

void CLevel::SpawnToe()
{
    mToes.push_back(new CToe());
    mToeSpawnCooldown = CTime::Seconds(5.0f);
}