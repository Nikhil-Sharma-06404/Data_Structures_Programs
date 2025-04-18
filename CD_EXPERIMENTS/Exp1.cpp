#include <bits/stdc++.h>
using namespace std;

enum State {
    START,C, O, M, P, I, L, E, ACCEPT
};

bool recognizesCompiler(const std::string& input) {
    State currentState = START;
    for (char ch : input) {
        switch (currentState) {
            case START:
                currentState = (ch == 'c') ? C : START;
                break;
            case C:
                currentState = (ch == 'o') ? O : START;
                break;
            case O:
                currentState = (ch == 'm') ? M : START;
                break;
            case M:
                currentState = (ch == 'p') ? P : START;
                break;
            case P:
                currentState = (ch == 'i') ? I : START;
                break;
            case I:
                currentState = (ch == 'l') ? L : START;
                break;
            case L:
                currentState = (ch == 'e') ? E : START;
                break;
            case E:
                currentState = (ch == 'r') ? ACCEPT : START;
                break;
            case ACCEPT:
                break;
        }
    }
    return currentState == ACCEPT;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    if (recognizesCompiler(input)) {
        cout << "The string is recognized by the NFA (matches 'compiler').\n";
    } else {
        cout << "The string is not recognized by the NFA.\n";
    }

return 0;
}
