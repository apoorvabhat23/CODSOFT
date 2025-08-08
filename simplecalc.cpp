#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char op;

    cout << "Welcome to the Calculator Program!\n";
    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter an operator (+, -, *, /): ";
    cin >> op;

    cout << "Enter second number: ";
    cin >> num2;

    double result;

    switch (op) {
        case '+':
            result = num1 + num2;
            cout << "Result: " << result << endl;
            break;
        case '-':
            result = num1 - num2;
            cout << "Result: " << result << endl;
            break;
        case '*':
            result = num1 * num2;
            cout << "Result: " << result << endl;
            break;
        case '/':
            if (num2 == 0) {
                cout << "Error: Division by zero is not allowed.\n";
            } else {
                result = num1 / num2;
                cout << "Result: " << result << endl;
            }
            break;
        default:
            cout << "Invalid operator. Please use +, -, *, or /.\n";
    }

    return 0;
}
