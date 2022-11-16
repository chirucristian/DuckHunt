#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2DTema.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    glm::vec3 bodyEndPoint;
    {
        // BODY
        glm::vec3 color = { 1, 0, 0 };
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(0, 60, 0), color),
            VertexFormat(corner + glm::vec3(0, 110, 0), color),
            VertexFormat(corner + glm::vec3(95, 85, 0), color),
        };
        bodyEndPoint = glm::vec3(94, 85, 0);

        Mesh* triangle = new Mesh("body");
        std::vector<unsigned int> indices = { 0, 1, 2 };
        triangle->InitFromData(vertices, indices);
        AddMeshToList(triangle);
    }

    {
        // LEFTWING
        glm::vec3 color = { 1, 0, 0 };
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(45, 85, 0), color),
            VertexFormat(corner + glm::vec3(80, 85, 0), color),
            VertexFormat(corner + glm::vec3(30, 150, 0), color),
        };

        Mesh* triangle = new Mesh("leftwing");
        std::vector<unsigned int> indices = { 0, 1, 2 };
        triangle->InitFromData(vertices, indices);
        AddMeshToList(triangle);
    }

    {
        // RIGHTWING
        glm::vec3 color = { 1, 0, 0 };
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(45, 85, 0), color),
            VertexFormat(corner + glm::vec3(80, 85, 0), color),
            VertexFormat(corner + glm::vec3(30, 20, 0), color),
        };

        Mesh* triangle = new Mesh("rightwing");
        std::vector<unsigned int> indices = { 0, 1, 2 };
        triangle->InitFromData(vertices, indices);
        AddMeshToList(triangle);
    }

    {
        // HEAD
        glm::vec3 color = { 1, 0, 0 };

        Mesh* circle = new Mesh("head");
        circle->SetDrawMode(GL_TRIANGLE_FAN);

        int triangleCount = 20;

        float twicePi = 2.0f * glm::pi<float>();

        std::vector<VertexFormat> vertices;

        int cx = 11, cy = 0, radius = 20;
        int bodyEndX = 94, bodyEndY = 85;

        for (int i = 0; i <= triangleCount; i++) {
            vertices.push_back(VertexFormat(glm::vec3(
                bodyEndX + cx + (radius * cos(i * twicePi / triangleCount)),
                bodyEndY + cy + (radius * sin(i * twicePi / triangleCount)),
                0),
                color));
        }

        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < 50; i++) {
            indices.push_back(i);
        }
        circle->InitFromData(vertices, indices);
        AddMeshToList(circle);
    }

    {
        // NOSE
        glm::vec3 color = { 0, 0, 1 };
        Mesh* triangle = new Mesh("nose");

        int headEndX = 115;
        int headEndY = 75;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(headEndX, headEndY, 0), color),
            VertexFormat(corner + glm::vec3(headEndX, headEndY + 15, 0), color),
            VertexFormat(corner + glm::vec3(headEndX + 25, headEndY + 7.5, 0), color),
        };

        std::vector<unsigned int> indices = { 0, 1, 2 };
        triangle->InitFromData(vertices, indices);
        AddMeshToList(triangle);
    }

    {
        // BOTTOM RECTANGLE
        glm::vec3 color = { 0, 1, 0 };
        Mesh* rect = new Mesh("rect");

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(window->GetResolution().x, 0, 0), color),
            VertexFormat(corner + glm::vec3(0, 125, 0), color),
            VertexFormat(corner + glm::vec3(window->GetResolution().x, 125, 0), color),
        };

        std::vector<unsigned int> indices = { 0, 1, 2,
                                             2, 3, 1, };

        rect->InitFromData(vertices, indices);
        AddMeshToList(rect);
    }

    {
        // DUCK BOX RECTANGLE
        glm::vec3 color = { 0, 0, 1 };
        Mesh* rect = new Mesh("rect_box");

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(-15, 30, 0), color),
            VertexFormat(corner + glm::vec3(-15, 150, 0), color),
            VertexFormat(corner + glm::vec3(120, 30, 0), color),
            VertexFormat(corner + glm::vec3(120, 150, 0), color),
        };
        std::vector<unsigned int> indices = { 0, 1, 2,
                                              2, 3, 1,
                                              2, 0, 1};

        rect->SetDrawMode(GL_LINE_LOOP);

        rect->InitFromData(vertices, indices);
        AddMeshToList(rect);
    }

    {
        // LIFE
        glm::vec3 color = { 1, 0, 0 };

        Mesh* circle = new Mesh("life");
        circle->SetDrawMode(GL_TRIANGLE_FAN);

        int triangleCount = 20;

        float twicePi = 2.0f * glm::pi<float>();

        std::vector<VertexFormat> vertices;

        float cx = 7.5, cy = 0, radius = 20;

        for (int i = 0; i <= triangleCount; i++) {
            vertices.push_back(VertexFormat(glm::vec3(
                cx + (radius * cos(i * twicePi / triangleCount)),
                cy + (radius * sin(i * twicePi / triangleCount)),
                0),
                color));
        }

        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < 50; i++) {
            indices.push_back(i);
        }
        circle->InitFromData(vertices, indices);
        AddMeshToList(circle);
    }

    {
        // BULLET
        glm::vec3 color = { 0, 1, 0 };
        Mesh* rect = new Mesh("bullet");

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(0, 0, 0), color),
            VertexFormat(corner + glm::vec3(23, 0, 0), color),
            VertexFormat(corner + glm::vec3(23, 45, 0), color),
            VertexFormat(corner + glm::vec3(0, 45, 0), color),
        };
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        rect->SetDrawMode(GL_LINE_LOOP);

        rect->InitFromData(vertices, indices);
        AddMeshToList(rect);
    }

    {
        // SCORE WIREFRAME
        glm::vec3 color = { 0, 0, 1 };
        Mesh* rect = new Mesh("score_wireframe");

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(0, 0, 0), color),
            VertexFormat(corner + glm::vec3(190, 0, 0), color),
            VertexFormat(corner + glm::vec3(190, 45, 0), color),
            VertexFormat(corner + glm::vec3(0, 45, 0), color),
        };
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        rect->SetDrawMode(GL_LINE_LOOP);

        rect->InitFromData(vertices, indices);
        AddMeshToList(rect);
    }

    {
        // SCORE
        glm::vec3 color = { 0, 0, 1 };
        Mesh* rect = new Mesh("score");

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(0, 0, 0), color),
            VertexFormat(corner + glm::vec3(10, 0, 0), color),
            VertexFormat(corner + glm::vec3(10, 45, 0), color),
            VertexFormat(corner + glm::vec3(0, 45, 0), color),
        };
        std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2};

        rect->InitFromData(vertices, indices);
        AddMeshToList(rect);
    }

    wingRotation = 0;
    actualWingRotation = wingRotation;
    wingRotationSpeed = 0.3f;
    wingDirectionBack = true;

    // make sure rotation is good
    RANDOM_ROTATIONS[0] = 0.4f;
    RANDOM_ROTATIONS[1] = 0.6f;
    RANDOM_ROTATIONS[2] = 0.8f;
    RANDOM_ROTATIONS[3] = 1.0f;
    RANDOM_ROTATIONS[4] = 2.2f;
    RANDOM_ROTATIONS[5] = 2.4f;
    RANDOM_ROTATIONS[6] = 2.6f;

    translateX = 0;
    translateY = 0;
    translationSpeed = 180;

    posX = true;
    posY = true;
    firstApperance = true;

    angularStep = RANDOM_ROTATIONS[rand() % 7];

    if (angularStep > glm::pi<float>() / 2) {
        posX = false;
    }

    translateX = rand() % 100 + 150;
    
    timeCounter = 0;
    escape = false;
    killed = false;

    timeUntilEscape = 8;

    birdOnScreen = true;

    mouseButtonX = 0;
    mouseButtonY = 0;

    duckCounter = 0;

    updateDifficulty = false;

    lives = 3;
    bullets = 3;

    score = 0;

    glDisable(GL_DEPTH_TEST);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (lives == 0) {
        exit(0);
    }

    timeCounter += deltaTimeSeconds;

    if (duckCounter % 5 == 0 && updateDifficulty) {
        translationSpeed *= 1.25;
        timeUntilEscape -= 2;
        updateDifficulty = false;

        cout << "Speed increase" << endl;
    }

    // check if ducked escaped
    if (translateY > 1200 && escape) {
        posX = true;
        angularStep = RANDOM_ROTATIONS[rand() % 7];
        if (angularStep > glm::pi<float>() / 2) {
            posX = false;
        }
        posY = true;

        translateX = rand() % 1000 + 150;
        translateY = 0;

        timeCounter = 0;
        escape = false;
        lives--;
        bullets = 3;
    }

    if (translateY < -200 && killed) {
        posX = true;
        angularStep = RANDOM_ROTATIONS[rand() % 7];
        if (angularStep > glm::pi<float>() / 2) {
            posX = false;
        }
        posY = true;

        translateX = rand() % 1000 + 150;
        translateY = 0;

        timeCounter = 0;
        killed = false;
        bullets = 3;
    }

    if (escape && killed) {
        mouseButtonX = 0;
        mouseButtonY = 0;
        escape = false;
        angularStep = 3 * glm::pi<float>() / 2;
        duckCounter++;
        updateDifficulty = true;
        score++;
    }

    if (!escape && !killed) {
        if (posX) {
            translateX += translationSpeed * deltaTimeSeconds;
        }
        else {
            translateX -= translationSpeed * deltaTimeSeconds;
        }

        if (posY) {
            translateY += translationSpeed * deltaTimeSeconds;
        }
        else {
            translateY -= translationSpeed * deltaTimeSeconds;
        }

        bool updated = false;

        if (translateX > 1280 && translateY > 720) {
            angularStep = glm::pi<float>() + angularStep;
            posX = false;
            posY = false;
            updated = true;
        }

        if (translateX < 0 && translateY > 720 && !updated) {
            angularStep = glm::pi<float>() + angularStep;
            posX = true;
            posY = false;
            updated = true;
        }

        if (translateX < 0 && translateY < 0 && !updated) {
            angularStep = glm::pi<float>() + angularStep;
            posX = true;
            posY = true;
            updated = true;
        }

        if (translateX > 1280 && translateY < 0 && !updated) {
            angularStep = glm::pi<float>() + angularStep;
            posX = true;
            posY = true;
            updated = true;
        }

        if (translateX > 1280 && !updated) {
            angularStep = glm::pi<float>() - angularStep;
            posX = false;
            updated = true;
        }

        if (translateX < 0 && !firstApperance && !updated) {
            angularStep = glm::pi<float>() - angularStep;
            posX = true;
            updated = true;
        }

        if (translateY > 680 && !updated) {
            angularStep = 2 * glm::pi<float>() - angularStep;
            posY = false;
            updated = true;
        }

        if (translateY < 0 && !firstApperance && !updated) {
            angularStep = 2 * glm::pi<float>() - angularStep;
            posY = true;
            updated = true;
        }
    }
    else if (escape && !killed) {
        translateY += translationSpeed * deltaTimeSeconds;
    }
    else if (killed && !escape) {
        translateY -= translationSpeed * deltaTimeSeconds;
    }

    if ((timeCounter > timeUntilEscape || bullets == 0) && !killed) {
        escape = true;
        angularStep = glm::pi<float>() / 2;
    }

    float hitBoxMinX = translateX - 15;
    float hitBoxMaxX = translateX + 120;
    float hitBoxMinY = translateY + 30;
    float hitBoxMaxY = translateY + 150;

    if ((mouseButtonX > hitBoxMinX && mouseButtonX < hitBoxMaxX) && (mouseButtonY > hitBoxMinY && mouseButtonY < hitBoxMaxY) && updateMouseInput && bullets > 0 && !killed) {
        cout << "Duck hit" << endl;
        mouseButtonX = 0;
        mouseButtonY = 0;
        killed = true;
        angularStep = 3 * glm::pi<float>() / 2;
        duckCounter++;
        updateDifficulty = true;
        score++;
    }

    if (updateMouseInput) {
        mouseButtonX = 0;
        mouseButtonY = 0;
        updateMouseInput = false;
    }

    float duckCenterX = 47.5f;
    float duckCenterY = 85;

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2DTema::Translate(translateX, translateY);

    modelMatrix *= transform2DTema::Translate(duckCenterX, duckCenterY);
    modelMatrix *= transform2DTema::Rotate(angularStep);
    modelMatrix *= transform2DTema::Translate(-duckCenterX, -duckCenterY);
 
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["nose"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

    // animate the wings
    if (wingDirectionBack) {
        wingRotation += wingRotationSpeed * deltaTimeSeconds;
        actualWingRotation = wingRotation;
        if (wingRotation >= 0.12f) {
            wingDirectionBack = false;
        }
    }
    else {
        wingRotation -= wingRotationSpeed * deltaTimeSeconds;
        actualWingRotation = 2 * glm::pi<float>() + wingRotation;
        if (wingRotation <= 0) {
            wingDirectionBack = true;
        }
    }

    glm::mat3 modelMatrixLeftWing = modelMatrix;
    modelMatrixLeftWing *= transform2DTema::Translate(42, 75);
    modelMatrixLeftWing *= transform2DTema::Rotate(actualWingRotation);
    modelMatrixLeftWing *= transform2DTema::Translate(-42, -75);
    RenderMesh2D(meshes["leftwing"], shaders["VertexColor"], modelMatrixLeftWing);

    glm::mat3 modelMatrixRightWing = modelMatrix;
    modelMatrixRightWing  *= transform2DTema::Translate(42, 75);
    modelMatrixRightWing *= transform2DTema::Rotate((2 * glm::pi<float>()) - actualWingRotation);
    modelMatrixRightWing *= transform2DTema::Translate(-42, -75);
    RenderMesh2D(meshes["rightwing"], shaders["VertexColor"], modelMatrixRightWing);

    if (translateY > 125) {
        firstApperance = false;
    }

    RenderMesh2D(meshes["rect"], shaders["VertexColor"], glm::mat3(1));

    // RENDER LIFES
    modelMatrix = transform2DTema::Translate(1050, 660);

    if (lives >= 1)
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2DTema::Translate(1130, 660);

    if (lives >= 2)
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2DTema::Translate(1210, 660);

    if (lives >= 3)
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);

    // RENDER BULLETS
    modelMatrix = transform2DTema::Translate(1046, 585);
    if (bullets >= 1)
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2DTema::Translate(1126, 585);
    if (bullets >= 2)
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2DTema::Translate(1206, 585);
    if (bullets >= 3)
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);

    // RENDER SCORE WIREFRAME
    modelMatrix = transform2DTema::Translate(1043, 520);
    RenderMesh2D(meshes["score_wireframe"], shaders["VertexColor"], modelMatrix);

    // RENDER SCORE
    if (score > 19) {
        score = 19;
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2DTema::Translate(1043, 520);
    modelMatrix *= transform2DTema::Scale(score, 1);
    RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    mouseButtonX = mouseX;
    mouseButtonY = 720 - mouseY;
    updateMouseInput = true;
    
    bullets--;
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
