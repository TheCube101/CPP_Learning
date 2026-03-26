#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;

void print_board(string board[3][3]) {
    //---+---+---+---+
    // 1 |   |   |   |
    //---+---+---+---+
    // 2 |   |   |   |
    //---+---+---+---+
    // 3 |   |   |   |
    //---+---+---+---+
    //   | A | B | C |

    // print board:
    for (int i = 0; i < 3; i++) {
        cout << "---+---+---+---+" << endl;
        cout << " " << i+1 << " ";
        for (int j = 0; j < 3; j++) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "| ";
        cout << endl;
    }
    cout << "---+---+---+---+" << endl;
    cout << "   | A | B | C |" << endl << endl;

}

int main() {
    string board[3][3] = {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "}
    };

    bool player_won = false;

    print_board(board);

    return 0;
}