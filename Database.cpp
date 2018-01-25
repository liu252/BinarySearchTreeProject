#include "Database.h"
#include <sstream>
#include <string>

using namespace std;

BST<Student> studentTree;
BST<Faculty> facultyTree;
BST<Student> sRollBackTreeOne;
BST<Student> sRollBackTreeTwo;
BST<Student> sRollBackTreeThree;
BST<Student> sRollBackTreeFour;
BST<Student> sRollBackTreeFive;
BST<Faculty> fRollBackTreeOne;
BST<Faculty> fRollBackTreeTwo;
BST<Faculty> fRollBackTreeThree;
BST<Faculty> fRollBackTreeFour;
BST<Faculty> fRollBackTreeFive;
int sCount = 0;
int fCount = 0;


Database::Database(){
}
 

//print stu record
void Database::optionOne(){
		cout << "              STUDENT RECORDS           " << endl;
		cout <<"------------------------------------------\n" << endl;

		if(studentTree.isEmpty())
            cout << "Student Records Empty\n" << endl;
		else
            studentTree.printTree();
}

//print fac records
void Database::optionTwo(){
		cout << "                   FACULTY RECORDS           " << endl;
		cout <<"-------------------------------------------------\n" << endl;

		if(!facultyTree.isEmpty())
            facultyTree.printTree();
		else
            cout << "\nFaculty Records Empty" << endl;
}

//display one student record
void Database::optionThree(){
		int studentID;
		cout << "            Find Student 		  " << endl;
		cout << "-----------------------------------  " << endl;
		cout << "\nEnter Student ID Number: ";
		cin >> studentID;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(256,'\n');
        cin >> studentID;
        cout<<"Invalid Input"<<endl;
        cout<<"Enter the ID number: ";
    }
    
    if(studentTree.contains(studentID))
            return studentTree.displayNode(studentID);
		
		else
            cout << "\n- Student Does Not Exist -" << endl;
}

//display one fac record
void Database::optionFour(){
		int facultyID;

		cout << "           Find Faculty 		  " << endl;
		cout << "-----------------------------------  " << endl;

		cout << "\nEnter Faculty ID Number: ";
		cin >> facultyID;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(256,'\n');
        cin >> facultyID;
        cout<<"Invalid Input"<<endl;
        cout<<"Enter the ID number: ";
    }

		if(facultyTree.contains(facultyID))
            facultyTree.displayNode(facultyID);
		
		else
            cout << "\n- Faculty Does Not Exist -" << endl;
}

//find fac advisor of student
void Database::optionFive(){
		int studentID;
		
		cout << "       Find Faculty of Student 		  " << endl;
		cout << "-----------------------------------  " << endl;
		
		cout << "\nEnter Student ID Number: ";
		cin >> studentID;
		
		if (studentTree.contains(studentID)){
				cout << "\nStudent Name: " << studentTree.returnKey(studentID).returnStudentName() << endl;

				int studentAdvisorID = studentTree.returnKey(studentID).returnStudentAdvisor();
				facultyTree.displayNode(studentAdvisorID);
		}
		
		else cout << "\n- Student Does Not Exist -" << endl;	
}
//print fac advisees
void Database::optionSix(){
		string adviseeIDString;
		int adviseeID;
		int facultyID;
		Faculty f;
		string line2;
		cout << "            Find Advisees		  " << endl;
		cout << "-----------------------------------  " << endl;

		cout << "\nEnter Faculty ID: ";
		cin >> facultyID;

		if (facultyTree.contains(facultyID)){
				ofstream myfile("adviseeList.txt");
				facultyTree.returnKey(facultyID).saveAdvisees(myfile);
				myfile.close();

				ifstream newfile("adviseeList.txt");
				if(newfile.is_open()){
						cout << "\nAdvisor Name: " << facultyTree.returnKey(facultyID).returnAdvisorName() << endl;

						while(getline(newfile,adviseeIDString)){
								 if( adviseeIDString != "" || adviseeIDString != "\t" || adviseeIDString != "\n" || !adviseeIDString.empty()){ 
								 		line2 = adviseeIDString;
								 }
							    
							     stringstream(adviseeIDString) >> adviseeID;
								 studentTree.displayNode(adviseeID);    
						}
				
				newfile.close();
				}
		}
		
		else cout << "\n- Faculty Does Not Exist -" << endl;	
}

//add a student to the record
void Database::optionSeven(){
		int studentID;
		string studentName;
		string studentClass;
		string studentMajor;
		double studentGPA;
		int studentAdvisor;
		int choice;

		cout << "      	   ADD STUDENT		  " << endl;
		cout << "-----------------------------------  " << endl;

		cout << "\n";
		cout << "Student ID      : "; 
		cin >> studentID;
        while(cin.fail()) {
        cin.clear();
        cin.ignore(256,'\n');
        cin >> studentID;
        cout<<"Invalid Input"<<endl;
        cout<<"Enter the ID number: "<<endl;
        }
		cout << "Student Name    : "; cin.ignore();
		getline(cin, studentName); 
		cout << "Student Class   : "; cin.ignore();
		getline(cin, studentClass); 
		cout << "Student Major   : "; cin.ignore();
		getline(cin, studentMajor); 
	    cout << "Student GPA     : ";
	    cin >> studentGPA;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(256,'\n');
        cin >> studentGPA;
        cout<<"Invalid Input"<<endl;
        cout<<"Enter the GPA: ";
    }
	    cout << "Student Advisor : "; 
	    cin >> studentAdvisor;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(256,'\n');
        cin >> studentAdvisor;
        cout<<"Invalid Input"<<endl;
        cout<<"Enter the Faculty ID number: ";
    }

	    if(studentTree.contains(studentID)){
	    		cout << "\nError: Student '" << studentID << "' already exists\n" << endl;
	    }

	    else if(!facultyTree.contains(studentAdvisor)){
	    		cout << "\nError: Faculty '" << studentAdvisor << "' does not exist\n" << endl;
	    }

	    else{
		    	cout << "\nAre you sure you want to add and save " << studentName << " to records?\n\t1) Yes\n\t2) No\nEnter: ";
				cin >> choice;

		    	if(choice == 1){
						Student s(studentID, studentName, studentClass, studentMajor, studentGPA, studentAdvisor);
						studentTree.addNode(s);		//Add student to the tree
						facultyTree.returnKey(studentAdvisor).addAdvisee(studentID);	//Add Advisee
				}

				else if(choice == 2) cout << "\n- Student Not Added -" << endl;
				
				else cout << "- Error: Invalid Entry -" << endl;	
		}
}

//delete stu
void Database::optionEight(){
		int studentID;
		int choice;
		Faculty f;
		

		cout << "         Delete Student		  " << endl;
		cout << "-----------------------------------  " << endl;

		cout << "\nEnter Student ID Number: ";
		cin >> studentID;

		if(studentTree.contains(studentID)){
				cout << "\nAre you sure you want to delete " << studentTree.returnKey(studentID).returnStudentName() << " ?";
				cout << "\n\t1) Yes\n\t2) No\nEnter: ";
				cin >> choice;
				
				if(choice == 1){
						facultyTree.returnKey(studentTree.returnKey(studentID).returnStudentAdvisor()).deleteAdvisee(studentID); 
						studentTree.deleteNode(studentID);
						
						cout << "\n- Student Deleted -\n" << endl;
				}
				
				else if(choice == 2) cout << "\n -Student Not Deleted -\n" << endl;

				else cout << "\n\n- Error: Invalid Input -" << endl;		
		}
		
		else cout << "\nError: Student Record Not Found" << endl;	
}

//add new faculty
void Database::optionNine(){
		int facultyID;
		string facultyName;
		string facultyLevel;
		string facultyDepartment;
		int facultyAdvisee;
		int choice;
		cout << "           ADD FACULTY 		  " << endl;
		cout << "-----------------------------------  " << endl;

		cout << "\n";
		cout << "Faculty ID          :";
		cin >> facultyID;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(256,'\n');
        cin >> facultyID;
        cout<<"Invalid Input"<<endl;
        cout<<"Enter the ID number: ";
    }
		cout << "Faculty Name        :"; cin.ignore();
		getline(cin, facultyName);
		cout << "Faculty Level       :";
		getline(cin, facultyLevel); 
		cout << "Faculty Department  :";
		getline(cin,facultyDepartment);
		cout << "Faculty Advisee     :"; 
		cin >> facultyAdvisee;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(256,'\n');
        cin >> facultyAdvisee;
        cout<<"Invalid Input"<<endl;
        cout<<"Enter the ID number: ";
    }

		if(facultyTree.contains(facultyID)){
				cout << "\nError: Faculty '" << facultyID <<"' already exists\n" << endl;
		}

		if(!studentTree.contains(facultyAdvisee)){
				cout << "\nError: Student '" << facultyAdvisee << "' does not exist\n" << endl;
		}

		else{

				cout << "\nAre you sure you want to add and save " << facultyName << " to records?\n\t1) Yes\n\t2) No\nEnter: ";
					cin >> choice;

			    	if(choice == 1){
							Faculty f(facultyID, facultyName, facultyLevel, facultyDepartment, facultyAdvisee);
							facultyTree.addNode(f);
							facultyTree.returnKey(facultyID).addAdvisee(facultyAdvisee);

					}

					else if(choice == 2) cout << "\n- Faculty Not Added -" << endl;
					
					else cout << "- Error: Invalid Entry -" << endl;	

	
		}
}

//delete facutly
void Database::optionTen(){
		int facultyID;
		int choice;
		string line;

		cout << "          Delete Faculty 		  " << endl;
		cout << "-----------------------------------  " << endl;

		cout << "\nEnter Faculty ID Number: ";
		cin >> facultyID;

		if(facultyTree.contains(facultyID)){
				cout << "\nAre you sure you want to delete " << facultyTree.returnKey(facultyID).returnAdvisorName() << " ?";
				cout << "\n\t1) Yes\n\t2) No\nEnter: ";
				cin >> choice;
				
				if(choice == 1){
						facultyTree.deleteNode(facultyID);
						cout << "\n- Faculty Deleted -\n" << endl;
				}
				
				else if(choice == 2) cout << "\n -Faculty Not Deleted -\n" << endl;
				
				else cout << "\n\n- Error: Invalid Input -" << endl;
		}

		else cout << "\n- Error: Faculty Member Not Found -" << endl;	
}

//change students advisor
void Database::optionEleven(){
		int studentID; 
		int facultyID;
		Student s;

		cout << "       	  Change Advisor		  " << endl;
		cout << "-----------------------------------  " << endl;

		cout << "\nEnter Studnet ID: ";
		cin >> studentID;

		if(studentTree.contains(studentID)){
            cout << studentTree.returnKey(studentID);
				s = studentTree.returnKey(studentID);
				cout << "\nEnter New Faculty ID: ";
				cin >> facultyID;
            if(facultyTree.contains(facultyID)){
				facultyTree.returnKey(studentTree.returnKey(studentID).returnStudentAdvisor()).deleteAdvisee(studentID);

				studentTree.deleteNode(studentID);
				Student s1(s.returnID(), s.returnStudentName(), s.returnStudentClass(), s.returnStudentMajor(), s.returnStudentGPA(), facultyID);
				studentTree.addNode(s1);

				facultyTree.returnKey(facultyID).addAdvisee(s.returnID());
            }
            else
                cout<<"Error: Faculty Member Does Not Exist"<<endl;
		}

		else cout << "Error: Student Does Not Exist" << endl;
}

//remove student from faculty list
void Database::optionTwelve(){
		int facultyID;
		int adviseeID;

		cout << "         Remove Advisee		  " << endl;
		cout << "-----------------------------------  " << endl;



		cout << "\nEnter Faculty ID: ";
		cin >> facultyID;

		if(facultyTree.contains(facultyID)){
				facultyTree.displayNode(facultyID);
				cout << "Enter Advisee ID to delete: ";
				cin >> adviseeID;
					

				if(studentTree.contains(adviseeID)){
						facultyTree.returnKey(facultyID).deleteAdvisee(adviseeID);
					
				}
				
				else cout << "Error: Student Does Not Exists\n";
			
		}

		else cout << "Error: Faculty Member Does Not Exist\n";
}
//Roll Back
void Database::optionThirteen(){
		cout << "         Roll Back		  " << endl;
		cout << "-----------------------------------  " << endl;
		string sORf;
		cout << "Enter Student to rollback student tree, enter faculty to rollback faculty: ";
		cin >> sORf;
		if(!sORf.compare("student")){
			if(sCount == 0){
				cout << "Nothing to Roll Back" << endl;
			}
			else if(sCount == 1){
				studentTree = sRollBackTreeOne;
				sCount--;
			}
			else if(sCount == 2){
				studentTree = sRollBackTreeTwo;
				sCount--;
			}
			else if(sCount == 3){
				studentTree = sRollBackTreeThree;
				sCount--;
			}
			else if(sCount == 4){
				studentTree = sRollBackTreeFour;
				sCount--;
			}
			else if(sCount == 5){
				studentTree = sRollBackTreeFive;
				sCount--;
			}			
		}
        else if(fCount == 0){
			if(fCount == 0){
				cout << "Nothing to Roll Back" << endl;
			}
			else if(fCount == 1){
				facultyTree = fRollBackTreeOne;
				fCount--;
			}
			else if(fCount == 2){
				facultyTree = fRollBackTreeTwo;
				fCount--;
			}
			else if(fCount == 3){
				facultyTree = fRollBackTreeThree;
				fCount--;
			}
			else if(fCount == 4){
				facultyTree = fRollBackTreeFour;
				fCount--;
			}
			else if(fCount == 5){
				facultyTree = fRollBackTreeFive;
				fCount--;
			}	
		}
    else
        cout<<"Invalid Input"<<endl;
}
//Save Roll Back records for Student Trees
void Database::saveStudentRollBack(){
		if(sCount == 0){
			sRollBackTreeOne = studentTree;
			sCount++;
		}
		else if(sCount == 1){
			sRollBackTreeTwo = studentTree;
			sCount++;
		}
		else if(sCount == 2){
			sRollBackTreeThree = studentTree;
			sCount++;
		}
		else if(sCount == 3){
			sRollBackTreeFour = studentTree;
			sCount++;
		}
		else if(sCount == 4){
			sRollBackTreeFive = studentTree;
			sCount++;
		}
		else if(sCount == 5){
			sRollBackTreeOne = sRollBackTreeTwo;
			sRollBackTreeTwo = sRollBackTreeThree;
			sRollBackTreeThree = sRollBackTreeFour;
			sRollBackTreeFour = sRollBackTreeFive;
			sRollBackTreeFive = studentTree;
		}
}
//Save Roll Back records for Faculty Trees
void Database::saveFacultyRollBack(){
		if(fCount == 0){
			fRollBackTreeOne = facultyTree;
			fCount++;
		}
		else if(fCount == 1){
			fRollBackTreeTwo = facultyTree;
			fCount++;
		}
		else if(fCount == 2){
			fRollBackTreeThree = facultyTree;
			fCount++;
		}
		else if(fCount == 3){
			fRollBackTreeFour = facultyTree;
			fCount++;
		}
		else if(fCount == 4){
			fRollBackTreeFive = facultyTree;
			fCount++;
		}
		else if(fCount == 5){
			fRollBackTreeOne = fRollBackTreeTwo;
			fRollBackTreeTwo = fRollBackTreeThree;
			fRollBackTreeThree = fRollBackTreeFour;
			fRollBackTreeFour = fRollBackTreeFive;
			fRollBackTreeFive = facultyTree;
		}
}

//Save student records to 'studentTable.txt'
void Database::saveStudentRecords(){
	
	ofstream studentFile("studentTable.txt");
	studentTree.serialize(studentFile);
	studentFile.close();
}
//Save student records to 'facultyTable.txt'
void Database::saveFacultyRecords(){
	 ofstream facultyFile("facultyTable.txt");
	 facultyTree.serialize(facultyFile);
	 facultyFile.close();					// serialize the advisees as well
}

//load records
void Database::loadRecords(){
		string line;
		string studentIDString;
		string studentName;
		string studentClass;
		string studentMajor;
		string studentGPAString;
		string studentAdvisorString;
		string facultyIDString;
		string facultyName;
		string facultyLevel;
		string facultyDepartment;
		int facultyID;
		int i = 0;
		int m = 0;
		int advisorList[50] = {};
		int studentList[50] = {};
		int studentAdvisor;
		int studentID;
		double studentGPA;

		ifstream facultyFile;
		ifstream studentFile;
		studentFile.open("studentTable.txt");
				if(studentFile.is_open()){
                    while(!studentFile.eof()){
                        getline(studentFile, line, ':'); getline(studentFile, studentIDString, '\n');//get studentID
                        getline(studentFile, line, ':'); getline(studentFile, studentName, '\n');//get studentName
                        getline(studentFile, line, ':'); getline(studentFile, studentClass, '\n');//get studentClass
                        getline(studentFile, line, ':'); getline(studentFile, studentMajor, '\n');//get studentMajor
                        getline(studentFile, line, ':'); getline(studentFile, studentGPAString, '\n');//getStudentGPA
                        getline(studentFile, line, ':'); getline(studentFile, studentAdvisorString, '\n');//get studentAdvisor
                        stringstream(studentAdvisorString) >> studentAdvisor;	//convert studentAdvisor into an integer
                        stringstream(studentIDString) >> studentID;				//convert studentID into an integer
                        stringstream ss;										//convert studentGPA into a double
                        ss << studentGPAString;
                        ss >> studentGPA;
                        if(!studentTree.contains(studentID)){				    //if new student...
                                Student s(studentID, studentName, studentClass, studentMajor, studentGPA, studentAdvisor);
                                studentTree.addNode(s);							//create and add a student
                                advisorList[i] = studentAdvisor; 	
                                studentList[m] = studentID;					
                        }
                        i++;
                        m++;
                    }
				}

			    facultyFile.open("facultyTable.txt");
			    if(facultyFile.is_open()){
				    	while(!facultyFile.eof()){
					    		getline(facultyFile, line, ':'); getline(facultyFile, facultyIDString, '\n');		//get facultyID
					    		getline(facultyFile, line, ':'); getline(facultyFile, facultyName, '\n');			//get facultyName
					    		getline(facultyFile, line, ':'); getline(facultyFile, facultyLevel, '\n');			//get facultyLevel
					    		getline(facultyFile, line, ':'); getline(facultyFile, facultyDepartment, '\n');		//get facultyDepartment
					    	
						    	stringstream(facultyIDString) >> facultyID;	

						    	for(int j = 0; j < i; j++){	//create each individual advisor
							    		if(advisorList[j] == facultyID && !facultyTree.contains(facultyID)){
							    				Faculty f(facultyID, facultyName, facultyLevel, facultyDepartment, 0);
							    				facultyTree.addNode(f);
							    		}
						    	}

						    	for(int r = 0; r < m-1; r++){	// if the student advisor is the same as the faculty member being added...
						    			if(studentTree.returnKey(studentList[r]).returnStudentAdvisor() == facultyID){   //... add advisee
						    					facultyTree.returnKey(facultyID).addAdvisee(studentTree.returnKey(studentList[r]).returnID());
						    			}			
						    	}	    
					   	}	 	    	  	    
				}			
}


Database::~Database(){
    
    studentTree.deleteTree();
    facultyTree.deleteTree();
}
