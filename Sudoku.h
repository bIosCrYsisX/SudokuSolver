///////////////////////////////////////////////////////////////////////
// Workfile: Sudoku.h
// Author: Christoph Dalpiaz
// Date: 14.02.2020
// Description: function declarations for Sudoku.cpp
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#ifndef SUDOKU_H
#define SUDOKU_H

size_t const dim = 9;  //dimension of sudoku
size_t const smallDim = 3; //dimension of small part fields
char const emptyChar = 'x'; //character printed for empty space, represented by 0

typedef size_t Sudoku[dim][dim];

//function for solving a sudoku
void Solve(Sudoku sudoku);

//print sudoku to console
void PrintSudoku(Sudoku const sudoku);

#endif