#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace sf;
using namespace std;

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 800;
    const int boardSize = 8;

    // key map
    static const std::unordered_map<sf::Keyboard::Scancode, std::string> keyNames = {
        {sf::Keyboard::Scancode::W, "W"},
        {sf::Keyboard::Scancode::S, "S"},
        {sf::Keyboard::Scancode::A, "A"},
        {sf::Keyboard::Scancode::D, "D"},
        {sf::Keyboard::Scancode::Space, "Space"},
        {sf::Keyboard::Scancode::Escape, "Escape"},
        {sf::Keyboard::Scancode::Enter, "Enter"}
    };

    RenderWindow window(VideoMode({windowWidth, windowHeight}), "My window");

    Font font("C:/CPP-projekct/Fonts/JetBrainsMonoNerdFontMono-Regular.ttf");

    Text text(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::Red);
    text.setStyle(Text::Bold);
    text.setPosition(Vector2f(windowWidth / 2.0f, windowHeight / 2.0f));

    Color prevColor = Color::White;
    float squareSize = 100.f;
    double maxWidth = squareSize * boardSize;
    double maxHeight = squareSize * boardSize;

    RectangleShape square(Vector2f(squareSize, squareSize));


    int counter = 0;
    float interval = 0.2f;

    Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }

            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == Mouse::Button::Left) {
                    cout << "Left Mouse button" << endl;
                    int posX = mouseEvent->position.x;
                    int posY = mouseEvent->position.y;

                    cout << "X coordinate: " << posX << " - Y coordinate: " << posY << endl;

                }
            }

            if (const auto* keyboardEvent = event->getIf<Event::KeyPressed>()) {
                //if (keyboardEvent->scancode == Keyboard::Scancode::W) {
                //    cout << "Key W pressed!" << endl;
                //}

                auto key = keyNames.find(keyboardEvent->scancode);

                if (key != keyNames.end()) {
                    std::cout << "Key pressed: " << key->second << std::endl;
                } else {
                    std::cout << "Key not in dictionary" << std::endl;
                }
            }
        }

        // Only increment counter every 'interval' seconds
        if (clock.getElapsedTime().asSeconds() >= interval)
        {
            counter++;
            clock.restart();        // Reset the clock for the next interval
        }
        window.clear(Color::Black);

        // Draw 8x8 board
        for (int row = 0; row < boardSize; row++) {
            if (row % 2 == 0) {
                prevColor = Color::White;
            } else {
                prevColor = Color::Black;
            }
            for (int col = 0; col < boardSize; col++) {
                square.setFillColor(prevColor);
                square.setPosition(Vector2f(row * squareSize, col * squareSize));
                window.draw(square);

                if (prevColor == Color::White) {
                    prevColor = Color::Black;
                } else {
                    prevColor = Color::White;
                }

            }
        }


        text.setString(to_string(counter));
        window.draw(text);
        window.display();
    }
}