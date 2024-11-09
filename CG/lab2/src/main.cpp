#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Vector3f {
    float x, y, z;
};

// Функция для проекции точки в 2D с учётом перспективы и угла обзора
sf::Vector2f projectPoint(float x, float y, float z, float focalLength) {
    float scale = focalLength / (focalLength + z);
    return sf::Vector2f(x * scale, y * scale);
}

// Функция вращения точки вокруг оси X
Vector3f rotateX(const Vector3f& p, float angle) {
    float rad = angle * M_PI / 180;
    return {
        p.x,
        p.y * cos(rad) - p.z * sin(rad),
        p.y * sin(rad) + p.z * cos(rad)
    };
}

// Функция вращения точки вокруг оси Y
Vector3f rotateY(const Vector3f& p, float angle) {
    float rad = angle * M_PI / 180;
    return {
        p.x * cos(rad) + p.z * sin(rad),
        p.y,
        -p.x * sin(rad) + p.z * cos(rad)
    };
}

// Функция вращения точки вокруг оси Z
Vector3f rotateZ(const Vector3f& p, float angle) {
    float rad = angle * M_PI / 180;
    return {
        p.x * cos(rad) - p.y * sin(rad),
        p.x * sin(rad) + p.y * cos(rad),
        p.z
    };
}

int main() {
    sf::Vector2f videoScale(1920.f, 1080.f);
    int FrameRateLimit = 120;
    float focalLength = 300.0f;
    float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;


    // Создаём окно
    sf::RenderWindow window(sf::VideoMode(videoScale.x, videoScale.y), "Lab 2");

    // Устанавливаем лимит частоты кадров
    window.setFramerateLimit(FrameRateLimit);

    // Координаты вершин пирамиды
    std::vector<Vector3f> points = {
        { -100, -100, 100 }, // Нижний левый
        {  100, -100, 100 }, // Нижний правый
        {  100,  100, 100 }, // Верхний правый
        { -100,  100, 100 }, // Верхний левый
        {    0,    0, -100 }  // Вершина пирамиды
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Управление углом обзора с помощью колесика мыши
            if (event.type == sf::Event::MouseWheelScrolled) {
                focalLength += event.mouseWheelScroll.delta * 10; // Увеличиваем или уменьшаем фокусное расстояние
                if (focalLength < 50) focalLength = 50;           // Ограничиваем минимальное значение
                if (focalLength > 1000) focalLength = 1000;       // Ограничиваем максимальное значение
            }
        }

        // Управление поворотом
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) angleX -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) angleX += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) angleY -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) angleY += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) angleZ -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) angleZ += 1;

        window.clear();

        // Преобразуем и вращаем точки пирамиды
        std::vector<sf::Vector2f> projectedPoints;
        for (const auto& p : points) {
            // Вращаем точку вокруг всех осей
            Vector3f rotated = rotateX(p, angleX);
            rotated = rotateY(rotated, angleY);
            rotated = rotateZ(rotated, angleZ);

            // Проецируем 3D-координаты в 2D с учетом фокусного расстояния
            projectedPoints.push_back(projectPoint(rotated.x, rotated.y, rotated.z, focalLength));
        }

        // Смещаем к центру экрана
        for (auto& p : projectedPoints) {
            p += sf::Vector2f(videoScale.x / 2, videoScale.y / 2);
        }

        // Соединяем точки линиями
        std::vector<std::pair<int, int>> edges = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Основание
            {0, 4}, {1, 4}, {2, 4}, {3, 4}  // Грани пирамиды
        };

        for (const auto& edge : edges) {
            sf::Vertex line[] = {
                sf::Vertex(projectedPoints[edge.first], sf::Color::Blue),
                sf::Vertex(projectedPoints[edge.second], sf::Color::Red)
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}
