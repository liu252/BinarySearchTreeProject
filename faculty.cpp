#include "Faculty.h"

using namespace std;

void Faculty::printAdvisees(){
		facultyAdvisees.printTree();
}

void Faculty::saveAdvisees(ostream &out){
		facultyAdvisees.serialize(out);
}


void Faculty::addAdvisee(int s){
		if(!facultyAdvisees.contains(s)){
			facultyAdvisees.addNode(s);
		}
}

void Faculty::deleteAdvisee(int s){
		facultyAdvisees.deleteNode(s);
}

string Faculty:: returnAdvisorName(void){
		return facultyName;
}

bool Faculty::operator>( Faculty &other) {
		return(facultyID > other.facultyID);

}

bool Faculty::operator<( Faculty &other) {
		return(facultyID < other.facultyID);

}

bool Faculty::operator==( Faculty &other) {
		return(facultyID == other.facultyID);

}

bool Faculty::operator!=( Faculty &other) {
		return(facultyID != other.facultyID);
}

ostream &operator<<(ostream &out, Faculty f) {
		out<<"_________________________________________________\n";
		out<<"Faculty ID	 		 :" << f.facultyID << endl;
		out<<"Faculty Name			 :" << f.facultyName << endl;
		out<<"Faculty Level			 :" << f.facultyLevel << endl;
		out<<"Faculty Department	         :" << f.facultyDepartment << endl;
		out<<"-------------------------------------------------\n";
		out<<"List of Student(s) ID reporting to this faculty  \n";
		out<<"-------------------------------------------------\n";
		f.facultyAdvisees.printTree();
		out<<"_________________________________________________\n\n";

		return(out);
}
