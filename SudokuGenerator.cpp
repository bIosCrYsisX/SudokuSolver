///////////////////////////////////////////////////////////////////////
// Workfile: SudokuGenerator.cpp
// Author: Christoph Dalpiaz
// Date: 30.07.2020
// Description: class for generating a solvable sudoku
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include <stack>				//include stack adapter
#include <algorithm>			//include standard library algorithms
#include <fstream>				//include filestream library
#include <cstdlib>				//needed for random number generator
#include <time.h>				//needed for random seed
#include "SudokuGenerator.h"	//include module header

using namespace std;	//resolve std namespace

//default constructor initializing empty sudoku
SudokuGenerator::SudokuGenerator() : SudokuSolver{ nullptr } {
	Init();
}

//initialize the sudoku
void SudokuGenerator::Init() {
	for (size_t i = 0; i < Dim; i++) {		//set all fields to zero
		for (size_t j = 0; j < Dim; j++) {
			sudoku[i][j] = 0;
		}
	}
}

//solves sudoku with recursion
void SudokuGenerator::SolveRecursive(size_t const pos) {
	if (pos < Dim * Dim && mNoSolutions <= 1) {		//check if position is in range and there are not yet multiple solutions
		if (sudoku[pos / Dim][pos % Dim] == 0) {						//if position is open, try to solve it
			PossibleNumbers possibilities = GetPossibilities(pos);		//get vector of possible numbers

			//try to solve sudoku for every possibility until solution is found
			for_each(possibilities.cbegin(), possibilities.cend(), [&](unsigned char const possibility)
				{ sudoku[pos / Dim][pos % Dim] = possibility; SolveRecursive(pos + 1); if (IsSolved()) { mNoSolutions++; } sudoku[pos / Dim][pos % Dim] = 0; });
		}
		else {						//try to solve for the remaining positions
			SolveRecursive(pos + 1);
		}
	}
}

//adds a random number to sudoku respecting rules
//return false if value cannot be found
bool SudokuGenerator::AddNumber(size_t& posY, size_t& posX) {
	posX = rand() % Dim;   //get random position on field
	posY = rand() % Dim;

	while (sudoku[posY][posX] != 0) {  //if position is not empty, continue searching
		posX = rand() % Dim;
		posY = rand() % Dim;
	}

	size_t init = rand() % Dim + 1;			//initial value
	sudoku[posY][posX] = (init % Dim) + 1;  //start checking at next value
	
	if (RespectRules()) { //check if this value is valid
		return true;	  //if yes, number is successfully added
	}
	sudoku[posY][posX] = (sudoku[posY][posX] % Dim) + 1; //go to next value

	while (!RespectRules() && sudoku[posY][posX] != init) {   //try to check values until init is reached
		sudoku[posY][posX] = (sudoku[posY][posX] % Dim) + 1;
	}

	if (sudoku[posY][posX] == init) { //if init has been reached again, there is no value
		return false;
	}

	return true;  //value is found
}

//returns true if sudoku respects rules
bool SudokuGenerator::RespectRules() {
	for (size_t i = 0; i < Dim; i++) {
		bool numInsideLine[Dim] = { 0 };    //indicates if number is inside, initially false
		bool numInsideColumn[Dim] = { 0 };

		for (size_t j = 0; j < Dim; j++) {		//check lines and columns
			if (sudoku[i][j] > 0) {
				if (numInsideLine[sudoku[i][j] - 1]) {  //rules are not respected if number is multiple inside
					return false;
				}
				numInsideLine[sudoku[i][j] - 1] = true;  //first encounter, set it to true
			}
			if (sudoku[j][i] > 0) {
				if (numInsideColumn[sudoku[j][i] - 1]) {
					return false;
				}
				numInsideColumn[sudoku[j][i] - 1] = true;
			}
		}
	}
	for (size_t i = SmallDim; i <= Dim; i += SmallDim) {  //check all small windows
		for (size_t j = SmallDim; j <= Dim; j += SmallDim) {
			bool numInsideWindow[Dim] = { 0 };
			for (size_t k = i - SmallDim; k < i; k++) {  //check all fields in small window
				for (size_t l = j - SmallDim; l < j; l++) {
					if (sudoku[l][k] > 0) {
						if (numInsideWindow[sudoku[l][k] - 1]) {
							return false;
						}
						numInsideWindow[sudoku[l][k] - 1] = true;
					}
				}
			}
		}
	}
	return true;  //sudoku respects rules
}

//generates n sudokus and writes them to file, optional print to printer
//WithSeperators true -> file with seperators becomes additionally created (not solvable, but better readable)
//fileName without file ending, MaxNoNumbers is maximum number of numbers in sudoku
void SudokuGenerator::Generate(string const& fileName, size_t const MaxNoNumbers, bool const WithSeperators) {

	size_t const NoInitNumbers = minimumNumbers;  //number of initially placed numbers in sudoku
	size_t noNumbers = NoInitNumbers;			  //number of numbers in sudoku

	size_t posY = 0;	//positions for actually added numbers, needed if step has to be reversed
	size_t posX = 0;

	srand(time(nullptr)); //set random seed
	mNoSolutions = 0;	  //number of solutions is initially zero

	while (mNoSolutions != 1) {		 //find a sudoku with one solution
		noNumbers = NoInitNumbers;	 //number of numbers initially init numbers
		Init();					//initialize with zeros
		size_t count = 0;		//loop counter
		while (count < NoInitNumbers) {	//if number cannot be added, start again
			if (!AddNumber(posY, posX)) {  
				Init();
				count = 0;
			}
			count++;
		}
		PrintWithSeperators(cout);  //print the sudoku to cout
		SolveRecursive();	//try to solve it

		while (mNoSolutions > 1) {	//if there are multiple solutions, add more numbers until there is only one
			mNoSolutions = 0;		
			AddNumber(posY, posX);		//add number and try to solve it again
			PrintWithSeperators(cout);
			SolveRecursive();
			if (mNoSolutions == 0) {  //if last step made the sudoku unsolvable, reverse the step
				sudoku[posY][posX] = 0; 
				mNoSolutions = UINT32_MAX;  //make number of solutions bigger than one
			}
			else {
				noNumbers++;	//number of numbers increased
			}
		}

		if (noNumbers > MaxNoNumbers) {	 //if sudoku has too much numbers, make a new one
			mNoSolutions = 0;
		}
	}

	WriteToFile(fileName, WithSeperators);
	PrintWithSeperators(cout);	//print finished sudoku to cout
}

//write sudoku to file
void SudokuGenerator::WriteToFile(std::string const& fileName, bool const WithSeperators) {
	ofstream writeFile{ fileName + FileEnding };  //define a filestream for solvable sudoku file

	if (!writeFile.is_open()) {  //check if opening file worked
		throw FileError;
	}

	Print(writeFile);	//write sudoku to filestream
	writeFile.close();

	if (WithSeperators) {		//check if file with seperators has to be created
		ofstream writeFile{ fileName + NameAdditionalSep + FileEnding };

		if (!writeFile.is_open()) {
			throw FileError;
		}

		PrintWithSeperators(writeFile);
		writeFile.close();
	}
}