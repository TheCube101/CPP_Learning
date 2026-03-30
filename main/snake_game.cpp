#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct snakePos {
    int xPos;
    int yPos;
};

int main() {
    // window dimensions
    constexpr  int windowWidth = 800;
    constexpr  int windowHeight = 800;

    // tick interval
    constexpr  float interval = 0.5f;

    // Each snake part/cell has a fixed width and height
    constexpr  int cellSize = 10;
    constexpr  int cellWidth = windowWidth/cellSize;
    constexpr  int cellHeight = windowHeight/cellSize;

    // starting direction
    char currentDirection = 'R';
    char newDirection = ' ';

    // setup body
    vector<snakePos> snakeBody;

    // starting pos for head
    snakeBody.push_back({10,10});

    // create rest of snake body from head
    constexpr int length = 3;
    for (int segment = 0; segment < length-1; segment++) {
        snakeBody.push_back({snakeBody[segment].xPos-1, snakeBody[segment].yPos});
    }

    // test struct print
    //for (const auto& segment : snakeBody) {
    //    std::cout << "(" << segment.xPos << ", " << segment.yPos << ")\n";
    //}

    // keyboard map
    static const unordered_map<Keyboard::Scancode, char> keyNames = {
        {Keyboard::Scancode::W, 'U'},
        {Keyboard::Scancode::S, 'D'},
        {Keyboard::Scancode::A, 'L'},
        {Keyboard::Scancode::D, 'R'},
    };

    // render the window
    RenderWindow window(VideoMode({windowWidth, windowHeight}), "Snake Game");

    // setup initial clock object
    Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<Event::Closed>())
                window.close();

            // access the keyboard events and reference with keyboard map "KeyNames"
            if (const auto* keyboardEvent = event->getIf<Event::KeyPressed>()) {
                auto key = keyNames.find(keyboardEvent->scancode);

                if (key != keyNames.end()) {
                    if (key->second != currentDirection) {
                        newDirection = key->second;
                        cout << "Key pressed: " << key->second << endl;
                    } else {
                        cout << "Invalid direction" << endl;
                    }
                } else {
                    cout << "Key not in dictionary" << endl;
                }
            }
        }

        // Clock system. If the clock is equal to the interval the do stuff - ending by resetting the clock
        if (clock.getElapsedTime().asSeconds() >= interval)
        {
            // do stuff here to move snake:

            currentDirection = newDirection;
            clock.restart(); // Reset the clock for the next interval
        }
        // clear the window with black color
        window.clear(Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }
}