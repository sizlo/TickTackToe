//
//  CToe.hpp
//  TickTackToe
//
//  Created by Tim Brier on 10/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __TickTackToe__CToe__
#define __TickTackToe__CToe__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CAnimatedSprite.hpp"
#include <random>

class CTack;
class CTick;

enum EToeState
{
    kNotHit,
    kHit,
    kKilledTick
};

class CToe : public CUpdateable, public CRenderable
{
public:
    CToe();
    ~CToe();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void MoveToRandomStartPoint();
    
    bool IsDead();
    
    CConvexShape GetHitbox();
    void ReactToCollisionWithTack(CTack *theTack);
    void ReactToCollisionWithTick(CTick *theTick);
    
private:
    CAnimatedSprite     mSprite;
    float               mSpeed;
    EToeState           mState;
    CTack               *mEmbeddedTack;
    CTime               mDeadCooldown;
};

#endif /* defined(__TickTackToe__CToe__) */
