/* 
 * File:   FlyingCamera.h
 * Author: qfeuille
 *
 * Created on 04 August 2012, 19:48
 */

#ifndef SURFACECAMERA_H
#define	SURFACECAMERA_H
//wasd to translate, arrow keys to look around, q and e to roll
#include "GLQuaternion.h"
#include "Timer.h"
#include "Physics.h"
#include <functional>
class SurfaceCamera {
    Timer mouseTime;
    //x,y,z are world axes.
    glm::vec3 pos;
    double pitch=0, yaw=0;
  
    
    //Sensitivity to key presses
    double transSens=0.001;
    double mouseSens=0.05;
    double rotSens=0.0005;
    //Orientation of camera
    GL_Quaternion<float> orientation;
    std::function<double (double x, double y)> getZpos;
public:
    void setUpCamera (glm::vec3 ipos,std::function<double (double x, double y)> igetZpos );
    void update(double timeElapsed);
    glm::mat4x4 getCameraMatrix();
    void handleMouseMotion (const SDL_MouseMotionEvent& motion);
        
};
    

#endif	/* SURFACECAMERA_H */

