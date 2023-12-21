#include <bits/stdc++.h>


using namespace std;

bool matchKeyword(const std::string& lexeme) {
    // List of common C++ keywords
    std::unordered_set<std::string> keywords = {
        "int", "double", "char", "if", "else", "while", "for", "return", "string"// Add more keywords as needed
    };
    // Check if the lexeme is in the set of keywords
    return keywords.find(lexeme) != keywords.end();
}

bool matchIdentifier(const std::string& lexeme) {
    // Regular expression for a C++ identifier
    std::regex identifierRegex("^[a-zA-Z_][a-zA-Z0-9_]*$");

    // Check if the lexeme matches the regex
    return std::regex_match(lexeme, identifierRegex);
}

bool matchOperator(const std::string& lexeme) {
    // List of common C++ keywords
    std::unordered_set<std::string> opeartors = {
        "=", "==", ">", "<", ">=", "<=", "!=", "~","|", "&", "&&"
        };
    return opeartors.find(lexeme) != opeartors.end();
}

bool matchNumeric(string& lexeme){
    regex numericRegex("[0-9]*");

    return regex_match(lexeme, numericRegex);
}

bool matchSpecialCharacter(string& lexeme){
    unordered_set<string> specialCharacters = {
        ",", ";", ":", ".", "(",")", "{", "}"
    };

    return specialCharacters.find(lexeme) != specialCharacters.end();
}


// Define a simple token structure
struct Token {
    string type;
    string value;
};


Token findType(string& currentToken){
     if (!currentToken.empty() && matchKeyword(currentToken)) 
            {                
                return { "keyword", currentToken };
            } 
            else if (!currentToken.empty() && matchIdentifier(currentToken)) 
            {
                return { "Identifier", currentToken };
            }
            else if (!currentToken.empty() && matchOperator(currentToken)) 
            {
                return { "Operator", currentToken };
            }
            else if (!currentToken.empty() && matchNumeric(currentToken)) 
            {
                return { "Numeric constant", currentToken };
            }
            else if (!currentToken.empty() && matchSpecialCharacter(currentToken)) 
            {
                return { "Special character", currentToken };
            }
            else {
                return {"No type" ,currentToken};
            }
}


deque<Token> tokens;
// Tokenize the input string
void tokenize(const string& input) {
    string currentToken;
    for (char c : input) {
        string str = "";
            str += c;
        if(matchSpecialCharacter(str)){
            if(!currentToken.empty() && currentToken != " "){
                tokens.push_back(findType(currentToken));
                currentToken.clear();
            }
            tokens.push_back({"special character", str});
        }
        else if (isspace(c) && !currentToken.empty())  
        {
           tokens.push_back(findType(currentToken));
           currentToken.clear();
        }
        else {
            currentToken += c;
        }
        if(currentToken == " "){
            currentToken.clear();
        }
    }

    if (!currentToken.empty()) {
           tokens.push_back(findType(currentToken));
    }

}


int main() {
    string input;

    // Get input string from the user
    cout << "Enter a C++-like instruction: \n";

    while(getline(cin, input))
    {
        tokenize(input);
    }
    for(auto token : tokens)
    {
        cout << "<" << token.type << " ," << token.value << ">\n"; 
    }

    return 0;

};
