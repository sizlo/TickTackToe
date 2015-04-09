//
//  CLevel.hpp
//  TickTackToe
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __TickTackToe__CLevel__
#define __TickTackToe__CLevel__

#include "CGameLocation.hpp"
#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CTick.hpp"

class CLevel : public CGameLocation, public CUpdateable, public CRenderable
{
public:
    CLevel();
    ~CLevel();
    
    void Enter();
    void Exit();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void AddTack(CTack *theTack);
    
private:
    CTick               mTick;
    std::list<CTack *>  mTacks;
};

#endif /* defined(__TickTackToe__CLevel__) */
