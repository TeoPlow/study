#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    sf::Vector2f videoScale(1920.f, 1080.f);
    sf::Vector2f figureScale(100.f, 400.f);
    float scaleFactor = 1.f;
    const float scaleStep = 0.01f;
    const float moveStep = 5.f;
    float angle = 0.f;
    const float angleStep = 1.f;
    sf::Vector2f position;
    bool show_debug_menu = false;
    
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(videoScale.x, videoScale.y), "Lab 1");

    // Создаем прямоугольник
    sf::RectangleShape rectangle(sf::Vector2f(figureScale.x, figureScale.y));
    rectangle.setPosition((videoScale.x / 2), (videoScale.y / 2)); // Позиционирование фигуры
    rectangle.setFillColor(sf::Color(255,255,255)); // Заливка
    rectangle.setOutlineThickness(20.f); // Толщина контура
    rectangle.setOutlineColor(sf::Color(255, 0, 255)); // Цвет контура (RGB)
    rectangle.setRotation(angle); // Угол поворота

    // Создаем Debug меню
    sf::Font font;
    std::filesystem::current_path(std::filesystem::path(argv[0]).remove_filename());
    if (!font.loadFromFile("shrift.ttf")) {
        std::cerr << "Error: шрифт не загрузился" << std::endl;
        return -1;
    }
    sf::Text debug_menu;
    debug_menu.setFont(font);
    debug_menu.setCharacterSize(24);
    debug_menu.setFillColor(sf::Color::Red);

    // Включение окна
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка ординарного нажатия клавиш
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::U) {
                    if (show_debug_menu == false) {
                        show_debug_menu = true;
                    } else {
                        show_debug_menu = false;
                    }
                }
            }
        }

        sf::Vector2f position = rectangle.getPosition();

        // Обработка зажатия клавиш
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            scaleFactor = std::min(scaleFactor + scaleStep, (videoScale.y / 100)); // Увеличиваем масштаб
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            scaleFactor = std::max(0.1f, scaleFactor - scaleStep); // Уменьшаем масштаб
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            angle += angleStep; // Увеличиваем угол
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            angle -= angleStep; // Уменьшаем угол
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (position.y > 0) {
                rectangle.move(0.f, -moveStep); // Перемещаем вверх
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (position.y < (videoScale.y - (figureScale.y * scaleFactor))) {
                rectangle.move(0.f, moveStep); // Перемещаем вниз
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (position.x > 0) {
                rectangle.move(-moveStep, 0.f); // Перемещаем влево
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (position.x < (videoScale.x - (figureScale.x * scaleFactor))) {
                rectangle.move(moveStep, 0.f); // Перемещаем вправо
            }
        }

        // Обновляем прямоугольник
        rectangle.setSize(sf::Vector2f(figureScale.x * scaleFactor, figureScale.y * scaleFactor));
        rectangle.setRotation(angle);
        rectangle.setOutlineColor(sf::Color(255 - std::min(static_cast<int>(scaleFactor * 64), 255) , 0, angle));


        // Обновляем Debug меню
        debug_menu.setString(
        "videoScale - X: " + std::to_string(static_cast<int>(videoScale.x)) + ", Y: " + std::to_string(static_cast<int>(videoScale.y)) + "\n" + 
        "figureScale: " + std::to_string(static_cast<int>(scaleFactor)) + "." +  std::to_string(static_cast<int>((scaleFactor * 1000)) % 1000) + "\n" + 
        "position - X: " + std::to_string(static_cast<int>(position.x)) +", Y: " + std::to_string(static_cast<int>(position.y)) + "\n" +
        "angle: " + std::to_string(static_cast<int>(angle)));

        window.clear();
        window.draw(rectangle); // Рисуем прямоугольник
        if (show_debug_menu) {
            window.draw(debug_menu); // Рисуем Debug меню
        }
        window.display(); // Отображаем нарисованное
    }

    return 0;
}

