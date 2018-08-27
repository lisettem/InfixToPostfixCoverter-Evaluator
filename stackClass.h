#include <string>
#include "node.h"
#include<assert.h>

class stackb
{
private:
	Node *top;
public:
	stackb();
	bool isempty(); //checks if the stack is empty
	void push(char op); //adds to the stack 
	void pop(); //deletes off the top of the stack 
	void deleteall(); //deletes the entire stack 
	char peek()const; //this is the top function 
};
stackb::stackb()
{
	top = nullptr;
}
bool stackb::isempty()
{
	if (top == nullptr)
		return true;
	else
		return false;
}
void stackb::push(char op)
{
	Node *temp;
	temp = new Node(); //make a new node

	temp->value = op; //value is set to whatever we are passing 
	temp->next = top;
	top = temp; //set the top to point to the temp(which is the new node created)
}
void stackb::pop()
{
	//when popping you only pop from the top 
	Node *temp;

	if (top != NULL) { //if the stack isnt empty 
		temp = top; //set temp = to the top of the stack 
		top = temp->next; //move the top to the next node (which is going down) 
		delete temp;
	}
	else
		cout << "Cannot remove from an empty stack";
}
void stackb::deleteall()
{
	Node *temp;
	while (top != nullptr)//while the stack isnt empty
	{
		temp = top; //set temp=top of the stack
		top = temp->next; //the top is the next element in the stack 
		delete temp;
	}
}
char stackb::peek() const {//this is the top 
	assert(top != NULL); //if the stack is emprt terminate the program 
	return top->value;

}

