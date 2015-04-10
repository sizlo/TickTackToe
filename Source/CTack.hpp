//
//  CTack.hpp
//  TickTackToe
//
//  Created by Tim Brier on 09/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __TickTackToe__CTack__
#define __TickTackToe__CTack__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"

class CToe;

enum ETackState
{
    kInTicksHand,
    kFlying,
    kInFoot
};

class CTack : public CUpdateable, public CRenderable
{
public:
    CTack();
    ~CTack();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void Throw(CVector2f aimVector);
    void SetPosition(CVector2f thePosition);
    
    bool IsInFoot();
    bool IsOutOfBounds();
    
    CConvexShape GetHitbox();
    void ReactToCollisionWithToe(CToe *theToe);
    
private:
    CSprite     mSprite;
    ETackState  mState;
    CVector2f   mVelocity;
};

#endif /* defined(__TickTackToe__CTack__) */
