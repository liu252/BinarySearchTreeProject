#include "Student.h"

using namespace std;


int Student::returnID(void){
		return studentID;
}

int Student::returnStudentAdvisor(void){
		return studentAdvisor;
}

string Student::returnStudentName(void){
		return studentName;
}

string Student::returnStudentClass(void){
		return studentClass;
}

double Student::returnStudentGPA(void){
		return studentGPA;
}

string Student::returnStudentMajor(void){
		return studentMajor;
}

bool Student::operator>( Student &other) {
 	 	return(studentID > other.studentID);
}

bool Student::operator<( Student &other) {
 		 return(studentID < other.studentID);
}

bool Student::operator==( Student &other) {
 		 return(studentID == other.studentID);	
}

bool Student::operator!=( Student &other) {
		return(studentID != other.studentID);
}

ostream &operator<<(ostream &out, Student s) {
		out<<"__________________________________________\n";
		out<<"Student ID	:"<<s.studentID << endl;
		out<<"Student Name	:"<<s.studentName << endl;
		out<<"Student Class	:"<<s.studentClass << endl;
		out<<"Student Major	:"<<s.studentMajor << endl;
		out<<"Student GPA	:"<<s.studentGPA << endl;
		out<<"Student Adv.	:"<<s.studentAdvisor << endl;
		out<<"__________________________________________\n";

		return(out);
}
