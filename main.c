#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node{
    char character;
    int row;
    int col;
    struct node *next;
}NODE;

typedef struct list{
    NODE* head;
    NODE* tail;
    int n;
}LIST;

LIST* initList(){
    LIST* list = malloc(sizeof(LIST));
    list->head = NULL;
    list->tail = NULL;
    list->n = 0;
    return list;
}

void insertInList(LIST* list, char character, int row, int col){
    NODE* newNode = malloc(sizeof(NODE));
    newNode->character = character;
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    }
    else{
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->n++;
}

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
    if (board->actualBoard[row][col] == '.') {
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

void setChar(BOARD* board, int row, int col, char character){
    if(validBoardPosition(board, row, col) == 0){
        return;
    }
    if (validBoardPosition(board, row, col) == -1) {
        displayActualBoard(board);
        exit(0);
    }
	board->playerBoard[row][col] = character;
    board->actualBoard[row][col] = character;
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

void setBoard(BOARD* board){
    int mines = ((board->rows)*(board->cols))/board->difficultyLevel;
    if (board->difficultyLevel == 1) {
        mines -= 25;
    }
    int randRow, randCol;
    while (mines != 0) {
        randRow = rand() % board->rows;
        randCol = rand() % board->cols;
        if (board->actualBoard[randRow][randCol] != ' ' &&
            board->actualBoard[randRow][randCol] != 'X') {
            board->actualBoard[randRow][randCol] = 'X';
        }
        mines--;
    }
    //TODO: set area around bombs to certain the number of spaces being touched
}


int main(){
    srand(time(NULL));
    BOARD* board = initBoard(getBoardCreationInput("rows"), getBoardCreationInput("columns"), getBoardCreationInput("difficulty"));
    displayPlayerBoard(board);
    char* inputString;
    char* parsedInput;
    int row = 0, col = 0;
    int notGameOver = 1;
    scanf("%i %i", &row, &col);
    setChar(board, row, col, ' ');
    displayPlayerBoard(board);
    setBoard(board);
    displayActualBoard(board);
    while (notGameOver == 1) {
        scanf("%i %i", &row, &col);
        setChar(board, row, col, ' ');
        displayPlayerBoard(board);
    }
	return 0;
}
