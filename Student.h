#ifndef Student_H
#define Student_H

#include <iostream>
#include <string>


using namespace std;

class Student
{
public:

		Student(){
				studentID = 0;
				studentName = "0";
				studentClass = "0";
				studentMajor = "0"; 
				studentGPA = 0.00;
				studentAdvisor = 0;
		}

		Student(int id, string name, string level, string major, double gpa, int advisor):
		studentID(id), studentName(name), studentClass(level), studentMajor(major), studentGPA(gpa), studentAdvisor(advisor) {}

		Student(int id): studentID(id), studentName("name"), studentClass("level"), studentMajor("major"), studentGPA(0.00), studentAdvisor(-1) {}

		
		string returnStudentName(void);
		string returnStudentClass(void);
		string returnStudentMajor(void);
		int returnID(void);
		double returnStudentGPA(void);
		int returnStudentAdvisor(void);

		bool operator>( Student &other);   // overload greater sign for student
		bool operator<( Student &other);	//overload less function for student
		bool operator==( Student &other);	//overlaod equal function for student
		bool operator!=( Student &other);   //overload not equal function for student
		friend ostream &operator<<(ostream &out, Student s); // overload for output


private:
		int studentID;
		string studentName;
		string studentClass;
		string studentMajor;
		double studentGPA;
		int studentAdvisor;
};

#endif



