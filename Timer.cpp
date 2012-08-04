/* 
 * File:   Timer.cpp
 * Author: qfeuille
 *
 * Created on 01 August 2012, 23:55
 */

#include "Timer.h"



void FTimer::printfps()
{   /* Gather our frames per second */
    frames++;
    time =SDL_GetTicks();
            if (time - startAverageTime >= 5000) {
                GLfloat seconds = (time - startAverageTime) / 1000.0;
                GLfloat fps = frames / seconds;
                printf("%d frames in %g seconds = %g FPS\n", frames, seconds, fps);
                startAverageTime = time;
                frames = 0;
            }
        
       
}

void FTimer::setFrameRate(double fps){
    timeperframe = 1000/fps;
 }

