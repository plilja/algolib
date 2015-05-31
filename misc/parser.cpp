#include <string>
#include <utility>
#include <cassert>

namespace //anonymous
{
    std::string last_begin_token = "";
    std::string errorstring = "!";
}

bool begins(const std::string &input, std::string token)
{
    last_begin_token = token;
    return token == input.substr(0, token.length());
}

void pass(std::string & input, std::string & token)
{
    input = input.substr(token.length());
}

void pass(std::string & input)
{
    pass(input, last_begin_token);
}

void skipChar(std::string & input)
{
    if (input.length() > 0) {
        input.erase(input.begin());
    }
}

char peekChar(std::string & input)
{
    if (input.length() > 0) {
        return input[0];
    }
    return 0;
}

std::string &error_string()
{
    return errorstring;
}

bool removePattern(std::string &input, std::string pattern, std::string replace)
{
    bool change = false;
    int pos = input.find(pattern, 0);
    while (pos != std::string::npos) {
        change = true;
        input.replace(pos, pattern.length(), replace);
        pos = input.find(pattern, pos);
    }
    return change;
}


int findFirstNotInParenthesis(std::string input, bool lookFor[256], bool notPrecededBy[256])
{
    int paramcount = 0;
    if (input[0] == '(') {
        paramcount++;
    } else if (input[0] == ')') {
        assert(!"Malformatted parathesis expression");
    }
    for (int i = 1; i < input.length() - 1; ++i) {
        if (paramcount < 0) {
            assert(!"Malformatted parathesis expression");
        }

        if (input[i] == '(') {
            paramcount++;
        } else if (input[i] == ')') {
            paramcount--;
        } else if (paramcount == 0 && lookFor[input[i]] && i - 1 >= 0 && !notPrecededBy[input[i - 1]]) {
            return i;
        }
    }
    return -1;
}

int findLastNotInParenthesis(std::string input, bool lookFor[256])
{
    int paramcount = 0;
    if (input[input.length() - 1] == ')') {
        paramcount++;
    } else if (input[input.length() - 1] == '(') {
        assert(!"Malformatted parathesis expression");
    }
    for (int i = input.length() - 2; i >= 1; --i) {
        if (paramcount < 0) {
            assert(!"Malformatted parathesis expression");
        }

        if (input[i] == ')') {
            paramcount++;
        } else if (input[i] == '(') {
            paramcount--;
        } else if (paramcount == 0 && lookFor[input[i]]) {
            return i;
        }
    }
    return -1;
}


void removeSpaces(std::string & s)
{
    for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
        for (int i = 0; i < s.length(); ++i) {
            while (i < s.length() && s[i] == ' ') {
                s.erase(i, 1);
            }
        }
    }
}
