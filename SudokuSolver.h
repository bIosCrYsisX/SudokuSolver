///////////////////////////////////////////////////////////////////////
// Workfile: SudokuSolver.h
// Author: Christoph Dalpiaz
// Date: 13.07.2020
// Description: class SudokuSolver for solving sudokus
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>			//include IO library
#include <algorithm>		//include standard library algorithms
#include <vector>			//include std::vector
#include <string>			//include std::string
#include "SudokuErrors.h"	//include error texts

unsigned char const Dim = 9;		//dimension of sudoku
unsigned char const SmallDim = 3;   //dimension of small part fields

char const SeperatorColumn = '|';	//column character
std::string const SeperatorLine = "------+------+------"; //seperator line for blocks

size_t const minimumNumbers = 17;  //minimum number of numbers for solvable sudoku

typedef unsigned char Sudoku[Dim][Dim];  //array of arrays of unsigned chars representing Sudoku
										 //Dim x Dim matrice

typedef std::vector<unsigned char> PossibleNumbers;  //vector with possible numbers for a position


class SudokuSolver {
protected:
	Sudoku sudoku = { 0 };

	//scans Sudoku from file, returns false if scanning failed
	bool ScanSudoku(std::string const& fileName);

	//returns true if sudoku is solvable, otherwise false
	bool IsSolvable();

	//solves sudoku with recursion
	virtual void SolveRecursive(size_t const pos = 0);

	//returns true if sudoku is solved
	bool IsSolved();

	//returns vector with all possible numbers for given position
	PossibleNumbers GetPossibilities(size_t const pos);

	//print sudoku to o
	void Print(std::ostream& o);

	//print with line and column seperators
	void PrintWithSeperators(std::ostream& o);

	//overloaded << operator for sudoku
	friend std::ostream& operator<<(std::ostream& o, Sudoku const sudoku);

public:
	//constructor with file from which sudoku becomes scanned
	explicit SudokuSolver(std::string const& fileName) {
		if (!ScanSudoku(fileName)) {
			std::cerr << ScanningError << std::endl;
		}
	}

	//constructor initializing sudoku
	explicit SudokuSolver(Sudoku const _sudoku);

	//solves Sudoku and writes result to file
	void Solve(std::string const& solvedFile);

	//make virtual destructor because there are derived classes
	virtual ~SudokuSolver() = default;
};

#endif