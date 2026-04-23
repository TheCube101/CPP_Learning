#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

using namespace std;
using namespace sf;

struct snakePos {
    int xPos;
    int yPos;
};

struct applePos {
    int xPos;
    int yPos;
};

int main() {
    // window dimensions
    constexpr  int windowWidth = 800;
    constexpr  int windowHeight = 800;

    // tick interval
    constexpr  float interval = 0.20f;

    // starting direction
    char currentDirection = 'D';
    char newDirection = currentDirection;

    // Segment max size
    constexpr  int maxSize = 100.f;
    RectangleShape segmentSquare(Vector2f(maxSize, maxSize));

    // setup body
    vector<snakePos> snakeBody;

    // starting pos for head
    snakeBody.push_back({0,0});

    // create rest of snake body from head
    constexpr int length = 10;
    for (int segment = 0; segment < length-1; segment++) {
        snakeBody.push_back({snakeBody[segment].xPos-1, snakeBody[segment].yPos});
    }

    // test struct print
    for (const auto& segment : snakeBody) {
        cout << "(" << segment.xPos << ", " << segment.yPos << ")\n";
    }
    cout << endl;

    // apple setup
    RectangleShape apple(Vector2f(maxSize, maxSize));
    apple.setFillColor(Color::Red);

    vector<applePos> appleObject;

    // setup random "engine"
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> randomNumber(1, windowHeight/maxSize);

    // give apple random pos
    appleObject.push_back({(randomNumber(gen)-1) * maxSize,(randomNumber(gen)-1) * maxSize});
    cout << appleObject[0].xPos << " " << appleObject[0].yPos << endl;

    // score
    int score = 0;

    // max body size
    constexpr int maxBodySize = (windowWidth/maxSize) * (windowHeight/maxSize);

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

    // custom font
    Font font("C:/CPP-projekct/Fonts/JetBrainsMonoNerdFontMono-Regular.ttf");

    Text text(font);
    text.setCharacterSize(70);
    text.setFillColor(Color(0xb3d0ffff));
    text.setStyle(Text::Bold);
    text.setPosition(Vector2f(windowWidth / 2.0f, windowHeight / 10.f));

    // setup game state
    string gameState = "Playing";

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
                        bool isXValid = false;
                        bool isYValid = false;

                        // opposite movement check and validation
                        // the current direction "reversed" is not the same as the new direction then isXValid and isYValid is true
                        if (get<0>(moveMap.find(currentDirection)->second) * (-1) != get<0>(moveMap.find(key->second)->second)) {
                            isXValid = true;
                        }
                        if (get<1>(moveMap.find(currentDirection)->second) * (-1) != get<1>(moveMap.find(key->second)->second)) {
                            isYValid = true;
                        }
                        if (isXValid && isYValid) {
                            newDirection = key->second;
                        }

                        cout << "Key pressed: " << key->second << endl;
                    } else {
                        cout << "Invalid direction" << endl;
                    }
                } else {
                    cout << "Key not in dictionary" << endl;
                }
            }
        }

        // Handle game state
        if (gameState == "Playing") {
            // Clock system. If the clock is equal to the interval the do stuff - ending by resetting the clock
            if (clock.getElapsedTime().asSeconds() >= interval)
            {

                currentDirection = newDirection; // update direction

                // do stuff here to move snake:
                // move the head and the rest of the body
                snakePos snakeHead = snakeBody[0];
                snakeBody[0].xPos += get<0>(moveMap.find(currentDirection)->second);
                snakeBody[0].yPos += get<1>(moveMap.find(currentDirection)->second);

                cout << snakeHead.yPos << windowWidth/maxSize << endl;

                // detect snake collision
                for (int i = 1; i < snakeBody.size(); i++) {
                    if (snakeHead.xPos == snakeBody[i].xPos && snakeHead.yPos == snakeBody[i].yPos) {
                        gameState = "Game Over";
                    }

                    if (snakeHead.xPos >= windowWidth/maxSize || snakeHead.xPos < (0)) {
                        gameState = "Game Over";
                    }

                    if (snakeHead.yPos >= windowHeight/maxSize || snakeHead.yPos < (0)) {
                        gameState = "Game Over";
                    }
                }

                // move the head and the rest of the body
                for (int i = 1; i < snakeBody.size(); i++) {
                    snakePos temp = snakeBody[i];
                    snakeBody[i] = snakeHead;
                    snakeHead = temp;
                }

                // add a temp segment every time the snake moves
                // "set apple random coordinate via variable x and y"
                if (snakeBody[0].xPos == appleObject[0].xPos/maxSize && snakeBody[0].yPos == appleObject[0].yPos/maxSize) {
                    // new segment must be the coordinates of the segment furthest back in the list
                    snakeBody.push_back({
                        snakeBody[snakeBody.size()-1].xPos,
                        snakeBody[snakeBody.size()-1].yPos
                    });

                    // if the snake is at its max size then the game ends
                    if (snakeBody.size() >= maxBodySize) {
                        gameState = "Won";
                    } else {
                        // new apple position if apple was intersected
                        bool isPosValid = false;

                        // validate new apple pos and try again if not valid
                        while (isPosValid == false) {
                            int appleXPos = (randomNumber(gen)-1) * maxSize;
                            int appleYPos = (randomNumber(gen)-1) * maxSize;

                            bool appleValidPos = true;

                            for (int i = 0; i < snakeBody.size(); i++) {
                                if (appleXPos/maxSize == snakeBody[i].xPos && appleYPos/maxSize == snakeBody[i].yPos) {
                                    appleValidPos = false;
                                }
                            }
                            if (appleValidPos) {
                                appleObject[0].xPos = appleXPos;
                                appleObject[0].yPos = appleYPos;
                                isPosValid = true;
                            }
                        }
                    }

                    cout << appleObject[0].xPos << " " << appleObject[0].yPos << endl;

                    score += 1;
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

                segmentSquare.setPosition(Vector2f(drawXPos, drawYPos));
                segmentSquare.setFillColor(Color::White);

                window.draw(segmentSquare);
            }

            text.setString(to_string(score));

            apple.setPosition(Vector2f(appleObject[0].xPos, appleObject[0].yPos));
            window.draw(apple);
            window.draw(text);
        }

        if (gameState == "Won") {
            cout << gameState << endl;
            // clear the window with black color
            window.clear(Color::Black);

            // do won screen
            // text, and button

        }

        if (gameState == "Game Over") {
            //cout << gameState << endl;
            // clear the window with black color
            window.clear(Color::Black);

            // do game over screen
            // text, and button

        }
        // end the current frame
        window.display();
    }
}