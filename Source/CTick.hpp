//
//  CTick.hpp
//  TickTackToe
//
//  Created by Tim Brier on 09/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __TickTackToe__CTick__
#define __TickTackToe__CTick__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CEventListener.hpp"
#include "CTack.hpp"

enum ETickState
{
    kHasTack,
    kWaitingForTack,
    kSteppedOn
};

class CTick : public CUpdateable, public CRenderable, public CEventListener
{
public:
    CTick();
    ~CTick();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void ReactToEvent(CEvent *theEvent);
    
    CVector2f       GetPosition();
    
    CConvexShape    GetHitbox();
    void ReactToCollisionWithToe(CToe *theToe);
    
private:
    CSprite     mSprite;
    CTack       *mTack;
    ETickState  mState;
    CTime       mTackCooldown;
    
    void AquireTack();
    void ThrowTack(CVector2f aimVector);
};

#endif /* defined(__TickTackToe__CTick__) */
