#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    // Regular expressions for different token types
    regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");
    regex keywordRegex("\\b(if|else|while|for|int|float|char)\\b");
    regex operatorRegex("[+\\-*/%=]|==|!=|<=?|>=?|&&|\\|\\|");
    regex numericConstantRegex("\\d+\\.?\\d*|\\.\\d+");
    regex characterConstantRegex("'[^']'");
    regex stringLiteralRegex("\"[^\"]*\"");
    regex specialCharacterRegex("[{}();,]");
    regex commentRegex("//.*|/\\*.*?\\*/");
    regex whitespaceRegex("\\s+");
    regex newlineRegex("\\n");

    string input;
    cout << "Enter the C++ code (type 'exit' to quit):\n";

    while (true) {
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        smatch match;

        // Process the input string until no matches are found
        while (!input.empty()) {
            if (regex_search(input, match, keywordRegex)) {
                cout << "Keyword: " << match[0] << endl;
            } else if (regex_search(input, match, identifierRegex)) {
                cout << "Identifier: " << match[0] << endl;
            } else if (regex_search(input, match, operatorRegex)) {
                // Output the entire matched sequence as an operator
                cout << "Operator: " << match[0] << endl;
            } else if (regex_search(input, match, specialCharacterRegex)) {
                cout << "Special Character: " << match[0] << endl;
                // Move to the next character after the match
            } else if (regex_search(input, match, numericConstantRegex)) {
                cout << "Numeric Constant: " << match[0] << endl;
            } else if (regex_search(input, match, characterConstantRegex)) {
                cout << "Character Constant: " << match[0] << endl;
            } else if (regex_search(input, match, stringLiteralRegex)) {
                cout << "String Literal: " << match[0] << endl;
            } else if (regex_search(input, match, commentRegex)) {
                cout << "Comment: " << match[0] << endl;
                // Move to the next line after a comment
                size_t pos = input.find_first_of("\n");
                if (pos != string::npos) {
                    input = input.substr(pos + 1);
                } else {
                    break; // No newline found, exit the loop
                }
            } else if (regex_search(input, match, whitespaceRegex)) {
                // Stop tokenizing at whitespaces
            } else if (regex_search(input, match, newlineRegex)) {
                // Stop tokenizing at newlines
            }
            // Move to the next character after the match
            input = match.suffix();
        }
    }

    return 0;
}

