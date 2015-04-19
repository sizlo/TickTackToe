//
//  CTick.cpp
//  TickTackToe
//
//  Created by Tim Brier on 09/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CTick.hpp"
#include "CMessageBroadcaster.hpp"
#include "SystemUtilities.hpp"

CTick::CTick()
: mTack(NULL)
{
    // Listen to events
    CMessageBroadcaster<CEvent>::Subscribe(this);
    
    mSprite = CSprite("Tick.png");
    mSprite.setOrigin(256.0f, 256.0f);
    mSprite.setScale(0.25f, 0.25f);
    mSprite.setPosition(100.0f, GameOptions::viewHeight - 100.0f);
}

CTick::~CTick()
{
    CMessageBroadcaster<CEvent>::Unsubscribe(this);
    SAFE_DELETE(mTack);
}

void CTick::Init()
{
    mInputState = kMouseUp;
    mSprite.setRotation(0.0f);
    SAFE_DELETE(mTack);
    AquireTack();
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
            
        case kSteppedOn:
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

bool CTick::HandleMessage(CEvent theEvent)
{
    switch (theEvent.type)
    {
        case CEvent::MouseButtonPressed:
            if (theEvent.mouseButton.button == CMouse::Left)
            {
                mInputState = kMouseDown;
                CVector2i windowPosition = CVector2i(theEvent.mouseButton.x, theEvent.mouseButton.y);
                mMouseDragStartPosition = SystemUtilities::GetViewPosition(windowPosition);
            }
            break;
            
        case CEvent::MouseButtonReleased:
            if (theEvent.mouseButton.button == CMouse::Left)
            {
                mInputState = kMouseUp;
                CVector2i windowPosition = CVector2i(theEvent.mouseButton.x, theEvent.mouseButton.y);
                CVector2f viewPosition = SystemUtilities::GetViewPosition(windowPosition);
                
                CVector2f aimVector = viewPosition - mMouseDragStartPosition;
                ThrowTack(aimVector);
            }
            break;
            
        default:
            // Do nothing
            break;
    }
    
    return false;
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
    if (mState == kHasTack)
    {
        mTack->Throw(aimVector);
        mTack = NULL;
        
        mTackCooldown = CTime::Seconds(3.0f);
        
        mState = kWaitingForTack;
    }
}

CConvexShape CTick::GetHitbox()
{
    CConvexShape theHitbox = CCircleShape(222.0f * 0.25f);
    theHitbox.setPosition(mSprite.getPosition());
    
    return theHitbox;
}

void CTick::ReactToCollisionWithToe(CToe *theToe)
{
    mState = kSteppedOn;
    mSprite.setRotation(180.0f);
}