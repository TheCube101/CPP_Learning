#include <iostream>
#include <vector>

using namespace std;

struct Position {
    int x;
    int y;
};

int main() {
    std::vector<Position> snakeBody;

    snakeBody.push_back({10, 10});
    snakeBody.push_back({snakeBody[0].x-1, snakeBody[0].y});
    snakeBody.push_back({snakeBody[1].x-1, snakeBody[1].y});

    for (int i = 2; i < 10; i++) {
        snakeBody.push_back({snakeBody[i].x-1,10});
    }

    for (const auto& segment : snakeBody) {
        std::cout << "(" << segment.x << ", " << segment.y << ")\n";
    }

    cout << endl;

    //// move 1 on x-axis 10 times
    //for (int i = 0; i < 10; i++) {
    //    int snakeSize = snakeBody.size();
    //    for (int i = 0; i < snakeSize; i++) {
    //        snakeBody[i].x = snakeBody[i].x + 1;
    //    }
    //    for (const auto& segment : snakeBody) {
    //        std::cout << "(" << segment.x << ", " << segment.y << ")\n";
    //    }
    //    cout << endl;
    //}
//
    ////for (const auto& segment : snakeBody) {
    ////    std::cout << "(" << segment.x << ", " << segment.y << ")\n";
    ////}
    //cout << endl;
    return 0;
}
