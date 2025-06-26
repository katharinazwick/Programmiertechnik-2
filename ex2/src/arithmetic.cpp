#include <stdio.h>
#include <stdexcept>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include <sstream>
#include <iostream>

//Aufgabe 2 Mini Taschenrechner
/* Infix in Postfix
 *
 */
using namespace std;
bool is_float(string t){
    try {
        std::stof(t);
        return true;
    } catch (...) {
        return false;
    }
}

auto precedence = [](const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
};

//infix to postfix (2+4*2 => 3 4 2 * +)
std::string infix_to_postfix(std::string inp)
{
    // TODO: Implement me.
    // Eingabe: string von tokens, gleitkommazahlen separiert durch " "

//stack speichert Operatoren und Queue speichert Postfix Ausgabe
    Stack<std::string>* S = new Stack<std::string>();
    Queue<std::string>* Q = new Queue<std::string>();
    std::istringstream iss(inp);

    std::string t; // cool token buffer
    while (iss >> t) {

        //wenn Operator stärkeren von S nach Q
        // ( auf S / ) alles nach Q bis (
        if (is_float(t)){
            Q->enqueue(t);

        }
        else if (t == "+" || t == "-" || t == "*" || t == "/") {
            while (!S->is_empty() && S->top() != "(" && precedence(t) <= precedence(S->top())) {
                Q->enqueue(S->pop()); 
            }
            
            S->push(t);

        }
        else if (t == "("){
            S->push(t);


        }
        else if (t == ")") { 
    
            while (S->top() != "(") {
                Q->enqueue(S->pop());
            }
            S->pop();
        }
    }
    // Pop remaining operators from stack
    while (!S->is_empty()) {
        if (S->top() == "(") {
            delete S;
            delete Q;
            throw std::runtime_error("Mismatched parentheses");
        }
        Q->enqueue(S->pop());
    }
    string result = "";
    // Build result string from queue
    while (!Q->is_empty()) {
        result += Q->dequeue();
        if (!Q->is_empty()) {
            result += " ";
        }
    }
    
    // Clean up
    delete S;
    delete Q;
    
    return result;

}

//wertet Infix Ausdruck aus
float evaluate_infix(std::string inp)
{
    // TODO: Implement me.
    std::string postfix;
    try {
        postfix = infix_to_postfix(inp);
    } catch (const std::exception& e) {
        throw std::runtime_error("Invalid infix expression: " + std::string(e.what()));
    }

    // Stack for evaluation
    Stack<float> eval_stack;
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        if (is_float(token)) {
            try {
                eval_stack.push(std::stof(token));
            } catch (const std::exception&) {
                throw std::runtime_error("Invalid number format: " + token);
            }
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Ensure there are enough operands
            if (eval_stack.length() < 2) {
                throw std::runtime_error("Insufficient operands for operator: " + token);
            }

            // Pop two operands (in reverse order for correct operation)
            float b = eval_stack.pop();
            float a = eval_stack.pop();
            float result;

            // Perform the operation
            if (token == "+") {
                result = a + b;
            } else if (token == "-") {
                result = a - b;
            } else if (token == "*") {
                result = a * b;
            } else if (token == "/") {
                if (b == 0.0f) {
                    throw std::runtime_error("Division by zero");
                }
                result = a / b;
            }

            // Push result back to stack
            eval_stack.push(result);
        } else {
            throw std::runtime_error("Invalid token in postfix expression: " + token);
        }
    }



    return eval_stack.pop();
}