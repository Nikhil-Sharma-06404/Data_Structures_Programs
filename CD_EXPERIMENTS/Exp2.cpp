#include <bits/stdc++.h>
using namespace std;

unordered_set<string> keywords = {"int", "float", "if", "else", "while"};
unordered_set<string> operators = {"+", "-", "*", "/", "=", "!", ">", "<", ">=", "<=", "==", "!="};
unordered_set<char> delimiters = {'(', ')', '{', '}', ';', ','};

// Structure for a token
struct Token {
    string type;
    string value;
};

// Function to check if a string is a number (integer or floating-point)
bool isNumber(const string& str) {
    bool hasDecimalPoint = false;
    for (char ch : str) {
        if (ch == '.') {
            if (hasDecimalPoint) return false; // More than one decimal point
            hasDecimalPoint = true;
        } else if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

// Function to tokenize the input string
vector<Token> tokenize(const string& input) {
    vector<Token> tokens;
    string word;
    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];

        if (isspace(ch)) continue;

        // Check if the character is a delimiter
        if (delimiters.count(ch)) {
            continue;
        }

        // Check if the character is part of an operator
        else if (ispunct(ch) && ch != '.') {
            string op(1, ch);
            if (i + 1 < input.size() && operators.count(op + input[i + 1])) {
                op += input[++i];
            }
            tokens.push_back({"Operator", op});
        }

        // Collect multi-character words or numbers
        else if (isalnum(ch) || ch == '.') {
            word.clear();
            bool isPotentialNumber = true;
            while (i < input.size() && (isalnum(input[i]) || input[i] == '.')) {
                if (!isdigit(input[i]) && input[i] != '.') {
                    isPotentialNumber = false;
                }
                word += input[i++];
            }
            --i;

            // Classify the word
            if (keywords.count(word)) {
                tokens.push_back({"Keyword", word});
            } else if (isPotentialNumber && isNumber(word)) {
                tokens.push_back({"Constant", word});
            } else {
                tokens.push_back({"Identifier", word});
            }
        }
    }
    return tokens;
}

int main() {
    string input;
    
    // Take input from the user
    cout << "Enter the input string: ";
    getline(cin, input);
    
    // Get the tokens
    vector<Token> tokens = tokenize(input);
    
    // Output the tokens
    for (const auto& token : tokens) {
        cout << "Token(Type: " << token.type << ", Value: " << token.value << ")\n";
    }

    return 0;
}
