#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//My approach to create random sudoku puzzles with their solutions consists in filling diagonal 3x3 boxes with random numbers to then fill the remaining spaces using recurssion

time_t t1;

int** solution;

int** sudoku;

int** restart;

char start, go, setter;

//Allocate memory for matrixes using calloc (automatically set the values to 0)

void CallocateMemory() {

    solution = (int**)calloc(9, sizeof(int*));

    for (int i = 0; i < 9; i++){
        solution[i] = (int*)calloc(9, sizeof(int));
    }

    sudoku = (int**)calloc(9, sizeof(int*));

    for (int i = 0; i < 9; i++){
        sudoku[i] = (int*)calloc(9, sizeof(int));
    }

    restart = (int**)calloc(9, sizeof(int*));

    for (int i = 0; i < 9; i++){
        restart[i] = (int*)calloc(9, sizeof(int));
    }

}

//Free memory previously allocated

void FreeMemory(){
    for(int i = 0; i < 9; i++){
        free(solution[i]);
    }
    free(solution);

    for(int i = 0; i < 9; i++){
        free(sudoku[i]);
    }
    free(sudoku);

    for(int i = 0; i < 9; i++){
        free(restart[i]);
    }
    free(restart);
}

//Check if a certain number is present in every 3x3 box

bool CheckDigitInBox(int digit, int row, int column, int** solution) {

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {

            if (solution[row + i][column + j] == digit) {

                return false;
            }
        }
    }

    return true;

}

//Fill a given 3x3 column without repeated numbers

void Fill3x3(int row, int column, int** solution) {

    int digit;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            do {
                digit = (rand() % 9) + 1;
            } while (CheckDigitInBox(digit, row, column, solution) == false);

            solution[row + i][column + j] += digit;
        }
    }

}

//Fill all 3 diagonal 3x3 boxes

void FillDiagonalSquares(int** solution) {

    for (int i = 0; i <= 6; i += 3) {

        Fill3x3(i, i, solution);
    }

}

//Check if digit is present in a given column

bool CheckColumn(int i, int digit, int** solution) {

    for (int j = 0; j < 9; j++) {

        if (solution[i][j] == digit) {

            return false;
        }
    }
    return true;

}

//Check if digit is present in a given row

bool CheckRow(int j, int digit, int** solution) {

    for (int i = 0; i < 9; i++) {

        if (solution[i][j] == digit) {

            return false;

        }
    }
    return true;

}

//Check if a digit can fill a certain space considering boxes, columns and rows

bool CheckIfAvailable(int num, int i, int j, int** solution){

    if (CheckDigitInBox(num, i - i % 3, j - j % 3, solution) && CheckRow(j, num, solution) && CheckColumn(i, num, solution) ){
        return true;
    }
    return false;
}

//Recursively fill remaining spaces from the solution matrix

bool FillBlankSpaces(int** solution){
    int num;

    for (int m = 0; m < 9; m++){

        for(int n = 0; n < 9; n++){

            if (solution[m][n] == 0){

                for(num = 1; num < 10; num++){
                    
                    if(CheckIfAvailable(num, m, n, solution)){
                        solution[m][n] = num;

                        //Function calling itself
            
                        if (FillBlankSpaces(solution)){
                            return true;
                        }
                        else{
                            solution[m][n] = 0;
                        }   
                    }
                }
                return false;
            }
        }
    }           
}

//Check if a given space is 0

bool CheckIfZero(int i, int j, int** solution){
    if(solution[i][j] == 0){
        return true;
    }
    return false;
}

//Make a copy of one matrix to another

void SudokuTemplate(int** copy, int** template){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            copy[i][j] += solution[i][j];
        }
    }
}

//Remove "diff" digits from the sudoku puzzle

void CreatePuzzle(int** sudoku){

    int diff;

    if (setter == 'H'){
        diff = 50;
    } else if (setter == 'N'){
        diff = 30;
    } else if (setter == 'E'){
        diff = 15;
    } else if (setter == 'y'){
        diff = 1;
    }else{
        diff = 30;
    }

    while (diff != 0) {
            
        int i = rand() % 9;
        int j = rand() % 9;
        
        if (!CheckIfZero(i, j, sudoku)) {
            diff--;
            sudoku[i][j] = 0;
        }
    }
}

//Display a given matrix, printing an X for every 0 or available space

void Display(int** solution) {

    printf("\n");
    printf(" 0 | 1  2  3 | 4  5  6 | 7  8  9 |\n");
    printf(" ---------------------------------\n");

    for (int i = 0, k = 1; i < 9; i++, k++) {

        for (int j = 0; j < 9; j++) {

            if (j == 0) {

                printf(" %d |", k);
                if(CheckIfZero(i, j, solution)){
                    printf(" %c ", 'X');
                }else{
                    printf(" %d ", solution[i][j]);
                }

            }
            else if ((j) % 3 == 0) {

                printf("|");
                if(CheckIfZero(i, j, solution)){
                    printf(" %c ", 'X');
                }else{
                    printf(" %d ", solution[i][j]);
                }

            }
            else if (j == 8) {

                if(CheckIfZero(i, j, solution)){
                    printf(" %c ", 'X');
                }else{
                    printf(" %d ", solution[i][j]);
                }
                printf("|");

            }
            else {

                if(CheckIfZero(i, j, solution)){
                    printf(" %c ", 'X');
                }else{
                    printf(" %d ", solution[i][j]);
                }

            }
        }

        printf("\n");

        if ((i + 1) % 3 == 0) {
            printf(" ---------------------------------\n");
        }
    }
}

//Take input from user

void UserChoice(int** matrix){

    int i,j,value;

    printf("Enter Coordinates and Value to input (x y value): ");
    scanf("%i %i %i", &i, &j, &value);

    i--;
    j--;

    if(value > 9 || value <= 0 ){
        printf("\nInvalid value!! \n");

    }else if(i > 8 || i < 0 || j > 8 || j < 0){

        printf("\nInvalid coordinate!! \n");

    }else if(!CheckIfZero(i,j, matrix)){

        printf("\nInput coordinate not available!! \n");

    }else if(!CheckIfAvailable(value,i,j, matrix)){

        printf("\nRemember to check for rows, 3x3 boxes and columns!! \n");

    }else{
        matrix[i][j] += value;
    }

}

//Check if a given matrix has no 0 digits

bool CheckIfSolved(int** matrix){

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(matrix[i][j] == 0){
                return false;
            }
        }
    }
    return true;

}

void Initializer(){

    srand ((unsigned) time (&t1));

    CallocateMemory();

    FillDiagonalSquares(solution); 

    FillBlankSpaces(solution);

    SudokuTemplate(sudoku, solution);

    CreatePuzzle(sudoku);  

    SudokuTemplate(restart, sudoku);


}


int main() {

    printf("\n\nEnter Difficulty (H, N, E): ");

    scanf("%c", &setter);

    printf("Enter S to start: ");

    scanf("%c", &start);

    while(start!='S'){

        scanf("%c", &start);
    }

    Initializer();

    printf("\n\n\n                                       WELCOME TO SUDOKU MASTER\n");
    printf("\n\n\n__________________________________________________________________________________________________________\n\n");
    printf("Sudoku is played on a grid of 9 x 9 spaces. Within the rows and columns are 9 squares (made up of 3 x 3 spaces). \nEach row, column and square (9 spaces each) needs to be filled out with the numbers 1-9, without repeating any\n numbers within the row, column or square. Does it sound complicated? Use this software to practice!!");

    printf("\n\nC to continue / E to exit: ");

    scanf("%c", &go);

    while(go != 'E'){

        scanf("%c", &go);

        if(CheckIfSolved(sudoku)){
            go = 'S';
        }

        switch(go){
        case 'C':

            Display(sudoku);
            UserChoice(sudoku);

            printf("\n\nC to continue / R to restart / G to give up and check solution / E to exit: ");
            break;

        case 'R':

            SudokuTemplate(restart, sudoku);

            printf("\n\n");

            Display(sudoku);

            printf("\n\nC to continue / R to restart / G to give up and check solution / E to exit: ");
            break;

        case 'G':

            printf("\n\n");

            Display(solution);

            FreeMemory();

            Initializer();

            printf("\n\nWant to try a new sudoku puzzle? Enter C to continue / E to exit: ");

            break;

        case 'S':

            printf("\n__________________________________________________________________________________________________________");

            printf("\n\n\n                                  Congratulations!!");

            FreeMemory();

            Initializer();

            printf("\n\n\n\nWant to try a new sudoku puzzle? Enter C to continue / E to exit: ");

            break;

        }
    }
    printf("\n__________________________________________________________________________________________________________");
    printf("\n                                       See you next time!");
    
    return 0;
}

  