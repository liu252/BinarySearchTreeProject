#include "BST.h"
#include "Database.h"
#include "Student.h"

#include <iostream>
#include <string>

using namespace std;

int main(){

		Database data;
		int select;			//user input for options
		int selectAgain;	//user input to repeat
		bool check;			//check if user exits


		data.loadRecords();	//Load all records
        cout<<"Welcome to myDatabase!"<<endl;
		bool again = true;
		while(again){
				check = true;
				cout << "\n\nSelect an Option Below: " << endl;
				cout << "\t1) Print all students and their information "<< endl;
				cout << "\t2) Print all faculty and their information  " << endl;
				cout << "\t3) Find and display student information given the students ID  " << endl;
				cout << "\t4) Find and display faculty information given the faculty ID    " << endl;
				cout << "\t5) Given a student's ID, print the name and information their faculty advisor   " << endl;	
				cout << "\t6) Given a faculty ID, print all the names and information of his/her advisees "  << endl;	
				cout << "\t7) Add a new student " << endl;
				cout << "\t8) Delete a student, given an ID  "<< endl;
				cout << "\t9) Add new faculty member "<< endl;
				cout << "\t10) Delete a faculty member, given an ID  "<< endl;
				cout << "\t11) Change a student's advisor given the student ID and new faculty ID   " << endl;
				cout << "\t12) Remove an advisee from a faculty member given the IDs	  " << endl;
				cout << "\t13) Rollback " << endl;
				cout << "\t14) Exit\n"  << endl;
				cout << "Enter: ";
				cin >> select;
				
				switch(select){
						case 1: 
								data.optionOne();
								break;
						case 2:
								data.optionTwo();
								break;
						case 3: 
								data.optionThree();
								break;
						case 4:
								data.optionFour();
								break;
						case 5:
								data.optionFive();
								break;
						case 6:
								data.optionSix();
								break;
						case 7:
                                data.saveStudentRollBack();
								data.optionSeven();
								break;
						case 8:
								data.saveStudentRollBack();
								data.optionEight();
								break;
						case 9:
								data.saveFacultyRollBack();
								data.optionNine();
								break;
						case 10:
								data.saveFacultyRollBack();
								data.optionTen();
								break;
						case 11:
								data.saveStudentRollBack();
								data.saveFacultyRollBack();
								data.optionEleven();
								break;
						case 12:
								data.saveStudentRollBack();
								data.saveFacultyRollBack();
								data.optionTwelve();
								break;
						case 13:
								data.optionThirteen();
								break;
						case 14:
								cout << " --- Exiting --- " << endl;
								again = false; check = false;
								break;
						default: 
								cout << "\n- Error: Invalid Input -" << endl;
								break;
			}

			if(check){
					cout << "\nWould you like to:\n\t1) Continue\n\t2) Exit\nEnter: ";
                
					cin >> selectAgain;
                while(cin.fail()) {
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> selectAgain;
                    cout<<"Invalid Input"<<endl;
                    cout<<"Enter 1 or 2: ";
                }
					if(selectAgain == 1)
                        again = true;
                    else if (selectAgain == 2) {
                     again = false;
                        system(EXIT_SUCCESS);
                    }
			}
		}
		data.saveStudentRecords();	//overwrite file each time
		data.saveFacultyRecords();  //overwrite file each time
		return 0;



}
