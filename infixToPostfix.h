#include <fstream>
#include<vector>
#include<algorithm>
#include <iostream>
#include "stackClass.h"
class infixToPostfix
{
public:
	void convertToPostfix(string infixExpression);
	bool comparePrecedence(char opr1, char opr2);//compares two operators and determines which precendence is higher/equal/less
	void showInfix();
	void showPostfix();
	void setpfx(string p);
	string getPfx(); 
	infixToPostfix(); //Default constructor
	bool isOperator(char op);
	int setPrecendance(char op); //sets arbitrary values to the precedence of operators 
	void reset();
	void evaluatePostFix(string s1); 

private:
	string  ifx;
	string  pfx;
};

