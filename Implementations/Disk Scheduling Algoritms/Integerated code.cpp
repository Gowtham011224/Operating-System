#include <iostream>
using namespace std;

#include "clook.hpp"
#include "cscan.hpp"
#include "fcfs.hpp"
#include "look.hpp"
#include "scan.hpp"
#include "sstf.hpp"

int main(){
	int choice;
	cout <<"MENU"<<endl;
	cout<<"1.FCFS \n"<< "2.STTF\n" <<"3.SCAN\n" << "4.CSCAN\n"<< "5.LOOK\n" << "6.CLOOK\n";
	cout <<"ENTER YOUR CHOICE " <<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:
			one();
			break;
		case 2:
			two();
			break;
		case 3:
			three();
			break;
		case 4:
			four();
			break;
		case 5:
			five();
			break;
		case 6:
			six();
			break;
		default:
			cout<<"Invalid Input"<<endl;

	}
	return 0;
}


