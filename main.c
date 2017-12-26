#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct board{
	char **playerBoard;
    char **actualBoard;
	int rows;
	int cols;
	int difficultyLevel;
    int mines;
    int squaresUncovered;
}BOARD;

BOARD* initBoard(int rows, int cols, int difficultyLevel){
	BOARD* board = malloc(sizeof(BOARD));
	board->rows = rows;
	board->cols = cols;
	board->difficultyLevel = difficultyLevel;
    board->mines = 0;
	board->playerBoard = malloc(sizeof(char*) * rows);
    board->actualBoard = malloc(sizeof(char*) * rows);
	int i, j;
	for(i = 0; i < rows; i++){
		board->playerBoard[i] = malloc(sizeof(char) * cols);
        board->actualBoard[i] = malloc(sizeof(char*) * cols);
	}
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			board->playerBoard[i][j] = '.';
            board->actualBoard[i][j] = '0';
		}
	}
	return board;
}


// TODO: I am currently thinking of a way to combine these 2 functions by passing a string of which board is wanted. But still do not know. 12-21-2017, Sean Barber.
void displayActualBoard(BOARD* board){
    int i, j;
    printf("Display board.\n");
    printf("   ");
    for(i = 0; i < board->rows; i++){
        printf("%d ", i);
        if(i < 10){
            printf(" ");
        }
    }
    printf("\n");
    for(i = 0; i < board->rows; i++){
        printf("%d ",i);
        if(i < 10){
            printf(" ");
        }
        for(j = 0; j < board->cols; j++){
            printf("%c  ", board->actualBoard[i][j]);
        }
        printf("\n");
    }
}

void displayPlayerBoard(BOARD* board){
	int i, j;
    printf("Display board.\n");
	printf("   ");
	for(i = 0; i < board->rows; i++){
		printf("%d ", i);
		if(i < 10){
			printf(" ");
		}
	}
	printf("\n");
	for(i = 0; i < board->rows; i++){
		printf("%d ",i);
		if(i < 10){
			printf(" ");
		}
		for(j = 0; j < board->cols; j++){
			printf("%c  ", board->playerBoard[i][j]);
		}
		printf("\n");
	}
}

int validBoardPosition(BOARD* board, int row, int col){
    if (row > board->rows - 1||
        row < 0 ||
        col > board->cols - 1||
        col < 0) {
        printf("Not a valid position.\nTry again.\n");
        return 0;
    }
    if (board->actualBoard[row][col] == '0' ||
        board->actualBoard[row][col] == '1' ||
        board->actualBoard[row][col] == '2' ||
        board->actualBoard[row][col] == '3' ||
        board->actualBoard[row][col] == '4' ||
        board->actualBoard[row][col] == '5' ||
        board->actualBoard[row][col] == '6' ||
        board->actualBoard[row][col] == '7' ||
        board->actualBoard[row][col] == '8') {
        return 1;
    }
    else if (board->actualBoard[row][col] == 'X'){
        return -1;
    }
    else{
        return 0;
    }
}

/*
 Function Name: setChar
 Passed: The board in use, the row and column to put the character
 Returns: void
 */

void setChar(BOARD* board, int row, int col, char character, int characterExists){
    if(validBoardPosition(board, row, col) == 0){
        return;
    }
    if (validBoardPosition(board, row, col) == -1) {
        printf("You lost!\n");
        displayActualBoard(board);
        exit(0);
    }
    if (characterExists == 0) {
        board->playerBoard[row][col] = board->actualBoard[row][col];
    }
    else{
        board->playerBoard[row][col] = character;
        board->actualBoard[row][col] = character;
    }
    board->squaresUncovered++;
}

/*
 Function Name: getInput
 Passed: A string that determines which input selection to be run
 Returns: Integer between the specified range depending on the input
*/

int getBoardCreationInput(char* string){
    char inputString[128];
    int notValid = 1;
    int inputNum = 0;
    while(notValid){
        if (strcmp(string, "difficulty") == 0) { // Combining getting input required me to do this. Otherwise I have would have 2 nearly identitcal functions
            printf("Enter a level of difficulty between 1 and 10: ");
        }
        else{
            printf("Enter the number of %s between 10 and 99: ", string);
        }
        scanf("%s", inputString);
        inputNum = atoi(inputString);
        if (strcmp(string, "difficulty") == 0) {
            if(inputNum < 1 || inputNum > 10){
                printf("Enter a difficulty between 1 and 10.\n");
            }
            else{
                notValid = 0;
            }
        }
        else{
            if(inputNum < 10 || inputNum > 99){
                printf("Enter a %s size between 10 and 99.\n", string);
            }
            else{
                notValid = 0;
            }
        }
    }
    return inputNum;
}

void setBoard(BOARD* board, int row, int col){
    int mines = ((board->rows)*(board->cols))/board->difficultyLevel;
    if (board->difficultyLevel == 1) {
        mines -= 25;
    }
    board->mines = mines;
    int randRow, randCol;
    printf("Total mines = %d\n", mines);
    while (mines != 0) {
        randRow = rand() % board->rows;
        randCol = rand() % board->cols;
        if (randRow == row ||
            randCol == col) {
            continue;
        }
        if (board->actualBoard[randRow][randCol] == '0') {
            board->actualBoard[randRow][randCol] = 'X';
            if (randRow - 1 >= 0 && randCol - 1 >= 0) {
                if (board->actualBoard[randRow-1][randCol-1] != 'X' &&
                    board->actualBoard[randRow-1][randCol-1] != ' ') {
                    board->actualBoard[randRow-1][randCol-1]++;
                }
            }
            if (randRow - 1 >= 0) {
                if (board->actualBoard[randRow-1][randCol] != 'X' &&
                    board->actualBoard[randRow-1][randCol] != ' ') {
                    board->actualBoard[randRow-1][randCol]++;
                }
            }
            if (randCol - 1 >= 0) {
                if (board->actualBoard[randRow][randCol-1] != 'X' &&
                    board->actualBoard[randRow][randCol-1] != ' ') {
                    board->actualBoard[randRow][randCol-1]++;
                }
            }
            if (randRow + 1 < board->rows && randCol + 1 < board->cols) {
                if (board->actualBoard[randRow+1][randCol+1] != 'X' &&
                    board->actualBoard[randRow+1][randCol+1] != ' ') {
                    board->actualBoard[randRow+1][randCol+1]++;
                }
            }
            if (randRow + 1 < board->rows) {
                if (board->actualBoard[randRow+1][randCol] != 'X' &&
                    board->actualBoard[randRow+1][randCol] != ' ') {
                    board->actualBoard[randRow+1][randCol]++;
                }
            }
            if (randCol + 1 < board->cols) {
                if (board->actualBoard[randRow][randCol+1] != 'X' &&
                    board->actualBoard[randRow][randCol+1] != ' ') {
                    board->actualBoard[randRow][randCol+1]++;
                }
            }
            if (randRow - 1 >= 0 && randCol + 1 < board->cols) {
                if (board->actualBoard[randRow-1][randCol+1] != 'X' &&
                    board->actualBoard[randRow-1][randCol+1] != ' ') {
                    board->actualBoard[randRow-1][randCol+1]++;
                }
            }
            if (randRow + 1 < board->rows && randCol - 1 >= 0) {
                if (board->actualBoard[randRow+1][randCol-1] != 'X' &&
                    board->actualBoard[randRow+1][randCol-1] != ' ') {
                    board->actualBoard[randRow+1][randCol-1]++;
                }
            }
            printf("Row = %d\n", randRow);
            printf("Col = %d\n", randCol);
        mines--;
        }
    }
}

void checkWin(BOARD* board){
    int totalSquares = (board->rows * board->cols) - board->mines;
    if (board->squaresUncovered == totalSquares) {
        printf("You win!\n");
        displayPlayerBoard(board);
        displayActualBoard(board);
        exit(0);
    }
}

int main(){
    srand(time(0));
    BOARD* board = initBoard(getBoardCreationInput("rows"), getBoardCreationInput("columns"), getBoardCreationInput("difficulty"));
    displayPlayerBoard(board);
    char inputString[10];
    char *parsedInput;
    int row = 0, col = 0;
    int notGameOver = 1;
    scanf("%i %i", &row, &col);
    setBoard(board, row, col);
    setChar(board, row, col, ' ', 0);
    displayPlayerBoard(board);
    while (notGameOver == 1) {
        scanf("%i %i", &row, &col);
        setChar(board, row, col, ' ', 0);
        checkWin(board);
        displayPlayerBoard(board);
    }
	return 0;
}
