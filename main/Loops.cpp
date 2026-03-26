#include <iostream>

using namespace std;

int main() {
    // i = 0: starting point
    // i <= 3: End point
    // i += x: incriment amount
    for (int i = 0; i <= 4; i+=2) {
        cout << "Hello World: " << i << endl;
    }
    cout << "For-loop done looping" << endl;

    bool my_bool = true; // Creates a bool for the while loop condition
    while (my_bool == true) {
        cout << "Enter boolean '1' or '0': " << endl; // Prints the message

        string temp_bool; // Creates temp bool of type string
        cin >> temp_bool; // Asks for input

        if (temp_bool == "1" || temp_bool == "0") { // If-statement asks 'if temp bool is equal to type string 1 or type string 2' then continue
            cout << "Temp_bool value: " << temp_bool << endl; // Prints message
            my_bool = stoi(temp_bool); // If temp_bool is either 1 or 0 then it converts string to int and sets my bool to that
        } else { // If the condition is not met then print invalid bool!
            cout << "Invalid bool! " << temp_bool << endl;
        }
    }
    return 0;
}