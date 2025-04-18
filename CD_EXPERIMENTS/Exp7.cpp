#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar, transformedGrammar;
map<char, set<char>> first, follow;
map<pair<char, char>, string> parsingTable;
char startSymbol;

void eliminateLeftRecursion() {
    for (auto &[lhs, prods] : grammar) {
        vector<string> alpha, beta;
        char newNonTerminal = lhs + '\''; // Create a new non-terminal

        for (auto &prod : prods) {
            if (prod[0] == lhs) // Left recursion
                alpha.push_back(prod.substr(1) + newNonTerminal);
            else
                beta.push_back(prod + newNonTerminal);
        }

        if (!alpha.empty()) { // Modify grammar to remove left recursion
            transformedGrammar[lhs] = beta;
            transformedGrammar[newNonTerminal] = alpha;
            transformedGrammar[newNonTerminal].push_back("e"); // ε production
        } else {
            transformedGrammar[lhs] = prods;
        }
    }
}

void leftFactoring() {
    for (auto &[lhs, prods] : transformedGrammar) {
        map<string, vector<string>> prefixGroups;

        for (auto &prod : prods) {
            prefixGroups[prod.substr(0, 1)].push_back(prod);
        }

        if (prefixGroups.size() == prods.size()) continue; // No common prefix

        char newNonTerminal = lhs + '\'';
        vector<string> newProductions;

        for (auto &[prefix, group] : prefixGroups) {
            if (group.size() > 1) {
                transformedGrammar[newNonTerminal] = {};
                for (auto &prod : group)
                    transformedGrammar[newNonTerminal].push_back(prod.substr(1));

                newProductions.push_back(prefix + newNonTerminal);
            } else {
                newProductions.push_back(group[0]);
            }
        }

        transformedGrammar[lhs] = newProductions;
    }
}

set<char> computeFirst(char symbol) {
    if (!isupper(symbol)) return {symbol};
    if (!first[symbol].empty()) return first[symbol];

    set<char> result;
    for (auto &prod : transformedGrammar[symbol]) {
        for (char ch : prod) {
            auto temp = computeFirst(ch);
            result.insert(temp.begin(), temp.end());
            if (temp.find('e') == temp.end()) break;
        }
    }
    return first[symbol] = result;
}

void computeFollow() {
    follow[startSymbol].insert('$');
    bool changed;

    do {
        changed = false;
        for (auto &[lhs, prods] : transformedGrammar) {
            for (auto &prod : prods) {
                for (int i = 0; i < prod.size(); ++i) {
                    char B = prod[i];
                    if (!isupper(B)) continue;

                    set<char> temp;
                    bool epsilonInNext = false;
                    for (int j = i + 1; j < prod.size(); ++j) {
                        auto firstNext = computeFirst(prod[j]);
                        temp.insert(firstNext.begin(), firstNext.end());

                        if (firstNext.find('e') == firstNext.end()) {
                            epsilonInNext = false;
                            break;
                        }
                        epsilonInNext = true;
                    }
                    if (i == prod.size() - 1 || epsilonInNext)
                        temp.insert(follow[lhs].begin(), follow[lhs].end());

                    if (temp.size() > follow[B].size()) {
                        follow[B].insert(temp.begin(), temp.end());
                        changed = true;
                    }
                }
            }
        }
    } while (changed);
}

void buildParsingTable() {
    for (auto &[lhs, prods] : transformedGrammar) {
        for (auto &prod : prods) {
            auto firstSet = computeFirst(prod[0]);
            for (auto ch : firstSet) {
                if (ch != 'e') parsingTable[{lhs, ch}] = prod;
            }
            if (firstSet.find('e') != firstSet.end()) {
                for (auto ch : follow[lhs])
                    parsingTable[{lhs, ch}] = prod;
            }
        }
    }
}

bool parseString(const string &input) {
    stack<char> stk;
    stk.push('$');
    stk.push(startSymbol);
    int idx = 0;

    while (!stk.empty()) {
        char top = stk.top();
        stk.pop();

        if (top == '$' && idx == input.size()) return true;
        if (!isupper(top)) {
            if (top == input[idx]) ++idx;
            else return false;
        } else {
            if (parsingTable.find({top, input[idx]}) == parsingTable.end()) return false;
            string prod = parsingTable[{top, input[idx]}];
            if (prod != "e")
                for (int i = prod.size() - 1; i >= 0; --i)
                    stk.push(prod[i]);
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cout << "Enter productions (e.g., E,E+T or E,e):\n";

    for (int i = 0; i < n; ++i) {
        string prod;
        cin >> prod;
        char lhs = prod[0];
        if (i == 0) startSymbol = lhs;
        string rhs = prod.substr(2);
        grammar[lhs].push_back(rhs);
    }

    eliminateLeftRecursion();
    leftFactoring();

    for (auto &[lhs, _] : transformedGrammar) computeFirst(lhs);
    computeFollow();
    buildParsingTable();

    string input;
    cout << "Enter input string: ";
    cin >> input;
    input += '$';

    if (parseString(input)) cout << "String accepted\n";
    else cout << "String rejected\n";

    return 0;
}
