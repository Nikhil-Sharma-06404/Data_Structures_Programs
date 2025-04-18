#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> first, follow;
map<pair<char, char>, string> parsingTable;
char startSymbol;

set<char> computeFirst(char symbol) {
    if (!isupper(symbol)) return {symbol};
    if (!first[symbol].empty()) return first[symbol];
    set<char> result;
    for (auto prod : grammar[symbol]) {
        for (auto ch : prod) {
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
        for (auto &[lhs, prods] : grammar) {
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
    for (auto &[lhs, prods] : grammar) {
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

    for (auto &[lhs, _] : grammar) computeFirst(lhs);
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
