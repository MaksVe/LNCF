//
//  Timer.hpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>

/*This class was originally from headerphile
 (http://headerphile.com/sdl2/sdl2-part-9-no-more-delays/)*/

class Timer
{
public:
    Timer();
    
    double GetDelta();
    
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> timePrev;
};

#endif /* Timer_hpp */
