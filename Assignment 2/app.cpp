#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<cstring>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();

int main() {
	int option,cont, source, order;
	char filename[20];
	BST t1,t2;
	Student student;
	do {
		option = menu();
		system("cls");
		if (option == 1) {
			cout << "Please key in filename to input student data (with.txt): ";
			cin >> filename;
			system("cls");
			readFile(filename, &t1);
		}
		else if (option == 2) {
			t1.deepestNodes();
		}
		else if (option == 3) {
			cout << "Display information in which order (1-Ascending, 2-Descending): ";
			cin>>order;
			cout << "Display information to screen or file (1-Screen, 2-File): ";
			cin >> source;
			system("cls");
			t1.display(order, source);
		}
		else if (option == 4) {
			cout<<"Please key in a student id: ";
			cin>>student.id;
			system("cls");
			t2.CloneSubTree(t1,student);
		}
		else if (option == 5) {
			t1.printLevelNodes();

		}
		else if (option == 6) {
			t1.printPath();
		}
		else if (option == 7) {
			break;
		}

		else {
			cout << "Invalid!" << endl;
		}
		cout << "\nContinue? (1-yes, 2-no): ";
		cin >> cont;

		system("cls");
	} while (cont == 1);

	cout << "Thanks for using this program" << endl;

	return 0;
}
bool readFile(const char *filename, BST *t1){
	char temp;
	Student student;
	ifstream readFile;
	readFile.open(filename);
	if (readFile.fail()) {
		cout << "\nUnable to open the file" << endl;
		readFile.close();
		return false;
	}
	else{
	while (!readFile.eof()) {
		do {
			readFile >> temp;
		} while (temp != '='); // read until '='
		readFile >> student.id;
		do {
			readFile >> temp;
		} while (temp != '=');
		readFile.get();
		readFile.getline(student.name, 30);
		do {
			readFile >> temp;
		} while (temp != '=');
		readFile.getline(student.address, 100);
		do {
			readFile >> temp;
		} while (temp != '=');
		readFile>>student.DOB;
		do {
			readFile >> temp;
		} while (temp != '=');
		readFile>>student.phone_no;
		do {
			readFile >> temp;
		} while (temp != '=');
		readFile>>student.course;
		do {
			readFile >> temp;
		} while (temp != '=');
		readFile>>student.cgpa;
			
		t1->insert(student);
	}
	readFile.close();
		//t1->topDownLevelTraversal();
		cout << "Student list has successfully created" << endl;
		cout<< "There are "<< t1->count <<" students in system."<<endl;
	return true;	
}	
}

int menu() {
	string option;
	cout << "Menu" << endl;
	cout << endl;
	cout << "1. Read data to BST" << endl;
	cout << "2. Print deepest nodes" << endl;
	cout << "3. Display student" << endl;
	cout << "4. Clone Subtree" << endl;
	cout << "5. Print Level Nodes" << endl;
	cout << "6. Print Path" << endl;
	cout << "7. Exit." << endl;
	cout << "Choice: ";
	cin >> option;
	if (isdigit(option[0]) && option.length() == 1) {
		return option[0] - '0';
	}
} 
