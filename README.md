# Sudoku Game: C
Sudoku game implemented in C language. 

## Rules

Sudoku is played on a grid of 9 x 9 spaces. Within the rows and columns are 9 squares (made up of 3 x 3 spaces). Each row, column and square (9 spaces each) needs to be filled out with the numbers 1-9, without repeating any numbers within the row, column or square. 

## Approach

A random solved sudoku board is generated everytime the game is run. 
The solved puzzle is kept in a template and random spaces from said board are then deleted for the user to fill.
User input values are compared with the ones from the solved template.
User input is also tested for invalidity. Ie. row outside of bounds, value greater than 9.

## Solver

Because of how sudoku works, the logic implemented to solve these puzzles consisted in first filling diagonal 3x3 squares with random integers from 1-9. This is because you only have to test for that specific square, and not for rows and columns. After that, recursion was used to fill in the blank spaces. *This makes the creation of a solved puzzle much faster than if you would fill every space using recursion.
