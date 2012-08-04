/*
 * File:   SDLlib.cpp
 * Author: qfeuille
 *
 * Created on 23 May 2012, 01:49
 */

#include "SDLlib.h"







void SDLBase::Quit( int returnCode )
{
    /* clean up the window */
    SDL_Quit( );

    /* and exit appropriately */
    exit( returnCode );
}


/* function to handle key press events */
void SDLBase::handleKeyDown( const SDL_keysym & keysym )
{
    switch ( keysym.sym )
	{
	case SDLK_ESCAPE:
	    /* ESC key was pressed */
	    Quit( 0 );
	    break;
	case SDLK_F1:
	    /* F1 key was pressed
	     * this toggles fullscreen mode
	     */
	    SDL_WM_ToggleFullScreen( surface );
	    break;
	default:
	    break;
	}

    return;
}
/* general OpenGL initialization function */

int SDLBase::initGL( float backr,float backg, float backb)
{    
    GLenum glew_status = glewInit();

  if (glew_status != GLEW_OK) {

    std::cerr<<"Error:"<< glewGetErrorString(glew_status);

    return 1;

  }

  if (!GLEW_VERSION_2_0) {

    std::cerr<< "Error: your graphic card does not support OpenGL 2.0\n";

    return 1;

  }
    makeResources ();
    /* Enable smooth shading */
  //  glShadeModel( GL_SMOOTH );
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /* Set the background colour */
    glClearColor(backr, backg, backb, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT);
    /* Depth buffer setup */
    glClearDepth( 1.0f );
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    return( true );
}

/* function to reset our viewport after a window resize */
int SDLBase::resizeWindow( int width, int height )
{
    
/* Protect against a divide by zero */
    if ( height == 0 )
	height = 1;    
    /* Height / width ration */
    screenWidth=width; screenHeight=height;

    

    screenRatio = ( float )screenWidth / ( float )screenHeight;
    glViewport(0, 0, screenWidth, screenHeight);
   drawGLScene( );

    return( true );
}



void SDLBase::init_SDL(const int screenWidth, const int screenHeight, const int screenBPP,
float backgroundr, float backgroundg, float backgroundb,
        const std::string name, double fps){
    done =false;
    isActive=true;

    /* initialize SDL */
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	   std::cerr<< "Video initialization failed: \n"
		    << SDL_GetError( );
	    Quit( 1 );
	}

    /* Fetch the video info */
    videoInfo = SDL_GetVideoInfo( );

    if ( !videoInfo )
	{
	    std::cerr<< "Video query failed:" <<SDL_GetError( ) ;
	    Quit( 1 );
	}

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
    surface = SDL_SetVideoMode( screenWidth, screenHeight, screenBPP,
				videoFlags );

    /* Verify there is a surface */
    if ( !surface )
	{
	    std::cerr<< "Video mode set failed: %s\n"<< SDL_GetError( );
	    Quit( 1 );
	}
    SDL_WM_SetCaption (name.c_str(),name.c_str());
    fclock.setFrameRate (fps);
    /* initialize OpenGL */
    initGL(backgroundr,backgroundg,backgroundb);
    
    /* resize the initial window */
    resizeWindow( screenWidth, screenHeight );
}

void SDLBase::message_Loop() {
    
    /* wait for events */
    while (!done) {
        //fclock.resetStart();
        /* handle the events in the queue */

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_ACTIVEEVENT:
                    /* Something's happened with our focus
                     * If we lost focus or we are iconified, we
                     * shouldn't draw the screen
                     */
                    if (event.active.gain == 0)
                        isActive = false;
                    else
                        isActive = true;
                    break;
                case SDL_VIDEORESIZE:
                    /* handle resize event */
                    surface = SDL_SetVideoMode(event.resize.w,
                            event.resize.h,
                            16, videoFlags);
                    if (!surface) {
                        std::cerr<< "Could not get a surface after resize: %s\n"<< SDL_GetError();
                        Quit(1);
                    }
                    resizeWindow(event.resize.w, event.resize.h);
                    break;
                case SDL_KEYDOWN:
                    /* handle key presses */
                    handleKeyDown(event.key.keysym);
                    break;
                case SDL_KEYUP:
                    /* handle key presses */
                    handleKeyUp(event.key.keysym);
                    break;
                case SDL_MOUSEBUTTONUP:
                    // handle mouse up
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            handleLeftMouseButtonUp(event.button.x, event.button.y);
                            break;
                        case SDL_BUTTON_RIGHT:
                            handleRightMouseButtonUp(event.button.x, event.button.y);
                            break;
                        case SDL_BUTTON_MIDDLE:
                            handleMiddleMouseButtonUp(event.button.x, event.button.y);
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // handle mouse up
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            handleLeftMouseButtonDown(event.button.x, event.button.y);
                            break;
                        case SDL_BUTTON_RIGHT:
                            handleRightMouseButtonDown(event.button.x, event.button.y);
                            break;
                        case SDL_BUTTON_MIDDLE:
                            handleMiddleMouseButtonDown(event.button.x, event.button.y);
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    handleMouseMotion (event.motion);
                    break;
                case SDL_QUIT:
                    /* handle quit requests */
                    done = true;
                    break;
                default:
                    break;
            }
        }

	    /* draw the scene */
	    if ( isActive )
		drawGLScene( );
                fclock.wait();
	}

    /* clean ourselves up and exit */
    Quit( 0 );

}

void SDLBase::centreMouse(){    
     SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
SDL_WarpMouse(screenWidth>>1, screenHeight>>1);
SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
}

int SDLBase::drawGLScene(){return 0;};
