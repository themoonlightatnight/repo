#pragma once
#include "../SDL2/SDL.h"
#include "../GL/gl.h"
#include <string>
namespace Bengine {
    enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, RESIZEABLE = 0x8
    };
    class Window
    {
    public:
        Window();
        ~Window();
        int create(std::string windowName, float screenWidth, float screenHeight, unsigned int currentFlags);
        void swapBuffer();
        void onSDLEvent(SDL_Event& evnt);
        //setter
        void setScreenDimentions(float screenWidth, float screenHeight)
        {
            m_screenWidth = screenWidth;
            m_screenHeight = screenHeight;
        }
        void setWindowFlag(Uint32 flag);
        //getter
        float getScreenWidth() { return m_screenWidth; }
        float getScreenHeight() { return m_screenHeight; }
        SDL_Window* getWindow() { return m_sdlWindow; }
        SDL_GLContext& getGLContext() { return  m_glContext; }
        bool windowChange = false;
        bool boderless = false;
    private:
        SDL_Window* m_sdlWindow;
        float m_screenWidth, m_screenHeight;
        Uint32 m_flag;
        SDL_GLContext m_glContext;
    };
}
