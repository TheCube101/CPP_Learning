#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double pi_function(int k) {
    double pi_aproximation = (1.0/pow(16,k))*((4.0/(8 * k + 1)) - (2.0/(8*k + 4)) - (1.0/(8*k + 5)) - (1.0/(8*k + 6)));
    return pi_aproximation;
}

int main() {
    double pi = 0;
    for (int i = 0; i <= 10; i++) {
        pi += pi_function(i);
    }

    cout << "Calculated Pi: " << endl << setprecision(50) << pi << endl;
    cout << "Actual Pi: " << endl << setprecision(50) << M_PI << endl;

    return 0;
}