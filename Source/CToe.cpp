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
{
    mSprite = CSprite("Toe.png");
    mSprite.setOrigin(75.0f, 400.0f);
    mSprite.setScale(0.25f, 0.25f);
    
    MoveToRandomStartPoint();
    
    mSpeed = 50.0f;
}

CToe::~CToe()
{
    
}

void CToe::Update(CTime elapsedTime)
{
    CVector2f tickPos = CTTTGame::Get()->GetLevel()->GetTickPosition();
    CVector2f toeToTick = tickPos - mSprite.getPosition();
    toeToTick.Normalise();
    CVector2f moveOffset = toeToTick * mSpeed * elapsedTime.asSeconds();
    mSprite.move(moveOffset);
}

void CToe::Draw(CWindow *theWindow)
{
    theWindow->DrawSprite(mSprite);
}

void CToe::MoveToRandomStartPoint()
{
    CVector2f start;
    start.x = GameOptions::viewWidth + 200.0f;
    start.y = MathsUtilities::RandomInRange(-100.0f,
                                            GameOptions::viewHeight - 128.0f);
    
    mSprite.setPosition(start);
}

bool CToe::IsDead()
{
    return false;
}