#include "FlyingCamera.h"



void FlyingCamera::handleMouseMotion(const SDL_MouseMotionEvent& motion){
   GLint time=mouseTime.getTimeElapsed();
   orientation=orientation
            *GL_Quaternion<float> (glm::vec3(1,0,0),-0.005*motion.yrel/time)
            *GL_Quaternion<float> (glm::vec3(0,0,1),-0.005*motion.xrel/time);
    orientation.normalise();
}

void FlyingCamera::update(float timeElapsed){
    orientation.normalise();
    recalculateVel();
    q.update (timeElapsed);
    orientation=
            orientation
            *GL_Quaternion<float> (glm::vec3(0,1,0),timeElapsed*rollVel)
            *GL_Quaternion<float> (glm::vec3(1,0,0),timeElapsed*pitchVel)
            * GL_Quaternion<float> (glm::vec3(0,0,1),timeElapsed*yawVel);
  //  orientation.normalise();
 }

void FlyingCamera::setUpCamera(float ixpos, float iypos, float izpos) {
    if (q.getNumCoordinates() == 0) {
        xpos = q.addCoordinate(ixpos, 0);
        ypos = q.addCoordinate(iypos, 0);
        zpos = q.addCoordinate(izpos, 0);
        orientation=GL_Quaternion<float> (glm::vec3(0,0,1),0);
    }
    else {
        q.setValue(xpos,ixpos);
        q.setValue(ypos,iypos);
        q.setValue(zpos,izpos);
}
}

void FlyingCamera::recalculateVel(){
    Uint8*keys=SDL_GetKeyState(NULL); 
  glm::vec3 vel=orientation.rotate(glm::vec3((keys[SDLK_d]-keys[SDLK_a])*transSens,(keys[SDLK_w]-keys[SDLK_s])*transSens,0.0f));
  pitchVel=(keys[SDLK_UP]-keys[SDLK_DOWN])*rotSens;
  yawVel = (keys[SDLK_LEFT]-keys[SDLK_RIGHT])*rotSens;
  rollVel = (keys[SDLK_q]-keys[SDLK_e])*rotSens;
    q.setVel(xpos,vel.x );
    q.setVel(ypos,vel.y );
    q.setVel(zpos,vel.z);
    
}


    
 glm::mat4x4 FlyingCamera::getCameraMatrix(){
  glm::vec3 translateVec(-q.getValue(xpos),-q.getValue(ypos),-q.getValue(zpos));
 
 
    return orientation.getMatrix()*glm::translate(glm::mat4x4(1.0f),translateVec);
     
 }   