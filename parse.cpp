/***************************************************************
  Student Names: Alex Reichel, Bradley Love
  File Name: Parse.cpp
  Assignment number Project 01

  Responsible for defining methods in the Parse class
***************************************************************/

#ifndef _Parse_CPP
#define _Parse_CPP
#include "parse.hpp"

using  namespace std;

Parse::Parse(){
	inputRedirect = outputRedirect = NULL;
	background = 0;
	argumentCount = 0;
}


void Parse::tokenize(char *ptr){
	inputRedirect = outputRedirect = NULL;

	char *dupVector[32];
	char *dup = strdup(ptr);
	argumentCount = 0;
	string fileName="";
	char *token = strtok(dup, " ");
	int size=0;
	int p=0;

	while (token != NULL){
		dupVector[p] = token;
		token = strtok(NULL, " ");
		size++;
		p++;
	 }

	int numOfArgs=0;
	int numOfArgsNow=0;
	int count=0;

	for(int i=1;i<size;i++){
	numOfArgs++;

	if(*dupVector[i-1] == '<'){
		numOfArgsNow = numOfArgs-1;

		for(int j=0;j<numOfArgsNow;j++){
			count++;
			addArgument(dupVector[j]);
		}

		setInputRedirect(dupVector[i]);
	}

	if(*dupVector[i-1] == '>'){
		numOfArgsNow = numOfArgs-1;

		for(int j=0;j<numOfArgsNow;j++){
			count++;
			addArgument(dupVector[j]);
		}

		setOutputRedirect(dupVector[i]);
	}

	}

	if(getOutputRedirect() == NULL && getInputRedirect() == NULL  ){
		for(int i=0;i<size;i++){
			addArgument(dupVector[i]);
		}
	}

	if(*dupVector[size-1]== '&'){
		setBackground(1);
	}

	else{
		setBackground(0);
	}
}

void Parse::redirection(){
	if(getInputRedirect()!=NULL){
		string line;
		fp= freopen(getInputRedirect(),"r",stdin);

		while(getline(cin,line)){
			cout<< line <<endl;
		}
	}

	if(getOutputRedirect()!= NULL){
		fp=freopen(getOutputRedirect(),"w", stdout);

	    	for(size_t i=0;i<argumentCount;i++){
	    		cout<<argumentVector[i]<<endl;
	    	}
	}
}



void Parse::addArgument (char* newArgument){
	argumentVector[argumentCount] = newArgument;
	argumentCount++;
}

char** Parse::getArguments(){
	return argumentVector;
}

void Parse::setInputRedirect(char *newInputRedirect){
	inputRedirect = newInputRedirect;
	outputRedirect = NULL;
}

void Parse::setOutputRedirect(char *newOutputRedirect){
	outputRedirect = newOutputRedirect;
	inputRedirect = NULL;
}

void Parse::setBackground(int newBackground){
	background = newBackground;
}

char* Parse::getInputRedirect(){
	return inputRedirect;
}


char* Parse::getOutputRedirect(){
	return outputRedirect;
}

int Parse::getBackground(){
    return background;
}

void Parse::execute(){
	char *dupVector[argumentCount+1];
	int size=0;

	for(int i=0;i<argumentCount;i++){
		dupVector[i] = argumentVector[i];
		size++;
	}

	dupVector[size]= NULL;

	pid_t pid;
	int    status;
	int childStatus;
	pid = fork();



	if (pid < 0){
		cout<<"*** ERROR: forking child process failed"<<endl;
		exit(1);
	}
	else if (pid == 0) {
		redirection();
		childStatus= execvp(dupVector[0], dupVector);

		if (childStatus < 0) {
			perror("Error");
			exit(1);
		}
	}
	else {
		if(getBackground()==1){
			pid = waitpid(-1, &status, WNOHANG);
		}
		else{
			pid = waitpid(pid, &status, 0);
		}

	}


}



void Parse::printParams(){
	cout << "InputRedirect: ["
	     << (inputRedirect != NULL) ? inputRedirect : "NULL";
	cout << "]"  << endl
		 << "OutputRedirect: ["
		 << (outputRedirect != NULL) ? outputRedirect : "NULL";
	cout << "]" << endl
		 << "Background: ["
		 << background
		 << "]"
		 << endl
		 << "ArgumentCount: ["
		 << argumentCount
		 << "]"
		 << endl;
	for (int i = 0; i < argumentCount; i++){
		cout << "ArgumentVector["
			 << i
			 << "]: ["
			 << argumentVector[i]
			 << "]"
			 << endl;
	}
}

#endif


