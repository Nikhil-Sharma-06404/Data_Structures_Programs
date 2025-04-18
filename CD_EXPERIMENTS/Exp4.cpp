#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

// Function to compute FIRST sets
void computeFirst(map<char, vector<string>> productions, map<char, set<char>>& first, char nonTerminal) {
    for (string prod : productions[nonTerminal]) {
        for (char symbol : prod) {
            if (isupper(symbol)) { // Non-terminal
                computeFirst(productions, first, symbol);
                for (char terminal : first[symbol]) {
                    if (terminal != 'ε') {
                        first[nonTerminal].insert(terminal);
                    }
                }
                if (first[symbol].find('ε') == first[symbol].end()) {
                    break;
                }
            } else { // Terminal
                first[nonTerminal].insert(symbol);
                break;
            }
        }
    }
}

int main() {
    // Input grammar
    map<char, vector<string>> productions = {
        {'S', {"AB", "ε"}},
        {'A', {"a", "BC", "ε"}},
        {'B', {"b"}},
        {'C', {"c", "ε"}}
    };

    // Initialize FIRST sets
    map<char, set<char>> first;
    for (auto& prod : productions) {
        first[prod.first] = set<char>();
    }

    // Compute FIRST sets
    for (auto& prod : productions) {
        computeFirst(productions, first, prod.first);
    }

    // Output FIRST sets
    for (auto& f : first) {
        cout << "FIRST(" << f.first << ") = {";
        bool firstTerminal = true;
        for (char terminal : f.second) {
            if (!firstTerminal) {
                cout << ", ";
            }
            if (terminal == 'ε') {
                cout << "ε";
            } else {
                cout << terminal;
            }
            firstTerminal = false;
        }
        cout << "}" << endl;
    }

    return 0;
}