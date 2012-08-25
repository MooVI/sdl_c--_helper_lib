#include "SurfaceCamera.h"



void SurfaceCamera::handleMouseMotion(const SDL_MouseMotionEvent& motion){
   GLint time=mouseTime.getTimeElapsed();
   yaw+= (glm::vec3(0,0,1),-mouseSens*motion.xrel/time);
   pitch+= (glm::vec3(1,0,0),-mouseSens*motion.yrel/time);
            
}

void SurfaceCamera::update(double timeElapsed) {
    Uint8*keys = SDL_GetKeyState(NULL);
    yaw += timeElapsed*(keys[SDLK_UP] - keys[SDLK_DOWN]) * rotSens;
    pitch += timeElapsed * (keys[SDLK_LEFT] - keys[SDLK_RIGHT]) * rotSens;
    if (pitch > PI / 2) pitch = PI / 2;
    else if (pitch<-PI / 2) pitch = -PI / 2;
    GL_Quaternion<float> yawed(glm::vec3(0, 0, 1), yaw);
    glm::vec3 vel = yawed.rotate(glm::vec3(
            (keys[SDLK_d] - keys[SDLK_a])*transSens,
            (keys[SDLK_w]-keys[SDLK_s])*transSens,
            0.0f));
    pos.x += timeElapsed*vel.x;
    pos.y += timeElapsed*vel.y;
    pos.z = getZpos (pos.x,pos.y);
    orientation= 
            yawed
            *GL_Quaternion<float> (glm::vec3(1,0,0),pitch)
            ;
            
    orientation.normalise();
 }

void SurfaceCamera::setUpCamera(glm::vec3 ipos ,std::function<double(double, double)> igetZpos) {
    pos=ipos;
    getZpos= igetZpos;
    pos.z = getZpos (pos.x,pos.y);
}




    
 glm::mat4x4 SurfaceCamera::getCameraMatrix(){
    return orientation.getMatrix()*glm::translate(glm::mat4x4(1.0f),-pos);
     
 }   