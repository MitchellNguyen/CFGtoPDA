#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// preprocessor constants
#define REQ_NUM_PARAM 2

/********************************************************
**
** CS 357 - Theory of Computation
** Programming Project
**
** Task:  Convert a CFG to an equivalent PDA
**
** Author:  Mitchell Nguyen
** Version:  4 December 2017
**
********************************************************/

/**
* 'main'
*
* open and read input text-file, print out to terminal and
* write to output.txt, and then close files
*/
int main (int argc, char* argv[]) {

  // create input-file pointers for the given input text-file that
  // contains some CFG, as well as create an output file for printing PDA to
  FILE* inputCFG;
  FILE* outputPDA;

  // if the number of paramaters does not fulfill requirements,
  // print out useful message to terminal, and exit program
  if (argc != REQ_NUM_PARAM) {
    printf("ERROR: Wrong number of inputted parameters.\n");
    printf("USAGE: %s input_*.txt\n", argv[0]);
    printf("  For input_*.txt, please use either \"input_1.txt\", \"input_2.txt\", or \"input_3.txt\".\n");
    printf("\nProgram ending...\n");
    return EXIT_FAILURE;
  }

  // ... if the given parameter is "input_1.txt", then open a
  // "readable" version of the like-data from the text file, "input_1.txt",
  // and open a "writable" version of a file named "output.txt"
  if (strcmp(argv[1], "input_1.txt") == 0) {
    inputCFG = fopen(argv[1], "r");
    printf("Opened input-stream for \"input_1.txt\".\n");

    outputPDA = fopen("output.txt", "w");
    printf("Opened output-stream for \"output.txt\".\n");
  }
  // ... if the given parameter is "input_2.txt", then open a
  // "readable" version of the like-data from the text file, "input_2.txt",
  // and open a "writable" version of a file named "output.txt"
  else if (strcmp(argv[1], "input_2.txt") == 0) {
    inputCFG = fopen(argv[1], "r");
    printf("Opened input-stream for \"input_2.txt\".\n");

    outputPDA = fopen("output.txt", "w");
    printf("Opened output-stream for \"output.txt\".\n");
  }
  // ... if the given parameter is "input_3.txt", then open a
  // "readable" version of the like-data from the text file, "input_3.txt",
  // and open a "writable" version of a file named "output.txt"
  else if (strcmp(argv[1], "input_3.txt") == 0) {
    inputCFG = fopen(argv[1], "r");
    printf("Opened input-stream for \"input_3.txt\".\n");

    outputPDA = fopen("output.txt", "w");
    printf("Opened output-stream for \"output.txt\".\n");
  }
  else {

    // ... if the user does not input either "likes_1.txt" or "likes_2.txt",
    // then print out a useful message to the terminal, and end the program
    printf("ERROR: The second given parameter must be either\n");
    printf("       \"input_1.txt\",\"input_2.txt\", or \"input_3.txt\".\n");
    printf("\nProgram ending...\n");
    return EXIT_FAILURE;
  }

  // if the given input CFG-file is empty, print a useful message
  // to the terminal, and exit out of the program
  if (inputCFG == NULL) {
    printf("The input text file could not be opened.\n");
    printf("\nProgram ending...\n");
    return EXIT_FAILURE;
  }


  // ... if input text-file has data, then begin gathering data
  // in order to build a PDA

  /**
  * Write PDA part #1:
  *     --- write out Q_start, transition to Q_1, and Q_1
  */
  writePDA_1();

  /** *********************************************************************** **/

  /**
  * Write PDA part #2:
  *     --- write out transition from Q_1 to Q_loop
  */

  // begin actually reading the input text-file
  char c;  // represents the current character that is being read

  // read through inputCFG text file character-by-character
  while ((c = fgetc(inputCFG)) != '\n') {

    // only grab the first character from the text file, which
    // is the Start Variable of the given CFG
    writePDA_2_part1();
    printf("%c", c);   // print Start Variable in transition to Q_loop
    writePDA_2_part2();

    // immediately break out of scanning-loop after retrieving start variable
    break;
  }

  // writePDA part #2 complete!!!
  fclose(inputCFG);
  inputCFG = fopen(argv[1], "r");

  /** *********************************************************************** **/

  /**
  * Write PDA part #3:
  *     --- scan for terminals (either 'a' or 'b'),
  *         and use the terminal to print out new rule on
  *         the first petal of Q_loop
  */

  // keeps track of if the characters of the given alphabet
  // need to printed in this self-loop petal
  int terminal_a = 0;
  int terminal_b = 0;

  // read through inputCFG text file character-by-character
  while ((c = fgetc(inputCFG)) != EOF) {

    if (c != '\n') {  // store each line of text separately
      if (c == 'a' && terminal_a == 0) {
        // if terminal-a has not been written down in this petal, then
        // print out rule "a, a -> Ɛ"
        writePDA_3();

        //print out self-loop transition with terminal to "empty"
        printf("%c, %c -> Ɛ", c, c);

        terminal_a = 1;   //terminal_a has already been printed

      } else if (c == 'b' && terminal_b == 0) {
        // if terminal-b has not been written down in this petal, then
        // print out rule "b, b -> Ɛ"
        writePDA_3();

        //print out self-loop transition with terminal to "empty"
        printf("%c, %c -> Ɛ", c, c);

        terminal_b = 1;   //terminal_b has already been printed
      }
    }
  }

  // writePDA part #3 complete!!!
  fclose(inputCFG);
  inputCFG = fopen(argv[1], "r");

  /** *********************************************************************** **/

  /**
  * Write PDA part #4:
  *     --- scan for any rules like A->Ɛ, and use the
  *         given variable A to print out another new rule
  *         on the first petal of Q_loop
  *     --- NOTE: the 'Ɛ' empty-char is actually stored as '3'-character
  *               in ANSI input text-file
  */

  char firstVar;   //stores first variable per-line of text, which is
                   //the variable on the left-hand side of the arrow
  int firstVarStored = 0;   //inidicates whether or not the first variable
                            //has been stored

  // read through inputCFG text file character-by-character
  while ((c = fgetc(inputCFG)) != EOF) {

    if (c != '\n') {  //store each line of text separately

      // store first variable (which will be printed out if we come
      // across a rule like A->Ɛ)
      if (firstVarStored == 0) {
        firstVar = c;
        firstVarStored = 1;
      }

      if (c == '3') {   //'3'-char represents empty character in input file...

          // if we read over a rule like A->Ɛ, then print out new rule
          // on first petal of Q_loop
          writePDA_4();

          //print out rule A->Ɛ as "Ɛ, A -> Ɛ" on self-loop transition
          printf("Ɛ, %c -> Ɛ", firstVar);

      }

    } else {

      // set defaults (to go to next line of text)
      firstVar = '\0';
      firstVarStored = 0;
    }
  }

  // PDA output part #4 complete!!
  fclose(inputCFG);
  inputCFG = fopen(argv[1], "r");

  /** *********************************************************************** **/

  /**
  * Write PDA part #5:
  *     --- scan for any rules like A->B or A->a, which
  *         only have one variable or one terminal on the
  *         right-hand side of the arrow, and create a new
  *         rule on the first petal of Q_loop that represents
  *         the A->B or A->a rule
  *
  * ... and Write PDA part #6
  *     --- simply print out ending portion of the first petal
  *         Q_loop, and prepare to create more complex petals
  *         for rules with more than one variable or terminal
  *         on the right-hand side of the arrow
  */

  // set defaults (to read in first variable on left-hand side of arrow)
  firstVar = '\0';
  firstVarStored = 0;

  // keep track of three consecutive characters in the same line
  char leftChar;   //will be used to see if 'givenChar' is enclosed by '|' or '>'

  char givenChar;  //represents variable or terminal on left-hand side of arrow

  char rightChar;  //will be used to see if 'givenChar' is enclosed by '|'

  // read through inputCFG text file character-by-character
  while ((c = fgetc(inputCFG)) != EOF) {

    if (c != '\n') {   //store each line of text separately

      // store first variable (which will be printed out if we come
      // across a rule like A->B or A->a)
      if (firstVarStored == 0) {
        firstVar = c;
        firstVarStored = 1;
      }

      // store the current character being read in as the right-most character,
      // and then store the 2 most previous characters in consecutive order
      leftChar = givenChar;
      givenChar = rightChar;
      rightChar = c;

      // check to see that the 'givenChar' is an alphabetical letter (upper-case or lower-case),
      // and check to see if single variable or terminal is enclosed by '|' or '>'
      //
      // NOTE: 'givenChar' has to be a VARIABLE or TERMINAL (which are alphabetic letters)
      if ((leftChar == '|' || leftChar == '>') && rightChar == '|' && isalpha(givenChar)) {
        //add new rule to self-looping transition on first petal of Q_loop
        writePDA_5();

        //print out self-loop with replacement to single variable or single terminal
        printf("Ɛ, %c -> %c", firstVar, givenChar);
      }

    }
    //check to see if single variable or single terminal is
    // at the end of the line of text
    else {
      // check if 'givenChar' is an alphabetical letter (upper-case or lower-case),
      // and check to see if single variable or terminal is enclosed by '|' or '\n'
      if ((leftChar == '|' || leftChar == '>') && isalpha(givenChar)) {
        //add new rule to self-looping transition on first petal of Q_loop
        writePDA_5();

        //print out self-loop with replacement to single var or single terminal
        printf("Ɛ, %c -> %c", firstVar, givenChar);
      }

      // at the end of a line of text, reset defaults (to prepare to read
      // more data in new line of text)
      leftChar = '\0';
      givenChar = '\0';
      rightChar = '\0';

      firstVar = '\0';
      firstVarStored = 0;
    }

  }

  // print out ending of first self-loop petal
  writePDA_6();

  // PDA output part #5 and part #6 complete!!
  fclose(inputCFG);
  inputCFG = fopen(argv[1], "r");

  /** *********************************************************************** **/

  /**
  * Write PDA part #7:
  *     --- scan for any OTHER rules that consist of more than one
  *         variable or terminal on the right-hand side of the arrow,
  *         and create petals that consist of multiple transitions and states
  *
  *     --- NOTE: assume that the longest length of consecutive
  *              variables and/or terminals is 3 (for my test-cases)
  *
  * ... and Write PDA part #8:
  *     --- simply print out the ending portion of PDA to terminal
  */

  // reset defaults (to read first variable on left-hand side of arrow)
  firstVar = '\0';
  firstVarStored = 0;

  // store four consecutive characters in the same line, which will keep track
  // of the number of variables and/or terminals there are in a rule
  char farLeftChar = '\0';
  leftChar = '\0';
  givenChar = '\0';
  rightChar = '\0';

  // read through inputCFG text file character-by-character
  while ((c = fgetc(inputCFG)) != EOF) {

    if (c != '\n') {   //store each line of text separately

      // store first variable on left-hand side of arrow
      if (firstVarStored == 0) {
        firstVar = c;
        firstVarStored = 1;
      }

      // store the current character being read in as the right-most character,
      // and then store the 3 most previous characters in consecutive order
      farLeftChar = leftChar;
      leftChar = givenChar;
      givenChar = rightChar;
      rightChar = c;

      // if there are only 2 variables and/or terminals that are written consecutively in same line
      // that are also enclosed by '|' or '>', then print out new petal
      //
      // NOTE: givenChar has to be a VARIABLE or TERMINAL (which are alphabetic letters)
      if ((farLeftChar == '|' || farLeftChar == '>') && rightChar == '|' && isalpha(leftChar) && isalpha(givenChar)) {
        writePDA_7_part1();   //start printing out new petal

        //print out beginning of whole petal on Q_loop
        printf("\n        |             Ɛ, %c -> %c", firstVar, givenChar);

        writePDA_7_part2();   //print transition to "mini"-state

        //print out further transitions on this petal
        printf("\n        |             Ɛ, Ɛ -> %c", leftChar);

        writePDA_7_part3();   //print ending portion of petal
      }

      // if there are 3 variables and/or terminals that are written consecutively in same line
      // that are also enclosed by '|' or '>', then print out new petal
      if (rightChar == '|' && isalpha(leftChar) && isalpha(givenChar) && isalpha(farLeftChar)) {
        writePDA_7_part1();   //start printing out new petal

        //print out beginning of whole petal on Q_loop
        printf("\n        |             Ɛ, %c -> %c", firstVar, givenChar);

        writePDA_7_part2();   //print transition to "mini"-state

        //print out further transitions on this petal
        printf("\n        |             Ɛ, Ɛ -> %c", leftChar);

        writePDA_7_part2();   //print transition to another "mini"-state

        //print out one more transition on this petal
        printf("\n        |             Ɛ, Ɛ -> %c", farLeftChar);

        writePDA_7_part3();   //print ending portion of petal
      }


    } else {

      // if there are only 2 variables and/or terminals that are written consecutively in same line
      // that are also enclosed by '|' (or '>') and '\n', then print out new petal
      if ((farLeftChar == '|' || farLeftChar == '>') && isalpha(leftChar) && isalpha(givenChar)) {
        writePDA_7_part1();   //start printing out new petal

        //print out beginning of whole petal on Q_loop
        printf("\n        |             Ɛ, %c -> %c", firstVar, givenChar);

        writePDA_7_part2();   //print transition to "mini"-state

        //print out further transitions on this petal
        printf("\n        |             Ɛ, Ɛ -> %c", leftChar);

        writePDA_7_part3();    //print ending portion of petal
      }

      // if there are 3 variables and/or terminals that are written consecutively in same line
      // that are also enclosed by '|' (or '>') and '\n', then print out new petal
      if (isalpha(leftChar) && isalpha(givenChar) && isalpha(farLeftChar)) {
        writePDA_7_part1();   //start printing out new petal

        //print out beginning of whole petal on Q_loop
        printf("\n        |             Ɛ, %c -> %c", firstVar, givenChar);

        writePDA_7_part2();   //print transition to "mini"-state

        //print out further transitions on this petal
        printf("\n        |             Ɛ, Ɛ -> %c", leftChar);

        writePDA_7_part2();   //print transition to another "mini"-state

        //print out one more transition on this petal
        printf("\n        |             Ɛ, Ɛ -> %c", farLeftChar);

        writePDA_7_part3();   //print ending portion of petal
      }

      // reset defaults (to gather data from another line of text)
      farLeftChar = '\0';
      leftChar = '\0';
      givenChar = '\0';
      rightChar = '\0';

      firstVar = '\0';
      firstVarStored = 0;
    }
  }

  // simply print out ending portion of PDA to terminal
  writePDA_8();

  // completed WritePda parts #7 and #8 !!!
  fclose(inputCFG);
  inputCFG = fopen(argv[1], "r");

  /** *********************************************************************** **/

  /**
  * 'writeOutputFile'
  *
  * essentially repeats the same functions as this 'main'-method,
  * but it prints the outputPDA to the desired output.txt (as opposed
  * to printing the PDA to the terminal)
  *
  * consists of its own helper-methods that print to output.txt
  * (these helper-methods correlate to the helper methods of the
  * 'main'-method, and are preceded by the phrase "out_" for their method name)
  */

  writeOutputFile(argv[1], inputCFG, outputPDA);

  /** *********************************************************************** **/

  /**
  * program complete!
  * close all used files and gracefully exit out of program
  */
  fclose(inputCFG);
  fclose(outputPDA);

  return EXIT_SUCCESS;

}


/** *********************************************************************** **/
/** *********************************************************************** **/
/** ***** HELPER-METHODS FOR 'MAIN' *************************************** **/
/** *********************************************************************** **/

/**
* 'writePDA_1'
*
* simply write out Q_start, transition to Q_1, and Q_1
*/
int writePDA_1() {

  // print out start-state (Q_start), transition to Q_1, and Q_1
  printf("\n  |\n  |\n  V");
  printf("\n------------\nQ_start    |\n------------");
  printf("\n  |\n  Ɛ, Ɛ -> $");
  printf("\n  |\n  V");
  printf("\n--------\nQ_1    |\n--------");

  return 0;
}

/**
* 'writePDA_2_part1'
*
* print out beginning portion of transition from Q_1 to Q_loop
*/
int writePDA_2_part1() {
  printf("\n  |");
  printf("\n  Ɛ, Ɛ -> ");

  return 0;
}

/**
* 'writePDA_2_part2'
*
* print out beginning portion of Q_loop
*/
int writePDA_2_part2() {
  printf("\n  |\n  V");
  printf("\n---------\nQ_loop  |  ------------");
  printf("\n        |             |");

  return 0;
}

/**
* 'writePDA_3'
*
* print out beginning portion of rule self-loop transition
* for first petal of Q_loop that consists of:
*    "terminal, terminal -> Ɛ"
*/
int writePDA_3() {
  printf("\n        |             ");

  return 0;
}

/**
* 'writePDA_4'
*
* print out beginning portion of rule self-loop transition
* for first petal of Q_loop that consists of:
*    "Ɛ, A -> Ɛ"
*/
int writePDA_4() {
  printf("\n        |             ");

  return 0;
}


/**
* 'writePDA_5'
*
* print out beginning portion of rule self-loop transition
* for first petal of Q_loop that consists of:
*       "Ɛ, variable -> (single)terminal"
*   or  "Ɛ, variable -> (single)variable"
*/
int writePDA_5() {   ///// SELF-LOOPS (((FOR VARIABLE -> SINGLE TERMINAL)))
                        //                 or VAR -> SINGLE VAR
  printf("\n        |             ");

  return 0;
}

/**
* 'writePDA_6'
*
* print ending portion of first self-loop petal on Q_loop
*/
int writePDA_6() {
  printf("\n        |             |");
  printf("\n        |  <-----------");

  return 0;
}


/**
* 'writePDA_7_part1',  'writePDA_7_part2',  'writePDA_7_part3'
*
* print out individual whole petals that consist of "mini"-states
* and more transitions on the petals
* ... these rules that will be printed like this have more than
*     one variables and/or terminals on the right-hand side of the arrow
*/
int writePDA_7_part1() {   //beginning portion of whole petal
  printf("\n        |");
  printf("\n        |  ------------");
  printf("\n        |             |");

  return 0;
}

int writePDA_7_part2() {   //transitions to "mini"-state
  printf("\n        |             |");
  printf("\n        |             V");
  printf("\n        |            [ ]");
  printf("\n        |             |");

  return 0;
}

int writePDA_7_part3() {   //ending portion of whole petal
  printf("\n        |             |");
  printf("\n        |  <-----------");

  return 0;
}

/**
* 'writePDA_8'
*
* write out ending portion of whole-petals, then print transition to
* Q_accept, then finally print out Q_accept
*/
int writePDA_8() {
  printf("\n---------");
  printf("\n  |\n  Ɛ, $ -> Ɛ\n  |\n  V");
  printf("\n---------------\n------------  |");
  printf("\nQ_accept   |  |");
  printf("\n------------  |\n---------------");

  return 0;
}


/** *********************************************************************** **/
/** *********************************************************************** **/
/** *********************************************************************** **/
/** ******* WRITE PDA TO OUTPUT.TXT CODE BELOW **************************** **/
/** *********************************************************************** **/


/**
* 'writeOutputFile'
*
* writes to resulting PDA to output.txt file
*
* NOTE: The following method (and helper printing methods below) are identical
*       to their corresponding methods that are shown above.
*       ... The only changes that were made were to the print-statements,
*           which are fprintf-statements in order to print to output.txt
**/
int writeOutputFile(char filename[300], FILE* inputCFG, FILE* outputPDA) {
  out_writePDA_1(outputPDA);   // write out Q_start

  // begin actually reading the input text file
  char c;  // represents the current character that is being read

  // read through inputCFG text file character-by-character
  while ((c = fgetc(inputCFG)) != '\n') {

    // only grab the first character from the text file, which
    // is the Start Variable of the given CFG
    out_writePDA_2_part1(outputPDA);
    fprintf(outputPDA, "%c", c);   // print Start Variable in transition to Q_loop
    out_writePDA_2_part2(outputPDA);

    // immediately break out of scanning-loop after retrieving start variable
    break;
  }

  // writePDA part #2 complete!!!
  fclose(inputCFG);
  inputCFG = fopen(filename, "r");

  // if the characters of the given alphabet need to printed in this self-loop petal
  int terminal_a = 0;
  int terminal_b = 0;

  // do looping stuff here for WRITE_PDA_3
  while ((c = fgetc(inputCFG)) != EOF) {

    if (c != '\n') {  // store each line of text separately
      if (c == 'a' && terminal_a == 0) {

        out_writePDA_3(outputPDA);

        //print out self-loop transition with terminal to "empty"
        fprintf(outputPDA, "%c, %c -> Ɛ", c, c);

        terminal_a = 1;   //terminal_a has already been printed

      } else if (c == 'b' && terminal_b == 0) {

        out_writePDA_3(outputPDA);

        //print out self-loop transition with terminal to "empty"
        fprintf(outputPDA, "%c, %c -> Ɛ", c, c);

        terminal_b = 1;
      }
    }
  }

  // writePDA part #3 complete!!!
  fclose(inputCFG);
  inputCFG = fopen(filename, "r");

  char firstVar;
  int firstVarStored = 0;

  while ((c = fgetc(inputCFG)) != EOF) {

    if (c != '\n') {  // store each line of text separately

      if (firstVarStored == 0) {
        firstVar = c;
        firstVarStored = 1;
      }

      if (c == '3') {

          out_writePDA_4(outputPDA);

          //print out self-loop transition with terminal to "empty"
          fprintf(outputPDA, "Ɛ, %c -> Ɛ", firstVar);
      }

    } else {
      // set defaults
      firstVar = '\0';
      firstVarStored = 0;
    }
  }

  // PDA output part #4 complete!!
  fclose(inputCFG);
  inputCFG = fopen(filename, "r");

  firstVar = '\0';
  firstVarStored = 0;

  char leftChar;
  char givenChar;
  char rightChar;

  while ((c = fgetc(inputCFG)) != EOF) {

    if (c != '\n') {

      if (firstVarStored == 0) {  // store first variable...
        firstVar = c;
        firstVarStored = 1;
      }

      leftChar = givenChar;
      givenChar = rightChar;
      rightChar = c;

      // givenChar has to be a VARIABLE or TERMINAL (which are alphabetic letters)
      if ((leftChar == '|' || leftChar == '>') && rightChar == '|' && isalpha(givenChar)) {
        out_writePDA_5(outputPDA);

        //print out self-loop with replacement to single var or single terminal
        fprintf(outputPDA, "Ɛ, %c -> %c", firstVar, givenChar);
      }


    } else {

      if ((leftChar == '|' || leftChar == '>') && isalpha(givenChar)) {
        out_writePDA_5(outputPDA);

        //print out self-loop with replacement to single var or single terminal
        fprintf(outputPDA, "Ɛ, %c -> %c", firstVar, givenChar);
      }

      leftChar = '\0';
      givenChar = '\0';
      rightChar = '\0';

      firstVar = '\0';
      firstVarStored = 0;
    }
  }

  out_writePDA_6(outputPDA); //ending of first self-loop petal

  // PDA output part #5/6 complete!!
  fclose(inputCFG);
  inputCFG = fopen(filename, "r");

  firstVar = '\0';
  firstVarStored = 0;

  char farLeftChar = '\0';
  leftChar = '\0';
  givenChar = '\0';
  rightChar = '\0';

  while ((c = fgetc(inputCFG)) != EOF) {

    if (c != '\n') {

      if (firstVarStored == 0) {  // store first variable...
        firstVar = c;
        firstVarStored = 1;
      }

      farLeftChar = leftChar;
      leftChar = givenChar;
      givenChar = rightChar;
      rightChar = c;

      // if there are only 2 variables and/or terminals that are written consecutively in same line
      // (givenChar has to be a VARIABLE or TERMINAL (which are alphabetic letters))
      if ((farLeftChar == '|' || farLeftChar == '>') && rightChar == '|' && isalpha(leftChar) && isalpha(givenChar)) {
        out_writePDA_7_part1(outputPDA);

        //print out beginning of whole petal on Q_loop
        fprintf(outputPDA, "\n        |             Ɛ, %c -> %c", firstVar, givenChar);

        out_writePDA_7_part2(outputPDA);

        //print out further transitions on this petal
        fprintf(outputPDA, "\n        |             Ɛ, Ɛ -> %c", leftChar);

        out_writePDA_7_part3(outputPDA);
      }

      // if there are 3 variables and/or terminals that are written consecutively in same line
      if (rightChar == '|' && isalpha(leftChar) && isalpha(givenChar) && isalpha(farLeftChar)) {
        out_writePDA_7_part1(outputPDA);

        //print out beginning of whole petal on Q_loop
        fprintf(outputPDA, "\n        |             Ɛ, %c -> %c", firstVar, givenChar);

        out_writePDA_7_part2(outputPDA);

        //print out further transitions on this petal
        fprintf(outputPDA, "\n        |             Ɛ, Ɛ -> %c", leftChar);

        out_writePDA_7_part2(outputPDA);

        //print out one more transition on this petal
        fprintf(outputPDA, "\n        |             Ɛ, Ɛ -> %c", farLeftChar);

        out_writePDA_7_part3(outputPDA);
      }


    } else {

      // if there are only 2 variables and/or terminals that are written consecutively in same line
      if ((farLeftChar == '|' || farLeftChar == '>') && isalpha(leftChar) && isalpha(givenChar)) {

        //print out beginning of whole petal on Q_loop
        fprintf(outputPDA, "\n        |             Ɛ, %c -> %c", firstVar, givenChar);

        out_writePDA_7_part2(outputPDA);

        //print out further transitions on this petal
        fprintf(outputPDA, "\n        |             Ɛ, Ɛ -> %c", leftChar);

        out_writePDA_7_part3(outputPDA);
      }

      // if there are 3 variables and/or terminals that are written consecutively in same line
      if (isalpha(leftChar) && isalpha(givenChar) && isalpha(farLeftChar)) {
        out_writePDA_7_part1(outputPDA);

        //print out beginning of whole petal on Q_loop
        fprintf(outputPDA, "\n        |             Ɛ, %c -> %c", firstVar, givenChar);

        out_writePDA_7_part2(outputPDA);

        //print out further transitions on this petal
        fprintf(outputPDA, "\n        |             Ɛ, Ɛ -> %c", leftChar);

        out_writePDA_7_part2(outputPDA);

        //print out one more transition on this petal
        fprintf(outputPDA, "\n        |             Ɛ, Ɛ -> %c", farLeftChar);

        out_writePDA_7_part3(outputPDA);
      }

      farLeftChar = '\0';
      leftChar = '\0';
      givenChar = '\0';
      rightChar = '\0';

      firstVar = '\0';
      firstVarStored = 0;
    }

  }

  out_writePDA_8(outputPDA);

  return 0;
}


/** *********************************************************************** **/
/** *********************************************************************** **/
/** *********************************************************************** **/
/** ******* HELPER-METHODS FOR 'WriteOutputFile' ************************** **/
/** *********************************************************************** **/

int out_writePDA_1(FILE* outputPDA) {

  // print out start-state (Q_start), transition to Q_1, and Q_1
  fprintf(outputPDA, "\n  |\n  |\n  V");
  fprintf(outputPDA, "\n------------\nQ_start    |\n------------");
  fprintf(outputPDA, "\n  |\n  Ɛ, Ɛ -> $");
  fprintf(outputPDA, "\n  |\n  V");
  fprintf(outputPDA, "\n--------\nQ_1    |\n--------");

  return 0;
}

int out_writePDA_2_part1(FILE* outputPDA) {

  // print out transition from Q_1 to Q_loop, and beginning
  // portion of Q_loop state
  fprintf(outputPDA, "\n  |");
  fprintf(outputPDA, "\n  Ɛ, Ɛ -> ");

  return 0;
}

int out_writePDA_2_part2(FILE* outputPDA) {
  // print out rest of transitionand beginning portion of Q_loop
  fprintf(outputPDA, "\n  |\n  V");
  fprintf(outputPDA, "\n---------\nQ_loop  |  ------------");
  fprintf(outputPDA, "\n        |             |");

  return 0;
}


// eventually print out self-loop transition with terminal to "empty"
int out_writePDA_3(FILE* outputPDA) {
  fprintf(outputPDA, "\n        |             ");

  return 0;
}


// eventually print out self-loop transition with variable to "empty"
int out_writePDA_4(FILE* outputPDA) {
  fprintf(outputPDA, "\n        |             ");

  return 0;
}

// eventually print out rules for variable to single variable or single terminal
int out_writePDA_5(FILE* outputPDA) {
  fprintf(outputPDA, "\n        |             ");

  return 0;
}

// print ending portion of self-loop petal
int out_writePDA_6(FILE* outputPDA) {
  fprintf(outputPDA, "\n        |             |");
  fprintf(outputPDA, "\n        |  <-----------");

  return 0;
}

// print out beginning portion of whole petals for the rest of the rules
int out_writePDA_7_part1(FILE* outputPDA) {
  fprintf(outputPDA, "\n        |");
  fprintf(outputPDA, "\n        |  ------------");
  fprintf(outputPDA, "\n        |             |");

  return 0;
}

// print out transitions to "mini"-states
int out_writePDA_7_part2(FILE* outputPDA) {
  fprintf(outputPDA, "\n        |             |");
  fprintf(outputPDA, "\n        |             V");
  fprintf(outputPDA, "\n        |            [ ]");
  fprintf(outputPDA, "\n        |             |");

  return 0;
}

// print out ending portion of whole petals fo rthe rest of the rules
int out_writePDA_7_part3(FILE* outputPDA) {
  fprintf(outputPDA, "\n        |             |");
  fprintf(outputPDA, "\n        |  <-----------");

  return 0;
}

// write out ending portion of whole-petals, then print transition to
// Q_accept, then finally print out Q_accept
int out_writePDA_8(FILE* outputPDA) {
  fprintf(outputPDA, "\n---------");
  fprintf(outputPDA, "\n  |\n  Ɛ, $ -> Ɛ\n  |\n  V");
  fprintf(outputPDA, "\n---------------\n------------  |");
  fprintf(outputPDA, "\nQ_accept   |  |");
  fprintf(outputPDA, "\n------------  |\n---------------");

  return 0;
}
