#include "ukulele.h"
#include "customErrorClass.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) 
{

	Ukulele uke;
	string root = "", type = "";

	cout << "Root note:" << endl;
	cin >> root;

	cout << "Chord type (M, m):" << endl;
	cin >> type;

	/*
	uke.printFretboardTones();
	cout << endl;
	uke.printFretboardNotes();
	*/

	try 
	{
		uke.printChord(root, type);
	}
	catch (myException &e)
	{
		cerr << e.what() << endl;
	}
}