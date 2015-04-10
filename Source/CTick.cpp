//
//  CTick.cpp
//  TickTackToe
//
//  Created by Tim Brier on 09/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CTick.hpp"
#include "SystemUtilities.hpp"

CTick::CTick()
{
    // Listen to events
    SystemUtilities::SubscribeToEvents(this);
    
    mSprite = CSprite("Tick.png");
    mSprite.setOrigin(256.0f, 256.0f);
    mSprite.setScale(0.25f, 0.25f);
    mSprite.setPosition(100.0f, GameOptions::viewHeight - 100.0f);
    
    AquireTack();
}

CTick::~CTick()
{
    SAFE_DELETE(mTack);
}

void CTick::Update(CTime elapsedTime)
{
    CVector2f p;
    
    switch (mState)
    {
        case kHasTack:
            mTack->Update(elapsedTime);
            break;
            
        case kWaitingForTack:
            mTackCooldown -= elapsedTime;
            if (mTackCooldown <= CTime::Zero)
            {
                AquireTack();
            }
            break;
    }
}

void CTick::Draw(CWindow *theWindow)
{
    theWindow->DrawSprite(mSprite);
    if (mState == kHasTack)
    {
        mTack->Draw(theWindow);
    }
}

void CTick::ReactToEvent(CEvent *theEvent)
{
    if (theEvent->IsExtra()
        && theEvent->extraType == CEvent::MouseDrag
        && theEvent->mouseDrag.button == CMouse::Left
        && mState == kHasTack)
    {
        CVector2f start = theEvent->mouseDrag.pressLocation;
        CVector2f finish = theEvent->mouseDrag.releaseLocation;
        CVector2f startToFinish = finish - start;
        ThrowTack(startToFinish);
    }
}

CVector2f CTick::GetPosition()
{
    return mSprite.getPosition();
}

void CTick::AquireTack()
{
    mTack = new CTack();
    mTack->SetPosition(mSprite.getPosition() + CVector2f(94.0f, 0.0f));
    mState = kHasTack;
}

void CTick::ThrowTack(CVector2f aimVector)
{
    mTack->Throw(aimVector);
    mTack = NULL;
    
    mTackCooldown = CTime::Seconds(3.0f);
    
    mState = kWaitingForTack;
}