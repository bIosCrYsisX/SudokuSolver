///////////////////////////////////////////////////////////////////////
// Workfile: SudokuErrors.h
// Author: Christoph Dalpiaz
// Date: 13.07.2020
// Description: error texts for SudokuSolver in Sudoku.cpp
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#ifndef SUDOKUERRORS_H
#define SUDOKUERRORS_H

#include <string>  //include std::string

std::string const ScanningError = "Error scanning Sudoku from file!";
std::string const WritingError = "Error writing solution to file!";
std::string const Unsolvable = "Sudoku is not solvable!";

#endif