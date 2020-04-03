
#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <cctype>
using namespace std;


int setPostFix(string infix, const Map& values, string& postfix);
bool precendence(char op1, char op2);
bool validChar(string infix, int i);

//If infix = invalid syntax ==> postfix may/may not change, don't change result, return 1
//If infix = syntax valid ==> set postfix to postfix version of infix
//If infix = syntax valid, but has values not in Map ==> don't change result, return 2
//If infix = syntax valid and all values in map, but divide by zero ==> don't change result, return 3
//If syntax valid, all valids in map, doesn't divide by zero ==> set result, return 0
int evaluate(string infix, const Map& values, string& postfix, int& result) {
	//If infix is empty, it is invalid
	if (infix.length() == 0)
		return 1;

	int pfResult = setPostFix(infix, values, postfix);

	if (pfResult == 1 || pfResult == 2) //Invalid syntax, return 1; value not in map, return 2
		return pfResult;

	stack<char> ops;
	for (int i = 0; i < postfix.length(); i++) {
		char ch = postfix[i];
		//If ch is an operand, check if it is in Map + push it's value if in Map
		if (islower(ch) && isalpha(ch)) {
			ValueType v;
			values.get(ch, v);
			ops.push(v);
		}
		//If ch is a binary operator
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			char op2, op1;
			if (ops.size() >= 2) {
				op2 = ops.top();
				ops.pop();
				op1 = ops.top();
				ops.pop();
			}
			else //If there is only 1 operand, invalid syntax
				return 1;

			if (ch == '+')
				ops.push(op1 + op2);
			else if (ch == '-')
				ops.push(op1 - op2);
			else if (ch == '*')
				ops.push(op1 * op2);
			else if (ch == '/') {
				if (op2 == 0) //If divide by 0, return 3
					return 3;
				ops.push(op1 / op2);
			}

		}
	}

	if (!ops.empty()){
		result = ops.top();
		ops.pop();
	}

	return 0; 
}

//Returns 1 if infix = invalid syntax
//Sets postfix equal to postfix version of infix if infix is valid, return 0
//If infix = syntax valid, but has values not in Map ==> return 2
//Syntax = valid if operands are only lowercase chars, all nonblank char legally follow non blank char before it
int setPostFix(string infix, const Map& values, string&postfix) {
	int output = 0;
	int numOpen = 0, numClosed = 0; //Counts #'s of parentheses

	//Init empty pf string and stack of operands
	string pf = "";
	stack<char> ops;

	//Loop through each char in infix
	for (int i = 0; i < infix.length(); i++) {
		//Return if invalid syntax
		if (!validChar(infix, i))
			return 1;

		char op = infix[i];
		//If the char is an operand (lowercase letter)
		if (islower(op) && isalpha(op)) {
			if (!values.contains(op))
				output = 2;

			pf += op;
		}
		//If the char is an opening parenthesis
		else if (op == '(') {
			ops.push(op);
			numOpen++;
		}
		//If the char is a closing parenthesis
		else if (op == ')') {
			//Loop until find open parenthesis
			//While stop top isn't (, append top to pf and remove it from the stack	 to get contents inside parentheses
			////ERROR: If more ) than (, checked for top before checking same # of (,) changed it so checked empty for access top
			while (!ops.empty() && ops.top() != '(') {
				if (!ops.empty()) {
					pf += ops.top();
					ops.pop();
				}
			}
			if(!ops.empty())
				ops.pop(); //Remove open parenthesis

			numClosed++;
		}
		//If char is a binary operator +, -, *, /
		else if (op == '+' || op == '-' || op == '*' || op == '/') {
			//While stack isn't empty, top isn't (, precendence of op <= precendence of stack top
			while (!ops.empty() && ops.top() != '(' && precendence(op, ops.top())) {
				pf += (ops.top());
				ops.pop();
			}
			//Push operator onto stack
			ops.push(op);
		}
		//If char is a blank space, don't append
		else if (op == ' ');
		else //If not lowercase letter, (), operator, or blank space, invalid char so return 1 for invalid syntax
			return 1;
	} //End of loop

	if (numOpen != numClosed) //If the # of open parentheses doesn't match the number of closed parentheses, invalid syntax
		return 1;

	//While stack isn't empty, append top to postfix and remove it from stack
	while (!ops.empty()) {
		pf += ops.top();
		ops.pop();
	}

	postfix = pf;
	return output;
}

//+ and - have equal precedence, * and / have equal precendence
//+, - have less precendence than *, /
//Returns true if precedence of op1 <= precendence of op2, false otherwise
bool precendence(char op1, char op2) {
	if (op1 == '+') {
		if (op2 == '+' || op2 == '-' || op2 == '*' || op2 == '/')
			return true;
	}
	else if (op1 == '-') {
		if (op2 == '+' || op2 == '-' || op2 == '*' || op2 == '/')
			return true;
	}
	else if (op1 == '*') {
		if (op2 == '*' || op2 == '/')
			return true;
	}
	else if (op1 == '/') {
		if (op2 == '*' || op2 == '/')
			return true;
	}
	
	return false;
}

//Returns true if char ch legally follows nearest nonblank char before it
//#'s/lowercase letters can follow operators, (, ==> can't follow #'s, )
//Operators can follow #'s, ) ==> can't follow operators, (, also can't be the first or last char in string
//( can follow (, operators ==> can't follow numbers, also can't be last char in string
//) can follow ), #'s ==> can't follow (, operators, also can't be first char in string
bool validChar(string infix, int i) {
	//Current char
	char ch = infix[i];

	//If the char is lowercase letter ==> rep #, can follow operators, (
	if (isalpha(ch) && islower(ch)) {
		if (i == 0) //If it is the first letter in string, valid
			return true;
		else {
			//Loop from current char to start of string until find nonblank 
			for (int j = i - 1; j > -1; j--) {
				if (infix[j] != ' ') {
					if (infix[j] == '(' || infix[j] == '+' || infix[j] == '-' || infix[j] == '*' || infix[j] == '/')
						return true;
					else
						return false;
				}
			}
			return true; //If reached all of loop w/o finding invalid char, only blank spaces
		}
	}
	//If operator: can follow #'s, ) ==> can't follow operators, (, also can't be the first or last char in string
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
		if (i == 0 || i == infix.length() - 1) //If first or last, invalid
			return false;
		else {
			//Loop from current char to start of string until find nonblank
			for (int j = i - 1; j > -1; j--) {
				if (infix[j] != ' ') {
					if ((isalpha(infix[j]) && islower(infix[j])) || infix[j] == ')')
						return true;
					else
						return false;
				}
			}
			return true; //If reached all of loop w/o finding invalid char, only blank spaces
		}
	}
	//If (: can follow (, operators ==> can't follow numbers, also can't be last char in string
	else if (ch == '(') {
		if (i == infix.length() - 1)
			return false;
		else {
			//Loop from current char to start of string until find nonblank
			for (int j = i - 1; j > -1; j--) {
				if (infix[j] != ' ') {
					if (infix[j] == '+' || infix[j] == '-' || infix[j] == '*' || infix[j] == '/' || infix[j] == '(')
						return true;
					else
						return false;
				}
			}
			return true; //If reached all of loop w/o finding invalid char, only blank spaces
		}
	}
	//If ): can follow ), #'s ==> can't follow (, operators, also can't be first char in string
	else if (ch == ')') {
		if (i == 0)
			return false;
		else {
			//Loop from current char to start of string until find nonblank
			for (int j = i - 1; j > -1; j--) {
				if (infix[j] != ' ') {
					if ((isalpha(infix[j]) && islower(infix[j])) || infix[j] == ')')
						return true;
					else
						return false;
				}
			}
			return true; //If reached all of loop w/o finding invalid char, only blank spaces
		}
	}
	//Blanks are always valid
	else if (ch == ' ')
		return true;
	else //Invalid char
		return false;
}

int main()
{
	Map smallberg;
	smallberg.insert('t', 3);
	smallberg.insert('v', 5);
	smallberg.insert('w', 2);
	smallberg.insert('x', -25);

	string str;
	int ans;
	cout << "1 = " << evaluate("w+(w+w))", smallberg, str, ans) << endl;

	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+" && answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate(" a+a+  ", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*" && answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+" && answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/" && answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	cout << "Passed all tests" << endl;
}