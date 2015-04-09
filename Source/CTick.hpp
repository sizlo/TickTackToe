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
    kWaitingForTack
};

class CTick : public CUpdateable, public CRenderable, public CEventListener
{
public:
    CTick();
    ~CTick();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void ReactToEvent(CEvent *theEvent);
    
private:
    CSprite     mSprite;
    CTack       *mTack;
    ETickState  mState;
    CTime       mTackCooldown;
    
    void AquireTack();
    void ThrowTack();
};

#endif /* defined(__TickTackToe__CTick__) */
