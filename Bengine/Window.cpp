#include "Bengine/Window.h"
#include "Bengine/BengineErrors.h"

namespace Bengine {

    Window::Window()
    {
    }

    Window::~Window()
    {
    }

    int Window::create(std::string windowName, float screenWidth, float screenHeight, unsigned int currentFlags)
    {
        m_flag = SDL_WINDOW_OPENGL;
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;

        if (currentFlags & INVISIBLE) {
            m_flag |= SDL_WINDOW_HIDDEN;
        }
        if (currentFlags & FULLSCREEN) {
            m_flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        if (currentFlags & BORDERLESS) {
            m_flag |= SDL_WINDOW_BORDERLESS;
        }
        if (currentFlags & RESIZEABLE) {
            m_flag |= SDL_WINDOW_RESIZABLE;
        }
      

        //Open an SDL window
        m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, m_flag);
        if (m_sdlWindow == nullptr) {
            fatalError("SDL Window could not be created!");
        }

        //Set up our OpenGL context
        m_glContext = SDL_GL_CreateContext(m_sdlWindow);
        if (m_glContext == nullptr) {
            fatalError("SDL_GL context could not be created!");
        }

        //Set up glew (optional but recommended)
        GLenum error = glewInit();
        if (error != GLEW_OK) {
            fatalError("Could not initialize glew!");
        }

        //Check the OpenGL version
        std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

        //Set the background color to blue
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        //Set VSYNC
        SDL_GL_SetSwapInterval(1);

        // Enable alpha blend
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     
      /*         SDL_MaximizeWindow(m_sdlWindow);
           SDL_GetWindowSize(m_sdlWindow, &m_screenWidth, &m_screenHeight);
           m_glContext = SDL_GL_CreateContext(m_sdlWindow);
           SDL_GL_MakeCurrent(m_sdlWindow, m_glContext);*/
        return 0;
    }



    void Window::swapBuffer() {
        SDL_GL_SwapWindow(m_sdlWindow);
    }
    void Window::onSDLEvent(SDL_Event& evnt)
    {
        if (evnt.type == SDL_WINDOWEVENT)
        {
            switch (evnt.window.event) {
           /* case SDL_WINDOWEVENT_SHOWN:
                SDL_Log("Window %d shown", evnt.window.windowID);
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                SDL_Log("Window %d hidden", evnt.window.windowID);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_Log("Window %d exposed", evnt.window.windowID);
                break;
            case SDL_WINDOWEVENT_MOVED:
                SDL_Log("Window %d moved to %d,%d",
                    evnt.window.windowID, evnt.window.data1,
                    evnt.window.data2);
                break;*/
            case SDL_WINDOWEVENT_RESIZED:
              
                m_screenWidth = (float)evnt.window.data1;
                m_screenHeight = (float)evnt.window.data2;
                windowChange = true;
                break;
         //   case SDL_WINDOWEVENT_SIZE_CHANGED:

         //       SDL_Log("Window %d size changed to %dx%d",
         //           evnt.window.windowID, evnt.window.data1,
         //           evnt.window.data2);
         //       break;
         //   case SDL_WINDOWEVENT_MINIMIZED:
         //       SDL_Log("Window %d minimized", evnt.window.windowID);
         //       break;
         //   case SDL_WINDOWEVENT_MAXIMIZED:
         ///*       SDL_MaximizeWindow(m_sdlWindow);
         //       SDL_GetWindowSize(m_sdlWindow, &m_screenWidth, &m_screenHeight);
         //       m_glContext = SDL_GL_CreateContext(m_sdlWindow);
         //       SDL_GL_MakeCurrent(m_sdlWindow, m_glContext);*/
         //       SDL_Log("Window %d maximized", evnt.window.windowID);
         //       break;
         //   case SDL_WINDOWEVENT_RESTORED:
         //       SDL_Log("Window %d restored", evnt.window.windowID);
         //       break;
         //   case SDL_WINDOWEVENT_ENTER:
         //       SDL_Log("Mouse entered window %d",
         //           evnt.window.windowID);
         //       break;
         //   case SDL_WINDOWEVENT_LEAVE:
         //       SDL_Log("Mouse left window %d", evnt.window.windowID);
         //       break;
         //   case SDL_WINDOWEVENT_FOCUS_GAINED:
         //       SDL_Log("Window %d gained keyboard focus",
         //           evnt.window.windowID);
         //       break;
         //   case SDL_WINDOWEVENT_FOCUS_LOST:
         //       SDL_Log("Window %d lost keyboard focus",
         //           evnt.window.windowID);
         //       break;
         //   case SDL_WINDOWEVENT_CLOSE:
         //       SDL_Log("Window %d closed", evnt.window.windowID);
         //       break;
            }
        }
    }
    void Window::setWindowFlag(Uint32 flag)
    {
        m_flag = flag;
    }
}
