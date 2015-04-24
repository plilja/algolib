#pragma once

#include <string>

/*
 * Evaluate a string in the following grammar. 
 * 
 * <input> := <expression>
 * <expression> := <term> | <term> + <expression> | <term> - <expression>
 * <term> := <factor> | <factor> * <term> | <factor> / <term> 
 * <factor> := ( <expression> ) | <number>  
 * <number> := 12, 5, -56, -9, 0, ...
 * 
 * Also has possibility to evaluate expression that don't 
 * entirely fit the above grammar by applying the reduce function (for example -- => +).
 * 
 * The normal operator precedence applies. Returns the
 * result as a double. 
 * 
 * Program will terminate if input is malformatted.    
 */
double eval(std::string input);
