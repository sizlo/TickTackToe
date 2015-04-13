//
//  CToe.cpp
//  TickTackToe
//
//  Created by Tim Brier on 10/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CToe.hpp"
#include "MathsUtilities.hpp"
#include "CTTTGame.hpp"

CToe::CToe()
:   mSprite("ToeAnim.png")
{
    mSprite.AddFrame(CIntRect(0, 0, 512, 512), CTime::Seconds(1.0f));
    mSprite.AddFrame(CIntRect(512, 0, 512, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(1024, 0, 512, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(512, 0, 512, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(0, 0, 512, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(512, 512, 512, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(1024, 512, 512, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(512, 512, 512, 512), CTime::Seconds(0.07f));
    mSprite.Start();
    
    mSprite.setOrigin(75.0f, 400.0f);
    mSprite.setScale(0.25f, 0.25f);
    
    MoveToRandomStartPoint();
    
    mSpeed = 50.0f;
    
    mDeadCooldown = CTime::Seconds(2.0f);
    
    mState = kNotHit;
    mEmbeddedTack = NULL;
}

CToe::~CToe()
{
    SAFE_DELETE(mEmbeddedTack);
}

void CToe::Update(CTime elapsedTime)
{
    CVector2f tickPos, toeToTick, moveOffset;
    
    switch (mState)
    {
        case kNotHit:
            tickPos = CTTTGame::Get()->GetLevel()->GetTickPosition();
            toeToTick = tickPos - mSprite.getPosition();
            toeToTick.Normalise();
            moveOffset = toeToTick * mSpeed * elapsedTime.asSeconds();
            mSprite.move(moveOffset);
            mSprite.Update(elapsedTime);
            break;
            
        case kHit:
            mEmbeddedTack->Update(elapsedTime);
            mDeadCooldown -= elapsedTime;
            break;
            
        case kKilledTick:
            break;
    }
}

void CToe::Draw(CWindow *theWindow)
{
    theWindow->DrawSprite(mSprite);

    if (mState == kHit)
    {
        mEmbeddedTack->Draw(theWindow);
    }
}

void CToe::MoveToRandomStartPoint()
{
    static auto getRandomYPoint = MathsUtilities::GetRandomGeneratorFunctionForRange(0.0f, GameOptions::viewHeight - 20.0f);
    
    CVector2f start;
    start.x = GameOptions::viewWidth + 20.0f;
    start.y = getRandomYPoint();
    
    mSprite.setPosition(start);
}

bool CToe::IsDead()
{
    return mDeadCooldown <= CTime::Zero;
}

CConvexShape CToe::GetHitbox()
{
    float left = -45.0f * 0.25f;
    float right = 130.0f * 0.25f;
    float top = -50.0f * 0.25f;
    float bottom = 50.0f * 0.25f;
    
    std::list<CVector2f> thePoints;
    thePoints.push_back(CVector2f(left, top));
    thePoints.push_back(CVector2f(right, top));
    thePoints.push_back(CVector2f(right, bottom));
    thePoints.push_back(CVector2f(left, bottom));
    
    CConvexShape theHitbox = CConvexShape(thePoints);
    theHitbox.setPosition(mSprite.getPosition());
    
    return theHitbox;
}

void CToe::ReactToCollisionWithTack(CTack *theTack)
{
    mState = kHit;
    mEmbeddedTack = theTack;
}

void CToe::ReactToCollisionWithTick(CTick *theTick)
{
    mState = kKilledTick;
}