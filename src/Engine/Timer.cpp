//
//  Timer.cpp
//  sdl_brawler_mac
//
//  Created by Максим on 4/9/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Timer.hpp"

Timer::Timer() : timePrev(std::chrono::high_resolution_clock::now())
{
    
}

double Timer::GetDelta()
{
    auto timeCurrent = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> delta(timeCurrent - timePrev);
    timePrev = std::chrono::high_resolution_clock::now();
    
    return delta.count();
}
