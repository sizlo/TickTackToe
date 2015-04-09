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
    switch (mState)
    {
        case kInTicksHand:
            break;
            
        case kFlying:
            // Adjust velocity for gravity
            mVelocity += (CVector2f(0.0f, 10.0f) * elapsedTime.asSeconds());
            mSprite.move(mVelocity * elapsedTime.asSeconds());
            break;
            
        case kInFoot:
            break;
    }
}

void CTack::Draw(CWindow *theWindow)
{
    theWindow->DrawSprite(mSprite);
}

void CTack::Throw()
{
    mVelocity = CVector2f(50.0f, -50.0f);
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