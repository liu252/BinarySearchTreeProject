#ifndef Faculty_H
#define Faculty_H

#include "Student.h"
#include "BST.h"
#include <iostream>
#include <string>


using namespace std;


class Faculty
{
public:
		Faculty(){
				facultyID = 0;
				facultyName = "0";
				facultyLevel = "0";
				facultyDepartment = "0"; 
		}


		Faculty(int id, string name, string level, string department, int advisees){
					facultyID = id; 
					facultyName = name;
					facultyLevel = level;
					facultyDepartment = department;
					addAdvisee(advisees);
		}

		Faculty(int id): facultyID(id), facultyName("name"), facultyLevel("level"), 
				facultyDepartment("department"), facultyAdvisees() {}


		void addAdvisee(int s);
		void deleteAdvisee(int s);
		void printAdvisees();
		string returnAdvisorName(void);

		void saveAdvisees(ostream &out);

		bool operator>( Faculty &other);   // overload greater sign for student
		bool operator<( Faculty &other);	//overload less function for student
		bool operator==( Faculty &other);	//overlaod equal function for student
		bool operator!=( Faculty &other);   //overload not equal function for student
		friend ostream &operator<<(ostream &out, Faculty f); // overload for output


private:
		int facultyID;
		string facultyName;
		string facultyLevel;
		string facultyDepartment;
		BST<int> facultyAdvisees;

};

#endif



