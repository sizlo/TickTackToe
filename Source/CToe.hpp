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

class CToe : public CUpdateable, public CRenderable
{
public:
    CToe();
    ~CToe();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void MoveToRandomStartPoint();
    
    bool IsDead();
    
private:
    CSprite mSprite;
    float   mSpeed;
};

#endif /* defined(__TickTackToe__CToe__) */
