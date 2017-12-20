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
	printf("  ");
	for(i = 0; i < board->rows; i++){
		printf("%d ", i);
	}
	printf("\n");
	for(i = 0; i < board->rows; i++){
		printf("%c ", 65+i);
		for(j = 0; j < board->cols; j++){
			printf("%c ", board->board[i][j]);
		}
		printf("\n");
	}
}
int main(){
	
	BOARD* board = initBoard(10,10,1);
	printf("Display board.\n");
	displayBoard(board);

	return 0;
}
