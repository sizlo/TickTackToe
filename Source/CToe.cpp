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
    mSprite.AddFrame(CIntRect(10, 0, 502, 512), CTime::Seconds(1.0f));
    mSprite.AddFrame(CIntRect(522, 0, 502, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(1034, 0, 502, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(522, 0, 502, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(10, 0, 502, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(522, 512, 502, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(1034, 512, 502, 512), CTime::Seconds(0.07f));
    mSprite.AddFrame(CIntRect(522, 512, 502, 512), CTime::Seconds(0.07f));
    mSprite.Start();
    
    mSprite.setOrigin(75.0f, 400.0f);
    mSprite.setScale(0.25f, 0.25f);
    
    SetupHitboxes();
    
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
    static auto getRandomYPoint = MathsUtilities::GetRandomGeneratorFunctionForRange(0.0f, GameOptions::viewHeight - 128.0f);
    
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
    CConvexShape currentBox = mHitboxes[mSprite.GetCurrentFrameIndex()];
    currentBox.setPosition(mSprite.getPosition());
    currentBox.move(-mSprite.getOrigin() * 0.25f);
    return currentBox;
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

void CToe::SetupHitboxes()
{
    CConvexShape midBox = CConvexShape(5);
    midBox.setPoint(0, CVector2f(30.0f, 350.0f));
    midBox.setPoint(1, CVector2f(200.0f, 370.0f));
    midBox.setPoint(2, CVector2f(200.0f, 450.0f));
    midBox.setPoint(3, CVector2f(50.0f, 460.0f));
    midBox.setPoint(4, CVector2f(20.0f, 400.0f));
    
    CConvexShape up1Box = CConvexShape(5);
    up1Box.setPoint(0, CVector2f(40.0f, 330.0f));
    up1Box.setPoint(1, CVector2f(200.0f, 370.0f));
    up1Box.setPoint(2, CVector2f(200.0f, 445.0f));
    up1Box.setPoint(3, CVector2f(40.0f, 440.0f));
    up1Box.setPoint(4, CVector2f(20.0f, 380.0f));
    
    CConvexShape up2Box = CConvexShape(5);
    up2Box.setPoint(0, CVector2f(60.0f, 300.0f));
    up2Box.setPoint(1, CVector2f(215.0f, 375.0f));
    up2Box.setPoint(2, CVector2f(215.0f, 445.0f));
    up2Box.setPoint(3, CVector2f(40.0f, 400.0f));
    up2Box.setPoint(4, CVector2f(30.0f, 350.0f));
    
    CConvexShape down1Box = CConvexShape(5);
    down1Box.setPoint(0, CVector2f(25.0f, 380.0f));
    down1Box.setPoint(1, CVector2f(200.0f, 370.0f));
    down1Box.setPoint(2, CVector2f(200.0f, 440.0f));
    down1Box.setPoint(3, CVector2f(50.0f, 480.0f));
    down1Box.setPoint(4, CVector2f(20.0f, 425.0f));
    
    CConvexShape down2Box = CConvexShape(5);
    down2Box.setPoint(0, CVector2f(25.0f, 400.0f));
    down2Box.setPoint(1, CVector2f(200.0f, 370.0f));
    down2Box.setPoint(2, CVector2f(200.0f, 445.0f));
    down2Box.setPoint(3, CVector2f(65.0f, 495.0f));
    down2Box.setPoint(4, CVector2f(25.0f, 450.0f));
    
    midBox.setScale(0.25f, 0.25f);
    up1Box.setScale(0.25f, 0.25f);
    up2Box.setScale(0.25f, 0.25f);
    down1Box.setScale(0.25f, 0.25f);
    down2Box.setScale(0.25f, 0.25f);
    
    mHitboxes[kMiddle] = midBox;
    mHitboxes[kHigherUpwards] = up1Box;
    mHitboxes[kHighest] = up2Box;
    mHitboxes[kHigherDownwards] = up1Box;
    mHitboxes[kMiddleAgain] = midBox;
    mHitboxes[kLowerDownwards] = down1Box;
    mHitboxes[kLowest] = down2Box;
    mHitboxes[kLowerUpwards] = down1Box;
}