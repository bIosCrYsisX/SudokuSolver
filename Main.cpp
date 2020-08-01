///////////////////////////////////////////////////////////////////////
// Workfile: Main.cpp
// Author: Christoph Dalpiaz
// Date: 13.07.2020
// Description: test driver for Sudoku.cpp
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include "SudokuSolver.h"
#include "SudokuGenerator.h"

using namespace std;

int main()
{
	try {
		//SudokuSolver sudoku{ "F://personalProjects/SudokuSolverV2/mySudoku.txt" };
		//sudoku.Solve("sudoku.txt");

		SudokuGenerator generator{};
		generator.Generate("mySudoku5", 28, true);
	}
	catch (bad_alloc const& ex) {
		cerr << ex.what() << endl;
		return 1;
	}	
	catch (string const& ex) {
		cerr << ex << endl;
		return 1;
	}
	catch (exception const& ex) {
		cerr << ex.what() << endl;
		return 1;
	}	
	catch (...) {
		cerr << "Unhandled exception!" << endl;
		return 1;
	}

	return 0;
}