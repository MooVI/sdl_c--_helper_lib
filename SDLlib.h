/* 
 * File:   SDLlib.h
 * Author: qfeuille
 *
 * Created on 23 May 2012, 01:44
 */

#ifndef SDLLIB_H
#define	SDLLIB_H


/*
 * This code was created by Jeff Molofee '99 
 * (ported to Linux/SDL by Ti Leggett '01)
 *
 * If you've found this code useful, please let me know.
 *
 * Visit Jeff at http://nehe.gamedev.net/
 * 
 * or for port-specific comments, questions, bugreports etc. 
 * email to leggett@eecs.tulane.edu
 */
 
#include "Timer.h"
#include "GLQuaternion.h"
#include "FlyingCamera.h"
#include "GLResources.h"
#include "Physics.h"

//SDL Base Class intended to be inherited from
class SDLBase {
    
   /* Flags to pass to SDL_SetVideoMode */
    int videoFlags;
    /* main loop variable */
    int done;
    /* used to collect events */
    SDL_Event event;
    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;
    /* whether or not the window is active */
    int isActive;
protected:    
    SDL_Surface *surface;
    int screenWidth; int screenHeight; float screenRatio;
public:
    
    /* OpenGL Resources; shaders, buffers etc.*/
GLResources resources;
//Timer
FTimer fclock;
int initGL( float backr,float backg, float backb);
void init_SDL(const int screenWidth, const int screenHeight, const int screenBPP,
float backgroundr=1.0, float backgroundg=1.0, float backgroundb=1.0, 
const std::string name="", double fps=100);
virtual int makeResources () {};
void centreMouse ();

void message_Loop() ;
 /* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode );
int resizeWindow( int width, int height );

//Functions to be overridden to provide custom behaviour
virtual void  handleLeftMouseButtonUp(const Uint16 x,const Uint16 y){};
virtual void  handleRightMouseButtonUp(const Uint16 x,const Uint16 y){};
virtual void  handleMiddleMouseButtonUp(const Uint16 x,const Uint16 y){};
virtual void  handleLeftMouseButtonDown(const Uint16 x,const Uint16 y){};
virtual void  handleRightMouseButtonDown(const Uint16 x,const Uint16 y){};
virtual void  handleMiddleMouseButtonDown(const Uint16 x,const Uint16 y){};
virtual void  handleMouseMotion (const SDL_MouseMotionEvent& motion){};
virtual void  handleKeyUp(const SDL_keysym & keysym ){};

virtual void handleKeyDown(const SDL_keysym & keysym );
virtual int drawGLScene( );

};


#endif	/* SDLLIB_H */

