#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
const float CAMERA_SHAKETIME_RATE = 0.1f;
namespace Bengine {
    //Camera class for 2D games
    class Camera2D
    {
    public:
        Camera2D();
        ~Camera2D();
        //sets up the orthographic matrix and screen dimensions
        void init(float screenWidth, float screenHeight, float maxScale = 80.0f, float minScale = 1.0f);
        //updates the camera matrix if needed
        void update();
        glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
        bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);
        void offsetPosition(const glm::vec2& offset) { m_position += offset; m_needsMatrixUpdate = true; }
        void offsetScale(float offset) { m_scale += offset; if (m_scale < 0.001f) m_scale = 0.001f; m_needsMatrixUpdate = true; }
        //setters
        void setPosition(const glm::vec2& newPosition) { m_position = newPosition; m_needsMatrixUpdate = true; }
        void setScale(float newScale);
        //getters
        const glm::vec2& getPosition() const { return m_position; }
        const float& getScale() const { return m_scale; }
        const glm::mat4& getCameraMatrix() const { return _cameraMatrix; }
        float getAspectRatio() const { return (float)m_screenWidth / (float)m_screenHeight; }
        const float& getSreenWidth() const { return m_screenWidth; }
        const float& getSreenHeight() const { return m_screenHeight; }

        inline const float& getShakeTime() const { return m_shakeLifetime; }
        void savePos();
        void startShake(float shakeTime, float vertFreq, float hozFreq);
        void stopShake() { m_shakeLifetime = 0.0f; }
        void setLimitScale(glm::vec2 val);
        void setMaxScale(float maxScale);
        void setMinScale(float minScale);
        void logicUpdate(float deltatime);
        inline const float& getMaxScale() { return m_maxScale; }
        inline const float& getMinScale() { return m_minScale; }
    private:
        float m_screenWidth, m_screenHeight;
        bool m_needsMatrixUpdate;
        float m_scale;
        glm::vec2 m_position;
        glm::mat4 _cameraMatrix;
        glm::mat4 _orthoMatrix;

        glm::vec2 m_savedPos;

        float m_vertShakeFreq;
        float m_hozShakeFreq;

        float m_shakeLifetime = 0.0f;
        float m_maxScale;
        float m_minScale;
    };
}