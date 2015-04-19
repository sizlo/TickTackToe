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
#include "CToe.hpp"

class CLevel :  public CGameLocation,
                public CUpdateable,
                public CRenderable,
                public CMessageListener<CEvent>
{
public:
    CLevel();
    ~CLevel();
    
    void Enter();
    void Exit();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    bool HandleMessage(CEvent theEvent);
    
    void AddTack(CTack *theTack);
    
    CVector2f GetTickPosition();
    
private:
    CTick               mTick;
    std::list<CTack *>  mTacks;
    std::list<CToe *>   mToes;
    
    CTime               mToeSpawnCooldown;
    
    void StartLevel();
    void DeleteEntities();
    void SpawnToe();
    void HandleCollisions();
    void DrawHitbox(CConvexShape theHitbox, CWindow *theWindow);
};

#endif /* defined(__TickTackToe__CLevel__) */
