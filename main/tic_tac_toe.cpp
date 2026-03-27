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
    cout << "   | 1 | 2 | 3 |" << endl << endl;

}

int main() {
    string board[3][3] = {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "}
    };

    bool player_won = false;
    string player_turn = "X";
    int turn_count = 0;

    while (player_won == false) {
        bool player_input = false;

        // checks if the player input is valid - if not try again
        while (player_input == false) {
            int row;
            int column;

            cout << turn_count;

            if (turn_count == 4) {  //
                player_won = true;  // simple game stopper after 4 moves
            }                       //

            cout << endl << "Please enter row: ";
            cin >> row;
            // check if input failed
            while (cin.fail()) {
                cout << "Invalid row! Please use 1-3" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> row;
            }

            cout << endl << "Please enter column: ";
            cin >> column;
            // check if input failed and try again
            while (cin.fail()) {
                cout << "Invalid column! Please use 1-3" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> column;
            }

            // checks if the row/column is in the correct number range
            if (row >= 1 && row <= 3) {
                if (column >= 1 && column <= 3) {
                    board[row-1][column-1] = player_turn;
                    if (player_turn == "X") {
                        player_turn = "O";
                    } else {
                        player_turn = "X";
                    }
                    turn_count += 1;
                    print_board(board);
                    player_input = true;
                } else {
                    column = 0;
                    cout << "Invalid column! Please use 1-3" << endl;
                }
            } else {
                row = 0;
                cout << "Invalid row! Please use 1-3" << endl;
            }
        }
    }

    //print_board(board);

    return 0;
}