//
//  CLevel.cpp
//  TickTackToe
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CLevel.hpp"
#include "CTTTGame.hpp"
#include "DebugOptions.hpp"
#include "CMessageBroadcaster.hpp"


CLevel::CLevel()
{
    
}

CLevel::~CLevel()
{
    DeleteEntities();
}

void CLevel::Enter()
{
    CTTTGame::Get()->RegisterRenderable(this);
    CTTTGame::Get()->RegisterUpdateable(this);
    
    CTTTGame::Get()->SetGameState(kGameStateInGame);
    
    CMessageBroadcaster<CEvent>::Subscribe(this);
    
    StartLevel();
}

void CLevel::Exit()
{
    CTTTGame::Get()->UnregisterRenderable(this);
    CTTTGame::Get()->UnregisterUpdateable(this);
    
    CTTTGame::Get()->UnsetGameState(kGameStateInGame);
    
    CMessageBroadcaster<CEvent>::Unsubscribe(this);
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
        if (!tack->IsInFoot())
        {
            SAFE_DELETE(tack);
        }
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
    
    HandleCollisions();
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
    
#if TGL_DEBUG // Draw hitboxes
    if (DebugOptions::showMouseCoords)
    {
        DrawHitbox(mTick.GetHitbox(), theWindow);
        for (CTack *tack: mTacks)
        {
            DrawHitbox(tack->GetHitbox(), theWindow);
        }
        for (CToe *toe: mToes)
        {
            DrawHitbox(toe->GetHitbox(), theWindow);
        }
    }
#endif
}

bool CLevel::HandleMessage(CEvent theEvent)
{
    if (theEvent.type == CEvent::KeyPressed)
    {
        if (theEvent.key.code == CKeyboard::R)
        {
            StartLevel();
        }
    }
    
    return false;
}

void CLevel::AddTack(CTack *theTack)
{
    mTacks.push_back(theTack);
}

CVector2f CLevel::GetTickPosition()
{
    return mTick.GetPosition();
}

void CLevel::StartLevel()
{
    mTick.Init();
    DeleteEntities();
    SpawnToe();
}

void CLevel::DeleteEntities()
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

void CLevel::SpawnToe()
{
    mToes.push_back(new CToe());
    mToeSpawnCooldown = CTime::Seconds(5.0f);
}

void CLevel::HandleCollisions()
{
    // Toe with tick
    for (CToe *toe: mToes)
    {
        CConvexShape tickHitbox = mTick.GetHitbox();
        if (toe->GetHitbox().IsCollidingWith(tickHitbox))
        {
            toe->ReactToCollisionWithTick(&mTick);
            mTick.ReactToCollisionWithToe(toe);
        }
    }
    
    // Tack with toe
    for (CTack *tack: mTacks)
    {
        for (CToe *toe: mToes)
        {
            CConvexShape toeHitbox = toe->GetHitbox();
            if (tack->GetHitbox().IsCollidingWith(toeHitbox))
            {
                tack->ReactToCollisionWithToe(toe);
                toe->ReactToCollisionWithTack(tack);
            }
        }
    }
}

void CLevel::DrawHitbox(CConvexShape theHitbox, CWindow *theWindow)
{
    theHitbox.setFillColor(CColour(0, 255, 0, 64));
    theWindow->DrawShape(theHitbox);
}