///////////////////////////////////////////////////////////////////////
// Workfile: Sudoku.h
// Author: Christoph Dalpiaz
// Date: 14.02.2020
// Description: test driver for Sudoku.cpp
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include <iostream> //include IO library
#include "Sudoku.h" //include sudoku module

int main()
{
	Sudoku sudokuOne = { 0, 8, 0, 0, 3, 5, 0, 1, 0,
					  0, 0, 5, 0, 0, 0, 9, 0, 4,
					  9, 1, 0, 0, 0, 6, 0, 7, 0,
					  0, 0, 2, 0, 0, 0, 0, 9, 1,
				      8, 0, 9, 0, 0, 0, 6, 0, 3,
					  6, 4, 0, 0, 0, 0, 8, 0, 0,
					  0, 3, 0, 6, 0, 0, 0, 8, 7,
					  7, 0, 8, 0, 0, 0, 4, 0, 0,
					  0, 9, 0, 7, 4, 0, 0, 2, 0 };

	Sudoku sudokuTwo = { 0, 0, 0, 0, 0, 2, 0, 7, 0,
					  0, 5, 7, 0, 9, 0, 0, 0, 0,
					  4, 0, 0, 5, 0, 0, 0, 0, 0,
					  0, 4, 1, 0, 0, 3, 5, 0, 6,
					  0, 0, 0, 4, 8, 0, 9, 0, 0,
					  6, 0, 0, 0, 0, 0, 0, 0, 7,
					  0, 3, 0, 2, 5, 0, 0, 0, 0,
					  1, 0, 0, 0, 0, 4, 8, 0, 3,
					  9, 0, 4, 0, 1, 0, 0, 0, 2 };

	Sudoku sudokuThree = { 8, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 3, 6, 0, 0, 0, 0, 0,
					       0, 7, 0, 0, 9, 0, 2, 0, 0,
					       0, 5, 0, 0, 0, 7, 0, 0, 0,
					       0, 0, 0, 0, 4, 5, 7, 0, 0,
					       0, 0, 0, 1, 0, 0, 0, 3, 0,
					       0, 0, 1, 0, 0, 0, 0, 6, 8,
					       0, 0, 8, 5, 0, 0, 0, 1, 0,
					       0, 9, 0, 0, 0, 0, 4, 0, 0 };
	Solve(sudokuOne);
	PrintSudoku(sudokuOne);
	std::cout << std::endl << std::endl << std::endl;
	Solve(sudokuTwo);
	PrintSudoku(sudokuTwo);
	std::cout << std::endl << std::endl << std::endl;
	Solve(sudokuThree);
	PrintSudoku(sudokuThree);

	return 0;
}