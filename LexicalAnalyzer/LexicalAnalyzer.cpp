// In The Name Of Allah
// Name : Lexical Analyzer
// Porpuse : Analyzing A File Lexically
// Programmers : Ali Salimi, Mohammadamin Izadi, Ali Sarabadani

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

// declaration of functions
string type(string);
string isId(string);
string isNum(string);
string isStr(string);
string isSign(string);

// declaration of keywords, operators and signs
const int sizeOfKey = 8;
string key[sizeOfKey] = { "int", "double", "while", "for", "if", "else", "switch", "case" }; // Keywords
const int sizeOfOp = 12;
string op[sizeOfOp] = { "+", "-", "*", "/", "%", "=", "==", "!=", ">", ">=", "<", "<=" }; // Operators
const int sizeOfSi = 6;
string si[sizeOfSi] = { "(", ")", "{", "}", ",", ";" }; // Signs
/* Note : If you want to change content of arrays you should change sizeOf variables ,too.
To set size of arrays into sizOf variables.*/

int e; // number of errors

// main function : running the program
int main()
{
	// start
	cout << "In The Name Of Allah\n" << endl;
	cout << "Lexical Analzer\n" << endl;
	cout << "Input : input.next file (in location of source code)\n" << endl;

	// declarations
	ifstream in("input.txt"); // input file
	string tok[1000]; // sequence of tokens
	string t; // temp string
	int a = 0;
	char ch = 1;
	e = 0;

	// creating sequence of tokens
	while (ch)
	{
		ch = 0;
		in.get(ch);
		if ( ch == ' ' || ch == '\t' || ch == '\n' || ch == 0 )
		{
			if (t != "")
			{
				tok[a] = type(t);
				a++;
			}
			t = "";
		}
		else
		{
			t = t + ch;
		}
	}

	in.close();
	
	// displaying sequence of tokens
	cout << "\nSequence Of Tokens :\n" << endl;
	for (int i = 0; i < a; i++)
		cout << tok[i] << endl;

	// displaying number of errors
	cout << "\n\nNumber Of Errors : " << e << endl;

	// end
	cout << "\n\nPress any key to exit...";
	_getch();

	return EXIT_SUCCESS;
}

// type function : returning type of string ( returning a token )
string type(string s)
{
	if ((s[0] >= 65 && s[0] <= 90) || (s[0] >= 97 && s[0] <= 122) || s[0] == 95)
		return isId(s);
	else if (s[0] >= 48 && s[0] <= 57)
		return isNum(s);
	else if (s[0] == 34 || s[0] == 39)
		return isStr(s);
	else
		return isSign(s);
}

// isId function : determining that a string is a identifier or not or is a keyword
string isId(string s)
{
	int i = 0;
	int state = 0;
	while (i < static_cast<int>(s.length()))
	{
		switch (state)
		{
		case 0:
			if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122) || s[i] == 95)
				state = 1;
			else
			{
				e++;
				return "error-" + s;
			}
			break;

		case 1:
			if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122) || s[i] == 95 || (s[i] >= 48 && s[i] <= 57))
				state = 1;
			else
			{
				e++;
				return "error-" + s;
			}
			break;
		}

		i++;
	}

	if (state == 0)
	{
		e++;
		return "error-" + s;
	}

	for (int j = 0; j < sizeOfKey; j++)
	if (s == key[j])
		return "keyword";

	return "identifier";
}

// isNum function : determining that a string is a number or not and is a integer or float
string isNum(string s)
{
	int i = 0;
	int state = 0;

	while (i < static_cast<int>(s.length()))
	{
		switch (state)
		{
		case 0:
			if (s[i] >= 48 && s[i] <= 57)
				state = 1;
			else
			{
				e++;
				return "error-" + s;
			}
			break;

		case 1:
			if (s[i] >= 48 && s[i] <= 57)
				state = 1;
			else if (s[i] == 46)
				state = 2;
			else
			{
				e++;
				return "error-" + s;
			}
			break;

		case 2:
			if (s[i] >= 48 && s[i] <= 57)
				state = 3;
			else
			{
				e++;
				return "error-" + s;
			}
			break;

		case 3:
			if (s[i] >= 48 && s[i] <= 57)
				state = 3;
			else
			{
				e++;
				return "error-" + s;
			}
			break;
		}

		i++;
	}

	if (state == 0 || state == 2)
	{
		e++;
		return "error-" + s;
	}
	if (state == 1)
		return "literal-number-integer";
	return "literal-number-float";
}

// isStr function : determining that a string is a literal string or not
string isStr(string s)
{
	int i = 0;
	int state = 0;

	while (i < static_cast<int>(s.length()))
	{
		switch (state)
		{
		case 0:
			if (s[i] == 34)
				state = 1;
			else if (s[i] == 39)
				state = 3;
			else
			{
				e++;
				return "error-" + s;
			}
			break;

		case 1:
			if (s[i] == 34)
				state = 2;
			else
				state = 1;
			break;

		case 2:
			e++;
			return "error-" + s;
			break;

		case 3:
			if (s[i] == 39)
				state = 2;
			else
				state = 4;
			break;

		case 4:
			if (s[i] == 39)
				state = 2;
			else
			{
				e++;
				return "error-" + s;
			}
			break;
		}

		i++;
	}
	
	if (state == 2)
		return "literal-string";
	e++;
	return "error-" + s;
}

// isSign function : determining that a string is a sign or operator or not
string isSign(string s)
{
	for (int i = 0; i < sizeOfOp; i++)
		if (s == op[i])
			return "operator-" + op[i];

	for (int i = 0; i < sizeOfSi; i++)
		if (s == si[i])
			return "sign-" + si[i];

	e++;
	return "error-" + s;
}