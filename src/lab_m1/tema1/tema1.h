#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        glm::mat3 modelMatrix;
        float translateX, translateY, translationSpeed;
        float angularStep;

        float wingRotation;
        float actualWingRotation;
        float wingRotationSpeed;
        bool wingDirectionBack;

        bool posX;
        bool posY;
        bool firstApperance;

        float timeCounter;
        bool escape;
        bool killed;

        float timeUntilEscape;

        bool birdOnScreen;

        float RANDOM_ROTATIONS[7];

        int mouseButtonX, mouseButtonY;

        int duckCounter;

        bool updateDifficulty;
        bool updateMouseInput;

        int lives, bullets;

        int score;
    };
}   // namespace m1
