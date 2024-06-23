#include	<iostream>
#include	<fstream>
#include	<string>
#include	"List.h"
#include	"Student.h"

using namespace std;

bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool DisplayStudent(List, int);
bool AddExamResult(const char*, List*);
bool FilterStudent(List, List*, char*, int, int);
bool recalculateResult(List, char*);
bool checkEligibleFYP(List, char*);
int menu();
const char* getGrade_new(double);
double getGradePoint_new(double);
string convertToString(char*, int);

int main() {
	int option, cont, source, year, totalcredit;
	char filename[20], course[3], id[12];
	List list;
	List list1;
	do {
		option = menu();
		system("cls");
		if (option == 1) {
			cout << "Please key in filename to input student data (with.txt): ";
			cin >> filename;
			CreateStuList(filename, &list);
		}
		else if (option == 2) {
			cout << "Please key in the student id: ";
			cin >> id;
			DeleteStudent(&list, id);
		}
		else if (option == 3) {
			cout << "Display information to screen or file (1-screen, 2-file): ";
			cin >> source;
			system("cls");
			DisplayStudent(list, source);
		}
		else if (option == 4) {
			cout << "Please key in filename to input exam data (with.txt): ";
			cin >> filename;
			AddExamResult(filename, &list);

		}
		else if (option == 5) {
			cout << "Enter the student id to recalculate result based on revised grading: ";
			cin >> id;
			recalculateResult(list, id);

		}
		else if (option == 6) {
			cout << "Please key in the details that want to be filtered accordingly: " << endl;
			cout << "Course: ";
			cin >> course;
			cout << "Year: ";
			cin >> year;
			cout << "Total Credit: ";
			cin >> totalcredit;
			FilterStudent(list, &list1, course, year, totalcredit);
		}
		else if (option == 7) {
			cout << "Enter the student id to check if eligible to take FYP: ";
			cin >> id;
			checkEligibleFYP(list, id);

		}
		else if (option == 8) {
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

bool CreateStuList(const char* filename, List* list) {
	Student student;
	string line;
	int count = 1;
	ifstream inputfile;
	inputfile.open(filename);
	bool check_duplicate = false;
	if (inputfile.is_open()) {
		// Just wanna get exact value from line
	  // found is the position of "="
	  // found+2 means 2nd character after "=", 1st is space  
		size_t found;
		while (!inputfile.eof()) {
			getline(inputfile, line);
			found = line.find("=");
			//substr = substring, means extract part of text from original string
		  // 1st parameter is beginning position of the substring; 2nd is length of substring
			strcpy(student.id, line.substr(found + 2, 12).c_str());
			getline(inputfile, line);
			found = line.find("=");
			strcpy(student.name, line.substr(found + 2, 30).c_str());
			getline(inputfile, line);
			found = line.find("=");
			strcpy(student.course, line.substr(found + 2, 2).c_str());
			getline(inputfile, line);
			found = line.find("=");
			strcpy(student.phone_no, line.substr(found + 2, 10).c_str());
			getline(inputfile, line);
			for (Node* cur = list->head; cur != NULL; cur = cur->next) {
				if (strcmp(student.id, cur->item.id) == 0) {
					cout << "\nError!! Duplicate record " << endl;
					check_duplicate = true;
					break;
				}
			}
			if(!check_duplicate){
				list->insert(count, student);
				count++;
			}
		}
		inputfile.close();
		cout << "\nStudent list has successfully created" << endl;
		return true;
	}
	else {
		cout << "\nUnable to open the file" << endl;
		return false;
	}
}

bool DeleteStudent(List* list, char* id) {
	bool check = false;
	Student s;
	if (list->empty()) {
		cout << "\nThe list is empty. Please insert something into the list." << endl;
		return false;
	}
	for (int i = 1; i <= list->size(); i++) {
		list->get(i, s);
		if (strcmp(id, s.id) == 0) {
			cout << "\nStudent id " << id << " found and successfully removed." << endl;
			list->remove(i);
			check = true;
			return check;
		}
	}
	if (!check) {
		cout << "\nUnable to find the id" << endl;
		check = false;
		return check;
	}
}

bool DisplayStudent(List list, int source) {
	Student s;
	Exam exam;
	if (source == 1) {
		if (list.empty()) {
			cout << "\nThe list is empty. Please insert something into the list." << endl;
			return false;
		}
		for (int i = 1; i <= list.size(); i++) {
			list.get(i, s);
			cout << "******************************************************Student " << i << "******************************************************";
			s.print(cout);
			if (s.exam_cnt == 0) {
				cout << "THIS STUDENT HAVEN'T TAKEN ANY EXAM YET" << endl;
				cout << endl;
			}
			else {
				cout << "Number of past exam: " << s.exam_cnt << endl;
				cout << "\n*****************************************************PAST EXAM RESULT*****************************************************\n";
				for (int j = 0; j < s.exam_cnt; j++) {
					s.exam[j].print(cout);
				}
			}
		}
	}
	else if (source == 2) {
		if (list.empty()) {
			cout << "\nThe list is empty. Please insert something into the list." << endl;
			return false;
		}
		ofstream outFile;
		outFile.open("student_result.txt");
		for (int i = 1; i <= list.size(); i++) {
			list.get(i, s);
			outFile << "******************************************************Student " << i << "******************************************************";
			s.print(outFile);
			if (s.exam_cnt == 0) {
				outFile << "THIS STUDENT HAVEN'T TAKEN ANY EXAM YET" << endl;
				outFile << endl;
			}

			else {
				outFile << "Number of past exam: " << s.exam_cnt << endl;
				outFile << "\n*****************************************************PAST EXAM RESULT*****************************************************\n";
				for (int j = 0; j < s.exam_cnt; j++) {
					s.exam[j].print(outFile);
				}
			}
		}
		outFile.close();
		cout << "File has been successfully created" << endl;
	}
	else {
		cout << "Invalid input" << endl;
		return false;
	}
	return true;
}

bool AddExamResult(const char* filename, List* list) {
	Exam exam;
	Student s;
	char id[12];
	ifstream inFile;
	inFile.open(filename);
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			inFile >> id;
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, s);
				if (strcmp(id, s.id) == 0) {
					inFile >> exam.trimester;
					inFile >> exam.year;
					inFile >> exam.numOfSubjects;
					for (int j = 0; j < exam.numOfSubjects; j++) {
						inFile >> exam.sub[j].subject_code >> exam.sub[j].subject_name >> exam.sub[j].credit_hours >> exam.sub[j].marks;
					}
					for (Node* cur = list->head; cur != NULL; cur = cur->next) {
						if (strcmp(cur->item.id, id) == 0) {
							cur->item.exam[cur->item.exam_cnt++] = exam;
							cur->item.exam[s.exam_cnt].calculateGPA();
							cur->item.calculateCurrentCGPA();
						}
					}

					inFile.ignore();
				}
			}
		}
		inFile.close();
		cout << "\nThe exam data has successfully added into the list." << endl;
		return true;
	}
	else {
		cout << "\nUnable to open the file" << endl;
		return false;
	}
}

bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit) {
	Student s;
	Exam exam;
	int last_2digityear = year - 2000;
	int id_size = sizeof(s.id) / sizeof(char);
	string s_id;
	bool filter=false;
	if (list1.empty()) {
		cout << "The list is empty. Please insert something into the list." << endl;
		return false;
	}
	
	else{
		for (int i = 1; i <= list1.size(); i++) {
		list1.get(i, s);
		s_id = convertToString(s.id, id_size); //convert char to string then convert to int
		if ((strcmp(course, s.course) == 0) && (last_2digityear == stoi(s_id)) && (s.totalCreditsEarned >= totalcredit)) {
					if (!list2->empty()) {
						cout << "The list 2 is not empty." << endl;
						return false;
					}
					else{
						list2->insert(s);
						system("cls");
						DisplayStudent(*list2, 1);
						filter = true;
						return filter;
					}
		}
		else{
			filter = false;
		}
			}
	if(!filter){
		cout<<"\nCannot filter any student with these data."<<endl;
	}
	}
}

bool recalculateResult(List list, char* id) {
	Student s;
	Exam exam;
	Subject sub;
	bool check = false;
	double sum = 0;
	int total_credit_hours = 0;
	if (list.empty()) {
		cout << "The list is empty. Please insert something into the list." << endl;
		return false;
	}
	for (int i = 1; i <= list.size(); i++) {
		list.get(i, s);
		if (strcmp(id, s.id) == 0) {
			if (s.exam_cnt == 0) {
				cout << "\nTHIS STUDENT HAVEN'T TAKEN ANY EXAM YET." << endl;
				cout << endl;
			}
			else {
				cout << endl;
				cout << "RESULT OUTPUT BASED ON ORIGINAL GRADING:" << endl;
				cout << "________________________________________";
				s.print(cout);
				cout << "\n-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------\n";
				for (int j = 0; j < s.exam_cnt; j++) {
					s.exam[j].print(cout);
				}
				cout << "\n-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------\n";
				cout << endl;
				double* gpa_new = nullptr;
				for (int z = 0; z < s.exam_cnt; z++) {
					for (int y = 0; y < s.exam[z].numOfSubjects; y++) {
						sum = sum + getGradePoint_new(s.exam[z].sub[y].marks) * s.exam[z].sub[y].credit_hours;
						total_credit_hours = total_credit_hours + s.exam[z].sub[y].credit_hours;
					}
					s.exam[z].gpa = sum / (double)total_credit_hours;
					gpa_new = &s.exam[z].gpa;
				}
				cout << "RESULT OUTPUT BASED ON REVISED GRADING:" << endl;
				cout << "________________________________________";
				cout << "\n\nName: " << s.name;
				cout << "\nId: " << s.id;
				cout << "\nCourse: " << s.course;
				cout << "\nPhone No: " << s.phone_no;
				cout << "\nCurrent CGPA: " << *gpa_new;
				cout << "\nTotal Credits Earned: " << s.totalCreditsEarned;
				cout << endl;
				cout << "\n-----------------------------------------------REVISED GRADING EXAM RESULT:-------------------------------------------------\n";
				for (int z = 0; z < s.exam_cnt; z++) {
					sum = 0;
					total_credit_hours = 0;
					cout << "\n\n" << s.exam[z].printTrimester() << " " << s.exam[z].year << " Exam Results: " << endl;
					cout << "\n" << s.exam[z].numOfSubjects << " subjects taken.";
					cout << "\n___________________________________________________________________________________________________________________________";
					cout << "\nSubject Code\t" << setw(70) << left << "Subject Name" << "Credit Hours" << "\tGrade " << "\tGrade Point";
					cout << "\n___________________________________________________________________________________________________________________________";
					cout << "\n";
					for (int y = 0; y < s.exam[z].numOfSubjects; y++) {
						int marks = s.exam[z].sub[i].marks;
						cout << s.exam[z].sub[y].subject_code << "\t" << setw(70) << left << s.exam[z].sub[y].subject_name << setw(7) << right << s.exam[z].sub[y].credit_hours <<
							"\t" << setw(10) << left << " " << getGrade_new(s.exam[z].sub[y].marks) << "\t  " << setprecision(5) << fixed << showpoint << getGradePoint_new(s.exam[z].sub[y].marks) << endl;
						sum = sum + getGradePoint_new(s.exam[z].sub[y].marks) * s.exam[z].sub[y].credit_hours;
						total_credit_hours = total_credit_hours + s.exam[z].sub[y].credit_hours;
					}
					s.exam[z].gpa = sum / (double)total_credit_hours;
					cout << "GPA: " << s.exam[z].gpa;
					cout << "\n\n";
				}
				cout << "\n-----------------------------------------------REVISED GRADING EXAM RESULT:-------------------------------------------------\n";
				cout << endl;
				check = true;
				return check;
			}

		}
	}

	if (!check) {
		cout << "\nThere is no student with id " << id << " in the list." << endl;
		cout << "Cannot recalculate result." << endl;
		check = false;
		return check;
	}
}

bool checkEligibleFYP(List list, char* id) {
	bool check_1 = false, check_2 = false, final_check = false, found = false;
	Student s;
	Subject subject;
	Exam exam;
	char newGrade_1[3];
	char newGrade_2[3];
	char course_code_1[] = "UCCD2502", course_code_2[] = "UCCD2513";
	for (int i = 1; i <= list.size(); i++) {
		list.get(i, s);
		if (strcmp(id, s.id) == 0) {
			found = true;
			for (int j = 0; j <= s.exam_cnt; j++) {
				for (int z = 0; z < s.exam[j].numOfSubjects; z++) {
					int result_1 = strcmp(s.exam[j].sub[z].subject_code, course_code_1);
					if ((result_1 == 0) && (s.exam[j].sub[z].marks >= 50 || s.exam[j].sub[z].marks <= 100)) {
						strcpy(newGrade_1, s.exam[j].sub[z].getGrade());
						check_1 = true;
						break;
					}
				}
				for (int z = 0; z < s.exam[j].numOfSubjects; z++) {
					int result_2 = strcmp(s.exam[j].sub[z].subject_code, course_code_2);
					if ((result_2 == 0) && (s.exam[j].sub[z].marks >= 50 || s.exam[j].sub[z].marks <= 100)) {
						strcpy(newGrade_2, s.exam[j].sub[z].getGrade());
						check_2 = true;
						break;
					}
				}
				if ((check_1 == true && check_2 == true) && (s.totalCreditsEarned >= 30)) {
					cout << "This student is eligible to take FYP. Below are the detailes of the students:" << endl;
					s.print(cout);
					cout << "\nGrade obtained for UCCD2502 Introduction to Inventive Problem Solving is " << newGrade_1 << endl;
					cout << "Grade obtained for UCCD2513 Mini Project is " << newGrade_2 << endl;
					final_check = true;
					return final_check;
				}
			}
			if (!final_check) {
				cout << "\nThis student " << s.name << " is not eligible to register for FYP yet." << endl;
				final_check = false;
				return final_check;
			}
		}
	}
	if (!found) {
		cout << "\nThere is no student with id " << id << " in the list." << endl;
		cout << "\nCannot check if student is eligible for FYP." << endl;
		return false;
	}
}

int menu() {
	string option;
	cout << "Menu" << endl;
	cout << endl;
	cout << "1. Create student list" << endl;
	cout << "2. Delete student" << endl;
	cout << "3. Print student list" << endl;
	cout << "4. Add exam resutlt" << endl;
	cout << "5. Recalculate Result" << endl;
	cout << "6. Filter Student" << endl;
	cout << "7. Check Eligible FYP Student" << endl;
	cout << "8. Exit." << endl;
	cout << "Choice: ";
	cin >> option;
	if (isdigit(option[0]) && option.length() == 1) {
		return option[0] - '0';
	}
}

const char* getGrade_new(double marks) {

	if (marks >= 0 && marks < 36)
		return "F";
	else if (marks >= 36 && marks < 41)
		return "E";
	else if (marks >= 41 && marks < 46)
		return "D-";
	else if (marks >= 46 && marks < 56)
		return "D";
	else if (marks >= 56 && marks < 61)
		return "C";
	else if (marks >= 61 && marks < 66)
		return "C+";
	else if (marks >= 66 && marks < 71)
		return "B-";
	else if (marks >= 71 && marks < 76)
		return "B";
	else if (marks >= 76 && marks < 81)
		return "B+";
	else if (marks >= 81 && marks < 86)
		return "A-";
	else if (marks >= 86 && marks <= 100)
		return "A";
	else
		return "N/A";
}

double getGradePoint_new(double marks) {
	if (marks >= 0 && marks < 36)
		return 0.00;
	else if (marks >= 36 && marks < 41)
		return 1.00;
	else if (marks >= 41 && marks < 46)
		return 1.33;
	else if (marks >= 46 && marks < 56)
		return 1.67;
	else if (marks >= 56 && marks < 61)
		return 2.00;
	else if (marks >= 61 && marks < 66)
		return 2.30;
	else if (marks >= 66 && marks < 71)
		return 2.7;
	else if (marks >= 71 && marks < 76)
		return 3.00;
	else if (marks >= 76 && marks < 81)
		return 3.30;
	else if (marks >= 81 && marks < 86)
		return 3.70;
	else if (marks >= 86 && marks <= 100)
		return 4.00;
	else
		return -1.0;
}

string convertToString(char* arr, int size) {
	int i;
	string s = "";
	for (i = 0; i < 2; i++) {
		s = s + arr[i];
	}
	return s;
}


