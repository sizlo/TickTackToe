//
//  CTack.cpp
//  TickTackToe
//
//  Created by Tim Brier on 09/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CTack.hpp"
#include "CTTTGame.hpp"
#include "TTTOptions.hpp"

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
            mVelocity += (TTTOptions::gravity * elapsedTime.asSeconds());
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

CVector2f CTack::GetPosition()
{
    return mSprite.getPosition();
}

bool CTack::IsInFoot()
{
    return mState == kInFoot;
}

bool CTack::IsOutOfBounds()
{
    return mSprite.getPosition().y > (GameOptions::viewHeight + 256.0f);
}

CConvexShape CTack::GetHitbox()
{
    CVector2f direction = mVelocity;
    direction.Normalise();
    CVector2f perpDirection;
    perpDirection.x = direction.y;
    perpDirection.y = -direction.x;
    
    CVector2f tip = mSprite.getPosition() + (direction * (244.0f * 0.25f));
    CVector2f left = mSprite.getPosition()
                        - (perpDirection * (14.0f * 0.25f))
                        + (direction * (224.0f * 0.25f));
    CVector2f right = mSprite.getPosition()
                        + (perpDirection * (14.0f * 0.25f))
                        + (direction * (224.0f * 0.25f));
    
    std::list<CVector2f> points;
    points.push_back(tip);
    points.push_back(left);
    points.push_back(right);
    CConvexShape theHitbox = CConvexShape(points);
    
    return theHitbox;
}

void CTack::ReactToCollisionWithToe(CToe *theToe)
{
    mState = kInFoot;
}