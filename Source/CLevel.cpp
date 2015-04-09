//
//  CLevel.cpp
//  TickTackToe
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CLevel.hpp"
#include "CTTTGame.hpp"


CLevel::CLevel()
{
    
}

CLevel::~CLevel()
{
    
}

void CLevel::Enter()
{
    CTTTGame::Get()->RegisterRenderable(this);
    CTTTGame::Get()->RegisterUpdateable(this);
}

void CLevel::Exit()
{
    CTTTGame::Get()->UnregisterRenderable(this);
    CTTTGame::Get()->UnregisterUpdateable(this);
}

void CLevel::Update(CTime elapsedTime)
{
    
}

void CLevel::Draw(CWindow *theWindow)
{
    CCircleShape circle(20.0f);
    circle.setPosition(300.0f, 300.0f);
    circle.setFillColor(CColour::Red);
    theWindow->DrawShape(circle);
}