/*
 * This file defines the main function, which serves as the entry point for the
 * ResistCalc application. It delegates execution to the ResistCalcMain function
 * in the ResistCalc namespace.
 */

#include <ResistCalc/ResistCalc.h>

int
main(int argc, char* argv[]) {
  return resist_calc::ResistCalcMain(argc, argv);
}
