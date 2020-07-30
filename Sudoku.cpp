///////////////////////////////////////////////////////////////////////
// Workfile: Sudoku.cpp
// Author: Christoph Dalpiaz
// Date: 13.07.2020
// Description: functions for solving a sudoku
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include <fstream>		//include filestream library
#include <algorithm>	//include STL algorrithms
#include <array>		//include std::array
#include <iterator>		//include iterator library
#include "Sudoku.h"		//include module header

using namespace std;	//resolve std namespace

size_t const minimumNumbers = 17; //minimum number of numbers for solvable sudoku

//overloaded << operator for sudoku
std::ostream& operator<<(std::ostream& o, Sudoku const sudoku) {
	if (o.good()) {   //check if ostream is valid
		for_each(&sudoku[0], &sudoku[0] + Dim, [&](unsigned char const line[]) { copy(&line[0], &line[0] + Dim, ostream_iterator<size_t>(o, " ")); o << endl; });
	}
	return o;  //return manipulated ostream
}

//scans Sudoku from file, returns false if scanning failed
bool SudokuSolver::ScanSudoku(std::string const& fileName) {
	ifstream file{ fileName };  //define a input filestream

	if (!file.is_open()) {   //check if opening file worked
		return false;		 //return false if not
	}

	copy(istream_iterator<size_t>{file}, istream_iterator<size_t>{}, &sudoku[0][0]);  //read sudoku in
	
	return true;   //reading sudoku worked
}

//returns true if sudoku is solvable, otherwise false
bool SudokuSolver::IsSolvable() {
	size_t numCounter = 0;   //number of given numbers in sudoku

	 //count number of numbers and return false if there is a number bigger than Dim
	if (find_if(&sudoku[0][0], &sudoku[0][0] + Dim * Dim, [&](unsigned char num) { if (num > Dim) { return true; } else if (num != 0) { numCounter++; } return false; }) 
		!= &sudoku[0][0] + Dim * Dim) {																																	
		return false;
	}

	return numCounter >= minimumNumbers;
}

//solves sudoku with recursion
void SudokuSolver::SolveRecursive(size_t const pos) {
	if(pos < Dim * Dim && !IsSolved()){
		if (sudoku[pos / Dim][pos % Dim] == 0) {					//if position is open, try to solve it
			PossibleNumbers possibilities = GetPossibilities(pos);	//get vector of possible numbers

			//try to solve sudoku for every possibility until solution is found
			find_if(possibilities.cbegin(), possibilities.cend(), [&](unsigned char const possibility)
				{ sudoku[pos / Dim][pos % Dim] = possibility; SolveRecursive(pos + 1); if (IsSolved()) { return true; } sudoku[pos / Dim][pos % Dim] = 0; return false; });
		}
		else {						//try to solve for the remaining positions
			SolveRecursive(pos + 1);
		}
	}
}

//returns true if sudoku is solved
bool SudokuSolver::IsSolved() {
	array<unsigned char, Dim> numTimes = { 0 };  //counters for how often number is inside

	//count all encounters of all numbers, if there is a zero, it is not solved
	if (find_if(&sudoku[0][0], &sudoku[0][0] + Dim * Dim, [&](unsigned char num) { if (num == 0) { return true; } numTimes[num - 1]++; return false; })
		!= &sudoku[0][0] + Dim * Dim) {
		return false;
	}

	//return true if all numbers are contained Dim times
	return find_if(numTimes.cbegin(), numTimes.cend(), [](unsigned char count) {return count != Dim; }) == numTimes.cend();
}

//returns vector with all possible numbers for given position
PossibleNumbers SudokuSolver::GetPossibilities(size_t const pos) {
	PossibleNumbers possibilities{};
	bool numberInside[Dim] = { 0 };
	size_t const line = pos / Dim; //get position line
	size_t const column = pos % Dim; //get position column

	for (size_t i = 0; i < Dim; i++) { //check lines and columns
		if (sudoku[line][i] != 0) { //check the line
			numberInside[sudoku[line][i] - 1] = true;
		}
		if (sudoku[i][column] != 0) { //check the column
			numberInside[sudoku[i][column] - 1] = true;
		}
	}

	for (size_t i = line - line % SmallDim; i < (line - line % SmallDim) + SmallDim; i++) { //check the block
		for (size_t j = column - column % SmallDim; j < (column - column % SmallDim) + SmallDim; j++) {
			if (sudoku[i][j] != 0) {
				numberInside[sudoku[i][j] - 1] = true;
			}
		}
	}

	for (size_t i = 0; i < Dim; i++) { //build possibilities vector
		if (!numberInside[i]) {
			possibilities.push_back(i + 1);
		}
	}

	return possibilities;  //return possibilities vector
}

//solves Sudoku and writes result to file
void SudokuSolver::Solve(std::string const& solvedFile) {
	if (!IsSolvable()) {   //print error if sudoku is unsolvable
		cerr << Unsolvable << endl;
	}
	else {  //otherwise, solve and write solution to file
		ofstream writeFile{ solvedFile };  //defina an output filestream

		if (!writeFile.is_open()) {  //check if opening file worked, if not print an error
			cerr << WritingError << endl;
		}
		else {  //otherwise, solve and write to file
			SolveRecursive();
			writeFile << sudoku;
			cout << "Written solution to file " << solvedFile << endl;
		}
	}
}