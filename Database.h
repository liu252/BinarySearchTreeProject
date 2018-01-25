#ifndef Database_H
#define Database_H


#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>

using namespace std;

class Database{
public:
		Database();
		void optionOne();		//Print all student records
		void optionTwo();	    //Print all faculty records
		void optionThree();     //Find and display one student
		void optionFour();      //Find and display one faculty
		void optionFive();		//Find and display faculty information of a given student with an ID 
		void optionSix();		//Print faculty member advisees
		void optionSeven();		//Add a student to the records
		void optionEight();		//Fine a delete a student
		void optionNine();		//Add new faculty member to the records
		void optionTen();		//Fine and delete a faculty member
		void optionEleven();	//Change student's advisor
		void optionTwelve();	//Remove advisee from a faculty member
		void optionThirteen(); 	//Roll Back
		void saveFacultyRecords();  //Save faculty records to facultyTable.txt
		void saveStudentRecords();	//Save student records to studentTable.txt
		void saveStudentRollBack();	//Saves Roll Back information
		void saveFacultyRollBack();	//Saves Roll Back information
		void loadRecords();			//Load all records

		virtual ~Database();
};

#endif
