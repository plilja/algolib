#include "parser.h"
#include "calculator.h"
#include <cassert>
#include <string>

bool expression(double &result, std::string input);

/*
 * Evaluate a <num>. Result is placed in the variable
 * result.
 *
 * Returns true if evaluation is successful, false
 * otherwise.
 */
bool num(double &result, std::string input)
{
    std::string number = "";
    auto it = input.begin();
    int chars_read = 0;
    if (input.length() > 0 && input[0] == '-') {
        chars_read = 1;
        number += '-';
        skip_char(input);
    }
    while (it != input.end() && *it >= '0' && *it <= '9') {
        number += *it;
        ++it;
        chars_read++;
    }
    if (number == "") {
        return false;
    }
    result = stol(number);
    return chars_read == (int) input.length();
}

/*
 * Evaluate a factor. The result is placed in
 * the result variable.
 *
 * Returns true if evaluation is successful.
 */
bool factor(double &result, std::string input)
{
    if (input == "") {
        return 0;
    }
    result = 0;
    if (input[0] == '-') {
        if (factor(result, input.substr(1))) {
            result = -result;
            return true;
        }
        return false;
    }
    if (input[0] == '(' && input[input.length() - 1] == ')') {
        return expression(result, input.substr(1, input.length() - 2));
    }
    //input must be <num>
    return num(result, input);
}

/*
 * Evaluates a <term>. The result is placed
 * in the variable result.
 *
 * Return true if succesfull evaluation, false
 * iterwise.
 */
bool term(double &result, std::string input)
{
    int pos = find_last_not_in_parenthesis(input, mult_div);
    if (pos == -1) {
        //input is a <factor>
        return factor(result, input);
    } else {
        //input is <factor> * <term> or <factor> / <term>
        std::string term1 = input.substr(pos + 1);
        double tmp1;
        if (!factor(tmp1, term1)) {
            return false;
        }
        double tmp2;
        std::string expr1 = input.substr(0, pos);
        if (!term(tmp2, expr1)) {
            return false;
        }
        if (input[pos] == '*') {
            result = tmp2 * tmp1;
        } else if (input[pos] == '/') {
            result = tmp2 / tmp1;
        } else {
            assert(false);
        } //should be impossible to get here
        return true;
    }
}

/*
 * Evaluate an expression.
 *
 * The result of the evaluation are added to the result variable.
 *
 * Return true if successful evaluation, false otherwise.
 */
bool expression(double &result, std::string input)
{
    int pos = find_first_not_in_parenthesis(input, plus_minus, mult_div);
    if (pos == -1) {
        //input was a <term>
        double tmp;
        term(tmp, input);
        result += tmp;
        return true;
    } else {
        //input was <term> + <expression> or <term> - <expression>
        std::string term1 = input.substr(0, pos);
        double tmp1;
        if (!term(tmp1, term1)) {
            return false;
        }
        result += tmp1;
        std::string expr1;
        if (input[pos] == '-') {
            expr1 = input.substr(pos);
        } else {
            expr1 = input.substr(pos + 1);
        }
        return expression(result, expr1);
    }
}

/*
 * Transformes an expression to a simpler expression. Spaces
 * are remove and the following transformations are applied:
 *
 * +- => -
 * -+ => -
 * -- => +
 * ++ => +
 * (+ => (
 * *+ => *
 * /+ => /
 */
void reduce(std::string &input)
{
    bool progress = true;
    while (progress) {
        progress = false;
        progress = progress || remove_pattern(input, " ", "");
        progress = progress || remove_pattern(input, "+-", "-");
        progress = progress || remove_pattern(input, "-+", "-");
        progress = progress || remove_pattern(input, "--", "+");
        progress = progress || remove_pattern(input, "++", "+");
        progress = progress || remove_pattern(input, "(+", "(");
        progress = progress || remove_pattern(input, "*+", "*");
        progress = progress || remove_pattern(input, "/+", "/");
    }
}

double eval(std::string input)
{
    reduce(input);
    while (input != "" && peek_char(input) == '+') {
        skip_char(input);
    }
    double ans = 0;
    if (expression(ans, input)) {
        return ans;
    }
    assert(!"Malformatted expression in function eval");
    return 0;
}

