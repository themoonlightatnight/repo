#include "Camera2D.h"
#include <time.h>
#include <random>
namespace Bengine
{
    Camera2D::Camera2D() : m_position(0.0f, 0.0f),
        _cameraMatrix(1.0f),
        _orthoMatrix(1.0f),
        m_scale(1.0f),
        m_needsMatrixUpdate(true),
        m_screenWidth(500),
        m_screenHeight(500)
    {
    }
    Camera2D::~Camera2D()
    {
    }
    void Camera2D::init(float screenWidth, float screenHeight, float maxScale/* = 80.0f*/, float minScale /*= 1.0f*/) {
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;
        m_maxScale = maxScale;
        m_minScale = minScale;
        _orthoMatrix = glm::ortho(0.0f, m_screenWidth, 0.0f, m_screenHeight);
    }
    //updates the camera matrix if needed
    void Camera2D::update()
    {
        //Only update if our position or scale have changed
        if (m_needsMatrixUpdate)
        {
            //Camera Translation
            glm::vec3 translate(-m_position.x + m_screenWidth / 2.0f, -m_position.y + m_screenHeight / 2.0f, 0.0f);
            _cameraMatrix = glm::translate(_orthoMatrix, translate);
            //Camera Scale
            glm::vec3 scale(m_scale, m_scale, 0.0f);
            _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
            m_needsMatrixUpdate = false;
        }
    }
    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
        // Invert Y direction
        screenCoords.y = m_screenHeight - screenCoords.y;
        // Make it so that 0 is the center
        screenCoords -= glm::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f);
        // Scale the coordinates
        screenCoords.x /= m_scale;
        screenCoords.y /= m_scale;
        // Translate with the camera position
        screenCoords += m_position;
        return screenCoords;
    }
    // Simple AABB test to see if a box is in the camera view
    bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions) {

        glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / (m_scale);

        // The minimum distance before a collision occurs
        const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
        const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

        // Center position of the parameters
        glm::vec2 centerPos = position + dimensions / 2.0f;
        // Center position of the camera
        glm::vec2 centerCameraPos = m_position;
        // Vector from the input to the camera
        glm::vec2 distVec = centerPos - centerCameraPos;

        // Get the depth of the collision
        float xDepth = MIN_DISTANCE_X - abs(distVec.x);
        float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

        // If both the depths are > 0, then we collided
        if (xDepth > 0 && yDepth > 0) {
            // There was a collision
            return true;
        }
        return false;
    }
    void Camera2D::setScale(float newScale)
    {
        if (newScale <= m_maxScale)
        {
            m_scale = newScale;
            m_needsMatrixUpdate = true;
        }
        else
        {
            m_scale = newScale;
        }
    }
    void Camera2D::savePos()
    {
        m_savedPos = m_position;
    }
    void Camera2D::startShake(float shakeTime, float vertFreq, float hozFreq)
    {
        m_shakeLifetime = shakeTime;
        m_vertShakeFreq = vertFreq;
        m_hozShakeFreq = hozFreq;
        m_savedPos = m_position;
    }

    void Camera2D::setLimitScale(glm::vec2 val)
    {
        m_maxScale = val.x;
        m_minScale = val.y;
    }

    void Camera2D::setMaxScale(float maxScale)
    {
        m_minScale = maxScale;
    }

    void Camera2D::setMinScale(float minScale)
    {
        m_minScale = minScale;
    }
    void Camera2D::logicUpdate(float deltatime)
    {
        if (m_shakeLifetime > 0.0f)
        {
            m_shakeLifetime -= CAMERA_SHAKETIME_RATE * deltatime;
            static std::mt19937 randomEngine(unsigned int(time(NULL)));
            std::uniform_real_distribution<float> hoziShake(-m_hozShakeFreq, m_hozShakeFreq);
            std::uniform_real_distribution<float> vertShake(-m_vertShakeFreq, m_vertShakeFreq);

            m_position.x = m_savedPos.x + hoziShake(randomEngine);
            m_position.y = m_savedPos.y + vertShake(randomEngine);
            m_needsMatrixUpdate = true;
        }
    }
   
}
