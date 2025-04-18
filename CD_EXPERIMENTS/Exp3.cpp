#include<bits/stdc++.h>
using namespace std;

// Function to compute the FIRST set of a non-terminal
void computeFirst(string nonTerminal, map<string, set<string>> &firstSets, map<string, vector<string>> &productions, set<string> &visited) {
    if (visited.find(nonTerminal) != visited.end()) return; // Avoid recomputation
    visited.insert(nonTerminal);

    for (const string &rule : productions[nonTerminal]) {
        if (islower(rule[0]) || !isalpha(rule[0])) { // Terminal or symbol
            firstSets[nonTerminal].insert(string(1, rule[0]));
        } else { // Non-terminal
            computeFirst(string(1, rule[0]), firstSets, productions, visited);
            for (const string &symbol : firstSets[string(1, rule[0])]) {
                if (symbol != "ε") firstSets[nonTerminal].insert(symbol); // Exclude ε
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of productions: ";
    cin >> n;
    cin.ignore(); // Clear newline from input buffer

    map<string, vector<string>> productions;
    map<string, set<string>> firstSets;

    cout << "Enter the productions (e.g., A->aB|b):" << endl;
    for (int i = 0; i < n; i++) {
        string input;
        getline(cin, input);

        stringstream ss(input);
        string nonTerminal, production;
        getline(ss, nonTerminal, '-'); // Get the non-terminal
        ss.ignore(1);                 // Ignore '>'
        while (getline(ss, production, '|')) {
            productions[nonTerminal].push_back(production);
        }
    }

    // Compute FIRST sets for all non-terminals
    for (const auto &entry : productions) {
        set<string> visited;
        computeFirst(entry.first, firstSets, productions, visited);
    }

    // Display FIRST sets
    cout << "\nFIRST Sets:" << endl;
    for (const auto &entry : firstSets) {
        cout << "FIRST(" << entry.first << ") = { ";
        bool first = true;
        for (const string &symbol : entry.second) {
            if (!first) cout << ", ";
            cout << symbol;
            first = false;
        }
        cout << " }" << endl;
    }

    return 0;
}


