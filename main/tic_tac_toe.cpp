#include <iostream>

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

// const string& player_turn ------ use the original string - don't copy - don't allow changes inside function
bool win_detector(string board[3][3], const string& player_turn) {
    int squares_occupied = 0;
    bool won_handler = false;

    // check all rows
    squares_occupied = 0;
    for (int i = 0; i < 3; i++) {
        squares_occupied = 0;

        for (int j = 0; j < 3; j++) {
            if (board[j][i] == player_turn) {
                squares_occupied += 1;
            }
        }
    }
    if (squares_occupied == 3) {
        won_handler = true;
    }

    // check columns
    squares_occupied = 0;
    for (int i = 0; i < 3; i++) {
        squares_occupied = 0;

        for (int j = 0; j < 3; j++) {
            if (board[i][j] == player_turn) {
                squares_occupied += 1;
            }
        }
    }
    if (squares_occupied == 3) {
        won_handler = true;
    }

    // check diagonals
    squares_occupied = 0;
    for (int i = 0; i < 3; i++) {
        // add one square to the occupied int if the square is occupied by player turn
        if (board[i][i] == player_turn) {
            squares_occupied += 1;
        }
    }
    if (squares_occupied == 3) {
        won_handler = true;
    }

    // check diagonals
    squares_occupied = 0;
    for (int i = 0; i < 3; i++) {
        // add one square to the occupied int if the square is occupied by player turn
        if (board[3-i-1][i] == player_turn) {
            squares_occupied += 1;
        }
    }
    if (squares_occupied == 3) {
        won_handler = true;
    }

    return won_handler;
}

int main() {
    string board[3][3] = {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "}
    };

    bool player_won = false;
    string player_turn = "X";

    while (player_won == false) {
        bool player_input = false;

        // checks if the player input is valid - if not try again
        while (player_input == false) {
            int row;
            int column;

            print_board(board); // prints board
            cout << "Player " << player_turn << " to move" << endl;

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
                    // If cell already contains an X or O it will not be valid
                    if (board[row-1][column-1] == "X" || board[row-1][column-1] == "O") {
                        cout << "Invalid move! Choose another cell" << endl;
                        player_input = false;
                    } else {
                        board[row-1][column-1] = player_turn;
                        player_input = true;

                        if (win_detector(board, player_turn)) {
                            player_won = true;
                            print_board(board);
                            cout << "Player " << player_turn << " won!" << endl;
                            break;
                        }

                        // switch turn
                        if (player_turn == "X") {
                            player_turn = "O";
                        } else {
                            player_turn = "X";
                        }
                    }
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
    return 0;
}