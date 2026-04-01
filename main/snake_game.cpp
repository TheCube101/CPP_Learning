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
    constexpr  float interval = 0.25f;

    // starting direction
    char currentDirection = 'R';
    char newDirection = currentDirection;

    // Segment max size
    constexpr  int maxSize = 15.f;
    RectangleShape segmentSquare(Vector2f(maxSize, maxSize));

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
    for (const auto& segment : snakeBody) {
        cout << "(" << segment.xPos << ", " << segment.yPos << ")\n";
    }
    cout << endl;

    // keyboard map
    static const unordered_map<Keyboard::Scancode, char> keyNames = {
        {Keyboard::Scancode::W, 'U'},
        {Keyboard::Scancode::S, 'D'},
        {Keyboard::Scancode::A, 'L'},
        {Keyboard::Scancode::D, 'R'},
    };

    // movement map
    static const unordered_map<char, tuple<int, int>> moveMap = {
        {'U', {0, -1}},
        {'D', {0, 1}},
        {'L', {-1, 0}},
        {'R', {1, 0}},
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

                ////// remember to check for oposite movement
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
            currentDirection = newDirection; // update direction

            // do stuff here to move snake:
            // move the head and the rest of the body
            snakePos snakeHead = snakeBody[0];
            snakeBody[0].xPos += get<0>(moveMap.find(currentDirection)->second);
            snakeBody[0].yPos += get<1>(moveMap.find(currentDirection)->second);

            for (int i = 1; i < snakeBody.size(); i++) {
                snakePos temp = snakeBody[i];
                snakeBody[i] = snakeHead;
                snakeHead = temp;
            }


            clock.restart(); // Reset the clock for the next interval
        }
        // clear the window with black color
        window.clear(Color::Black);

        // draw everything here...
        // draw snake
        // for each element in snakeBody -> get rectangle coordinates for display -> draw on those coordinates
        for (int i = 0; i < snakeBody.size(); i++) {
            float drawXPos = snakeBody[i].xPos * maxSize;
            float drawYPos = snakeBody[i].yPos * maxSize;

            cout << "X-pos: " << drawXPos << "Y-pos: " << drawYPos << endl;

            segmentSquare.setPosition(Vector2f(drawXPos, drawYPos));
            segmentSquare.setFillColor(Color::White);

            window.draw(segmentSquare);
        }

        // end the current frame
        window.display();
    }
}