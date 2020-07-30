///////////////////////////////////////////////////////////////////////
// Workfile: Main.cpp
// Author: Christoph Dalpiaz
// Date: 13.07.2020
// Description: test driver for Sudoku.cpp
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include "Sudoku.h"

int main()
{
	SudokuSolver sudoku{ "F://personalProjects/SudokuSolverV2/Debug/sudoku.txt" };

	sudoku.Solve("F://solved.txt");

	return 0;
}