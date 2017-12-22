#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct board{
	char **playerBoard;
    char **actualBoard;
	int rows;
	int cols;
	int difficultyLevel;
}BOARD;

BOARD* initBoard(int rows, int cols, int difficultyLevel){
	BOARD* board = malloc(sizeof(BOARD));
	board->rows = rows;
	board->cols = cols;
	board->difficultyLevel = difficultyLevel;
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
            board->actualBoard[i][j] = '.';
		}
	}
	return board;
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

/*
 Function Name: setChar
 Passed: The board in use, the row and column to put the character
 Returns: void
 */

void setChar(BOARD* board, int row, int col, char character){
	if(row > board->rows || row < 1 || col > board->cols || col < 1){ // simple error checking to see if the row or column is out of range
		printf("Row or column is not a valid spot.\n");
	}
	board->playerBoard[row][col] = character;
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
            printf("Enter the number of %s between 1 and 99: ", string);
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
            if(inputNum < 1 || inputNum > 99){
                printf("Enter a %s size between 1 and 99.\n", string);
            }
            else{
                notValid = 0;
            }
        }
    }
    return inputNum;
}

int validBoardPosition(BOARD* board, int row, int col){
    if (row > board->rows ||
        row < 1 ||
        col > board->cols ||
        col < 1) {
        printf("Not a valid position.\nTry again.\n");
    }
}

int main(){
    BOARD* board = initBoard(getBoardCreationInput("rows"), getBoardCreationInput("columns"), getBoardCreationInput("difficulty"));
    displayPlayerBoard(board);
    int row, col;
    scanf("%d %d", &row, &col);
    int notGameOver = 1;
    while (notGameOver == 1) {
        // execute command
    }
	return 0;
}
