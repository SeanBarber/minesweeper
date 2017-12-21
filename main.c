#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct board{
	char **board;
	int rows;
	int cols;
	int difficultyLevel;
}BOARD;

BOARD* initBoard(int rows, int cols, int difficultyLevel){
	BOARD* board = malloc(sizeof(BOARD));
	board->rows = rows;
	board->cols = cols;
	board->difficultyLevel = difficultyLevel;
	board->board = malloc(sizeof(char*)*rows);
	int i, j;
	for(i = 0; i < rows; i++){
		board->board[i] = malloc(sizeof(char)*cols);
	}
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			board->board[i][j] = '.';
		}
	}
	return board;
}

void displayBoard(BOARD* board){
	int i, j;
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
			printf("%c  ", board->board[i][j]);
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
	board->board[row][col] = character;
}

/*
 Function Name: getInput
 Passed: A string that determines which input selection to be run
 Returns: Integer between the specified range depending on the input
*/

int getInput(char* string){
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

int main(){
    int rows, cols, difficultyLevel;
    rows = getInput("rows");
    cols = getInput("columns");
    difficultyLevel = getInput("difficulty");
    BOARD* board = initBoard(rows, cols, difficultyLevel);
    printf("Display board.\n");
    displayBoard(board);
	return 0;
}
