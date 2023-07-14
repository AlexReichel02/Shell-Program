
/***************************************************************
  Student Names: Alex Reichel, Bradley Love
  File Name: main.cpp
  Assignment number Project 01

  Responsible for calling methods from Param class to run the program
***************************************************************/
#include <iostream>
#include "parse.hpp"
using namespace std;

int main(int argc, char **argv) {
	bool option = true;
	bool debug = false;
	char command[32];
	string input;

	if(argc > 1){
		if(strcmp(argv[1],"-Debug") == 0){
			debug = true;

		}
	}

	if(!debug){
		while(option == true){
			Parse obj;
			cout<<"$$$ ";
			cin.getline(command,32);

			if(strcmp(command, "exit")==0){
				cout << "------------------"<<endl;
				cout << "Program Terminated" <<endl;
				option = false;
				exit(1);
			}
		obj.tokenize(command);
		obj.execute();

		}
	}

	if(debug){
		while(option == true){
			Parse obj2;
			cout<<"$$$ ";
			cin.getline(command,32);

			if(strcmp(command, "exit")==0){
				cout << "------------------"<<endl;
				cout << "Program Terminated" <<endl;
				option = false;
				exit(1);
			}

			obj2.tokenize(command);
			obj2.printParams();
		  }
	}

	return 0;
}
