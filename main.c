#include <stdio.h>
#include <stdlib.h>

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

void setChar(BOARD* board, int row, int col, char character){
	if(row > board->rows || row < 1 || col > board->cols || col < 1){
		printf("Row or column is not a valid spot.\n");
	}
	board->board[row][col] = character;
}

int main(){
	
	BOARD* board = initBoard(50,50,1);
	printf("Display board.\n");
	displayBoard(board);
	setChar(board, 5,5,'a');
	displayBoard(board);
	return 0;
}
