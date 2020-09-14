#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool isValid(string infix);

string createPostfix(string infix, string& postfix);

int precedence(char c);

bool isOperand(char c);

char performOp1(char op1);

char performOp2(char op1, char op2, char opand);

int evaluate(string infix, string& postfix, bool& result) {

	char current;
	char operand1;
	char operand2;

	if (!isValid(infix))
		return 1;
	postfix = createPostfix(infix, postfix);

	stack<char> operandStack;

	for (int i = 0; i < postfix.size(); i++) {

		current = postfix[i];

		if (isOperand(current))
			operandStack.push(current);
		else {
			if (current == '!') {
				operand1 = operandStack.top();
				operandStack.pop();
				operandStack.push(performOp1(operand1));
			}
			else {
				operand2 = operandStack.top();
				operandStack.pop();
				operand1 = operandStack.top();
				operandStack.pop();
				operandStack.push(performOp2(operand1, operand2, current));
			}
		}	
	}

	if (operandStack.top() == 'T') {
			result = true;
			return 0;
	}
	if (operandStack.top() == 'F') {
			result = false;
			return 0;

	}
	return 1;
}

bool isValid(string infix) {

	string newinfix = "";

	for (int i = 0; i < infix.size(); i++) {				// remove blank spaces
		if (infix[i] != ' ')
			newinfix += infix[i];
	}
	infix = newinfix;
	//cout << infix << endl;

	// Check for correct characters
	for (int i = 0; i < infix.size(); i++) {

		if ((infix[i] != 'T') && (infix[i] != 'F') &&
			(infix[i] != '!') && (infix[i] != '&') &&
			(infix[i] != '^') && (infix[i] != '(') &&
			(infix[i] != ')'))
			return false;
	}

	// check for operators at the end of the infix
	if (infix.size() > 1) {
		if (infix[infix.size() - 1] == '&' ||
			infix[infix.size() - 1] == '!' ||
			infix[infix.size() - 1] == '^')
			return false;
		// Check invalid time for letter to be last
		if ((infix[infix.size() - 1] == 'T' && infix[infix.size() - 2] == ')') ||
			(infix[infix.size() - 1] == 'F' && infix[infix.size() - 2] == ')'))
			return false;
	}

	// Check first char in infix
	if (infix[0] == '&' || infix[0] == '^')
		return false;
	// Check first char with parantheses after
	if (((infix[0] == 'T') && (infix[1] == '(')) ||
		((infix[0] == 'F') && (infix[1] == '(')))
		return false;

	// Checking for operands
	int count = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == 'T' || infix[i] == 'F')
			count++;
	}
	if (count == 0)
		return false;

	// Check all middle cases
	if (infix.size() >= 2) {
		for (int i = 1; i <= infix.size() - 1; i++) {
			// Check for letters on both sides of '!'
			if (((infix[i] == '!') && (infix[i - 1] == 'T') && (infix[i + 1] == 'T')) ||
				((infix[i] == '!') && (infix[i - 1] == 'T') && (infix[i + 1] == 'F')) ||
				((infix[i] == '!') && (infix[i - 1] == 'F') && (infix[i + 1] == 'T')) ||
				((infix[i] == '!') && (infix[i - 1] == 'F') && (infix[i + 1] == 'F')))
				return false;
			// Check for parantheses next to letters
			if (((infix[i] == 'T') && (infix[i + 1] == '(')) ||
				((infix[i] == 'F') && (infix[i + 1] == '(')) ||///////////////////////////////////////
				((infix[i] == 'T') && (infix[i - 1] == ')')) ||
				((infix[i] == 'F') && (infix[i - 1] == ')')))
				return false;
			// Check for multiple & or ^ next to each other
			if (((infix[i] == '&') && (infix[i - 1] == '&')) ||
				((infix[i] == '&') && (infix[i - 1] == '^')) ||
				((infix[i] == '^') && (infix[i - 1] == '&')) ||
				((infix[i] == '^') && (infix[i - 1] == '^')) ||
				((infix[i] == '&') && (infix[i + 1] == '&')) ||
				((infix[i] == '&') && (infix[i + 1] == '^')) ||
				((infix[i] == '^') && (infix[i + 1] == '&')) ||
				((infix[i] == '^') && (infix[i + 1] == '^')))
				return false;
			// Check if ! in wrong position
			if (((infix[i] == '&') && (infix[i - 1] == '!')) ||
				((infix[i] == '^') && (infix[i - 1] == '!')))
				return false;
			//Check if operators are next to parantheses
			if (((infix[i] == '&') && (infix[i - 1] == '(')) ||
				((infix[i] == '^') && (infix[i - 1] == '(')) ||
				((infix[i] == '&') && (infix[i + 1] == ')')) ||
				((infix[i] == '^') && (infix[i + 1] == ')')) ||
				((infix[i] == '!') && (infix[i - 1] == ')')))
				return false;
			//Check if operands are next to parantheses
			if (((infix[i] == 'T') && (infix[i + 1] == '(')) ||
				((infix[i] == 'F') && (infix[i + 1] == '(')) ||
				((infix[i] == 'T') && (infix[i - 1] == ')')) ||
				((infix[i] == 'F') && (infix[i - 1] == ')')))
				return false;
			// Check letters are not next to each other
			if (((infix[i] == 'T') && (infix[i - 1] == 'T')) ||
				((infix[i] == 'T') && (infix[i - 1] == 'F')) ||
				((infix[i] == 'F') && (infix[i - 1] == 'T')) ||
				((infix[i] == 'F') && (infix[i - 1] == 'F')) ||
				((infix[i] == 'T') && (infix[i + 1] == 'T')) ||
				((infix[i] == 'T') && (infix[i + 1] == 'F')) ||
				((infix[i] == 'F') && (infix[i + 1] == 'T')) ||
				((infix[i] == 'F') && (infix[i + 1] == 'F')))
				return false;
		}
	}

	// Check parantheses
	stack<char> par;
	for (int i = 0; i < infix.size(); i++) {
		char current = infix[i];
		switch (current) 
		{
			case '(':
				par.push(current);
				break;
			case ')':
				par.pop();
				break;
		}
	}
	if (!par.empty())
		return false;

	// Survived all checks
	return true;
}

string createPostfix(string infix, string &postfix) {

	if (isValid(infix)) {

		postfix = "";

		stack<char> opstack;

		for (int i = 0; i < infix.size(); i++) {

			char current = infix[i];

			switch (current) {
				case '!':
				case '(':
					opstack.push(current);
					break;
				case ')':
					while (opstack.top() != '(') { 
						postfix += opstack.top();
						opstack.pop();
					}
					opstack.pop();
					break;
				case '&':
				case '^':
					while ( ((!opstack.empty()) && (opstack.top() != '(')) 
						&& (precedence(current) <= precedence(opstack.top())))
					{
						postfix += opstack.top();
						opstack.pop();
					}
					opstack.push(current);
					//cout << postfix << endl;
					break;
				case ' ':
					break;
				default:
					postfix += current;
					break;
			}
		}
		while (!opstack.empty()) {
			postfix += opstack.top();
			opstack.pop();
		}
		return postfix;
	}
	return "Not A valid String";
}

int precedence(char c) {

	switch (c) {
		case '!': 
			return 4;
		case '&':
			return 3;
		case '^':
			return 2;
		default:
			return 1;
	}
}

bool isOperand(char c) {
	if (c == 'F' || c == 'T')
		return true;
	return false;
}

char performOp1(char op1) {
	if (op1 == 'T')
		return 'F';
	else
		return 'T';
}

char performOp2(char op1, char op2, char opand) {
	if (opand == '&') {
		if (op1 == 'T' && op2 == 'T')
			return 'T';
		else
			return 'F';
	}
	else {
		if (op1 == 'T' || op2 == 'T')
			return 'T';
		else
			return 'F';
	}
}



/////////////////////// MAIN FUNCTION ////////////////////////

int main() {

		string pf;
		bool answer;
		assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
		assert(evaluate("T^", pf, answer) == 1);
		assert(evaluate("T!", pf, answer) == 1);
		assert(evaluate("!T", pf, answer) == 0);
		assert(evaluate("T!T", pf, answer) == 1);
		assert(evaluate("F F", pf, answer) == 1);
		assert(evaluate("TF", pf, answer) == 1);
		assert(evaluate("()", pf, answer) == 1);

		assert(evaluate("()T", pf, answer) == 1);
		assert(evaluate("()!T", pf, answer) == 1);

		assert(evaluate("!(T)", pf, answer) == 0);
		assert(evaluate("(!)T", pf, answer) == 1);

		assert(evaluate("", pf, answer) == 1);

		assert(evaluate("(T)^(F)^(T)&(T)!(F)", pf, answer) == 1);
		assert(evaluate("(T)^(F)^(T)&(T)&!(F)", pf, answer) == 0 && answer);
		assert(evaluate("(((((((((T)))))))))", pf, answer) == 0);

		assert(evaluate("T&T&!T&!F&!F^!F", pf, answer) == 0 && answer);
		assert(evaluate("T&T&", pf, answer) == 1);

		assert(evaluate("T(F^T)", pf, answer) == 1);

		assert(evaluate("T(&T)", pf, answer) == 1);

		assert(evaluate("(T&(F^F)", pf, answer) == 1);
		assert(evaluate("T|F", pf, answer) == 1);
		assert(evaluate("", pf, answer) == 1);
		assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
			&& pf == "FF!TF&&^" && !answer);
		assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
		assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);

		cout << "Passed all tests" << endl;

}