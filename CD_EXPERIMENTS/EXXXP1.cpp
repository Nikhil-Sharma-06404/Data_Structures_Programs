#include <iostream>
#include <string>

using namespace std;
bool isAcceptedNFA(const string &input)
{
    int state = 0;
    for (size_t i = 0; i < input.length(); ++i)
    {
        char ch = input[i];
        switch (state)
        {
        case 0:
            if (ch == 'c')
            {
                state = 1;
            }
            else
            {
                return false;
            }
            break;
        case 1:
            if (ch == 'o')
            {
                state = 2;
            }
            else
            {
                return false;
            }
            break;
        case 2:
            if (ch == 'm')
            {
                state = 3;
            }
            else
            {
                return false;
            }
            break;
        case 3:
            if (ch == 'p')
            {
                state = 4;
            }
            else
            {
                return false;
            }
            break;
        case 4:
            if (ch == 'i')
            {
                state = 5;
            }
            else
            {
                return false;
            }
            break;
        case 5:
            if (ch == 'l')
            {
                state = 6;
            }
            else
            {
                return false;
            }
            break;
        case 6:
            if (ch == 'e')
            {
                state = 7;
            }
            else
            {
                return false;
            }
            break;
        case 7:
            if (ch == 'r')
            {
                state = 8;
            }
            else
            {
                return false;
            }
            break;
        case 8:
            return false;
        }
    }
    return state == 8;
}
int main()
{
    string input;
    cout << "Enter a string: ";
    cin >> input;
    if (isAcceptedNFA(input))
    {
        cout << "The string is accepted by the NFA." << endl;
    }
    else
    {
        cout << "The string is not accepted by the NFA." << endl;
    }
    return 0;
}
