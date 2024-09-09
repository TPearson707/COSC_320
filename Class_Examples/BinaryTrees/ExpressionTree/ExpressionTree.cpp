#include <iostream>
#include <cstdlib>

#include "Function.h"

using namespace std;

void PrintMenu();

int main() {
	Function f, fdiff;
	char c;
	char buf[1000];
	int quit = 0, error = 0;
	double xval, ans;

	do {
		PrintMenu();

		cout << "Make a Selection: ";
		cin >> c;
		cin.getline(buf, 1000, '\n');

		switch (c) {
		case '1':
			cout << "\n";
			cout << "Input an expression: ";
			cin >> f;
			cin.getline(buf, 1000, '\n');
			fdiff = f.differentiate();
			break;
		case '2':
			cout << "\n";
			cout << "Input a real number: ";
			cin >> xval;
			cin.getline(buf, 1000, '\n');
			ans = f.Evaluate(xval, error);
			if (error)
				cout << "There was a numeric error during evaluation. \n";
			else
				cout << "The function value is " << ans << endl;
			break;
		case '3':
			cout << "\n" << f << "\n";
			break;
		case '4':
			cout << "\n";
			f.PrintFunctionTree();
			cout << "\n";
			break;
		case '5':
			cout << "\n";
			f.PrintFunctionPostfix();
			cout << "\n";
			break;
		case '6':
			cout << "\n";
			cout << "Input a real number: ";
			cin >> xval;
			cin.getline(buf, 1000, '\n');
			ans = fdiff.Evaluate(xval, error);
			if (error)
				cout << "There was a numeric error during evaluation.\n";
			else
				cout << "The value of the derivative is " << ans << endl;
			break;
		case '7':
			cout << "\n" << fdiff << "\n";
			break;
		case '8':
			cout << "\n";
			fdiff.PrintFunctionTree();
			cout << "\n";
			break;
		case '9':
			cout << "\n";
			fdiff.PrintFunctionPostfix();
			cout << "\n";
			break;
		case 'q':
		case 'Q':
			quit = 1;
			break;
		default:
			cout << "\n\nInvalid Input \n\n";
		}
	} while (!quit);

	return 0;
}

void PrintMenu() {
	cout << "\n";
	cout << "(1)  Input Function (no spaces)" << "\n";
	cout << "(2)  Evaluate Function" << "\n";
	cout << "(3)  Print Function" << "\n";
	cout << "(4)  Print Function Tree" << "\n";
	cout << "(5)  Print Function Postfix" << "\n";
	cout << "(6)  Evaluate Derivative of Function" << "\n";
	cout << "(7)  Print Derivative Function" << "\n";
	cout << "(8)  Print Derivative Function Tree" << "\n";
	cout << "(9)  Print Derivative Function Postfix" << "\n";
	cout << "(Q)  Quit" << "\n\n";
}

