#pragma once

#include "Bengine.h"
#include "Window.h"
#include "InputManager.h"
#include <memory>

namespace Bengine {

    class ScreenList;
    class IGameScreen;

    class IMainGame {
    public:
        IMainGame();
        virtual ~IMainGame();

        // Runs and initializes the game
        void run();
        // Exits the game
        void exitGame();
        float SDLGetWindowRefreshRate(SDL_Window* Window);
        float getScreenRefreshRate() { return m_screenRefreshRate; }

        // Called on initialization
        virtual void onInit() = 0;
        // For adding all screens
        virtual void addScreens() = 0;
        // Called when exiting
        virtual void onExit() = 0;

        void onSDLEvent(SDL_Event& evnt);

        const float getFps() const {
            return m_fps;
        }

        const float getMaxFps() const {
            return m_maxFPS;
        }
        InputManager* inputManager = nullptr;
        float getDeltaTime() { return m_deltaTime; }
       float timeTransitionScaleCamera = 0.0f;
       float timeCameraZoom = 0.0f;
       float valueCameraZoom = 0.0f;
       bool activeWheel = false;
    protected:
        // Custom update function
        virtual void update(float deltaTime);
        // Custom render function
        virtual void draw();

        bool init();
        bool initSystems();

        std::unique_ptr<ScreenList> m_screenList = nullptr;
        IGameScreen* m_currentScreen = nullptr;
        bool m_isRunning = false;
        float m_fps = 0.0f;
        Window m_window;
        float m_screenRefreshRate;
        float m_deltaTime;
        float m_maxFPS =60.0f;

    };
}