/***************************************************************
  Student Names: Alex Reichel, Bradley Love
  File Name: Param.hpp
  Assignment number Project 01

  Declares methods and variables that will hold and use input data
***************************************************************/
#ifndef _PARAM_HPP
#define _PARAM_HPP
#include<iostream>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#define MAXARGS 32

class Parse
{
	private:

		/*
		 * file name or NULL
		 */
		 char *inputRedirect;

		 /*
		 *  file name or NULL
		 */
		 char *outputRedirect;

		 /*
		 * either 0 (false) or 1 (true)
		 */
		 int background;

		 /*
		 * same as argc in main()
		 */
		 int argumentCount;

		/*
		 * array of strings
		 */
		 char *argumentVector[MAXARGS];

		 /*
		 * pointer to a file
		 */
		 FILE *fp;

	public:

		/*
		* Constructs an empty Param object.
		*/
		Parse();

		/*
		* tokenizes a string that is input by the user
		*
		* @param ptr pointer to a character in the string given by the user
		*/
		void tokenize(char* ptr);

		 /*
		 * Adds an argument string to the argument list in this object. This function
		 * does not create a string copy of the original string.
		 *
        	 * @param newArgument a new argument to be added to the argument list;
		 *  	if NULL nothing will be added
         	 */
		 void addArgument (char* newArgument);

		 /*
		 * Returns an argument list referencing char* strings. The last element in the
		 * list is NULL to mark the end of list elements. This makes the size of
		 * the list one larger than the number of arguments added to this object.
		 *
		 * Note:
		 *   Caller must deallocate memory for the list.
		 */
		char** getArguments();

		/*
		 * Sets the filename for input redirection.
		 *
		 * @param newInputRedirect a string specifying the input redirect filename
		 */
		void setInputRedirect(char *newInputRedirect);

		/*
		* Sets the filename for output redirection.
		*
		* @param newOutputRedirect a string for specifying the output redirect filename
		*/
		void setOutputRedirect(char *newOutputRedirect);

		/*
		* sets the process that will be in the background
		*
		* @param newBackground an int for identifying what process is in the background
		*/
		void setBackground(int newBackground);

		/**
		* Returns the filename for input redirection.
		*
		* @return a string representing a filename
		*/
		char* getInputRedirect();

		/*
		* Returns the filename for the output redirection
		*
		* @return a string representing the output filename
		*/
		char* getOutputRedirect();

		/*
		* Returns the integer representing a background process
		*
		* @return and integer representing a background process
		*/
		int getBackground();

		/*
		* Responsible for handling I/O redirection
		*/
		void redirection();

		/*
		* responsible for executing commands given to the program
		*/
		void execute();

		/*
		* Prints the information in the specified structure to standard out.
         	*/
		void printParams();
};

#endif

