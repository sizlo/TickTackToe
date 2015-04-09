//
//  Main.cpp
//  TickTackToe
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CTTTGame.hpp"

int main(int argc, char **argv)
{
    CTTTGame theGame;
    theGame.Init(kGameLocationLevel);
    int returnCode = theGame.Run();
    theGame.Cleanup();
    
    return returnCode;
}
