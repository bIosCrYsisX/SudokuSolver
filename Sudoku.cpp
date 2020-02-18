///////////////////////////////////////////////////////////////////////
// Workfile: Sudoku.cpp
// Author: Christoph Dalpiaz
// Date: 14.02.2020
// Description: functions for solving a sudoku
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include <iostream> //include IO library
#include "Sudoku.h" //include module header

static bool solved = false; //state variable if sudoku is solved
size_t const minimumNumbers = 17; //minimum number of numbers for solvable sudoku

//------------------------------------Internal functions---------------------------------------

//internal recursive function for solving a sudoku
void SolveSudoku(Sudoku sudoku, size_t const pos = 0);

//saves possible numbers into possibilities array, returns length
size_t GetPossibilities(Sudoku const sudoku, size_t possibilities[], size_t const pos);

//checks if sudoku is solved and maintains solved variable
void IsSolved(Sudoku const sudoku);

//checks if sudoku is solvable
bool IsSolvable(Sudoku const sudoku);

//---------------------------------------------------------------------------------------------

//function for solving a sudoku
void Solve(Sudoku sudoku) {
	if (IsSolvable(sudoku)) {
		SolveSudoku(sudoku);
		solved = false;
	}
	else {
		std::cout << "Sudoku is not solvable!" << std::endl;
	}
}

//internal recursive function for solving a sudoku
void SolveSudoku(Sudoku sudoku, size_t const pos) {
	IsSolved(sudoku); //check if sudoku is already solved
	if (pos < dim * dim && !solved) { //if pos is in range and sudoku not solved, try to solve
		if (sudoku[pos / dim][pos % dim] == 0) { //check if field is empty
			size_t possibilities[dim] = { 0 }; //array for possible numbers
			size_t const len = GetPossibilities(sudoku, possibilities, pos); //get possibilities and length
			size_t i = 0; //loop counter

			while (i < len && !solved) { //try to solve for every possibility
				sudoku[pos / dim][pos % dim] = possibilities[i]; //set number
				SolveSudoku(sudoku, pos + 1); //try to complete solution
				if (!solved) { //if solution was not reached, clear previous steps
					sudoku[pos / dim][pos % dim] = 0;
				}
				i++; //increase loop counter
			}
		}
		else {
			SolveSudoku(sudoku, pos + 1); //try to complete solution
		}
	}
}

//saves possible numbers into possibilities array, returns length
size_t GetPossibilities(Sudoku const sudoku, size_t possibilities[], size_t const pos) {
	bool numberInside[dim] = { 0 };
	size_t const line = pos / dim; //get position line
	size_t const column = pos % dim; //get position column
	size_t len = 0; //length for possibilities array
	
	for (size_t i = 0; i < dim; i++) { //check lines and columns
		if (sudoku[line][i] != 0) { //check the line
			numberInside[sudoku[line][i] - 1] = true;
		}
		if (sudoku[i][column] != 0) { //check the column
			numberInside[sudoku[i][column] - 1] = true;
		}
	}

	for (size_t i = line - line % smallDim; i < (line - line % smallDim) + smallDim; i++) { //check the block
		for (size_t j = column - column % smallDim; j < (column - column % smallDim) + smallDim; j++) {
			if (sudoku[i][j] != 0) {
				numberInside[sudoku[i][j] - 1] = true;
			}
		}
	}

	for (size_t i = 0; i < dim; i++) { //build possibilities array
		if (!numberInside[i]) {
			possibilities[len] = i + 1;
			len++;
		}
	}
	
	return len; //return length of possibilities array
}

//checks if sudoku is solvable
bool IsSolvable(Sudoku const sudoku) {
	size_t numberCount[dim] = { 0 };
	size_t totalCount = 0; //counter for number of numbers
	for (size_t i = 0; i < dim; i++) {
		for (size_t j = 0; j < dim; j++) {
			if (sudoku[i][j] != 0) {  //check every value for zero
				if (sudoku[i][j] > dim) { //all numbers have to be smaller or equal to dim
					return false;
				}
				numberCount[sudoku[i][j] - 1]++;
			}
		}
	}
	for (size_t i = 0; i < dim; i++) {
		totalCount += numberCount[i];
	}
	return totalCount >= minimumNumbers;
}

//checks if sudoku is solved and maintains solved variable
void IsSolved(Sudoku const sudoku) {
	size_t numberCount[dim] = { 0 };
	for (size_t i = 0; i < dim; i++) {
		for (size_t j = 0; j < dim; j++) {
			if (sudoku[i][j] != 0) {  //check every value for zero
				numberCount[sudoku[i][j] - 1]++;
			}
		}
	}
	for (size_t i = 0; i < dim; i++) {
		if (numberCount[i] != dim) {
			return;
		}
	}
	solved = true; //every number dim times inside --> solved
}

//print sudoku to console
void PrintSudoku(Sudoku const sudoku) {
	for (size_t i = 0; i < dim; i++) {
		if (i % smallDim == 0) { //print a new line after every block
			std::cout << std::endl;
		}
		for (size_t j = 0; j < dim; j++) {
			if (j % smallDim == 0) { //make space after every block
				std::cout << "  ";
			}
			//print number, emptyChar for empty space, represented by 0
			sudoku[i][j] == 0 ? std::cout << emptyChar << "   " : std::cout << sudoku[i][j] << "   ";
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << std::endl;
}