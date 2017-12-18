#include <gl_core_4_5.hpp>
#include <SDL.h>
#undef main

#include <stdio.h>
#include <string>

static const int c_windowWidth = 1024;
static const int c_windowHeight = 768;

void draw()
{
  static int colour = 0;

  if(colour++ % 2)
  {
	  gl::ClearColor(1, 0, 0, 1);
  }
  else
  {
	  gl::ClearColor(0, 1, 0, 0);
  }
}

void update()
{
  SDL_Delay(250);
}

int main()
{
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  // Why not be bleeding edge :)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

  /* Turn on double buffering with a 24bit Z buffer.
  * You may need to change this to 16 or 32 for your system */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  SDL_Window* window = NULL;
  window = SDL_CreateWindow("OpenGL Window",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            c_windowWidth, c_windowHeight,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if(!window)
  {
    printf("Unable to create window : %s\n", SDL_GetError());
    return 1;
  }

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (!context)
  {
	  printf("Unable to create context : %s\n", SDL_GetError());
	  return 1;
  }

  gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
  if (!didLoad)
  {
	  // @ToDo proper error handling
	  printf("glLoadGen failed!");
	  return 1;
  }

  SDL_GL_SetSwapInterval(1);

  gl::ClearColor(0, 0, 0, 1);

  bool bQuit = false;

  while(!bQuit)
  {
    { /* Start event block */
      SDL_Event event;

      while(SDL_PollEvent(&event))
      {
        if(event.type == SDL_QUIT)
        {
          bQuit = true;
        }

        if(event.type == SDL_KEYDOWN)
        {
          switch(event.key.keysym.sym)
          {
            case SDLK_ESCAPE:
              bQuit = true;
              break;

            default:
              break;
          }
        }
      } /* End event loop */
    } /* End event block */

    update();

    gl::Clear(gl::COLOR_BUFFER_BIT);

    draw();

    SDL_GL_SwapWindow(window);
  } /* End render loop */

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

