/* 
 * File:   FlyingCamera.h
 * Author: qfeuille
 *
 * Created on 04 August 2012, 19:48
 */

#ifndef FLYINGCAMERA_H
#define	FLYINGCAMERA_H
//wasd to translate, arrow keys to look around, q and e to roll
#include "GLQuaternion.h"
#include "Timer.h"
#include "Physics.h"
class FlyingCamera {
    Timer mouseTime;
    //x,y,z are world axes.
    int xpos;
    int ypos;
    int zpos;
    //Rate of change of camera Euler angles
    float rollVel=0;
    float pitchVel=0;
    float yawVel=0;
    //Sensitivity to key presses
    float transSens=0.001;
    float rotSens=0.0005;
    //Velocity of camera in camera axes
    void recalculateVel ();
    //Orientation of camera
    GL_Quaternion<float> orientation;
public:
   
    NoAcceleration<float> q;
    void setUpCamera (float xpos,float ypos, float zpos);
    void update(float timeElapsed);
    glm::mat4x4 getCameraMatrix();
    void handleMouseMotion (const SDL_MouseMotionEvent& motion);
        
};
    

#endif	/* FLYINGCAMERA_H */

