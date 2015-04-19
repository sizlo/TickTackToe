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
#include "TTTOptions.hpp"

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
    mSprite.setRotation(0.0f);
    SAFE_DELETE(mTack);
    AquireTack();
}

void CTick::Update(CTime elapsedTime)
{
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
    
    if (CMouse::isButtonPressed(CMouse::Left) && mState == kHasTack)
    {
        mThrowPathPoints.clear();
        CVector2f pathPosition = mTack->GetPosition();
        CVector2f velocity = SystemUtilities::GetMousePosition() - mMouseDragStartPosition;
        CTime dummyUpdateTime = CTime::Seconds(0.016f); // 60 fps
       
        CVector2f lastPosition = pathPosition;
        while (pathPosition.y < (GameOptions::viewHeight + 256.0f))
        {
            velocity += TTTOptions::gravity * dummyUpdateTime.asSeconds();
            pathPosition += velocity * dummyUpdateTime.asSeconds();
            CVector2f distance = pathPosition - lastPosition;
            if (distance.GetMagnitude() > 50.0f)
            {
                CVector2f direction = velocity;
                direction.Normalise();
                mThrowPathPoints.push_back(pathPosition + direction * (244.0f * 0.25f));
                lastPosition = pathPosition;
            }
            
        }
    }
}

void CTick::Draw(CWindow *theWindow)
{
    theWindow->DrawSprite(mSprite);
    if (mState == kHasTack)
    {
        mTack->Draw(theWindow);
    }
    
    if (CMouse::isButtonPressed(CMouse::Left) && mState == kHasTack)
    {
        for (CVector2f p: mThrowPathPoints)
        {
            CCircleShape c = CCircleShape(2.5f);
            c.setPosition(p);
            c.setFillColor(CColour::White);
            theWindow->DrawShape(c);
        }
    }
}

bool CTick::HandleMessage(CEvent theEvent)
{
    switch (theEvent.type)
    {
        case CEvent::MouseButtonPressed:
            if (theEvent.mouseButton.button == CMouse::Left)
            {
                CVector2i windowPosition = CVector2i(theEvent.mouseButton.x, theEvent.mouseButton.y);
                mMouseDragStartPosition = SystemUtilities::GetViewPosition(windowPosition);
            }
            break;
            
        case CEvent::MouseButtonReleased:
            if (theEvent.mouseButton.button == CMouse::Left)
            {
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