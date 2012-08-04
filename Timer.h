/* 
 * File:   Timer.h
 * Author: qfeuille
 *
 * Created on 01 August 2012, 23:56
 */

#ifndef TIMER_H
#define	TIMER_H

#include <SDL/SDL.h>
#include"GLResources.h"

class FTimer {
    //For counting individual frame per second
    GLint startTime = 0;
    //For counting average frame rate
    GLint startAverageTime = 0;
    GLint startCapTime=0;
    //For counting average frame rate
    GLint time;
    //To count frames
    GLint frames = 0;
    //Measured in milliseconds per frame
    GLint timeperframe;
    //Measured in milliseconds
    GLint timeElapsed;
    //Measured in milliseconds
    GLint simTimeLeft=0;
public:  
    void printfps ();
    //I'd advise not using this, actually.
    bool capFrameRate ();
    void resetStart ();
    GLuint getTimeElapsed ();
    GLuint getTimeLeft (){return simTimeLeft;};
    bool isTimeAvailable (GLint timestep); 
    double getLinearBlendFactor (GLint timestep);
    void setFrameRate (double fps);
    void wait () {SDL_Delay(1);}
}; 





inline GLuint FTimer::getTimeElapsed (){
    timeElapsed = SDL_GetTicks() - startTime;
    simTimeLeft += timeElapsed;
    return timeElapsed;
}

inline void FTimer::resetStart(){
    startTime=SDL_GetTicks();
}

inline bool FTimer::capFrameRate (){
    //Add render time
    time = SDL_GetTicks();
    timeElapsed=time-startCapTime;
    startCapTime=time;
    //If time elapsed is less than time per frame, wait
   if (timeElapsed < timeperframe) {
       SDL_Delay (timeperframe-timeElapsed);
       return true;
   }
   else return false;   
}

inline bool FTimer::isTimeAvailable (GLint timestep) {
    GLint timeAfterStep = simTimeLeft - timestep;
    if (timeAfterStep > 0) {
        simTimeLeft = timeAfterStep;
        return true;
    } else return false;  
}

inline double FTimer::getLinearBlendFactor(GLint timestep){
    return (double) simTimeLeft/ (double) timestep;
}

class Timer {
    GLint startTime=0;
    GLint timeElapsed;
public:
   GLint getTimeElapsed(){
        GLint time=SDL_GetTicks();
        timeElapsed=time-startTime;
        startTime=time;
        return timeElapsed;
    }
};

#endif	/* TIMER_H */

