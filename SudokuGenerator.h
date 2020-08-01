///////////////////////////////////////////////////////////////////////
// Workfile: SudokuGenerator.h
// Author: Christoph Dalpiaz
// Date: 30.07.2020
// Description: class for generating a solvable sudoku
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <string>				//include std::string
#include "SudokuSolver.h"		//include solver module

std::string const FileError = "Error opening file for writing";	
std::string const PrintingError = "Error printing sudoku";

std::string const NameAdditionalSep = "Sep";	//added for files with seperators
std::string const FileEnding = ".txt";			//file ending for all files

//class for generating sudokus needs solver functionality
class SudokuGenerator : public SudokuSolver {
private:

	size_t mNoSolutions = 0;

	//initialize the sudoku
	void Init();

	//solves sudoku with recursion
	virtual void SolveRecursive(size_t const pos = 0) override;

	//adds a random number to sudoku respecting rules
	//return false if value cannot be found
	bool AddNumber(size_t& posY, size_t& posX);

	//returns true if sudoku respects rules
	bool RespectRules();

	//write sudoku to file
	void WriteToFile(std::string const& fileName, bool const WithSeperators);

public:
	//generates n sudokus and writes them to file, optional print to printer
	//WithSeperators true -> file with seperators becomes additionally created (not solvable, but better readable)
	//fileName without file ending, MaxNoNumbers is maximum number of numbers in sudoku
	void Generate(std::string const& fileName, size_t const MaxNumbers, bool const WithSeperators = false);

	//default constructor initializing empty sudoku
	SudokuGenerator();
};

#endif