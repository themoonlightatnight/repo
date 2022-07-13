#include "IMainGame.h"
#include "Timing.h"
#include "ScreenList.h"
#include "IGameScreen.h"
#include <algorithm>
#include <cmath>
#include <iostream>
// Some helpful constants.
const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime
namespace Bengine 
{
    IMainGame::IMainGame() 
    {
        m_screenList = std::make_unique<ScreenList>(this);
        inputManager = new InputManager();
    }
    IMainGame::~IMainGame() 
    {
        // Empty
    }
    void IMainGame::run() 
    {
        if (!init()) return;
        FpsLimiter limiter;
        m_screenRefreshRate = (float)SDLGetWindowRefreshRate(m_window.getWindow());
        limiter.setMaxFPS(m_screenRefreshRate);
        m_maxFPS = m_screenRefreshRate;
        // Game loop
        m_isRunning = true;

        Uint32 previousTicks = SDL_GetTicks();
        while (m_isRunning)
        {
            limiter.begin();
            Uint32 newTicks = SDL_GetTicks();
            Uint32 frameTime = newTicks - previousTicks;
            previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame
            float totalDeltaTime = frameTime / DESIRED_FRAMETIME;
           


            // Call the custom update and draw method
            int i = 0; // This counter makes sure we don't spiral to death!
             // Loop while we still have steps to process.
            while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
                // The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
                m_deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
                // Update all physics here and pass in deltaTime
                // Since we just took a step that is length deltaTime, subtract from totalDeltaTime

                update(m_deltaTime);
                totalDeltaTime -= m_deltaTime;
                inputManager->update();
                // Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
                i++;
            }
            
            if (m_isRunning)
            {
                draw();
                m_fps = limiter.end();
                m_window.swapBuffer();
            }
        }
    }
    float IMainGame::SDLGetWindowRefreshRate(SDL_Window* Window)
    {
        SDL_DisplayMode Mode;
        int DisplayIndex = SDL_GetWindowDisplayIndex(Window);
        // If we can't find the refresh rate, we'll return this:
        float DefaultRefreshRate = 60.0f;
        if (SDL_GetDesktopDisplayMode(DisplayIndex, &Mode) != 0)
        {
            return DefaultRefreshRate;
        }
        if (Mode.refresh_rate == 0)
        {
            return DefaultRefreshRate;
        }
        return (float)Mode.refresh_rate;
    }
    void IMainGame::exitGame() {
        m_currentScreen->onExit();
        if (m_screenList) {
            m_screenList->destroy();
            m_screenList.reset();
        }
        m_isRunning = false;
    }
    void IMainGame::onSDLEvent(SDL_Event& evnt) 
    {
        switch (evnt.type) 
        {
            case SDL_QUIT:
                exitGame();
                break;
            case SDL_MOUSEMOTION:
                inputManager->setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                inputManager->pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                inputManager->releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                inputManager->pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                inputManager->releaseKey(evnt.button.button);
                break;
            case SDL_MOUSEWHEEL:
                activeWheel = true;
                timeTransitionScaleCamera = 0.0f;
                timeCameraZoom = 1.5f;
                valueCameraZoom = (float)evnt.wheel.y;
                break;
            default:
                break;
        }
        m_window.onSDLEvent(evnt);
    }
    bool IMainGame::init() {
        Bengine::init();
        if (!initSystems()) return false;
        onInit();
        addScreens();
        m_currentScreen = m_screenList->getCurrent();
        m_currentScreen->onEntry();
        m_currentScreen->setRunning();
        return true;
    }
    bool IMainGame::initSystems() 
    {
        m_window.create("Engine", 1024, 768, WindowFlags::RESIZEABLE);
        return true;
    }
    void IMainGame::update(float deltaTime)
    {
        if (m_currentScreen) 
        {
            switch (m_currentScreen->getState()) 
            {
                case ScreenState::RUNNING:
                    m_currentScreen->update(deltaTime);
                    break;
                case ScreenState::CHANGE_NEXT:
                    m_currentScreen->onExit();
                    m_currentScreen = m_screenList->moveNext();
                    if (m_currentScreen)
                    {
                        m_currentScreen->setRunning();
                        m_currentScreen->onEntry();
                    }
                    break;
                case ScreenState::CHANGE_PREVIOUS:
                    m_currentScreen->onExit();
                    m_currentScreen = m_screenList->movePrevious();
                    if (m_currentScreen) 
                    {
                        m_currentScreen->setRunning();
                        m_currentScreen->onEntry();
                    }
                    break;
                case ScreenState::EXIT_APPLICATION:
                    exitGame();
                    break;
                default:
                    break;
            }
        } 
        else 
        {
            exitGame();
        }
    }
    void IMainGame::draw() {
        glViewport(0, 0, (GLsizei)m_window.getScreenWidth(), (GLsizei)m_window.getScreenHeight());
        if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
            m_currentScreen->draw();
        }
    }
}