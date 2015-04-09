//
//  CTack.cpp
//  TickTackToe
//
//  Created by Tim Brier on 09/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CTack.hpp"
#include "CTTTGame.hpp"

CTack::CTack()
{
    mSprite = CSprite("Tack.png");
    mSprite.setOrigin(256.0f, 128.0f);
    mSprite.setScale(0.25f, 0.25f);
    
    mVelocity = CVector2f(0.0f, 0.0f);
    
    mState = kInTicksHand;
}

CTack::~CTack()
{
    
}

void CTack::Update(CTime elapsedTime)
{
    CVector2f originalDirection = CVector2f(1.0f, 0.0f);
    
    switch (mState)
    {
        case kInTicksHand:
            break;
            
        case kFlying:
            // Adjust velocity for gravity and move
            mVelocity += (CVector2f(0.0f, 250.0f) * elapsedTime.asSeconds());
            mSprite.move(mVelocity * elapsedTime.asSeconds());
            
            // Adjust sprite rotation based on velocity
            mSprite.setRotation(originalDirection.AngleTo(mVelocity));
            break;
            
        case kInFoot:
            break;
    }
}

void CTack::Draw(CWindow *theWindow)
{
    theWindow->DrawSprite(mSprite);
}

void CTack::Throw(CVector2f aimVector)
{
    mVelocity = aimVector;
    mState = kFlying;
    CTTTGame::Get()->GetLevel()->AddTack(this);
}

void CTack::SetPosition(CVector2f thePosition)
{
    mSprite.setPosition(thePosition);
}

bool CTack::IsInFoot()
{
    return mState == kInFoot;
}

bool CTack::IsOutOfBounds()
{
    return mSprite.getPosition().y > (GameOptions::viewHeight + 256.0f);
}