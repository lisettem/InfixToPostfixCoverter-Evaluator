#include "infixToPostfix.h"
#include "ArgumentManager.h"
int main(int argc, char* argv[])
{		
	if (argc < 2) {
		std::cerr << "Usage: count filename=input1.txt\n";
	}
	ArgumentManager am(argc, argv);
	string filename = am.get("input"); //get the name of the file
	ifstream infile(filename.c_str()); 
	infixToPostfix  InfixExp;
	string infix;
	if (!infile) {
		cout << "Cannot open input file. Program terminates!!!" << endl; return 1;
	}
	while (getline(infile, infix))
	{
		InfixExp.convertToPostfix(infix); //converts the file infix to postfix	
		InfixExp.evaluatePostFix(InfixExp.getPfx());
		cout << endl; 
		InfixExp.reset();//resets the postfix to " " in order to print the next one without 
					 //the contents of the previous postfix
	}
	infile.close();
	return 0;
}
void infixToPostfix::convertToPostfix(string infixExpression) {
	ifx = infixExpression;
	string infixDummy = infixExpression;

	char pr = '(', p = '+'; 

	for (int i = 0; i < infixDummy.length(); i++) //this for loop takes care of a plus being a sign instead of an operator 
	{
		if (infixDummy[i] == pr && infixDummy[i + 1] == p)
		{
			infixDummy[i + 1] = ' ';
		}
		if (infixDummy[i] == p && infixDummy[i + 1] == p)
		{
			infixDummy[i + 1] = ' ';
		}
		if (infixDummy[0] == p)
			infixDummy[0] = ' ';
	}

	infixExpression = infixDummy;
	stackb stk;

	for (int i = 0; i < infixExpression.length(); i++) {


		if (infixExpression[i] == ' ') continue;//skip if there is a space
		else if (isalpha(infixExpression[i]))
			pfx += infixExpression[i]; //if its a letter then add it to the postfix 
		else if (infixExpression[i] == '(')
			stk.push(infixExpression[i]); //if its an open ( then add it to the stack 
		else if (infixExpression[i] == ')')
		{
			while (!stk.isempty() && stk.peek() != '(')
			{
				pfx += stk.peek(); //save everything that is in the stack up until (
				stk.pop(); //pop the top
			}
			stk.pop(); //pops the open (, which is now the top 
		}
		else if (isOperator(infixExpression[i]))
		{
			//not an empty stack, the top cannot be '(' and the top operator has to have greater 
			//precendence than the other one 
			while (!stk.isempty() && stk.peek() != '(' && comparePrecedence(stk.peek(), infixExpression[i])) {
				pfx += stk.peek(); //add whatever is in the top to the postfix 
				stk.pop(); //delete the top 
			}
			stk.push(infixExpression[i]);
		}

	}

	while (!stk.isempty())
	{
		pfx += stk.peek();
		stk.pop();
	}
}
infixToPostfix::infixToPostfix()
{
	ifx = "";
	pfx = "";
}
bool infixToPostfix::isOperator(char op) {
	if (op == '+' || op == '*') //recognize the operator 
		return true;
	else
		return false;
}
int infixToPostfix::setPrecendance(char op)
{
	int pv;

	switch (op)
	{
	case '+':
		pv = 1;
		break;
	case '*':
		pv = 2;
		break;
	}
	return pv;
}
bool infixToPostfix::comparePrecedence(char opr1, char opr2) {

	if (setPrecendance(opr1) == setPrecendance(opr2))
		return true;
	else if (setPrecendance(opr1) > setPrecendance(opr2))
		return true;
	else
		return false;

}
void infixToPostfix::showInfix() {
	cout << ifx << "=";
}
void infixToPostfix::showPostfix() {
	cout << "Postfix Expression " << pfx << endl;
}
void infixToPostfix::reset() {
	pfx = " ";
}
void infixToPostfix::evaluatePostFix(string s1) {

	stackb stackOne;
	string filename;
	char dummy;

	vector <int> set; //where the answer will be stored 
	for (int i = 0; i < s1.length(); i++) //this for loop will execute for each line in expression.txt
	{
		if (isalpha(s1[i])) //if its a letter push it into the stack 
		{
			stackOne.push(s1[i]);
		}

		//once you hit an operator you will have one of these options
		if (s1[i] == '+' && set.size() == 0) //if its a plus operator and the vector set is empty 
		{
			dummy = stackOne.peek(); //assign one of the letters to dummy 
			stackOne.pop(); //pop it from the stack 

			//get the file name and open file 
			filename = "";
			filename.push_back(dummy);
			filename += ".txt";
			ifstream ifs(filename.c_str());
			string list;

			vector <int> unionV;
			while (ifs >> list) //read the numbers as string from the specific textfile and store them into the int vector unionV
			{
				unionV.push_back(stoi(list));
			}

			dummy = stackOne.peek(); //assign the next letter in the stack to dummy 
			stackOne.pop(); //pop it from the stack 

			//get the filename of that specific text file and read it 
			filename = "";
			filename.push_back(dummy);
			filename += ".txt";
			ifstream fs2(filename.c_str());
			string list2;
			vector <int> v1; //store the second text file numbers here 

			while (fs2 >> list2)
			{
				v1.push_back(stoi(list2));
			}

			sort(unionV.begin(), unionV.end()); //sort the first text file numbers 
			unionV.erase(unique(unionV.begin(), unionV.end()), unionV.end()); //get rid of duplicates in order to be able to sort them easier at the end 

			sort(v1.begin(), v1.end()); //sort the second text file numbers 
			v1.erase(unique(v1.begin(), v1.end()), v1.end());//get rid of duplicates within that same file 

			int x; //set the size of the vector 
			if (unionV.size() > v1.size())
			{
				x = 2 * unionV.size();
			}
			else
			{
				x = 2 * v1.size();
			}
			vector <int> setd(x); //where you store the result of the union

			vector<int>::iterator it = set_union(unionV.begin(), unionV.end(), v1.begin(), v1.end(), setd.begin()); //get the union of the two vectors
			setd.resize(it - setd.begin());

			for (int i = 0; i < setd.size(); i++)
			{
				set.push_back(setd[i]); //put the result of the union in the vector 
			}

			//close both files and clear setd 
			ifs.close();
			fs2.close();
			setd.clear();
		}
		else if (s1[i] == '+' && set.size() != 0) //if you have plus operator and the set vector is not empty (which means you already performed an operation) 
		{
			//pop only one thing from the stack
			dummy = stackOne.peek();
			stackOne.pop();

			//get file name and open 
			filename = "";
			filename.push_back(dummy);
			filename += ".txt";
			ifstream ify(filename.c_str());

			vector <int> union2; //read file into union2 vector 
			string s;
			while (ify >> s)
			{
				union2.push_back(stoi(s));
			}

			//you will now be comparing union2 vector with the set vector 
			sort(union2.begin(), union2.end()); //sort the vector 
			union2.erase(unique(union2.begin(), union2.end()), union2.end()); //erase duplicates 
			sort(set.begin(), set.end());
			set.erase(unique(set.begin(), set.end()), set.end()); 

			int x;//size of result vector 
			if (union2.size() > set.size())
			{
				x = 2 * union2.size();
			}
			else
			{
				x = 2 * set.size();
			}
			vector <int> set2(x); //create an int vector of this size 

			vector<int>::iterator it = set_union(union2.begin(), union2.end(), set.begin(), set.end(), set2.begin()); //perform union 
			set2.resize(it - set2.begin());

			set.clear(); //clear the main result set in order to store the new main result 

			for (int i = 0; i < set2.size(); i++)
			{
				set.push_back(set2[i]);
			}

			//close file and clear set 2
			set2.clear();
			ify.close();
		}

		//same logic as above but only difference is the operator and that it is an intersection 
		else if (s1[i] == '*' && set.size() == 0)
		{
			dummy = stackOne.peek();
			stackOne.pop();

			filename = "";
			filename.push_back(dummy);
			filename += ".txt";
			ifstream ifs(filename.c_str());
			string list;

			vector <int> unionV;
			while (ifs >> list)
			{
				unionV.push_back(stoi(list));
			}

			dummy = stackOne.peek();
			stackOne.pop();

			filename = "";
			filename.push_back(dummy);
			filename += ".txt";
			ifstream fs2(filename.c_str());
			string list2;
			vector <int> v1;

			while (fs2 >> list2)
			{
				v1.push_back(stoi(list2));
			}

			sort(unionV.begin(), unionV.end());
			unionV.erase(unique(unionV.begin(), unionV.end()), unionV.end());

			sort(v1.begin(), v1.end());
			v1.erase(unique(v1.begin(), v1.end()), v1.end());
			std::vector<int>::iterator it;
			int x;
			if (unionV.size() > v1.size())
			{
				x = 2 * unionV.size();
			}
			else
			{
				x = 2 * v1.size();
			}
			vector <int> setd(x);

			it = std::set_intersection(unionV.begin(), unionV.end(), v1.begin(), v1.end(), setd.begin());
			setd.resize(it - setd.begin());

			for (int i = 0; i < setd.size(); i++)
			{
				set.push_back(setd[i]);
			}

			ifs.close();
			fs2.close();
			setd.clear();
		}
		else if (s1[i] == '*' && set.size() != 0)
		{
			//pop only one thing from the stack
			dummy = stackOne.peek();
			stackOne.pop();

			filename = "";
			filename.push_back(dummy);
			filename += ".txt";
			ifstream ify(filename.c_str());

			vector <int> union2;
			string s;
			while (ify >> s)
			{
				union2.push_back(stoi(s));
			}

			sort(union2.begin(), union2.end());
			union2.erase(unique(union2.begin(), union2.end()), union2.end());
			sort(set.begin(), set.end());
			set.erase(unique(set.begin(), set.end()), set.end());

			int x;
			if (union2.size() > set.size())
			{
				x = 2 * union2.size();
			}
			else
			{
				x = 2 * set.size();
			}
			vector <int> set2(x);
			std::vector<int>::iterator it;
			it = std::set_intersection(union2.begin(), union2.end(), set.begin(), set.end(), set2.begin());
			set2.resize(it - set2.begin());

			set.clear();

			for (int i = 0; i < set2.size(); i++)
			{
				set.push_back(set2[i]);
			}
			set2.clear();
			ify.close();
		}

	}

	//this displays the result of the entire function 
	showInfix();
	for (int i = 0; i < set.size(); i++)
	{
		cout << set[i] << " ";
	}
}
string infixToPostfix::getPfx() {
	return pfx;
}
void infixToPostfix::setpfx(string p) {
	pfx = p;
}