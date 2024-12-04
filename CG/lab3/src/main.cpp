#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <cmath>


// Параметры окна
sf::Vector2f videoScale(1920.f, 1080.f);
int FrameRateLimit = 120;

// Параметры курсора
bool cursorVisible = false;
bool curosorNoOutOfTheWindow = true;

// Параметры куба
float cubeScale = 0.5f;
float cubePos[] = { 0.0f, 0.0f, 0.0f };

// Параметры пирамиды
float pyramidScale = 0.3f;
float pyramidPos[] = { -1.0f, 0.0f, 2.0f };

// Параметры сферы
float sphereColor[] = { 0.0f, 3.0f, 0.0f };
float spherePos[] = { -3.0f, 0.0f, 0.0f };
float sphereParametrs[] = { 1.0f, 32, 16 };

// Параметры света
float lightPos[] = { 0.0f, 2.0f, -2.0f, 1.0f }; // Изначальная позиция света
float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
float diffuseLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

// Параметры материала
float materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Цвет бликов
float materialShininess[] = { 50.0f };

// Параметры камеры
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;
float yaw = -90.0f, pitch = 0.0f;
float cameraSpeed = 0.05f;

// Инициализация OpenGL
void initOpenGL() {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING); // Включаем освещение
    glEnable(GL_LIGHT0);    // Включаем источник света 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   // Устанавливаем фоновое освещение
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   // Устанавливаем диффузное освещение
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); // Устанавливаем зеркальное освещение

    // Настройки материала для объекта
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

    glDepthFunc(GL_LESS);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

// Отрисовка куба
void drawCube(float cubePos[], float cubeScale) {
    glPushMatrix();
    glTranslatef(cubePos[0], cubePos[1], cubePos[2]);
    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glVertex3f(-1.0f * cubeScale, -1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, -1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, 1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(-1.0f * cubeScale, 1.0f * cubeScale, -1.0f * cubeScale);

    glColor3f(0, 1, 0);
    glVertex3f(-1.0f * cubeScale, -1.0f * cubeScale, 1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, -1.0f * cubeScale, 1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, 1.0f * cubeScale, 1.0f * cubeScale);
    glVertex3f(-1.0f * cubeScale, 1.0f * cubeScale, 1.0f * cubeScale);

    glColor3f(0, 0, 1);
    glVertex3f(-1.0f * cubeScale, -1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, -1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, -1.0f * cubeScale, 1.0f * cubeScale);
    glVertex3f(-1.0f * cubeScale, -1.0f * cubeScale, 1.0f * cubeScale);

    glColor3f(1, 1, 0);
    glVertex3f(-1.0f * cubeScale, 1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, 1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, 1.0f * cubeScale, 1.0f * cubeScale);
    glVertex3f(-1.0f * cubeScale, 1.0f * cubeScale, 1.0f * cubeScale);

    glColor3f(1, 0, 1);
    glVertex3f(-1.0f * cubeScale, -1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(-1.0f * cubeScale, 1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(-1.0f * cubeScale, 1.0f * cubeScale, 1.0f * cubeScale);
    glVertex3f(-1.0f * cubeScale, -1.0f * cubeScale, 1.0f * cubeScale);

    glColor3f(0, 1, 1);
    glVertex3f(1.0f * cubeScale, -1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, 1.0f * cubeScale, -1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, 1.0f * cubeScale, 1.0f * cubeScale);
    glVertex3f(1.0f * cubeScale, -1.0f * cubeScale, 1.0f * cubeScale);

    glEnd();

    glPopMatrix();
}

// Отрисовка пирамиды
void drawPyramid(float pyramidPos[], float pyramidScale) {
    glPushMatrix();
    glTranslatef(pyramidPos[0], pyramidPos[1], pyramidPos[2]);
    glBegin(GL_TRIANGLES);

    // Треугольники для каждой стороны пирамиды

    // Передняя сторона
    glColor3f(1, 0, 0); // Красный
    glVertex3f(0.0f, 1.0f * pyramidScale, 0.0f); // Вершина
    glVertex3f(-1.0f * pyramidScale, -1.0f * pyramidScale, 1.0f * pyramidScale); // Левый нижний угол
    glVertex3f(1.0f * pyramidScale, -1.0f * pyramidScale, 1.0f * pyramidScale); // Правый нижний угол

    // Правая сторона
    glColor3f(0, 1, 0); // Зелёный
    glVertex3f(0.0f, 1.0f * pyramidScale, 0.0f); // Вершина
    glVertex3f(1.0f * pyramidScale, -1.0f * pyramidScale, 1.0f * pyramidScale); // Правый нижний угол
    glVertex3f(1.0f * pyramidScale, -1.0f * pyramidScale, -1.0f * pyramidScale); // Правый нижний угол

    // Задняя сторона
    glColor3f(0, 0, 1); // Синий
    glVertex3f(0.0f, 1.0f * pyramidScale, 0.0f); // Вершина
    glVertex3f(1.0f * pyramidScale, -1.0f * pyramidScale, -1.0f * pyramidScale); // Правый нижний угол
    glVertex3f(-1.0f * pyramidScale, -1.0f * pyramidScale, -1.0f * pyramidScale); // Левый нижний угол

    // Левая сторона
    glColor3f(1, 1, 0); // Жёлтый
    glVertex3f(0.0f, 1.0f * pyramidScale, 0.0f); // Вершина
    glVertex3f(-1.0f * pyramidScale, -1.0f * pyramidScale, -1.0f * pyramidScale); // Левый нижний угол
    glVertex3f(-1.0f * pyramidScale, -1.0f * pyramidScale, 1.0f * pyramidScale); // Левый нижний угол

    // Нижняя грань (основа)
    glColor3f(0.5f, 0.5f, 0.5f); // Серый для основания
    glVertex3f(-1.0f * pyramidScale, -1.0f * pyramidScale, 1.0f * pyramidScale); // Левый верхний угол
    glVertex3f(1.0f * pyramidScale, -1.0f * pyramidScale, 1.0f * pyramidScale); // Правый верхний угол
    glVertex3f(1.0f * pyramidScale, -1.0f * pyramidScale, -1.0f * pyramidScale); // Правый нижний угол

    glVertex3f(-1.0f * pyramidScale, -1.0f * pyramidScale, 1.0f * pyramidScale); // Левый верхний угол
    glVertex3f(1.0f * pyramidScale, -1.0f * pyramidScale, -1.0f * pyramidScale); // Правый нижний угол
    glVertex3f(-1.0f * pyramidScale, -1.0f * pyramidScale, -1.0f * pyramidScale); // Левый нижний угол

    glEnd();
    glPopMatrix();
}

// Отрисовка cферы
void drawSphere(float sphereParametrs[], float spherePos[], float sphereColor[]) {
    glPushMatrix();
    glColor3f(sphereColor[0], sphereColor[1], sphereColor[2]);
    glTranslatef(spherePos[0], spherePos[1], spherePos[2]);

    GLUquadric* quadric = gluNewQuadric(); // Создаём объект quadric, чтобы описать сферу
    gluSphere(quadric, sphereParametrs[0], sphereParametrs[1], sphereParametrs[2]); // Создаём сферу
    gluDeleteQuadric(quadric); // Удаляем объект после использования

    glPopMatrix();
}

// Управление камерой с помощью клавиш W, A, S, D
void moveCamera(bool forward, bool backward, bool left, bool right) {
    float radYaw = yaw * M_PI / 180.0f;
    float radPitch = pitch * M_PI / 180.0f;

    // Вектор направления камеры
    float dirX = cos(radYaw) * cos(radPitch);
    float dirY = sin(radPitch);
    float dirZ = sin(radYaw) * cos(radPitch);

    // Вектор правого направления для движения влево-вправо
    float rightX = sin(radYaw);
    float rightZ = -cos(radYaw);

    if (forward) {
        camX += dirX * cameraSpeed;
        camY += dirY * cameraSpeed;
        camZ += dirZ * cameraSpeed;
    }
    if (backward) {
        camX -= dirX * cameraSpeed;
        camY -= dirY * cameraSpeed;
        camZ -= dirZ * cameraSpeed;
    }
    if (left) {
        camX -= rightX * cameraSpeed;
        camZ -= rightZ * cameraSpeed;
    }
    if (right) {
        camX += rightX * cameraSpeed;
        camZ += rightZ * cameraSpeed;
    }
}

int main() {
    // Создаём окно
    sf::Window window(sf::VideoMode(videoScale.x, videoScale.y), "Lab 3", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    // Устанавливаем лимит частоты кадров
    window.setFramerateLimit(FrameRateLimit);

    initOpenGL();

    bool forward = false, backward = false, left = false, right = false;
    window.setMouseCursorVisible(cursorVisible);
    window.setMouseCursorGrabbed(curosorNoOutOfTheWindow);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        lightPos[0] -= 0.1f;
                        break;
                    case sf::Keyboard::Right:
                        lightPos[0] += 0.1f;
                        break;
                    case sf::Keyboard::Up:
                        lightPos[2] += 0.1f;
                        break;
                    case sf::Keyboard::Down:
                        lightPos[2] -= 0.1f;
                        break;
                    case sf::Keyboard::O:
                        lightPos[1] += 0.1f;
                        break;
                    case sf::Keyboard::L:
                        lightPos[1] -= 0.1f;
                        break;
                    default:
                        break;
                }
                if (event.key.code == sf::Keyboard::W) forward = true;
                if (event.key.code == sf::Keyboard::S) backward = true;
                if (event.key.code == sf::Keyboard::A) right = true;
                if (event.key.code == sf::Keyboard::D) left = true;
                
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) forward = false;
                if (event.key.code == sf::Keyboard::S) backward = false;
                if (event.key.code == sf::Keyboard::A) right = false;
                if (event.key.code == sf::Keyboard::D) left = false;
            }
            if (event.type == sf::Event::MouseMoved) {
                int x = event.mouseMove.x;
                int y = event.mouseMove.y;

                yaw += (x - 400) * 0.1f;
                pitch -= (y - 300) * 0.1f;
                
                // Ограничение угла pitch для предотвращения переворота камеры
                if (pitch > 89.0f) pitch = 89.0f;
                if (pitch < -89.0f) pitch = -89.0f;

                sf::Mouse::setPosition(sf::Vector2i(400, 300), window);
            }
        }

        moveCamera(forward, backward, left, right);

        // Устанавливаем источник света
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Настройка проекционной матрицы
        glEnable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

        // Настройка видовой матрицы камеры
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float radYaw = yaw * M_PI / 180.0f;
        float radPitch = pitch * M_PI / 180.0f;

        float dirX = cos(radYaw) * cos(radPitch);
        float dirY = sin(radPitch);
        float dirZ = sin(radYaw) * cos(radPitch);

        gluLookAt(
            camX, camY, camZ,
            camX + dirX, camY + dirY, camZ + dirZ,
            0.0f, 1.0f, 0.0f
        );

        // Рисуем куб
        drawCube(cubePos, cubeScale);

        // Рисуем пирамиду
        drawPyramid(pyramidPos, pyramidScale);

        // Рисуем сферу
        drawSphere(sphereParametrs, spherePos, sphereColor);

        // Рисуем сферу освещения
        float lightSphereParametrs[] = { 0.1f, 32, 16 };
        drawSphere(lightSphereParametrs, lightPos, sphereColor);

        window.display();
    }

    return 0;
}
